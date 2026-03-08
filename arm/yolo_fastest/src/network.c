#include <stdio.h>
#include <time.h>
// #include <assert.h>
#include "network.h"
#include "image.h"
#include "data.h"
#include "utils.h"
#include "blas.h"
#include "parser.h"
#include "data.h"

#include "convolutional_layer.h"
#include "yolo_layer.h"
#include "route_layer.h"
#include "upsample_layer.h"
#include "shortcut_layer.h"


load_args get_base_args(network *net)
{
    load_args args = {0};
    args.w = net->w;
    args.h = net->h;
    args.size = net->w;

    args.min = net->min_crop;
    args.max = net->max_crop;
    args.angle = net->angle;
    args.aspect = net->aspect;
    args.exposure = net->exposure;
    args.center = net->center;
    args.saturation = net->saturation;
    args.hue = net->hue;
    return args;
}

//
network *load_network(char *cfg, char *weights, int clear)
{
    network *net = parse_network_cfg(cfg);
    if(weights && weights[0] != 0){
        load_weights(net, weights);
    }
    if(clear) (*net->seen) = 0;
    return net;
}



char *get_layer_string(LAYER_TYPE a)
{
    switch(a){
        case CONVOLUTIONAL:
            return "convolutional";
        case ACTIVE:
            return "activation";
        case LOCAL:
            return "local";
        case DECONVOLUTIONAL:
            return "deconvolutional";
        case CONNECTED:
            return "connected";
        case RNN:
            return "rnn";
        case GRU:
            return "gru";
        case LSTM:
	    return "lstm";
        case CRNN:
            return "crnn";
        case MAXPOOL:
            return "maxpool";
        case REORG:
            return "reorg";
        case AVGPOOL:
            return "avgpool";
        case SOFTMAX:
            return "softmax";
        case DETECTION:
            return "detection";
        case REGION:
            return "region";
        case YOLO:
            return "yolo";
        case DROPOUT:
            return "dropout";
        case CROP:
            return "crop";
        case COST:
            return "cost";
        case ROUTE:
            return "route";
        case SHORTCUT:
            return "shortcut";
        case NORMALIZATION:
            return "normalization";
        case BATCHNORM:
            return "batchnorm";
        default:
            break;
    }
    return "none";
}

//
network *make_network(int n)
{
    network *net = calloc(1, sizeof(network));
    net->n = n;
    net->layers = calloc(net->n, sizeof(layer));
    net->seen = calloc(1, sizeof(size_t));
    net->t    = calloc(1, sizeof(int));
    net->cost = calloc(1, sizeof(float));
    return net;
}

void forward_network(network *netp)
{
    network net = *netp;
    int i;
    for(i = 0; i < net.n; ++i){
        net.index = i;
        layer l = net.layers[i];
        if(l.delta){
            fill_cpu(l.outputs * l.batch, 0, l.delta, 1);
        }
        

		printf("Net %d (%s) forwarding...",net.index,get_layer_string(l.type));
	
        l.forward(l, net);
        net.input = l.output;

        printf("\tDone.\n");
        
        
        if(l.truth) {
            net.truth = l.output;
        }
    }
    calc_network_cost(netp);
}



void calc_network_cost(network *netp)
{
    network net = *netp;
    int i;
    float sum = 0;
    int count = 0;
    for(i = 0; i < net.n; ++i){
        if(net.layers[i].cost){
            sum += net.layers[i].cost[0];
            ++count;
        }
    }
    *net.cost = sum/count;
}

int get_predicted_class_network(network *net)
{
    return max_index(net->output, net->outputs);
}

void backward_network(network *netp)
{
    return;
}


float train_network(network *net, data d)
{
    return 0;
}

void set_temp_network(network *net, float t)
{
    int i;
    for(i = 0; i < net->n; ++i){
        net->layers[i].temperature = t;
    }
}


void set_batch_network(network *net, int b)
{
    net->batch = b;
    int i;
    for(i = 0; i < net->n; ++i){
        net->layers[i].batch = b;

    }
}


layer get_network_detection_layer(network *net)
{
    int i;
    for(i = 0; i < net->n; ++i){
        if(net->layers[i].type == DETECTION){
            return net->layers[i];
        }
    }
    printf("Detection layer not found!!\n");
    layer l = {0};
    return l;
}
/*
image get_network_image_layer(network *net, int i)
{
    layer l = net->layers[i];
    if (l.out_w && l.out_h && l.out_c){
        return float_to_image(l.out_w, l.out_h, l.out_c, l.output);
    }
    image def = {0};
    return def;
}

image get_network_image(network *net)
{
    int i;
    for(i = net->n-1; i >= 0; --i){
        image m = get_network_image_layer(net, i);
        if(m.h != 0) return m;
    }
    image def = {0};
    return def;
}

void visualize_network(network *net)
{
    image *prev = 0;
    int i;
    char buff[256];
    for(i = 0; i < net->n; ++i){
        sprintf(buff, "Layer %d", i);
        layer l = net->layers[i];
        if(l.type == CONVOLUTIONAL){
            prev = visualize_convolutional_layer(l, buff, prev);
        }
    } 
}
*/
void top_predictions(network *net, int k, int *index)
{
    top_k(net->output, net->outputs, k, index);
}


float *network_predict(network *net, float *input)
{
    network orig = *net;
    net->input = input;
    net->truth = 0;
    net->train = 0;
    net->delta = 0;
    forward_network(net);
    float *out = net->output;
    *net = orig;
    return out;
}

int num_detections(network *net, float thresh)
{
    int i;
    int s = 0;
    for(i = 0; i < net->n; ++i){
        layer l = net->layers[i];
        if(l.type == YOLO){
            s += yolo_num_detections(l, thresh);
        }
        if(l.type == DETECTION || l.type == REGION){
            s += l.w*l.h*l.n;
        }
    }
    return s;
}

detection *make_network_boxes(network *net, float thresh, int *num)
{
    layer l = net->layers[net->n - 1];
    int i;
    int nboxes = num_detections(net, thresh);
    if(num) *num = nboxes;
    detection *dets = calloc(nboxes, sizeof(detection));
    for(i = 0; i < nboxes; ++i){
        dets[i].prob = calloc(l.classes, sizeof(float));
        if(l.coords > 4){
            dets[i].mask = calloc(l.coords-4, sizeof(float));
        }
    }
    return dets;
}

void fill_network_boxes(network *net, int w, int h, float thresh, float hier, int *map, int relative, detection *dets)
{
    int j;
    for(j = 0; j < net->n; ++j){
        layer l = net->layers[j];
        if(l.type == YOLO){
            int count = get_yolo_detections(l, w, h, net->w, net->h, thresh, map, relative, dets);
            dets += count;
        }
    }
}

detection *get_network_boxes(network *net, int w, int h, float thresh, float hier, int *map, int relative, int *num)
{
    detection *dets = make_network_boxes(net, thresh, num);
    fill_network_boxes(net, w, h, thresh, hier, map, relative, dets);
    return dets;
}

void free_detections(detection *dets, int n)
{
    int i;
    for(i = 0; i < n; ++i){
        free(dets[i].prob);
        if(dets[i].mask) free(dets[i].mask);
    }
    free(dets);
}

layer get_network_output_layer(network *net)
{
    int i;
    for(i = net->n - 1; i >= 0; --i){
        if(net->layers[i].type != COST) break;
    }
    return net->layers[i];
}


// float *network_predict_image(network *net, image im)
// {
//     image imr = letterbox_image(im, net->w, net->h);
//     set_batch_network(net, 1);
//     float *p = network_predict(net, imr.data);
//     free_image(imr);
//     return p;
// }

int network_width(network *net){return net->w;}
int network_height(network *net){return net->h;}

void free_network(network *net)
{
    int i;
    for(i = 0; i < net->n; ++i){
        free_layer(net->layers[i]);
    }
    free(net->layers);
    if(net->input) free(net->input);
    if(net->truth) free(net->truth);

    if(net->workspace) free(net->workspace);
    if(net->seen) free(net->seen);
    if(net->t) free(net->t);
    if(net->cost) free(net->cost);
    if(net->policy == STEPS){
        if(net->steps) free(net->steps);
        if(net->scales) free(net->scales);
    }

    free(net);
}


layer network_output_layer(network *net)
{
    int i;
    for(i = net->n - 1; i >= 0; --i){
        if(net->layers[i].type != COST) break;
    }
    return net->layers[i];
}

int network_inputs(network *net)
{
    return net->layers[0].inputs;
}

int network_outputs(network *net)
{
    return network_output_layer(net).outputs;
}

float *network_output(network *net)
{
    return network_output_layer(net).output;
}



// matrix network_predict_data_multi(network *net, data test, int n)
// {
//     int i,j,b,m;
//     int k = net->outputs;
//     matrix pred = make_matrix(test.X.rows, k);
//     float *X = calloc(net->batch*test.X.rows, sizeof(float));
//     for(i = 0; i < test.X.rows; i += net->batch){
//         for(b = 0; b < net->batch; ++b){
//             if(i+b == test.X.rows) break;
//             memcpy(X+b*test.X.cols, test.X.vals[i+b], test.X.cols*sizeof(float));
//         }
//         for(m = 0; m < n; ++m){
//             float *out = network_predict(net, X);
//             for(b = 0; b < net->batch; ++b){
//                 if(i+b == test.X.rows) break;
//                 for(j = 0; j < k; ++j){
//                     pred.vals[i+b][j] += out[j+b*k]/n;
//                 }
//             }
//         }
//     }
//     free(X);
//     return pred;   
// }

// matrix network_predict_data(network *net, data test)
// {
//     int i,j,b;
//     int k = net->outputs;
//     matrix pred = make_matrix(test.X.rows, k);
//     float *X = calloc(net->batch*test.X.cols, sizeof(float));
//     for(i = 0; i < test.X.rows; i += net->batch){
//         for(b = 0; b < net->batch; ++b){
//             if(i+b == test.X.rows) break;
//             memcpy(X+b*test.X.cols, test.X.vals[i+b], test.X.cols*sizeof(float));
//         }
//         float *out = network_predict(net, X);
//         for(b = 0; b < net->batch; ++b){
//             if(i+b == test.X.rows) break;
//             for(j = 0; j < k; ++j){
//                 pred.vals[i+b][j] = out[j+b*k];
//             }
//         }
//     }
//     free(X);
//     return pred;   
// }

// float network_accuracy(network *net, data d)
// {
//     matrix guess = network_predict_data(net, d);
//     float acc = matrix_topk_accuracy(d.y, guess,1);
//     free_matrix(guess);
//     return acc;
// }

// float *network_accuracies(network *net, data d, int n)
// {
//     static float acc[2];
//     matrix guess = network_predict_data(net, d);
//     acc[0] = matrix_topk_accuracy(d.y, guess, 1);
//     acc[1] = matrix_topk_accuracy(d.y, guess, n);
//     free_matrix(guess);
//     return acc;
// }

//


// float network_accuracy_multi(network *net, data d, int n)
// {
//     matrix guess = network_predict_data_multi(net, d, n);
//     float acc = matrix_topk_accuracy(d.y, guess,1);
//     free_matrix(guess);
//     return acc;
// }



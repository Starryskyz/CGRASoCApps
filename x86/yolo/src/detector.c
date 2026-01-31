#include "darknet.h"

void test_detector(char *name_list, char *cfgfile, char *weightfile, char *labelbin, char *filename, float thresh, float hier_thresh, char *outfile, int fullscreen)
{
    // list *options = read_data_cfg(datacfg);
    // char *name_list = "data/coco.names";
    char **names = get_labels(name_list);
    // image **alphabet = load_alphabet();
    image *alphabet = load_alphabet2(labelbin);
    void draw_detections2(image im, detection *dets, int num, float thresh, char **names, image *alphabet, int classes);
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    srand(2222222);
    
    char buff[256];
    char *input = buff;
    float nms=.45;
    while(1){
        printf("Starting Yolo test: %s\n",filename);
        
        strncpy(input, filename, 256);
        
        image im = load_image_color(input,0,0);
        image sized = letterbox_image(im, net->w, net->h);
        layer l = net->layers[net->n-1];


        float *X = sized.data;
        
        network_predict(net, X);
        
        int nboxes = 0;
        detection *dets = get_network_boxes(net, im.w, im.h, thresh, hier_thresh, 0, 1, &nboxes);
        printf("step1\n");
        if (nms) do_nms_sort(dets, nboxes, l.classes, nms);
        printf("step2\n");
        // draw_detections(im, dets, nboxes, thresh, names, alphabet, l.classes);
        draw_detections2(im, dets, nboxes, thresh, names, alphabet, l.classes);
        // draw_detections(im, dets, nboxes, thresh, names, NULL, l.classes);
        printf("step3\n");
        free_detections(dets, nboxes);
        printf("step4\n");
        
        save_image(im, "predictions");
        
        printf("step5\n");
        free_image(im);
        free_image(sized);
        printf("step6\n");
        if (filename) break;
    }
}

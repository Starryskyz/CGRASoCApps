#include "dropout_layer.h"
#include "blas.h"
#include <stdio.h>
#include <stdlib.h>

dropout_layer make_dropout_layer(int batch, int w, int h, int c)
{
    dropout_layer l = {0};
    l.type = DROPOUT;
    l.batch = batch;
    l.w = w;
    l.h = h;
    l.c = c;
    l.out_w = w;
    l.out_h = h;
    l.out_c = c;
    l.outputs = w * h * c;
    l.inputs = l.outputs;
    l.output = calloc(l.outputs * batch, sizeof(float));
    l.delta = calloc(l.outputs * batch, sizeof(float));
    l.forward = forward_dropout_layer;
    l.backward = 0;
    printf("dropout       %4d x%4d x%4d   ->  %4d x%4d x%4d\n", w, h, c, l.out_w, l.out_h, l.out_c);
    return l;
}

void forward_dropout_layer(const dropout_layer l, network net)
{
    /* Inference: pass-through (copy input to output) */
    copy_cpu(l.outputs * l.batch, net.input, 1, l.output, 1);
}

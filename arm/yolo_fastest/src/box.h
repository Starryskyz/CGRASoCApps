#ifndef BOX_H
#define BOX_H
#include "darknet.h"

typedef struct{
    float dx, dy, dw, dh;
} dbox;

// float box_rmse(box a, box b);
// dbox diou(box a, box b);
// box decode_box(box b, box anchor);
// box encode_box(box b, box anchor);
typedef struct {
    float left, right, top, bot;
} boxabs;

float box_diou(box a, box b);
float box_diounms(box a, box b, float beta1);
void diounms_sort(detection *dets, int total, int classes, float thresh, int nms_kind, float beta1);

#endif

#include "darknet.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

extern void test_detector(char *name_list, char *cfgfile, char *weightfile, char *labelbin, char *filename, float thresh, float hier_thresh, char *outfile, int fullscreen);




int main()
{
    
        float thresh = 0.5;
        char *filename = "data/cat.jpg";
        char *name_list = "data/coco.names";
        char *outfile = 0;
        int fullscreen = 0;
        test_detector(name_list, "cfg/yolov3-tiny.cfg", "cfg/yolov3-tiny.weights", "cfg/labels.bin", filename, thresh, .5, outfile, fullscreen);
        

    return 0;
}


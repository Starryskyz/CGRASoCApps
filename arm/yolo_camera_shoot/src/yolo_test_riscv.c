#include "darknet.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "ff.h"

//extern void test_detector(char *name_list, char *cfgfile, char *weightfile, char *labelbin, char *pic, float thresh, float hier_thresh, char *outfile, int fullscreen);
//
//
//static FATFS fatfs;
//static FIL fil;
//
//int main()
//{
//    FRESULT rc;
//    rc = f_mount(&fatfs, "1:/", 0);
//    if (rc != FR_OK){
//    	return 0 ;
//    }
//        float thresh = 0.5;
//        char *filename = "1:/dog.bin";
//        char *name_list = "data/coco.names";
////        char *outfile = 0;
//        int fullscreen = 0;
//        test_detector("1:/cona", "1:/v3t.cfg", "1:/v3t.wgt", "1:/labels.bin", filename, thresh, .5, "1:/p.bin", fullscreen);
//
//    return 0;
//}
//

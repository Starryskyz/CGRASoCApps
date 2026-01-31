#include "data.h"
#include "utils.h"
#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ff.h"


list *get_paths(char *filename)
{
    char *path;

    FRESULT res;
    FIL file;
    unsigned int br;
    res = f_open(&file, filename, FA_OPEN_EXISTING | FA_READ);
    if(res != FR_OK){
    	xil_printf("error:%s f_open Failed!\r\n", filename) ;
    	//return ;
    }
    xil_printf("111 found\r\n");

//    FILE *file = fopen(filename, "r");
//    if(!file) printf("Could not open labels file: %s\n", filename);
    list *lines = make_list();
    while((path=fgetl(&file))){
        list_insert(lines, path);
    }
    f_close(&file);
//    fclose(file);
    return lines;
}



//list *get_paths(char *filename)
//{
//    char *path;
//    FILE *file = fopen(filename, "r");
//    if(!file) printf("Could not open labels file: %s\n", filename);
//    list *lines = make_list();
//    while((path=fgetl(file))){
//        list_insert(lines, path);
//    }
//    fclose(file);
//    return lines;
//}


char **get_labels(char *filename)
{
    list *plist = get_paths(filename);
    char **labels = (char **)list_to_array(plist);
    free_list(plist);
    return labels;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <unistd.h>
#include <float.h>
#include <limits.h>



#include "utils.h"
#include "ff.h"



int *read_map(char *filename)
{
    int n = 0;
    int *map = 0;
    char *str;

    FRESULT res;
    FIL file;
    unsigned int br;
    res = f_open(&file, filename, FA_OPEN_EXISTING | FA_READ);
    if(res != FR_OK){
    	xil_printf("error: f_open Failed!\r\n") ;
    	//return ;
    }

//    FILE *file = fopen(filename, "r");
//    if(!file) file_error(filename);
    while((str=fgetl(&file))){
        ++n;
        map = realloc(map, n*sizeof(int));
        map[n-1] = atoi(str);
        free(str);////
    }
    f_close(&file);
    return map;
}


// void del_arg(int argc, char **argv, int index)
// {
//     int i;
//     for(i = index; i < argc-1; ++i) argv[i] = argv[i+1];
//     argv[i] = 0;
// }

// int find_arg(int argc, char* argv[], char *arg)
// {
//     int i;
//     for(i = 0; i < argc; ++i) {
//         if(!argv[i]) continue;
//         if(0==strcmp(argv[i], arg)) {
//             del_arg(argc, argv, i);
//             return 1;
//         }
//     }
//     return 0;
// }


int alphanum_to_int(char c)
{
    return (c < 58) ? c - 48 : c-87;
}
char int_to_alphanum(int i)
{
    if (i == 36) return '.';
    return (i < 10) ? i + 48 : i + 87;
}



void top_k(float *a, int n, int k, int *index)
{
    int i,j;
    for(j = 0; j < k; ++j) index[j] = -1;
    for(i = 0; i < n; ++i){
        int curr = i;
        for(j = 0; j < k; ++j){
            if((index[j] < 0) || a[curr] > a[index[j]]){
                int swap = curr;
                curr = index[j];
                index[j] = swap;
            }
        }
    }
}

void error(const char *s)
{
    printf("Error: %s\n", s);
    // assert(0);
    // exit(-1);
}

// unsigned char *read_file(char *filename)
// {
//     FILE *fp = fopen(filename, "rb");
//     size_t size;

//     fseek(fp, 0, SEEK_END); 
//     size = ftell(fp);
//     fseek(fp, 0, SEEK_SET); 

//     unsigned char *text = calloc(size+1, sizeof(char));
//     fread(text, 1, size, fp);
//     fclose(fp);
//     return text;
// }

void malloc_error()
{
    printf("Malloc error\n");
    // exit(-1);
}

void file_error(char *s)
{
    printf("Couldn't open file: %s\n", s);
    // exit(0);
}

list *split_str(char *s, char delim)
{
    size_t i;
    size_t len = strlen(s);
    list *l = make_list();
    list_insert(l, s);
    for(i = 0; i < len; ++i){
        if(s[i] == delim){
            s[i] = '\0';
            list_insert(l, &(s[i+1]));
        }
    }
    return l;
}

void strip(char *s)
{
    size_t i;
    size_t len = strlen(s);
    size_t offset = 0;
    for(i = 0; i < len; ++i){
        char c = s[i];
        if(c==' '||c=='\t'||c=='\n') ++offset;
        else s[i-offset] = c;
    }
    s[len-offset] = '\0';
}

// void strip_char(char *s, char bad)
// {
//     size_t i;
//     size_t len = strlen(s);
//     size_t offset = 0;
//     for(i = 0; i < len; ++i){
//         char c = s[i];
//         if(c==bad) ++offset;
//         else s[i-offset] = c;
//     }
//     s[len-offset] = '\0';
// }

// void free_ptrs(void **ptrs, int n)
// {
//     int i;
//     for(i = 0; i < n; ++i) free(ptrs[i]);
//     free(ptrs);
// }

char *fgetl(FIL *fp){
    if(f_eof(fp))
    	return 0;
    size_t size = 512;
    char *line = malloc(size*sizeof(char));

    unsigned int br;
    FRESULT res;
    f_gets(line, size, fp);
//    if(res != FR_OK){
//    	free(line);
//    	return 0;
//    }

//    if(!fgets(line, size, fp)){
//        free(line);
//        return 0;
//    }

    size_t curr = strlen(line);

    while((line[curr-1] != '\n') && !f_eof(fp)){
        if(curr == size-1){
            size *= 2;
            line = realloc(line, size*sizeof(char));
            if(!line) {
                printf("%ld\n", size);
                malloc_error();
            }
        }
        size_t readsize = size-curr;
        if(readsize > INT_MAX) readsize = INT_MAX-1;
        f_gets(&line[curr], readsize, fp);
        curr = strlen(line);
    }
    if(line[curr-1] == '\n') line[curr-1] = '\0';

    return line;
}


//char *fgetl(FILE *fp)
//{
//    if(feof(fp)) return 0;
//    size_t size = 512;
//    char *line = malloc(size*sizeof(char));
//    if(!fgets(line, size, fp)){
//        free(line);
//        return 0;
//    }
//
//    size_t curr = strlen(line);
//
//    while((line[curr-1] != '\n') && !feof(fp)){
//        if(curr == size-1){
//            size *= 2;
//            line = realloc(line, size*sizeof(char));
//            if(!line) {
//                printf("%ld\n", size);
//                malloc_error();
//            }
//        }
//        size_t readsize = size-curr;
//        if(readsize > INT_MAX) readsize = INT_MAX-1;
//        fgets(&line[curr], readsize, fp);
//        curr = strlen(line);
//    }
//    if(line[curr-1] == '\n') line[curr-1] = '\0';
//
//    return line;
//}



float sum_array(float *a, int n)
{
    int i;
    float sum = 0;
    for(i = 0; i < n; ++i) sum += a[i];
    return sum;
}

void translate_array(float *a, int n, float s)
{
    int i;
    for(i = 0; i < n; ++i){
        a[i] += s;
    }
}

float mag_array(float *a, int n)
{
    int i;
    float sum = 0;
    for(i = 0; i < n; ++i){
        sum += a[i]*a[i];   
    }
    return sqrt(sum);
}





int max_int_index(int *a, int n)
{
    if(n <= 0) return -1;
    int i, max_i = 0;
    int max = a[0];
    for(i = 1; i < n; ++i){
        if(a[i] > max){
            max = a[i];
            max_i = i;
        }
    }
    return max_i;
}

int max_index(float *a, int n)
{
    if(n <= 0) return -1;
    int i, max_i = 0;
    float max = a[0];
    for(i = 1; i < n; ++i){
        if(a[i] > max){
            max = a[i];
            max_i = i;
        }
    }
    return max_i;
}

int int_index(int *a, int val, int n)
{
    int i;
    for(i = 0; i < n; ++i){
        if(a[i] == val) return i;
    }
    return -1;
}

int rand_int(int min, int max)
{
    if (max < min){
        int s = min;
        min = max;
        max = s;
    }
    int r = (rand()%(max - min + 1)) + min;
    return r;
}

// From http://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
float rand_normal()
{
    static int haveSpare = 0;
    static double rand1, rand2;

    if(haveSpare)
    {
        haveSpare = 0;
        return sqrt(rand1) * sin(rand2);
    }

    haveSpare = 1;

    rand1 = rand() / ((double) RAND_MAX);
    if(rand1 < 1e-100) rand1 = 1e-100;
    rand1 = -2 * log(rand1);
    rand2 = (rand() / ((double) RAND_MAX)) * TWO_PI;

    return sqrt(rand1) * cos(rand2);
}


/////////////////////////////////


// float mean_array(float *a, int n)
// {
//     return sum_array(a,n)/n;
// }

// float variance_array(float *a, int n)
// {
//     int i;
//     float sum = 0;
//     float mean = mean_array(a, n);
//     for(i = 0; i < n; ++i) sum += (a[i] - mean)*(a[i]-mean);
//     float variance = sum/n;
//     return variance;
// }

// float constrain(float min, float max, float a)
// {
//     if (a < min) return min;
//     if (a > max) return max;
//     return a;
// }

// float dist_array(float *a, float *b, int n, int sub)
// {
//     int i;
//     float sum = 0;
//     for(i = 0; i < n; i += sub) sum += pow(a[i]-b[i], 2);
//     return sqrt(sum);
// }

// float mse_array(float *a, int n)
// {
//     int i;
//     float sum = 0;
//     for(i = 0; i < n; ++i) sum += a[i]*a[i];
//     return sqrt(sum/n);
// }

// void normalize_array(float *a, int n)
// {
//     int i;
//     float mu = mean_array(a,n);
//     float sigma = sqrt(variance_array(a,n));
//     for(i = 0; i < n; ++i){
//         a[i] = (a[i] - mu)/sigma;
//     }
//     mu = mean_array(a,n);
//     sigma = sqrt(variance_array(a,n));
// }


// void scale_array(float *a, int n, float s)
// {
//     int i;
//     for(i = 0; i < n; ++i){
//         a[i] *= s;
//     }
// }



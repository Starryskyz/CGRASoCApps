#include "matrix.h"
#include "utils.h"
#include "blas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <assert.h>
#include <math.h>

void free_matrix(matrix m)
{
    int i;
    for(i = 0; i < m.rows; ++i) free(m.vals[i]);
    free(m.vals);
}

float matrix_topk_accuracy(matrix truth, matrix guess, int k)
{
    int *indexes = calloc(k, sizeof(int));
    int n = truth.cols;
    int i,j;
    int correct = 0;
    for(i = 0; i < truth.rows; ++i){
        top_k(guess.vals[i], n, k, indexes);
        for(j = 0; j < k; ++j){
            int class = indexes[j];
            if(truth.vals[i][class]){
                ++correct;
                break;
            }
        }
    }
    free(indexes);
    return (float)correct/truth.rows;
}



matrix resize_matrix(matrix m, int size)
{
    int i;
    if (m.rows == size) return m;
    if (m.rows < size) {
        m.vals = realloc(m.vals, size*sizeof(float*));
        for (i = m.rows; i < size; ++i) {
            m.vals[i] = calloc(m.cols, sizeof(float));
        }
    } else if (m.rows > size) {
        for (i = size; i < m.rows; ++i) {
            free(m.vals[i]);
        }
        m.vals = realloc(m.vals, size*sizeof(float*));
    }
    m.rows = size;
    return m;
}



matrix make_matrix(int rows, int cols)
{
    int i;
    matrix m;
    m.rows = rows;
    m.cols = cols;
    m.vals = calloc(m.rows, sizeof(float *));
    for(i = 0; i < m.rows; ++i){
        m.vals[i] = calloc(m.cols, sizeof(float));
    }
    return m;
}


// void scale_matrix(matrix m, float scale)
// {
//     int i,j;
//     for(i = 0; i < m.rows; ++i){
//         for(j = 0; j < m.cols; ++j){
//             m.vals[i][j] *= scale;
//         }
//     }
// }


// void matrix_add_matrix(matrix from, matrix to)
// {
//     assert(from.rows == to.rows && from.cols == to.cols);
//     int i,j;
//     for(i = 0; i < from.rows; ++i){
//         for(j = 0; j < from.cols; ++j){
//             to.vals[i][j] += from.vals[i][j];
//         }
//     }
// }

// matrix copy_matrix(matrix m)
// {
//     matrix c = {0};
//     c.rows = m.rows;
//     c.cols = m.cols;
//     c.vals = calloc(c.rows, sizeof(float *));
//     int i;
//     for(i = 0; i < c.rows; ++i){
//         c.vals[i] = calloc(c.cols, sizeof(float));
//         copy_cpu(c.cols, m.vals[i], 1, c.vals[i], 1);
//     }
//     return c;
// }
#include "imageedgefinder.h"

float ImageEdgeFinder::FILTER_MATRIX[EDGE_FINDER_MATRIX_SIZE][EDGE_FINDER_MATRIX_SIZE] = {
    0,  0, -1,  0,  0,
    0,  0, -1,  0,  0,
    0,  0,  2,  0,  0,
    0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,
 };

int ImageEdgeFinder::get_matrix_size() {
    return EDGE_FINDER_MATRIX_SIZE;
}

float ImageEdgeFinder::get_filter_matrix_at(int x, int y) {
    return ImageEdgeFinder::FILTER_MATRIX[x][y];
}

float ImageEdgeFinder::get_factor() {
    return 1.0;
}

float ImageEdgeFinder::get_bias() {
    return 0.0;
}


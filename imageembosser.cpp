#include "imageembosser.h"

float ImageEmbosser::FILTER_MATRIX[EMBOSSER_MATRIX_SIZE][EMBOSSER_MATRIX_SIZE] = {
    -1, -1,  0,
    -1,  0,  1,
     0,  1,  1
};

int ImageEmbosser::get_matrix_size() {
    return EMBOSSER_MATRIX_SIZE;
}

float ImageEmbosser::get_filter_matrix_at(int x, int y) {
    return ImageEmbosser::FILTER_MATRIX[x][y];
}

float ImageEmbosser::get_factor() {
    return 1.0;
}

float ImageEmbosser::get_bias() {
    return 128.0;
}


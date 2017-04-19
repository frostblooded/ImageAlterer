#include "imageblurrer.h"

float ImageBlurrer::FILTER_MATRIX[BLURRER_MATRIX_SIZE][BLURRER_MATRIX_SIZE] = {
    1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1,
};

int ImageBlurrer::get_matrix_size() {
    return BLURRER_MATRIX_SIZE;
}

float ImageBlurrer::get_filter_matrix_at(int x, int y) {
    return ImageBlurrer::FILTER_MATRIX[x][y];
}

float ImageBlurrer::get_factor() {
    return 1.0 / float(BLURRER_MATRIX_SIZE);
}

float ImageBlurrer::get_bias() {
    return 0.0;
}

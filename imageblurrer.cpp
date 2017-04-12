#include "imageblurrer.h"

float ImageBlurrer::FILTER_MATRIX[MATRIX_SIZE][MATRIX_SIZE] = {{0.01, 0.02, 0.04, 0.02, 0.01},
                                                               {0.02, 0.04, 0.08, 0.04, 0.02},
                                                               {0.04, 0.08, 0.16, 0.08, 0.04},
                                                               {0.02, 0.04, 0.08, 0.04, 0.02},
                                                               {0.01, 0.02, 0.04, 0.02, 0.01}};

int ImageBlurrer::get_matrix_size() {
    return MATRIX_SIZE;
}

float ImageBlurrer::get_filter_matrix_at(int x, int y) {
    return ImageBlurrer::FILTER_MATRIX[x][y];
}

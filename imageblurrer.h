#ifndef IMAGEBLURRER_H
#define IMAGEBLURRER_H

#include <abstractalgorithm.h>

#define MATRIX_SIZE 9

class ImageBlurrer: public AbstractAlgorithm
{
public:
    static float FILTER_MATRIX[MATRIX_SIZE][MATRIX_SIZE];

    virtual int get_matrix_size();
    virtual float get_filter_matrix_at(int, int);
};

#endif // IMAGEBLURRER_H

#ifndef IMAGEEMBOSSER_H
#define IMAGEEMBOSSER_H

#include <abstractalgorithm.h>

#define EMBOSSER_MATRIX_SIZE 3

class ImageEmbosser: public AbstractAlgorithm
{
public:
    static float FILTER_MATRIX[EMBOSSER_MATRIX_SIZE][EMBOSSER_MATRIX_SIZE];

    virtual int get_matrix_size();
    virtual float get_filter_matrix_at(int, int);
    virtual float get_factor();
    virtual float get_bias();
};

#endif // IMAGEEMBOSSER_H

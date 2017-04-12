#ifndef IMAGEEDGEFINDER_H
#define IMAGEEDGEFINDER_H

#include <abstractalgorithm.h>

#define EDGE_FINDER_MATRIX_SIZE 5

class ImageEdgeFinder: public AbstractAlgorithm
{
public:
    static float FILTER_MATRIX[EDGE_FINDER_MATRIX_SIZE][EDGE_FINDER_MATRIX_SIZE];

    virtual int get_matrix_size();
    virtual float get_filter_matrix_at(int, int);
    virtual float get_factor();
    virtual float get_bias();
};

#endif // IMAGEEDGEFINDER_H

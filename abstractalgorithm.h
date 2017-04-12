#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include <QColor>
#include <QProgressDialog>
#include <QImage>
#include <QDebug>
#include <QApplication>

class AbstractAlgorithm
{
public:
    QImage* apply(QImage*);

protected:
    static QProgressDialog* progress_dialog;

    virtual int get_matrix_size() = 0;
    virtual float get_filter_matrix_at(int, int) = 0;
    virtual float get_factor() = 0;
    virtual float get_bias() = 0;

    QColor*** get_pixel_neighbours(QImage*, int, int);

    QRgb apply(QImage*, int, int);
};

#endif // ABSTRACTALGORITHM_H

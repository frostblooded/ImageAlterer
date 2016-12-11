#ifndef IMAGEBLURRER_H
#define IMAGEBLURRER_H

#include <QImage>
#include <QColor>
#include <QDebug>

#define FILTER_MATRIX_SIZE 3

class ImageBlurrer
{
public:
    static QImage* blur(QImage*);

private:
    static float FILTER_MATRIX[FILTER_MATRIX_SIZE][FILTER_MATRIX_SIZE];

    static QColor*** get_pixel_neighbours(QImage*, int, int);
    static QRgb blur(QImage*, int, int);
};

#endif // IMAGEBLURRER_H

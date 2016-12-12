#ifndef IMAGEBLURRER_H
#define IMAGEBLURRER_H

#include <QImage>
#include <QColor>
#include <QDebug>
#include <QProgressDialog>
#include <QApplication>

#define FILTER_MATRIX_SIZE 5

class ImageBlurrer
{
public:
    static QImage* blur(QImage*, int);

private:
    static QColor*** get_pixel_neighbours(QImage*, int, int);
    static QRgb blur(QImage*, int, int, int);

    static QProgressDialog* progress_dialog;
};

#endif // IMAGEBLURRER_H

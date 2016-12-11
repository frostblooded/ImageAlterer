#include "imageblurrer.h"

float ImageBlurrer::FILTER_MATRIX[FILTER_MATRIX_SIZE][FILTER_MATRIX_SIZE] = {{0.111, 0.111, 0.111},
                                                                             {0.111, 0.111, 0.111},
                                                                             {0.111, 0.111, 0.111}};

QImage* ImageBlurrer::blur(QImage* image)
{
    if(!image)
        return NULL;

    QImage* result_image = new QImage(image->width(), image->height(), image->format());
    qDebug() << "Blurring image with sizes: " << image->width() << " to " << image->height();

    for(int i = 0; i < image->width(); i++) {
        for(int j = 0; j < image->height(); j++) {
            result_image->setPixel(i, j, blur(image, i, j));
        }
    }

    return result_image;
}

QRgb ImageBlurrer::blur(QImage* image, int x, int y)
{
//    qDebug() << "Getting neighbours";
    QColor*** neighbours = get_pixel_neighbours(image, x, y);
//    qDebug() << "Got neighbours";
//    QRgb new_pixel = (new QColor(0, 0, 0))->rgb();
    QRgb new_pixel = qRgb(0, 0, 0);

//    qDebug() << "Starting pixel blur";

    for(int i = 0; i < FILTER_MATRIX_SIZE; i++)
    {
//        qDebug() << "Blurring neighbours from column " << i;
        for(int j = 0; j < FILTER_MATRIX_SIZE; j++)
        {
//            qDebug() << "Blurring neighbours from row " << j;
            int new_red = qRed(new_pixel) + neighbours[i][j]->red() * FILTER_MATRIX[i][j];
            int new_green = qGreen(new_pixel) + neighbours[i][j]->green() * FILTER_MATRIX[i][j];
            int new_blue = qBlue(new_pixel) + neighbours[i][j]->blue() * FILTER_MATRIX[i][j];

            new_pixel = qRgb(new_red, new_green, new_blue);

//            int new_red = new_pixel->red() + neighbours[i][j] * FILTER_MATRIX[i][j];
//            int new_green = new_pixel->green() + neighbours[i][j] * FILTER_MATRIX[i][j];
//            int new_blue = new_pixel->blue() + neighbours[i][j] * FILTER_MATRIX[i][j];

//            new_pixel = new QColor(new_red, new_green, new_blue);
        }
    }

//    qDebug() << "Blurred pixel " << x << ";" << y;
    return new_pixel;
}

QColor*** ImageBlurrer::get_pixel_neighbours(QImage* image, int x, int y)
{
    QColor*** neighbours = 0;
    neighbours = new QColor**[FILTER_MATRIX_SIZE]();

    for(int i = 0; i < FILTER_MATRIX_SIZE; i++) {
        neighbours[i] = new QColor*[FILTER_MATRIX_SIZE]();

        for(int j = 0; j < FILTER_MATRIX_SIZE; j++) {
            neighbours[i][j] = new QColor(0, 0, 0);
        }
    }

    int offset = FILTER_MATRIX_SIZE / 2;
    int starting_x = std::max(x, offset - x);
    int starting_y = std::max(y, offset - y);

    for(int i = starting_x; i < x + FILTER_MATRIX_SIZE; i++)
    {
        for(int j = starting_y; j < y + FILTER_MATRIX_SIZE; j++)
        {
//            QRgb pixel = image->pixel(i - offset + x, j - offset + y);
//            neighbours[i][j] = new QColor(pixel);
            neighbours[i][j] = image->pixelColor(i - offset + x, j - offset + y);
        }
    }

    return neighbours;
}

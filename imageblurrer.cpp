#include "imageblurrer.h"

QProgressDialog* ImageBlurrer::progress_dialog;

QImage* ImageBlurrer::blur(QImage* image, int blur_strength)
{
    if(!image)
        return NULL;

    progress_dialog = new QProgressDialog("Blurring image...", "Abort Blur", 0, image->width() - 1);
    progress_dialog->setAutoClose(true);

    QImage* result_image = new QImage(image->width(), image->height(), image->format());

    for(int i = 0; i < image->width(); i++) {
        for(int j = 0; j < image->height(); j++) {
            result_image->setPixel(i, j, blur(image, blur_strength, i, j));
        }

        if(progress_dialog->wasCanceled())
            return image;

        progress_dialog->setValue(i);
        QApplication::processEvents();
    }

    return result_image;
}

QRgb ImageBlurrer::blur(QImage* image, int blur_strength, int x, int y)
{
    QColor*** neighbours = get_pixel_neighbours(image, x, y);
    QRgb new_pixel = qRgb(0, 0, 0);

    double blur_multiplier = 1.0 / (blur_strength * blur_strength);

    for(int i = 0; i < FILTER_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < FILTER_MATRIX_SIZE; j++)
        {
            int new_red = qRed(new_pixel) + neighbours[i][j]->red() * blur_multiplier;
            int new_green = qGreen(new_pixel) + neighbours[i][j]->green() * blur_multiplier;
            int new_blue = qBlue(new_pixel) + neighbours[i][j]->blue() * blur_multiplier;

            new_pixel = qRgb(new_red, new_green, new_blue);
        }
    }

    return new_pixel;
}

QColor*** ImageBlurrer::get_pixel_neighbours(QImage* image, int x, int y)
{
    QColor*** neighbours = new QColor**[FILTER_MATRIX_SIZE]();

    for(int i = 0; i < FILTER_MATRIX_SIZE; i++) {
        neighbours[i] = new QColor*[FILTER_MATRIX_SIZE]();

        for(int j = 0; j < FILTER_MATRIX_SIZE; j++) {
            neighbours[i][j] = new QColor(0, 0, 0);
        }
    }

    int offset = FILTER_MATRIX_SIZE / 2;
    int starting_x = std::max(x, offset);
    int starting_y = std::max(y, offset);
    int ending_x = std::min(x + FILTER_MATRIX_SIZE, image->width() - 1);
    int ending_y = std::min(y + FILTER_MATRIX_SIZE, image->height() - 1);

    for(int i = starting_x; i < ending_x; i++)
    {
        for(int j = starting_y; j < ending_y; j++)
        {
            QRgb pixel = image->pixel(i, j);
            neighbours[i - x][j - y] = new QColor(pixel);
        }
    }

    return neighbours;
}

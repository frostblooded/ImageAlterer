#include "imageblurrer.h"

QProgressDialog* ImageBlurrer::progress_dialog;

// Filter matrix which shows how much neighbouring pixels affect the current pixel's colour
float ImageBlurrer::FILTER_MATRIX[FILTER_MATRIX_SIZE][FILTER_MATRIX_SIZE] = {{0.01, 0.02, 0.04, 0.02, 0.01},
                                                                             {0.02, 0.04, 0.08, 0.04, 0.02},
                                                                             {0.04, 0.08, 0.16, 0.08, 0.04},
                                                                             {0.02, 0.04, 0.08, 0.04, 0.02},
                                                                             {0.01, 0.02, 0.04, 0.02, 0.01}};

QImage* ImageBlurrer::blur(QImage* image)
{
    if(!image)
        return NULL;

    // Show progress dialog
    progress_dialog = new QProgressDialog("Blurring image...", "Abort Blur", 0, image->width() - 1);
    progress_dialog->setAutoClose(true);

    QImage* result_image = new QImage(image->width(), image->height(), image->format());

    for(int i = 0; i < image->width(); i++) {
        for(int j = 0; j < image->height(); j++) {
            // Blur each pixel
            result_image->setPixel(i, j, blur(image, i, j));
        }

        if(progress_dialog->wasCanceled())
            return image;

        progress_dialog->setValue(i);

        // The application should explicitly be told to process events after
        // the progress dialog is updated, so that it gets redrawn
        QApplication::processEvents();
    }

    return result_image;
}

QRgb ImageBlurrer::blur(QImage* image, int x, int y)
{
    QColor*** neighbours = get_pixel_neighbours(image, x, y);
    QRgb new_pixel = qRgb(0, 0, 0);

    // Find out resulting color based on neighbouring pixels
    for(int i = 0; i < FILTER_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < FILTER_MATRIX_SIZE; j++)
        {
            // Multiply each color to the multiplier from the filter matrix
            int new_red = qRed(new_pixel) + neighbours[i][j]->red() * FILTER_MATRIX[i][j];
            int new_green = qGreen(new_pixel) + neighbours[i][j]->green() * FILTER_MATRIX[i][j];
            int new_blue = qBlue(new_pixel) + neighbours[i][j]->blue() * FILTER_MATRIX[i][j];

            new_pixel = qRgb(new_red, new_green, new_blue);
            delete neighbours[i][j];
        }

        delete neighbours[i];
    }

    delete neighbours;
    return new_pixel;
}

QColor*** ImageBlurrer::get_pixel_neighbours(QImage* image, int x, int y)
{
    QColor*** neighbours = new QColor**[FILTER_MATRIX_SIZE]();

    // Initialize neighbours
    for(int i = 0; i < FILTER_MATRIX_SIZE; i++) {
        neighbours[i] = new QColor*[FILTER_MATRIX_SIZE]();

        for(int j = 0; j < FILTER_MATRIX_SIZE; j++) {
            neighbours[i][j] = new QColor(0, 0, 0);
        }
    }

    // Handle starting and ending coordinates, so that
    // the algorithm doesn't attempt to get a pixel which
    // is outside the image's bounds
    //
    // Neighbours which are outside the image's borders
    // are returned as 0
    int offset = FILTER_MATRIX_SIZE / 2;
    int starting_x = std::max(x, offset);
    int starting_y = std::max(y, offset);
    int ending_x = std::min(x + FILTER_MATRIX_SIZE, image->width() - 1);
    int ending_y = std::min(y + FILTER_MATRIX_SIZE, image->height() - 1);

    for(int i = starting_x; i < ending_x; i++)
    {
        for(int j = starting_y; j < ending_y; j++)
        {
            // Populate the neighbours matrix
            QRgb pixel = image->pixel(i, j);
            delete neighbours[i - x][j - y];

            neighbours[i - x][j - y] = new QColor(pixel);
        }
    }

    return neighbours;
}

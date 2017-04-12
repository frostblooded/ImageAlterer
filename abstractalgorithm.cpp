#include "abstractalgorithm.h"

QProgressDialog* AbstractAlgorithm::progress_dialog;

QColor*** AbstractAlgorithm::get_pixel_neighbours(QImage* image, int x, int y)
{
    QColor*** neighbours = new QColor**[this->get_matrix_size()]();

    // Initialize neighbours
    for(int i = 0; i < this->get_matrix_size(); i++) {
        neighbours[i] = new QColor*[this->get_matrix_size()]();

        for(int j = 0; j < this->get_matrix_size(); j++) {
            neighbours[i][j] = new QColor(0, 0, 0);
        }
    }

    // Handle starting and ending coordinates, so that
    // the algorithm doesn't attempt to get a pixel which
    // is outside the image's bounds
    //
    // Neighbours which are outside the image's borders
    // are returned as 0
    int offset = this->get_matrix_size() / 2;
    int starting_x = std::max(x, offset);
    int starting_y = std::max(y, offset);
    int ending_x = std::min(x + this->get_matrix_size(), image->width() - 1);
    int ending_y = std::min(y + this->get_matrix_size(), image->height() - 1);

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

QImage* AbstractAlgorithm::apply(QImage* image)
{
    if(!image)
        return NULL;

    // Show progress dialog
    progress_dialog = new QProgressDialog("Applying algorithm...", "Abort", 0, image->width() - 1);
    progress_dialog->setAutoClose(true);

    QImage* result_image = new QImage(image->width(), image->height(), image->format());

    for(int i = 0; i < image->width(); i++) {
        for(int j = 0; j < image->height(); j++) {
            // Apply algorithm to each pixel
            result_image->setPixel(i, j, this->apply(image, i, j));
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

QRgb AbstractAlgorithm::apply(QImage* image, int x, int y)
{
    QColor*** neighbours = get_pixel_neighbours(image, x, y);
    QRgb new_pixel = qRgb(0, 0, 0);

    // Find out resulting color based on neighbouring pixels
    for(int i = 0; i < this->get_matrix_size(); i++)
    {
        for(int j = 0; j < this->get_matrix_size(); j++)
        {
            float current_filter_matrix_pixel = get_filter_matrix_at(i, j);

            // Multiply each color to the multiplier from the filter matrix
            int new_red = qRed(new_pixel) + neighbours[i][j]->red() * current_filter_matrix_pixel;
            int new_green = qGreen(new_pixel) + neighbours[i][j]->green() * current_filter_matrix_pixel;
            int new_blue = qBlue(new_pixel) + neighbours[i][j]->blue() * current_filter_matrix_pixel;

            new_pixel = qRgb(new_red, new_green, new_blue);
            delete neighbours[i][j];
        }

        delete neighbours[i];
    }

    delete neighbours;
    return new_pixel;
}

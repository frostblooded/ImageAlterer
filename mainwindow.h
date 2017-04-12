#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QSlider>
#include <QComboBox>

#include "imageblurrer.h"
#include "imageedgefinder.h"

#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 450

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void loadImage();
    void applyAlgorithm();

private:
    void updateImageLabel(QImage*);

    Ui::MainWindow *ui;
    QWidget* widget;
    QGridLayout* layout;
    QPushButton* loadImageButton;
    QComboBox* algorithmComboBox;
    QPushButton* applyAlgorithmButton;
    QLabel* imageLabel;
    QImage* image;
};

#endif // MAINWINDOW_H

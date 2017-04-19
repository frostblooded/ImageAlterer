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
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "imageblurrer.h"
#include "imageedgefinder.h"
#include "imageembosser.h"

#define WINDOW_WIDTH 800

#define IMAGE_WIDTH WINDOW_WIDTH
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
    void saveImage();
    void applyAlgorithm();

private:
    void updateImageLabel(QImage*);
    void initMenuBar();

    Ui::MainWindow *ui;
    QWidget* widget;
    QGridLayout* layout;
    QMenuBar* menubar;
    QComboBox* algorithmComboBox;
    QPushButton* applyAlgorithmButton;
    QLabel* imageLabel;
    QImage* image;
};

#endif // MAINWINDOW_H

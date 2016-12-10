#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QImage>
#include <QPixmap>

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
    Ui::MainWindow *ui;
    QWidget* widget;
    QGridLayout* layout;
    QPushButton* loadImageButton;
    QPushButton* applyAlgorithmButton;
    QLabel* imageLabel;
    QImage* image;
};

#endif // MAINWINDOW_H

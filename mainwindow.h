#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>

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

private:
    Ui::MainWindow *ui;
    QWidget* widget;
    QGridLayout* layout;
    QPushButton* loadImageButton;
    QLineEdit* imagePath;
};

#endif // MAINWINDOW_H

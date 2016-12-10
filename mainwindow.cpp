#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    removeWindowResize();

    widget = new QWidget(this);
    layout = new QGridLayout(widget);

    loadImageButton = new QPushButton("Load Image", widget);
    connect(loadImageButton, SIGNAL(clicked()), this, SLOT(loadImage()));
    layout->addWidget(loadImageButton);

    imagePath = new QLineEdit(widget);
    layout->addWidget(imagePath);

    widget->setLayout(layout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    QString path = QFileDialog::getOpenFileName(this, "Open image", "/");
    imagePath->setText(path);
}

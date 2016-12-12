#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget = new QWidget(this);
    layout = new QGridLayout(widget);

    loadImageButton = new QPushButton("Load Image", widget);
    connect(loadImageButton, SIGNAL(clicked()), this, SLOT(loadImage()));
    layout->addWidget(loadImageButton);

    applyAlgorithmButton = new QPushButton("Apply Algorithm", widget);
    connect(applyAlgorithmButton, SIGNAL(clicked()), this, SLOT(applyAlgorithm()));
    layout->addWidget(applyAlgorithmButton);

    imageLabel = new QLabel(widget);
    imageLabel->setFixedSize(IMAGE_WIDTH, IMAGE_HEIGHT);
    layout->addWidget(imageLabel);

    image = NULL;

    widget->setLayout(layout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    imageLabel->setText("loading image...");
    QString path = QFileDialog::getOpenFileName(this, "Open image", "C:\\Users\\frost\\Dropbox", "Images (*.png *.img *.jpg *.xpm)");

    updateImageLabel(new QImage(path));
}

void MainWindow::updateImageLabel(QImage* new_image)
{
    image = new_image;
    QPixmap pixmap = QPixmap::fromImage(*image);
    pixmap = pixmap.scaled(imageLabel->width(), imageLabel->height(), Qt::KeepAspectRatio);
    imageLabel->setPixmap(pixmap);
}

void MainWindow::applyAlgorithm()
{
    image = ImageBlurrer::blur(image);
    updateImageLabel(image);
}

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

    blurStrengthLabel = new QLabel("Blur strength:", widget);
    layout->addWidget(blurStrengthLabel);

    blurStrengthSlider = new QSlider(Qt::Horizontal, widget);
    connect(blurStrengthSlider, SIGNAL(valueChanged(int)), this, SLOT(setBlurStrength(int)));
    blurStrengthSlider->setRange(3, 15);
    blurStrengthSlider->setSingleStep(2);
    layout->addWidget(blurStrengthSlider);

    applyAlgorithmButton = new QPushButton("Apply Algorithm", widget);
    connect(applyAlgorithmButton, SIGNAL(clicked()), this, SLOT(applyAlgorithm()));
    layout->addWidget(applyAlgorithmButton);

    imageLabel = new QLabel(widget);
    imageLabel->setFixedSize(IMAGE_WIDTH, IMAGE_HEIGHT);
    layout->addWidget(imageLabel);

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

    image = new QImage(path);
    updateImageLabel(image);
}

void MainWindow::updateImageLabel(QImage* image)
{
    QPixmap pixmap = QPixmap::fromImage(*image);
    pixmap = pixmap.scaled(imageLabel->width(), imageLabel->height(), Qt::KeepAspectRatio);
    imageLabel->setPixmap(pixmap);
}

void MainWindow::applyAlgorithm()
{
    image = ImageBlurrer::blur(image, blurStrength);
    updateImageLabel(image);
}

void MainWindow::setBlurStrength(int strength)
{
    blurStrength = strength;
}

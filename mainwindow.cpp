#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize layout
    widget = new QWidget(this);
    layout = new QGridLayout(widget);

    // Initialize button for loading an image
    loadImageButton = new QPushButton("Load Image", widget);
    connect(loadImageButton, SIGNAL(clicked()), this, SLOT(loadImage()));
    layout->addWidget(loadImageButton);

    // Initialize dropdown menu for choosing the algorithm
    algorithmComboBox = new QComboBox(widget);
    algorithmComboBox->addItem("Motion Blur");
    algorithmComboBox->addItem("Find Edges");
    algorithmComboBox->addItem("Emboss");
    layout->addWidget(algorithmComboBox);

    // Initialize button for applying algorithm
    applyAlgorithmButton = new QPushButton("Apply algorithm", widget);
    connect(applyAlgorithmButton, SIGNAL(clicked()), this, SLOT(applyAlgorithm()));
    layout->addWidget(applyAlgorithmButton);

    // Initialize the label, which displays the image
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
    // Open dialog so the user can select an image to be opened
    QString path = QFileDialog::getOpenFileName(this, "Open image", "C:\\", "Images (*.png *.img *.jpg *.xpm)");

    if(!path.isEmpty()) {
        imageLabel->setText("loading image...");
        updateImageLabel(new QImage(path));
    }
}

void MainWindow::updateImageLabel(QImage* new_image)
{
    image = new_image;
    QPixmap pixmap = QPixmap::fromImage(*image);

    // Scale the image down so that it has a maximum size and fits in the form
    pixmap = pixmap.scaled(imageLabel->width(), imageLabel->height(), Qt::KeepAspectRatio);

    // Set image
    imageLabel->setPixmap(pixmap);
}

void MainWindow::applyAlgorithm()
{
    if(!image)
        return;

    image = ImageBlurrer::blur(image);
    updateImageLabel(image);
}

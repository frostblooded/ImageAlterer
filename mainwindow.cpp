#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize layout
    widget = new QWidget(this);
    layout = new QGridLayout(widget);

    // Initialize menu bar
    initMenuBar();
    layout->setMenuBar(menubar);

    // Initialize dropdown menu for choosing the algorithm
    algorithmComboBox = new QComboBox(widget);
    algorithmComboBox->setFixedSize(WINDOW_WIDTH * 80 / 100, 25);
    algorithmComboBox->addItem("Motion blur");
    algorithmComboBox->addItem("Find edges");
    algorithmComboBox->addItem("Emboss");
    layout->addWidget(algorithmComboBox, 1, 0, 1, 1, Qt::AlignCenter);

    // Initialize button for applying algorithm
    applyAlgorithmButton = new QPushButton(widget);
    applyAlgorithmButton->setIcon(QIcon(":/images/button.png"));
    applyAlgorithmButton->setStyleSheet("background-color: transparent; border: 0;");
    applyAlgorithmButton->setAutoFillBackground(true);
    applyAlgorithmButton->setIconSize(QSize(WINDOW_WIDTH * 20 / 100, 100));
    connect(applyAlgorithmButton, SIGNAL(clicked()), this, SLOT(applyAlgorithm()));
    layout->addWidget(applyAlgorithmButton, 1, 1, 1, 1, Qt::AlignCenter);

    // Initialize the label, which displays the image
    imageLabel = new QLabel(widget);
    imageLabel->setFixedSize(IMAGE_WIDTH, IMAGE_HEIGHT);
    layout->addWidget(imageLabel, 2, 0, 1, 2);

    image = NULL;

    widget->setLayout(layout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenuBar() {
    menubar = new QMenuBar(widget);

    QAction* load = new QAction("&Load", this);
    QAction* saveAs = new QAction("&Save as", this);

    QMenu* fileMenu = new QMenu("&File");
    QMenu* helpMenu = new QMenu("&Help");

    fileMenu->addAction(load);
    fileMenu->addAction(saveAs);

    connect(load, SIGNAL(triggered()), this, SLOT(loadImage()));
    connect(saveAs, SIGNAL(triggered()), this, SLOT(saveImage()));

    menubar->addMenu(fileMenu);
    menubar->addMenu(helpMenu);
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

void MainWindow::saveImage()
{
    // Open dialog so the user can select an image to be opened
    QString path = QFileDialog::getSaveFileName(this, "Save image", "C:\\image.png", "Images (*.png *.img *.jpg *.xpm)");

    if(!path.isEmpty()) {
        image->save(path);
    }
}

void MainWindow::updateImageLabel(QImage* new_image)
{
    image = new_image;
    QPixmap pixmap = QPixmap::fromImage(*image);

    // Scale the image down so that it has a maximum size and fits in the form
    pixmap = pixmap.scaled(imageLabel->width(), imageLabel->height(), Qt::KeepAspectRatio);

    // Set image
    imageLabel->show();
    imageLabel->setPixmap(pixmap);
}

void MainWindow::applyAlgorithm()
{
    if(!image)
        return;

    QString algorithm = algorithmComboBox->currentText();

    // Use the selected algorithm
    if(algorithm == "Motion blur"){
        ImageBlurrer* algorithm_applier = new ImageBlurrer();
        image = algorithm_applier->apply(image);
        updateImageLabel(image);
    }
    else if(algorithm == "Find edges"){
        ImageEdgeFinder* algorithm_applier = new ImageEdgeFinder();
        image = algorithm_applier->apply(image);
        updateImageLabel(image);
    }
    else if(algorithm == "Emboss"){
        ImageEmbosser* algorithm_applier = new ImageEmbosser();
        image = algorithm_applier->apply(image);
        updateImageLabel(image);
    }

    return;
}

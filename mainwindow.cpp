#include "mainwindow.h"
#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 创建画布
    paintWidget = new PaintWidget(this);
    paintWidget->setMinimumSize(800, 600);

    // 创建按钮
    colorButton = new QPushButton("Choose Color", this);
    clearButton = new QPushButton("Clear Canvas", this);
    eraserButton = new QPushButton("Eraser: OFF", this);

    colorButton->setMinimumSize(100, 30);
    clearButton->setMinimumSize(100, 30);
    eraserButton->setMinimumSize(100, 30);

    colorButton->setStyleSheet("QPushButton { background-color: lightblue; color: black; }");
    clearButton->setStyleSheet("QPushButton { background-color: lightgreen; color: black; }");
    eraserButton->setStyleSheet("QPushButton { background-color: lightcoral; color: black; }");

    // 创建横向布局用于工具栏
    QHBoxLayout *toolbarLayout = new QHBoxLayout;
    toolbarLayout->addWidget(colorButton);
    toolbarLayout->addWidget(clearButton);
    toolbarLayout->addWidget(eraserButton);

    QWidget *toolbar = new QWidget(this);
    toolbar->setLayout(toolbarLayout);
    toolbar->setFixedHeight(40);
    toolbar->setStyleSheet("background-color: lightgray;");

    zoomSlider = new QSlider(Qt::Horizontal, this);
    zoomSlider->setRange(10, 200);
    zoomSlider->setValue(100);
    connect(zoomSlider, &QSlider::valueChanged, this, [this](int value) {
        double zoomFactor = value / 100.0;
        paintWidget->setZoomFactor(zoomFactor);
    });

    // 设置主窗口布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(toolbar);
    mainLayout->addWidget(paintWidget);
    mainLayout->addWidget(zoomSlider);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // 连接信号和槽
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::chooseColor);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearCanvas);
    connect(eraserButton, &QPushButton::clicked, this, &MainWindow::toggleEraser);
}

MainWindow::~MainWindow() {
}

void MainWindow::chooseColor() {
    QColor chosenColor = QColorDialog::getColor(paintWidget->getColor(), this, "Choose Color");
    if (chosenColor.isValid()) {
        paintWidget->setPenColor(chosenColor);
    }
}

void MainWindow::clearCanvas() {
    paintWidget->clear();
}

void MainWindow::toggleEraser() {
    bool eraserMode = !paintWidget->getEraserMode();
    paintWidget->setEraserMode(eraserMode);
    eraserButton->setText(eraserMode ? "Eraser: ON" : "Eraser: OFF");
}
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintwidget.h"
#include <QPushButton>
#include <QSlider>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void chooseColor();
    void clearCanvas();
    void toggleEraser();

private:
    PaintWidget *paintWidget;
    QPushButton *colorButton;
    QPushButton *clearButton;
    QPushButton *eraserButton;
    QSlider *zoomSlider;
};

#endif // MAINWINDOW_H
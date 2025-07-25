#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QColor>
#include <QPen>
#include <QTransform>

class PaintWidget : public QWidget {
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    void clear();
    void setPenColor(const QColor &color);
    void setEraserMode(bool mode);
    QColor getColor() const; 
    bool getEraserMode() const; 
    void setZoomFactor(double factor);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPixmap pixmap;
    QPoint lastPoint;
    bool drawing = false;
    QPen pen;
    QColor color;
    bool eraserMode = false;
    QTransform transform;
    double zoomFactor = 1.0;
};

#endif // PAINTWIDGET_H
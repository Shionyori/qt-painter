#include "paintwidget.h"
#include <QDebug>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    pixmap = QPixmap(800, 600);
    pixmap.fill(Qt::white);
    pen.setWidth(3);
    pen.setColor(Qt::black);
    color = Qt::black;
    eraserMode = false;
    transform = QTransform().scale(zoomFactor, zoomFactor);
}

void PaintWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setTransform(transform);
    painter.drawPixmap(0, 0, pixmap);
    qDebug() << "Paint event triggered";
}

void PaintWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = transform.inverted().map(event->pos());
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton && drawing) {
        QPoint currentPoint = transform.inverted().map(event->pos());
        QPainter painter(&pixmap);
        if (eraserMode) {
            painter.setPen(Qt::NoPen);
            painter.setBrush(Qt::white);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.drawEllipse(currentPoint, pen.width(), pen.width());
        } else {
            painter.setPen(pen);
            painter.drawLine(lastPoint, currentPoint);
        }
        lastPoint = currentPoint;
        update();
        qDebug() << "Mouse move to" << currentPoint;
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = false;
    }
}

void PaintWidget::clear() {
    pixmap.fill(Qt::white);
    update();
}

void PaintWidget::setPenColor(const QColor &color) {
    this->color = color;
    pen.setColor(color);
}

void PaintWidget::setEraserMode(bool mode) {
    eraserMode = mode;
}

QColor PaintWidget::getColor() const {
    return color;
}

bool PaintWidget::getEraserMode() const {
    return eraserMode;
}

void PaintWidget::setZoomFactor(qreal factor) {
    zoomFactor = factor;
    transform = QTransform().scale(zoomFactor, zoomFactor);
    update();
}
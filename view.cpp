#include <QPointF>
#include "view.h"
#include "QDebug"
#include <QScrollBar>

void my::widget::View::wheelEvent(QWheelEvent* event) {
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if (event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    }
    else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void my::widget::View::mousePressEvent(QMouseEvent* event) {

    if (event->button() == Qt::LeftButton)
    {
        isMove = true;
        QPointF p = event->pos();
        startX = p.x();
        startY = p.y();

        setCursor(Qt::ClosedHandCursor);
        return;
    }
}


void my::widget::View::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
    {
        isMove = false;
        setCursor(Qt::ArrowCursor);
    }

}

void my::widget::View::mouseMoveEvent(QMouseEvent* event) {

    if (isMove)
    {
        QPointF p = event->pos();
        
        int moveX = p.x() - startX;
        int moveY = p.y() - startY;
        setTransformationAnchor(QGraphicsView::NoAnchor);
        translate(moveX, moveY);

        startX = p.x();
        startY = p.y();

        qDebug() << "x: " << sceneRect().x() << ", y:" << sceneRect().y();
    }

}
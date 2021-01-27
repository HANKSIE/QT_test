#include "view.h"

void my::widget::View::wheelEvent(QWheelEvent* event) {
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    QPointF oldPos = mapToScene(event->pos());
    if (event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    }
    else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    QPointF newPos = mapToScene(event->pos());
    QPointF move = newPos - oldPos;
    setTransformationAnchor(QGraphicsView::NoAnchor);
    translate(move.x(), move.y());
}

void my::widget::View::mousePressEvent(QMouseEvent* event) {

    if (event->button() == Qt::LeftButton)
    {
        isMove = true;
        QPointF p = event->pos();
        origin.setX(p.x());
        origin.setY(p.y());

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
        QPointF move = p - origin;

        setTransformationAnchor(QGraphicsView::NoAnchor);
        translate(move.x(), move.y());

        origin.setX(p.x());
        origin.setY(p.y());

    }

}
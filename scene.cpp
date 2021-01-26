#include "scene.h"
#include <QScrollBar>
#include <QPointF>
#include <QDebug>

void myQT::Scene::wheelEvent(QGraphicsSceneWheelEvent* event){
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if (event->delta() > 0) {
        // Zoom in
        view->scale(scaleFactor, scaleFactor);
    }
    else {
        // Zooming out
        view->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void myQT::Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    
    if (event->button() == Qt::LeftButton)
    {
        isMove = true;

        QPointF p = event->scenePos();
        startX = p.x();
        startY = p.y();
      
        view->setCursor(Qt::ClosedHandCursor);     
        return;
    }
}


void myQT::Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
    {
        isMove = false;
        view->setCursor(Qt::ArrowCursor);
    }

}

void myQT::Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
  
    if (isMove)
    {
        QPointF p = event->scenePos();
        int moveH = view->horizontalScrollBar()->value() - (p.x() - startX);
        int moveV = view->verticalScrollBar()->value() - (p.y() - startY);
        view->horizontalScrollBar()->setSliderPosition(moveH);
        view->verticalScrollBar()->setSliderPosition(moveV);
        /*
        view->horizontalScrollBar()->setValue(moveH);
        view->verticalScrollBar()->setValue(moveV);*/
        startX = p.x();
        startY = p.y();
    }
   
}

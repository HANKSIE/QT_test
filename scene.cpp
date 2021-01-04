#include "scene.h"
#include <QGraphicsSceneWheelEvent>

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
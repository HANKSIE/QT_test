#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneMouseEvent>

namespace myQT {
	class Scene : public QGraphicsScene {
		Q_OBJECT

	public:
		QGraphicsView* view;
		Scene(QGraphicsView* view) : view(view) {};
	private:
		bool isMove = false;
		int startX;
		int startY;
	protected:
		void wheelEvent(QGraphicsSceneWheelEvent*);
		void mousePressEvent(QGraphicsSceneMouseEvent*);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
		void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	};
}

#endif

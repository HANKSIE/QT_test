#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>

namespace myQT {
	class Scene : public QGraphicsScene {
		Q_OBJECT

	public:
		QGraphicsView* view;
		Scene(QGraphicsView* view) : view(view) {};
	protected:
		void wheelEvent(QGraphicsSceneWheelEvent*);
	};
}

#endif

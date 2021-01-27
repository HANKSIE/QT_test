#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPointF>

namespace my {
	namespace widget {
		class View : public QGraphicsView {

		private:
			bool isMove = false;
			double scaleFactor = 1.15;
			QPointF origin;

		protected:
			void wheelEvent(QWheelEvent*);
			void mousePressEvent(QMouseEvent*);
			void mouseReleaseEvent(QMouseEvent*);
			void mouseMoveEvent(QMouseEvent*);
		};
	}
}

#endif

#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>

namespace my {
	namespace widget {
		class View : public QGraphicsView {

		private:
			bool isMove = false;
			int startX;
			int startY;

		protected:
			void wheelEvent(QWheelEvent*);
			void mousePressEvent(QMouseEvent*);
			void mouseReleaseEvent(QMouseEvent*);
			void mouseMoveEvent(QMouseEvent*);
		};
	}
}

#endif

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
			enum class Scale
			{
				MIN = 0, MAX = 10
			};
			bool isMove = false;
			double scaleFactor = 1.15;
			int scaleCount = 0;
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

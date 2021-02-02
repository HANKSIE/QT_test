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
			int scaleCount = 0;
			QPointF origin;
			bool isDragMove = true;

		protected:
			void wheelEvent(QWheelEvent*) override;
			void mousePressEvent(QMouseEvent*) override;
			void mouseReleaseEvent(QMouseEvent*) override;
			void mouseMoveEvent(QMouseEvent*) override;

		public:
			void setDragMove(bool);
		};
	}
}

#endif

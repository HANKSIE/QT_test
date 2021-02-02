#ifndef SCENECONTEXT_H
#define SCENECONTEXT_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

#include <opencv2/highgui/highgui.hpp>

#include "converter.h"
#include "processExecutor.h"
#include "process.h"

namespace my {
	namespace widget {
		typedef Process<cv::Mat> ImageProcess;
		class SceneContext : public QGraphicsScene {

			Q_OBJECT

		protected slots:
			virtual void updateFrame() = 0;

		protected:
			cv::Mat frame;
			QGraphicsPixmapItem* _pixels;
			QTimer* timer;
			void update() {
				_pixels->setPixmap(Converter::Mat2QPixmap(frame));
			}
			QGraphicsLineItem* opItem;
			bool isMove = false;
			QPointF start;
			QPointF end;
		public:
			ProcessExecutor<cv::Mat> executor;
			SceneContext(ProcessExecutor<cv::Mat> executor) :executor(executor) {
				timer = new QTimer(this);
				connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
			}

			const QGraphicsPixmapItem* getPixels() {
				return _pixels;
			}
			
		protected:
			void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
				if (event->button() == Qt::LeftButton)
				{
					isMove = true;
					start = event->scenePos();
					QLineF l(start, start);
					QGraphicsLineItem* line = new QGraphicsLineItem();
					line->setLine(l);
					line->setPen(createPen());
					addItem(line);
					opItem = line;
				}
			}

			void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
				isMove = false;
			}

			void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
				if (isMove) {
					QLineF l = opItem->line();
					l.setP2(event->scenePos());
					opItem->setLine(l);
				}
			}

		private:
			QPen createPen() {
				QColor c(Qt::GlobalColor::red);
				QBrush brush(c);
				QPen pen(brush, 10);
				return pen;
			}
		};
	}
}

#endif
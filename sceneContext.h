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

		public:
			enum class Draw
			{
				NONE, LINE
			};

			void setDrawMode(Draw type) {
				drawMode = type;
			}

		protected:
			cv::Mat frame;
			QGraphicsPixmapItem* _pixels;
			QTimer* timer;
			void update() {
				_pixels->setPixmap(Converter::Mat2QPixmap(frame));
			}
			QGraphicsLineItem* opLine;
			bool isMove = false;
			Draw drawMode = Draw::NONE;

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
					if (drawMode == Draw::LINE) {
						isMove = true;
						QPointF p = event->scenePos();
						QGraphicsLineItem* line = createLine(p, p);
						addItem(line);
						opLine = line;
					}
				}
			}

			void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
				isMove = false;
				if (drawMode == Draw::LINE) {
					opLine = nullptr;
				}
			}

			void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
				if (isMove) {
					if (drawMode == Draw::LINE) {
						QLineF l = opLine->line();
						l.setP2(event->scenePos());
						opLine->setLine(l);
					}
				}
			}

		private:
			QPen createPen() {
				QColor c(Qt::GlobalColor::red);
				QBrush brush(c);
				QPen pen(brush, 10);
				return pen;
			}

			QGraphicsLineItem* createLine(QPointF p1, QPointF p2) {
				QLineF l(p1, p2);
				QGraphicsLineItem* line = new QGraphicsLineItem();
				line->setLine(l);
				line->setPen(createPen());
				return line;
			}
		};
	}
}

#endif
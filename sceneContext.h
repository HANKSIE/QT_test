#ifndef SCENECONTEXT_H
#define SCENECONTEXT_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include <opencv2/highgui/highgui.hpp>

#include "converter.h"
#include "imgProcTaskExecutor.h"
#include <QTimer>

namespace my {
	class SceneContext : public QGraphicsScene {
		Q_OBJECT
	protected:
		cv::Mat frame;
		QGraphicsPixmapItem* _pixels;
		QTimer* timer;
		
		void update() {
			_pixels->setPixmap(Converter::Mat2QPixmap(frame));
		}

	public:
		ImgProcTaskExecutor executor;
		SceneContext(ImgProcTaskExecutor e) {
			executor = e;
			timer = new QTimer(this);
			connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
		};
		
		const QGraphicsPixmapItem* getPixels() {
			return _pixels;
		}

	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent* event) {}
		void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {}
		void mouseMoveEvent(QGraphicsSceneMouseEvent* event) {}

	private slots:
		virtual void updateFrame()=0;
	};
}

#endif
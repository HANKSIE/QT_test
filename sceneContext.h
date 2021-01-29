#ifndef SCENECONTEXT_H
#define SCENECONTEXT_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include <opencv2/highgui/highgui.hpp>

#include "converter.h"
#include "processExecutor.h"
#include "process.h"

namespace my {
	typedef Process<cv::Mat> ImageProcess;
	class SceneContext : public QGraphicsScene {
		
	protected:
		cv::Mat frame;
		QGraphicsPixmapItem* _pixels;
		QTimer* timer;
		
		void update() {
			_pixels->setPixmap(Converter::Mat2QPixmap(frame));
		}

	public:
		
		ProcessExecutor<cv::Mat> executor;
		SceneContext(ProcessExecutor<cv::Mat> executor):executor(executor) {}
		
		const QGraphicsPixmapItem* getPixels() {
			return _pixels;
		}
		/*
	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent* event) {}
		void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {}
		void mouseMoveEvent(QGraphicsSceneMouseEvent* event) {}
		*/
	};
}

#endif
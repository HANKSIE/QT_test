#ifndef SCENECONTEXT_H
#define SCENECONTEXT_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <opencv2/highgui/highgui.hpp>
#include "converter.h"
#include "imgProcTaskExecutor.h"

namespace my {
	class SceneContext : public QGraphicsScene {

	protected:
		cv::Mat frame;
		QGraphicsPixmapItem* _pixels;
		
		void update() {
			_pixels->setPixmap(Converter::Mat2QPixmap(frame));
		}

	public:
		ImgProcTaskExecutor executor;
		SceneContext(ImgProcTaskExecutor e) : executor(e) {};
		~SceneContext() { delete _pixels; };
		const QGraphicsPixmapItem* getPixels() {
			return _pixels;
		}
	};
}

#endif
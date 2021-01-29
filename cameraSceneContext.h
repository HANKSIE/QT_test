#ifndef CAMERASCENECONTEXT_H
#define CAMERASCENECONTEXT_H

#include <QTimer>
#include <opencv2/videoio/videoio.hpp>
#include "sceneContext.h"

namespace my {
	class CameraSceneContext : public SceneContext {

        Q_OBJECT
	private:
		cv::VideoCapture cap;

    protected slots:
        void updateFrame()
        {
            cap.read(frame);
            executor.run(frame);
            update();
        }

	public:
        CameraSceneContext(ProcessExecutor<cv::Mat> executor) : SceneContext(executor) {
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
        }
		bool open() {
            if (cap.isOpened()) {
                return true;
            }
            clear();
            if (!timer->isActive()) {
                cap.open(0);
                if (cap.isOpened()) {
                    _pixels = new QGraphicsPixmapItem();
                    addItem(_pixels);
                    updateFrame();
                    timer->start(20);
					return true;
                }
            }
			return false;
		}

        void close() {
            timer->stop();
            cap.release();
            clear();
            executor.resetProcesses();
        }
	};
}

#endif
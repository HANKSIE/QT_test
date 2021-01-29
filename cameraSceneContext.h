#ifndef CAMERASCENECONTEXT_H
#define CAMERASCENECONTEXT_H

#include <opencv2/videoio/videoio.hpp>
#include "sceneContext.h"

namespace my {
	class CameraSceneContext : public SceneContext {
        using SceneContext::SceneContext;
	private:
		cv::VideoCapture cap;

    protected slots:
        void updateFrame() override
        {
            cap.read(frame);
            executor.run(frame);
            update();
        }

	public:
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
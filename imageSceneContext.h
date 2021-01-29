#ifndef IMAGESCENECONTEXT_H
#define IMAGESCENECONTEXT_H

#include "sceneContext.h"

namespace my {
	class ImageSceneContext : public SceneContext {
		using SceneContext::SceneContext;
	public:
		bool load(std::string filePath) {

			frame = cv::imread(filePath);
			if (!frame.empty())
			{
				reset();
				_pixels = new QGraphicsPixmapItem();
				addItem(_pixels);
				update();
			}
			return !frame.empty();
		}

		void process(std::string task) {

			if (frame.data) {
				executor.task(task)->handle(frame);
				update();
			}
		}

		void reset() {
			clear();
			executor.resetTask();
		}
		
	};
}

#endif
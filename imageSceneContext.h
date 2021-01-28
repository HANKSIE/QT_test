#ifndef IMAGESCENECONTEXT_H
#define IMAGESCENECONTEXT_H

#include "sceneContext.h"

namespace my {
	class ImageSceneContext : public SceneContext {
		using SceneContext::SceneContext;
	public:
		bool load(std::string filePath) {

			clear();

			frame = cv::imread(filePath);
			if (!frame.empty())
			{
				_pixels = new QGraphicsPixmapItem();
				addItem(_pixels);
				update();
			}
			return !frame.empty();
		}

		void process(std::string task) {

			if (frame.data) {
				executor.runTask(task, frame);
				update();
			}
		}
	};
}

#endif
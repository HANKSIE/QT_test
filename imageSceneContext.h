#ifndef IMAGESCENECONTEXT_H
#define IMAGESCENECONTEXT_H

#include "sceneContext.h"

namespace my {
	class ImageSceneContext : public SceneContext {
		using SceneContext::SceneContext;
	private:
		cv::Mat origin;

	public:

		bool open(std::string filePath) {

			frame = cv::imread(filePath); 
			if (!frame.empty())
			{
				origin = frame.clone();
				_pixels = new QGraphicsPixmapItem();
				addItem(_pixels);
				update();
			}
			
			return !frame.empty();
		}

		void close() {
			clear();
			executor.resetProcesses();
		}
	};
}

#endif
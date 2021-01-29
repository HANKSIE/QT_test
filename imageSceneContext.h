#ifndef IMAGESCENECONTEXT_H
#define IMAGESCENECONTEXT_H

#include "sceneContext.h"

namespace my {
	class ImageSceneContext : public SceneContext {
		using SceneContext::SceneContext;
	protected slots:
		void updateFrame() override
		{
			executor.run(frame);
			update();
			frame = origin.clone();
		}
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
				timer->start(100);
				update();
			}
			
			return !frame.empty();
		}

		void close() {
			timer->stop();
			clear();
			executor.resetProcesses();
		}
	};
}

#endif
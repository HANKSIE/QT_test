#ifndef IMGPROCTASK_H
#define IMGPROCTASK_H

#include <opencv2/core/core.hpp>

namespace my {
	class ImgProcTask {
	protected:
		bool _isEnable = false;
	public:
		virtual void handle(const cv::Mat) {};
		virtual void reset() { disable(); };
		void enable() { _isEnable = true; };
		void disable() { _isEnable = false; };
		void turn() { _isEnable = !_isEnable; }
		bool isEnable() { return _isEnable; };
	};
}

#endif
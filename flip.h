#ifndef FLIP_H
#define FLIP_H

#include <opencv2/core/core.hpp>
#include "imgProcTask.h"

namespace my {
	class Flip : public ImgProcTask {
	private:
		int flipCode;

	public:
		Flip(int flipCode) :flipCode(flipCode) {};
		void handle(const cv::Mat m) override {
			cv::flip(m, m, flipCode);
		};
	};
}

#endif
#ifndef FLIP_H
#define FLIP_H

#include <opencv2/core/core.hpp>
#include "process.h"

namespace my {
	class Flip : public Process<cv::Mat> {
	private:
		int flipCode;

	public:
		Flip(int flipCode) :flipCode(flipCode) {};
		void define(const cv::Mat m) override {
			cv::flip(m, m, flipCode);
		};
	};
}

#endif
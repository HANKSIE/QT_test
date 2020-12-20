#include "opencv2/videoio/videoio.hpp"
#include <QTimer>
#include <qwidget.h>
#include <iostream>

using namespace cv;
namespace mylib  {
	class CameraWindow : public QWidget {
	private:
		VideoCapture cap;
		Mat frame;
		QTimer* timer;

	public:
		CameraWindow() {
			timer = new QTimer(this);
			//connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
			std::cout << "" << std::endl;
			timer->start(20);
		}

    public slots:
        void updatePicture()
        {
            cap >> frame;
        }
	};
}

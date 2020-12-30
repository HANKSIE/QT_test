#ifndef CONVERTER_H
#define CONVERTER_H

#include <opencv2/core.hpp>
#include <iostream>
#include <QString>
#include <QPixmap>

using namespace std;
using namespace cv;

namespace helper {
	class Converter {
	public:
		// �N string �ഫ�� QString
		static QString s2q(const string&);

		// �N QString �ഫ�� string
		static string q2s(const QString&);

		static QPixmap Mat2QPixmap(const Mat);
	};
}

#endif // CONVERTER_H

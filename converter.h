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
		// 將 string 轉換成 QString
		static QString s2q(const string&);

		// 將 QString 轉換成 string
		static string q2s(const QString&);

		static QPixmap Mat2QPixmap(const Mat);
	};
}

#endif // CONVERTER_H

#ifndef CONVERTER_H
#define CONVERTER_H


#include <iostream>
#include <QString>

using namespace std;

namespace helper {
	class Converter {
	public:
		// 將 string 轉換成 QString
		QString s2q(const string&);

		// 將 QString 轉換成 string
		string q2s(const QString&);
	};
}

#endif // CONVERTER_H

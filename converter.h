#ifndef CONVERTER_H
#define CONVERTER_H


#include <iostream>
#include <QString>

using namespace std;

namespace helper {
	class Converter {
	public:
		// �N string �ഫ�� QString
		QString s2q(const string&);

		// �N QString �ഫ�� string
		string q2s(const QString&);
	};
}

#endif // CONVERTER_H

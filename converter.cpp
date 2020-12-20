#include <converter.h>

using namespace helper;

QString Converter::s2q(const string& s) {
    return QString(QString::fromLocal8Bit(s.c_str()));
}

string Converter::q2s(const QString& s) {
    return string(static_cast<const char*>(s.toLocal8Bit()));
}
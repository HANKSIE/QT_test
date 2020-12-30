#include <converter.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace helper;
using namespace cv;

QString Converter::s2q(const string& s) {
    return QString(QString::fromLocal8Bit(s.c_str()));
}

string Converter::q2s(const QString& s) {
    return string(static_cast<const char*>(s.toLocal8Bit()));
}

QPixmap Converter::Mat2QPixmap(const Mat m) {
    cvtColor(m, m, COLOR_BGR2RGB);
    return QPixmap::fromImage(QImage((const unsigned char*)m.data, m.cols, m.rows, m.cols * m.channels(), QImage::Format_RGB888));
}
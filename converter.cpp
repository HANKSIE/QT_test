#include <converter.h>
#include <opencv2/imgproc/imgproc.hpp>

QString my::Converter::s2q(const string& s) {
    return QString(QString::fromLocal8Bit(s.c_str()));
}

string my::Converter::q2s(const QString& s) {
    return string(static_cast<const char*>(s.toLocal8Bit()));
}

QPixmap my::Converter::Mat2QPixmap(const cv::Mat m) {
    cv::cvtColor(m, m, cv::COLOR_BGR2RGB);
    return QPixmap::fromImage(QImage((const unsigned char*)m.data, m.cols, m.rows, m.cols * m.channels(), QImage::Format_RGB888));
}
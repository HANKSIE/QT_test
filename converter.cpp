#include <converter.h>
#include <opencv2/imgproc/imgproc.hpp>

QString my::Converter::s2q(const string& s) {
    return QString(QString::fromLocal8Bit(s.c_str()));
}

string my::Converter::q2s(const QString& s) {
    return string(static_cast<const char*>(s.toLocal8Bit()));
}

QPixmap my::Converter::Mat2QPixmap(const cv::Mat m) {
    cv::Mat clone = m.clone();
    cv::cvtColor(m, clone, cv::COLOR_BGR2RGB);
    return QPixmap::fromImage(QImage((const unsigned char*)clone.data, clone.cols, clone.rows, clone.cols * clone.channels(), QImage::Format_RGB888));
}
#ifndef CONVERTER_H
#define CONVERTER_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <QImage>

namespace Convert {

namespace CvMat {

    QImage toQImage(cv::Mat *mat, bool copy);

} // end namespace CvMat

namespace qImage {

    cv::Mat toCvMat(QImage *img, bool copy);

} // end namesapce QImage

} // end namespace Converter

#endif // CONVERTER_H

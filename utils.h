#ifndef UTILS_H
#define UTILS_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/traits.hpp>

#include <QImage>

namespace Utils {

namespace Convert {

namespace CvMat {

    QImage toQImage(cv::Mat *mat, bool copy);

} // end namespace CvMat

namespace qImage {

    cv::Mat toCvMat(QImage *img, bool copy);

} // end namesapce QImage

} // end namespace Converter

} // end namespace utils

#endif // UTILS_H

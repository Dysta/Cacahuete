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

    /**
     * @brief toQImage
     * @param mat a cv::Mat to convert into a QImage
     * @param copy bool to return a copy of the QImage
     * @return a QImage
     */
    QImage toQImage(cv::Mat *mat, bool copy);

} // end namespace CvMat

namespace qImage {

    /**
     * @brief toCvMat
     * @param img a QIMage to cv::Mat
     * @param copy bool to return a copy of the cv::Mat
     * @return a cv::Mat
     */
    cv::Mat toCvMat(QImage *img, bool copy);

} // end namesapce QImage

} // end namespace Converter

} // end namespace utils

#endif // UTILS_H

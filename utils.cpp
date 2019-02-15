#include "utils.h"

namespace Utils {

namespace Convert {

namespace CvMat {

    QImage toQImage(cv::Mat *mat, bool copy) {
        QImage::Format format;
        switch(mat->type()) {
            case CV_8U :{
                format = QImage::Format_Indexed8;
                break;
            }

            case CV_8UC4 :{
               format = QImage::Format_ARGB32;
               break;
            }
        }

        QImage img = QImage(mat->data, mat->cols, mat->rows, mat->step, format);
        return ( copy ) ? img.copy() : img ;
    }

            cv::Laplacian(grey, laplacian, CV_16S);
            cv::convertScaleAbs(laplacian, absLaplacian);
            return absLaplacian;
        }

        cv::Mat toSobel(cv::Mat mat, bool reduceNoise) {
            cv::Mat sobel, grey;
            /// Generate grad_x and grad_y
            cv::Mat gradX, absX;
            cv::Mat gradY, absY;
            // reduce noise by blurring and convert in greyscale
            if ( reduceNoise )
                cv::GaussianBlur(mat, mat, cv::Size(3,3), 0, 0);
            cv::cvtColor(mat, grey, cv::COLOR_BGR2GRAY);

            // Sobel gradient X
            cv::Sobel(grey, gradX, CV_16S, 1, 0);
            cv::convertScaleAbs(gradX, absX);

            // Sobel gradient Y
            cv::Sobel(grey, gradY, CV_16S, 0, 1);
            cv::convertScaleAbs(gradY, absY);

            // Total gradient
            cv::addWeighted(absX, 0.5, absY, 0.5, 0, sobel);
            return sobel;
        }

        cv::Mat toDisparity(cv::Mat mat, Convert::Mode mode) {
            cv::Mat gLeft, gRight, disp, disp8;

} // end namespace CvMat

namespace qImage {
    cv::Mat toCvMat(QImage *img, bool copy) {
        cv::Mat mat = cv::Mat(img->height(), img->width(), CV_8UC4, const_cast<uchar*>(img->bits()), img->bytesPerLine());
        return ( copy ) ? mat.clone() : mat ;
    }
} // end namespace qImage

} // end namespace Converter

} // end namespace utils


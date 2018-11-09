#include "utils.h"

namespace Utils {

namespace Convert {

namespace CvMat {

    QImage toQImage(cv::Mat *mat, bool copy) {
        QImage img = QImage(mat->data, mat->cols, mat->rows, mat->step, QImage::Format_ARGB32);
        return ( copy ) ? img.copy() : img ;
    }

    cv::Mat toLaplacian(cv::Mat mat, bool reduceNoise) {
        cv::Mat laplacian, grey, absLaplacian;
        // reduce noise by blurring and convert in greyscale
        if ( reduceNoise )
            cv::GaussianBlur(mat, mat, cv::Size(3,3), 0, 0);
        cv::cvtColor(mat, grey, cv::COLOR_BGR2GRAY);

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

        //régler le problème largeur impaire et expliquer pourquoi en commentaire
        cv::Mat left = mat.colRange(0, mat.cols/2);
        cv::Mat right = mat.colRange(mat.cols/2, mat.cols);

        cv::cvtColor(left, gLeft, CV_BGR2GRAY);
        cv::cvtColor(right, gRight, CV_BGR2GRAY);

        if(mode == Convert::Mode::SBM ){
            cv::StereoBM sbm(CV_STEREO_BM_BASIC, 112, 9);
            sbm(gLeft, gRight, disp);
        } else if(mode == Convert::Mode::SGBM){
            cv::StereoSGBM sgbm(-64, 192, 5, 600, 2400, 10, 4, 1, 150, 2, false);
            sgbm(gLeft, gRight, disp);
        }


        cv::normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

        return disp8;
    }

} // end namespace CvMat

namespace qImage {
    cv::Mat toCvMat(QImage *img, bool copy) {
        cv::Mat mat = cv::Mat(img->height(), img->width(), CV_8UC4, const_cast<uchar*>(img->bits()), img->bytesPerLine());
        return ( copy ) ? mat.clone() : mat ;
    }
} // end namespace qImage

} // end namespace Converter

} // end namespace utils


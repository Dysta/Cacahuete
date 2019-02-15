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
  
    void reconstructChess(cv::Mat mat, int columns, int lines){
            cv::Size patternSize(columns, lines);
            cv::Mat gray;
            //cv::Mat chess = new cv::Mat;
            cv::cvtColor(mat, gray, CV_BGR2GRAY);
            std::vector<cv::Point2f> corners;

            bool patternFound = cv::findChessboardCorners(gray, patternSize, corners);

            if(patternFound){
                cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
            }

            cv::drawChessboardCorners(mat, patternSize, cv::Mat(corners), patternFound);


        }

    } // end namespace CvMat

} // end namespace CvMat

namespace qImage {
    cv::Mat toCvMat(QImage *img, bool copy) {
        cv::Mat mat = cv::Mat(img->height(), img->width(), CV_8UC4, const_cast<uchar*>(img->bits()), img->bytesPerLine());
        return ( copy ) ? mat.clone() : mat ;
    }
} // end namespace qImage

} // end namespace Converter

} // end namespace utils


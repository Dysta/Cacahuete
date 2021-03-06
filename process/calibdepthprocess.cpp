#include "calibdepthprocess.h"
#include "mainwindow.h"

using namespace std;

CalibDepthProcess::CalibDepthProcess(MainWindow* parent, DisparityProcess* dispProcess)
    : _numCornersH(9), _numCornersV(6)
{
    this->_parent = parent;
    this->_dispProcess = dispProcess;
}

void CalibDepthProcess::calibration(QStringList sList, int numBoards, bool isVideo) {

    std::list<cv::Mat> matList;     // List of matrix of the given images
    cv::VideoCapture capture;

    if(isVideo){
        cout << sList.at(0).toStdString() << endl;
        capture = cv::VideoCapture(sList.at(0).toStdString());
    } else {

        QImage *tmpImage = new QImage();

        for(int c = 0; c < sList.size(); c++){  // We give to matList all the images
            tmpImage->load(sList.at(c));
            cv::Mat tmpMat = Utils::Convert::qImage::toCvMat(tmpImage, true);
            matList.push_back(tmpMat);
        }
    }

    cv::Size boardSize = cv::Size(this->_numCornersH, this->_numCornersV);    // The size of the chessboard

    vector<vector<cv::Point3f>> objectPoints;   // Points in a 3D space
    std::vector<std::vector<cv::Point2f>> imagePoints;  // Points on the image (2D)
    std::vector<cv::Point2f> corners;   // Corners of the chessboard
    int successes = 0;  // Number of images skipped
    int numSquares = this->_numCornersH * this->_numCornersV; // Total number of squares

    cv::Mat image;  // Current image
    cv::Mat grayImage;  // Image converted to a gray scale image
    vector<cv::Point3f> obj;    // Points of the chessboard in the current image

    if(isVideo){
        capture >> image;
    } else {
        image = matList.front();    // Getting the first image
    }

    // Entering pattern searching loop
    while(successes < numBoards){
        // Convert the image to a gray scale image
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
        // Refreshing image
        if(!isVideo)
            image = matList.front();
        // Searching for a pattern
        bool patternFound = cv::findChessboardCorners(grayImage, boardSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);


        if  (patternFound){
            // If a pattern is found, keep it and draw the current points of the chessboard
            cv::cornerSubPix(grayImage, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            cv::drawChessboardCorners(grayImage, boardSize, corners, patternFound);

            obj.clear();
            for(int x = 0; x < this->_numCornersV; x++){
                for(int y = 0; y < this->_numCornersH; y++){
                    obj.push_back(cv::Point3f((float)y * numSquares, (float)x * numSquares, 0));
                }
            }

            imagePoints.push_back(corners);
            objectPoints.push_back(obj);
            cout << "Snap stored!" << endl;
            successes++;
            if(isVideo)
                capture >> image;
            else
                matList.pop_front();
            if(successes>=numBoards)
                break;
        } else {
            // Else find another pattern
            cout << "Snap skipped" << endl;
            successes++;
            if(isVideo)
                capture >> image;
            else
                matList.pop_front();
            if(successes>=numBoards)
                break;
        }
    }
    std::vector<cv::Mat> rvecs;
    std::vector<cv::Mat> tvecs;

    cv::Mat newIntrinsic;
    cv::Mat newDistCoeffs;

    // Do the calibration with the parameters
    if(imagePoints.size() < 2){
        QMessageBox::warning(this->_parent, "Erreur", "Calibration echouee.\nVous avez probablement entre de mauvaises coordonnees pour l'echiquier, ou vous avez charge pas assez d'images.");
        return;
    }

    cv::calibrateCamera(objectPoints, imagePoints, image.size(), newIntrinsic, newDistCoeffs, rvecs, tvecs);

    this->setIntrisic(newIntrinsic);
    this->setDistCoeffs(newDistCoeffs);

    QMessageBox::warning(this->_parent, "Termine", "Calibration terminee !");

}

void CalibDepthProcess::setImage(int value){
    switch (value){
        case 0:
            {
                QImage left = *this->_parent->getOriginalLeftPicture();
                this->_parent->setLeftPicture(left);
                break;
            }
        case 1:
            {
                QImage right = *this->_parent->getOriginalRightPicture();
                this->_parent->setLeftPicture(right);
                break;
            }
    }
    this->_parent->updateImage();
}

void CalibDepthProcess::undistort(){

    if(this->_intrinsic.empty() && this->_distcoeffs.empty()){
        QMessageBox::warning(this->_parent, "Erreur", "Veuillez d'abord recuperer les donnees de calibration !");
        return;
    }

    cv::Mat mat = Utils::Convert::qImage::toCvMat(this->_parent->getLeftPicture(), true);
    cv::Mat imageUndistored;

    // Undistort the current frame
    cv::undistort(mat, imageUndistored, this->_intrinsic, this->_distcoeffs);
    QImage pic = Utils::Convert::CvMat::toQImage(&imageUndistored, true);
    this->_parent->setRightPicture(pic);
    this->_parent->updateImage();
}

void CalibDepthProcess::stereoCalib(QStringList sList, int numBoards, bool isVideo){

    std::list<cv::Mat> matListL, matListR, matList2;     // List of matrix of the given images
    cv::VideoCapture capture;

    if(isVideo){
        cout << sList.at(0).toStdString() << endl;
        capture = cv::VideoCapture(sList.at(0).toStdString());
    } else {

        QImage *tmpImageL = new QImage();
        QImage *tmpImageR = new QImage();

        for(int c = 0; c < sList.size()/2; c++){  // We give to matList all the images
            tmpImageL->load(sList.at(c));
            cv::Mat tmpMatL = Utils::Convert::qImage::toCvMat(tmpImageL, true);
            matListL.push_back(tmpMatL);
            tmpImageR->load(sList.at(c + sList.size()/2));
            cv::Mat tmpMatR = Utils::Convert::qImage::toCvMat(tmpImageR, true);
            matListR.push_back(tmpMatR);
            matList2.push_back(tmpMatL);
            matList2.push_back(tmpMatR);
        }
    }

    cv::Size boardSize = cv::Size(this->_numCornersH, this->_numCornersV);    // The size of the chessboard

    vector<vector<cv::Point3f>> objectPoints;   // Points in a 3D space
    std::vector<std::vector<cv::Point2f>> imagePoints1, imagePoints2;  // Points on the image (2D)
    std::vector<cv::Point2f> cornersL, cornersR;   // Corners of the chessboard

    int successes = 0;  // Number of images skipped
    int numSquares = this->_numCornersH * this->_numCornersV;; // Total number of squares

    cv::Mat imageL, imageR;  // Current image
    cv::Mat grayImageL, grayImageR;  // Image converted to a gray scale image
    vector<cv::Point3f> obj;    // Points of the chessboard in the current image

    // Entering pattern searching loop

    while(successes < numBoards/2){
        cout << "Snap number : " << successes +1 << " & " << successes+1+numBoards/2 << endl;

        // Refreshing image


        if(!isVideo){
            imageL = matListL.front();
            imageR = matListR.front();
        } else {
            capture >> imageL;
        }

        // Convert the image to a gray scale image
        cv::cvtColor(imageL, grayImageL, cv::COLOR_BGR2GRAY);
        cv::cvtColor(imageR, grayImageR, cv::COLOR_BGR2GRAY);

        // Searching for a pattern
        bool patternFoundL = cv::findChessboardCorners(grayImageL, boardSize, cornersL, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);
        bool patternFoundR = cv::findChessboardCorners(grayImageR, boardSize, cornersR, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);


        if  (patternFoundL && patternFoundR){
            // If a pattern is found, keep it and draw the current points of the chessboard
            cv::cornerSubPix(grayImageL, cornersL, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            cv::drawChessboardCorners(grayImageL, boardSize, cornersL, patternFoundL);
            cv::cornerSubPix(grayImageR, cornersR, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            cv::drawChessboardCorners(grayImageR, boardSize, cornersR, patternFoundR);

            obj.clear();
            for(int x = 0; x < this->_numCornersV; x++){
                for(int y = 0; y < this->_numCornersH; y++){
                    obj.push_back(cv::Point3f((float)y * numSquares, (float)x * numSquares, 0));
                }
            }

            imagePoints1.push_back(cornersL);
            imagePoints2.push_back(cornersR);
            objectPoints.push_back(obj);
            cout << "Snap stored!" << endl;
            successes++;
            if(isVideo)
                capture >> imageL;
            else {
                matListL.pop_front();
                matListR.pop_front();
            }
            if(successes>=numBoards)
                break;
        } else {
            // Else find another pattern
            cout << "!!! SNAP SKIPPED !!!" << endl;
            successes++;
            if(isVideo)
                capture >> imageL;
            else {
                matListL.pop_front();
                matListR.pop_front();
            }
            if(successes>=numBoards)
                break;
        }
    }

    cout << imagePoints1.size() << " " << imagePoints2.size() << endl;

    cv::Mat image = matList2.front();
    matList2.pop_front();
    imageR = matList2.front();

    if(imagePoints1.size() < 2 || imagePoints2.size() < 2){
        QMessageBox::warning(this->_parent, "Erreur", "Calibration echouee.\nVous avez probablement entre de mauvaises coordonnees pour l'echiquier, ou vous avez charge pas assez d'images.");
        return;
    }

    cv::Mat intrinsic1, intrinsic2, distcoeffs1, distcoeffs2, R, T, E, F;
    cv::stereoCalibrate(objectPoints, imagePoints1, imagePoints2, intrinsic1, distcoeffs1, intrinsic2, distcoeffs2, image.size(), R, T, E, F);


    cv::Mat R1, R2, P1, P2, Q;
    cv::stereoRectify(intrinsic1, distcoeffs1, intrinsic2, distcoeffs2, image.size(), R, T, R1, R2, P1, P2, Q);


    cv::Mat map1, map2;
    cv::initUndistortRectifyMap(intrinsic1, distcoeffs1, R1, P1, image.size(), CV_32FC1, map1, map2);


    QString file = QFileDialog::getSaveFileName(this->_parent, "Enregistrer les parametres", "", "File (*.json)");

    if (!file.isEmpty()) {
        if (!file.contains(".json"))
            file.append(".json");
        cv::FileStorage fs = cv::FileStorage(file.toStdString(), cv::FileStorage::WRITE | cv::FileStorage::FORMAT_JSON);

        this->setQ(Q);
        this->setMaps(map1, map2);

        fs.write("map1", map1);
        fs.write("map2", map2);
        fs.write("Q", Q);

        fs.release();
    }

    QMessageBox::information(this->_parent, "Termine", "Calibration terminee !");

}


void CalibDepthProcess::depthMap(){

    if(this->_map1.empty() && this->_map2.empty() && this->_Q.empty()){
        QMessageBox::warning(this->_parent, "Erreur", "Veuillez d'abord recuperer les donnees de calibration !");
        return;
    }

    cv::Mat left = Utils::Convert::qImage::toCvMat(this->_parent->getOriginalLeftPicture(), true);
    cv::Mat right = Utils::Convert::qImage::toCvMat(this->_parent->getOriginalRightPicture(), true);

    cv::Mat depthMap = this->depthMap(left, right);

    QImage pic = Utils::Convert::CvMat::toQImage(&depthMap, true);
    this->_parent->setPictureDepth(pic);
    this->_parent->updateImage();

    cv::imshow("Carte de profondeur", depthMap);
}

cv::Mat CalibDepthProcess::depthMap(cv::Mat left, cv::Mat right){

    if(this->_map1.empty() && this->_map2.empty() && this->_Q.empty()){
        QMessageBox::warning(this->_parent, "Erreur", "Veuillez d'abord recuperer les donnees de calibration !");
        return cv::Mat();
    }

    if(this->_useRemap){
        cv::Mat correctedImgL, correctedImgR;
        cv::remap(left, correctedImgL, this->_map1, this->_map2, cv::INTER_LINEAR);
        cv::remap(right, correctedImgR, this->_map1, this->_map2, cv::INTER_LINEAR);
        left = correctedImgL;
        right = correctedImgR;
    }


    cv::Mat disp = this->_dispProcess->process(left, right);

    cv::Mat depthMap3Chans;

    cv::reprojectImageTo3D(disp, depthMap3Chans, this->_Q);


//    this->_parent->_trackBox->_process->process(depthMap3Chans);

    vector<cv::Mat> channels(3);
    cv::split(depthMap3Chans, channels);
    cv::Mat depthMap = channels[2];

    this->_parent->setMatDepth(depthMap);

    return depthMap;
}

void CalibDepthProcess::setUseRemap(bool useRemap)
{
    _useRemap = useRemap;
}

void CalibDepthProcess::loadParam(){
    QString file = QFileDialog::getOpenFileName(this->_parent,
                                                "Sélectionnez le fichier contenant les parametres",
                                                "",
                                                "JSON File (*.json)",
                                                NULL,
                                                QFileDialog::ReadOnly
                                                );

    if (file.isEmpty()) return;

    cv::FileStorage fs;

    try {
        fs = cv::FileStorage(file.toStdString(), cv::FileStorage::READ | cv::FileStorage::FORMAT_JSON);
    } catch (const cv::Exception e) {
        Q_UNUSED(e);
        QMessageBox::critical(this->_parent, "Erreur", "Impossible d'ouvrir le fichier");
        return;
    }

    if(!fs.isOpened()){
        QMessageBox::critical(this->_parent, "Erreur", "Erreur dans l'ouverture du fichier");
        return;
    }

    try {
        cv::FileNode map1Node = fs["map1"];
        cv::FileNode map2Node = fs["map2"];
        cv::FileNode QNode = fs["Q"];

        cv::Mat map1 = map1Node.mat();
        cv::Mat map2 = map2Node.mat();
        cv::Mat Q = QNode.mat();

        this->setMaps(map1, map2);
        this->setQ(Q);
    } catch (const cv::Exception e) {
        QMessageBox::critical(this->_parent, "Erreur", e.what());
        return;
    }

    fs.release();

    QMessageBox::information(this->_parent, "Termine", "Parametres charges avec succes.");
}

void CalibDepthProcess::setNumCornersH(int value){
    this->_numCornersH = value;
}

void CalibDepthProcess::setNumCornersV(int value){
    this->_numCornersV = value;
}

void CalibDepthProcess::setIntrisic(cv::Mat mat){
    this->_intrinsic = mat;
}

void CalibDepthProcess::setDistCoeffs(cv::Mat mat){
    this->_distcoeffs = mat;
}

void CalibDepthProcess::setQ(cv::Mat mat){
    this->_Q = mat;
}

void CalibDepthProcess::setMaps(cv::Mat map1, cv::Mat map2){
    this->_map1 = map1;
    this->_map2 = map2;
}

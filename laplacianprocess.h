#ifndef LAPLACIANPROCESS_H
#define LAPLACIANPROCESS_H

#include <iostream>


class LaplacianProcess
{
public:
    LaplacianProcess();
    void setActiveBlur(bool state);
    void setSizeH(int value);
    void setSizeL(int value);
    void setSigmaX(int value);
    void setSigmaY(int value);

private:
    void updatePicture(void);

    bool _activeBlur;
    int _sizeH;
    int _sizeL;
    int _sigmaX;
    int _sigmaY;
};

#endif // LAPLACIANPROCESS_H

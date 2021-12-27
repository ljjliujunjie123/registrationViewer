//
// Created by 19956875375 on 2021/12/15.
//

#ifndef REGISTRATIONVIEWER_IMAGESHOWNCONTROLLER_H
#define REGISTRATIONVIEWER_IMAGESHOWNCONTROLLER_H
#include "qboxlayout.h"
#include <QFrame>
#include <QSize>
#include "ImageShownWidget.h"

using namespace std;

class ImageShownController {

public:
    ImageShownController(QWidget* parent);

    void showFirstImage(string dirPath);

    void showSecondImage(string dirPath);

    void showResImage(string dirPath);

private:
    ImageShownWidget* preImageOne = new ImageShownWidget();

    ImageShownWidget* preImageTwo = new ImageShownWidget();

    ImageShownWidget* resImage = new ImageShownWidget();

};


#endif //REGISTRATIONVIEWER_IMAGESHOWNCONTROLLER_H

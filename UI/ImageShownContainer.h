//
// Created by 19956875375 on 2021/12/15.
//

#ifndef REGISTRATIONVIEWER_IMAGESHOWNCONTAINER_H
#define REGISTRATIONVIEWER_IMAGESHOWNCONTAINER_H
#include "qboxlayout.h"
#include <QFrame>
#include <QSize>
#include "ImageShownWidget.h"

using namespace std;

class ImageShownContainer: public QFrame {

public:
    ImageShownContainer(QWidget *parent = nullptr);

    void showFirstImage(string dirPath);

    void showSecondImage(string dirPath);

    void showResImage(string dirPath);

private:
    ImageShownWidget* preImageOne = new ImageShownWidget(this);

    ImageShownWidget* preImageTwo = new ImageShownWidget(this);

    ImageShownWidget* resImage = new ImageShownWidget(this);

};


#endif //REGISTRATIONVIEWER_IMAGESHOWNCONTAINER_H

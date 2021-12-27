//
// Created by 19956875375 on 2021/12/15.
//

#include "ImageShownContainer.h"
#include <vtkAutoInit.h>
ImageShownContainer::ImageShownContainer(QWidget *parent) {
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);

    auto hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(10);

    auto vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(10);

    vLayout->addWidget(preImageOne);
    vLayout->addWidget(preImageTwo);

    hLayout->addLayout(vLayout);
    hLayout->addWidget(resImage);
    this->setLayout(hLayout);
}

void ImageShownContainer::showFirstImage(string dirPath) {
    preImageOne->showImageFromDir(dirPath);
}

void ImageShownContainer::showSecondImage(string dirPath) {
    preImageTwo->showImageFromDir(dirPath);
}

void ImageShownContainer::showResImage(string dirPath) {
    resImage->showImageFromDir(dirPath);
}

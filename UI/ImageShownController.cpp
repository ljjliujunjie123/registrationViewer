//
// Created by 19956875375 on 2021/12/15.
//

#include "ImageShownController.h"
#include <vtkAutoInit.h>
ImageShownController::ImageShownController(QWidget* parent) {
    preImageOne->setParent(parent);
    preImageTwo->setParent(parent);
    resImage->setParent(parent);

    preImageOne->hide();
    preImageTwo->hide();
    resImage->hide();
}

void ImageShownController::showFirstImage(string dirPath) {
    preImageOne->showImageFromDir(dirPath);
    preImageOne->setWindowTitle("待匹配图像");
}

void ImageShownController::showSecondImage(string dirPath) {
    preImageTwo->showImageFromDir(dirPath);
    preImageTwo->setWindowTitle("目标匹配图像");
}

void ImageShownController::showResImage(string dirPath) {
    resImage->showImageFromDir(dirPath);
    resImage->setWindowTitle("匹配结果");
}

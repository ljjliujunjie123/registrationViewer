//
// Created by 19956875375 on 2021/12/27.
//

#ifndef REGISTRATIONVIEWER_IMAGESHOWNWIDGET_H
#define REGISTRATIONVIEWER_IMAGESHOWNWIDGET_H
#pragma once

#include <vtkAutoInit.h>
#include <vtkRenderer.h>
#include <QVTKOpenGLNativeWidget.h>
#include <iostream>
#include <vtkPiecewiseFunction.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include<vtkSmartPointer.h>

using namespace std;

class ImageShownWidget : public  QVTKOpenGLNativeWidget {
    Q_OBJECT
public:
    explicit ImageShownWidget(QWidget* parent = nullptr);

    void showImageFromDir(string dirPath);
};

#endif //REGISTRATIONVIEWER_IMAGESHOWNWIDGET_H
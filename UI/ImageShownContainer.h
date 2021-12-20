//
// Created by 19956875375 on 2021/12/15.
//

#ifndef REGISTRATIONVIEWER_IMAGESHOWNCONTAINER_H
#define REGISTRATIONVIEWER_IMAGESHOWNCONTAINER_H

#include <QFrame>
#include <QSize>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

class ImageShownContainer: public QFrame {

public:
    ImageShownContainer(QWidget *parent = nullptr);

};


#endif //REGISTRATIONVIEWER_IMAGESHOWNCONTAINER_H

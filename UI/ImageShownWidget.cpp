//
// Created by 19956875375 on 2021/12/27.
//
#include "ImageShownWidget.h"
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkNIFTIImageReader.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

ImageShownWidget::ImageShownWidget(QWidget* parent)
    :QVTKOpenGLNativeWidget(parent){

}

void ImageShownWidget::showImageFromDir(string path) {
//    dirPath = "/Users/zzy/Downloads/tes/Body_CT_202";
//    vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkNIFTIImageReader>  reader = vtkSmartPointer<vtkNIFTIImageReader>::New();
//    reader->SetDirectoryName(dirPath.c_str());
    reader->SetFileName(path.c_str());
    reader->Update();

    int imageDims[3];
    reader->GetOutput()->GetDimensions(imageDims);
    cout << "dimension[] :" << imageDims[0] << " " << imageDims[1] << " " << imageDims[2] << endl;

    vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
    cast->SetInputData((vtkDataObject*)reader->GetOutput());
    cast->SetOutputScalarTypeToFloat();
    cast->SetOutputScalarTypeToUnsignedChar();
    cast->Update();

    vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper>::New();
//    基于GPU加速的光线投射体绘制算法
    volumeMapper->SetInputData(cast->GetOutput());
    volumeMapper->SetImageSampleDistance(1.0);
    volumeMapper->SetSampleDistance(1.0);
    volumeMapper->SetAutoAdjustSampleDistances(1);

    vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();//定义对象属性
    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(0.4);
    volumeProperty->SetDiffuse(0.6);
    volumeProperty->SetSpecular(0.2);

    vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
    //Defines a piecewise function mapping.
    compositeOpacity->AddPoint(60, 0.00);
    compositeOpacity->AddPoint(140, 0.40);
    compositeOpacity->AddPoint(180, 0.90);

    volumeProperty->SetScalarOpacity(compositeOpacity);

    vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
    color->AddRGBPoint(0, 0, 0, 0);
    color->AddRGBPoint(64, 1, 0.52, 0.30);
    color->AddRGBPoint(190.0, 1, 1, 1);
    color->AddRGBPoint(220, 0.2, 0.2, 0.2);

    volumeProperty->SetColor(color);

    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);

    vtkSmartPointer<vtkRenderer> rendererVolume = vtkSmartPointer<vtkRenderer>::New();

    rendererVolume->AddVolume(volume);
    renderWindow->AddRenderer(rendererVolume);
    iren->SetRenderWindow(renderWindow);

    renderWindow->Render();
    iren->Start();
}

void ImageShownWidget::setWindowTitle(char* title) {
    renderWindow.Get()->SetWindowName(title);
}

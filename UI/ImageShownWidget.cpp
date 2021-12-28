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
    volumeProperty->SetSpecularPower(1);// 高光强度

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

void ImageShownWidget::showRegistrationImage(string resPath) {
//    moving 图像
    vtkSmartPointer<vtkNIFTIImageReader>  readerRes = vtkSmartPointer<vtkNIFTIImageReader>::New();
//    reader->SetDirectoryName(dirPath.c_str());
    readerRes->SetFileName(resPath.c_str());
    readerRes->Update();

    int imageDims[3];
    readerRes->GetOutput()->GetDimensions(imageDims);
    cout << "dimension[] :" << imageDims[0] << " " << imageDims[1] << " " << imageDims[2] << endl;

    vtkSmartPointer<vtkImageCast> castRes = vtkSmartPointer<vtkImageCast>::New();
    castRes->SetInputData((vtkDataObject*)readerRes->GetOutput());
    castRes->SetOutputScalarTypeToFloat();
    castRes->SetOutputScalarTypeToUnsignedChar();
    castRes->Update();

    vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper> volumeMapperRes = vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper>::New();
//    基于GPU加速的光线投射体绘制算法
    volumeMapperRes->SetInputData(castRes->GetOutput());
    volumeMapperRes->SetImageSampleDistance(1.0);
    volumeMapperRes->SetSampleDistance(1.0);
    volumeMapperRes->SetAutoAdjustSampleDistances(1);

    vtkSmartPointer<vtkVolumeProperty> volumePropertyRes = vtkSmartPointer<vtkVolumeProperty>::New();//定义对象属性
    volumePropertyRes->SetInterpolationTypeToLinear();
    volumePropertyRes->ShadeOn();
    volumePropertyRes->SetAmbient(0.4);
    volumePropertyRes->SetDiffuse(0.6);
    volumePropertyRes->SetSpecular(0.2);
    volumePropertyRes->SetSpecularPower(1);// 高光强度

    vtkSmartPointer<vtkPiecewiseFunction> compositeOpacityRes = vtkSmartPointer<vtkPiecewiseFunction>::New();
    //Defines a piecewise function mapping.
    compositeOpacityRes->AddPoint(60, 0.00);
    compositeOpacityRes->AddPoint(140, 0.40);
    compositeOpacityRes->AddPoint(230, 0.60);

    volumePropertyRes->SetScalarOpacity(compositeOpacityRes);

    vtkSmartPointer<vtkColorTransferFunction> colorRes = vtkSmartPointer<vtkColorTransferFunction>::New();
    colorRes->AddRGBPoint(0, 0, 0, 0);
    colorRes->AddRGBPoint(64, 1, 0.52, 0.30);
    colorRes->AddRGBPoint(190.0, 1, 1, 1);
    colorRes->AddRGBPoint(220, 0.2, 0.2, 0.2);

    volumePropertyRes->SetColor(colorRes);

    vtkSmartPointer<vtkVolume> volumeRes = vtkSmartPointer<vtkVolume>::New();
    volumeRes->SetMapper(volumeMapperRes);
    volumeRes->SetProperty(volumePropertyRes);

//    fix 图像
    vtkSmartPointer<vtkNIFTIImageReader>  readerMov = vtkSmartPointer<vtkNIFTIImageReader>::New();
    readerMov->SetFileName(fixImagePath.c_str());
    readerMov->Update();

    int imageDims_[3];
    readerMov->GetOutput()->GetDimensions(imageDims_);
    cout << "dimension[] :" << imageDims_[0] << " " << imageDims_[1] << " " << imageDims_[2] << endl;

    vtkSmartPointer<vtkImageCast> castMov = vtkSmartPointer<vtkImageCast>::New();
    castMov->SetInputData((vtkDataObject*)readerMov->GetOutput());
    castMov->SetOutputScalarTypeToFloat();
    castMov->SetOutputScalarTypeToUnsignedChar();
    castMov->Update();

    vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper> volumeMapperMov = vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper>::New();
//    基于GPU加速的光线投射体绘制算法
    volumeMapperMov->SetInputData(castMov->GetOutput());
    volumeMapperMov->SetImageSampleDistance(1.0);
    volumeMapperMov->SetSampleDistance(1.0);
    volumeMapperMov->SetAutoAdjustSampleDistances(1);

    vtkSmartPointer<vtkVolumeProperty> volumePropertyMov = vtkSmartPointer<vtkVolumeProperty>::New();//定义对象属性
    volumePropertyMov->SetInterpolationTypeToLinear();
    volumePropertyMov->ShadeOn();
    volumePropertyMov->SetAmbient(0.4);
    volumePropertyMov->SetDiffuse(0.6);
    volumePropertyMov->SetSpecular(0.2);
    volumePropertyMov->SetSpecularPower(1);// 高光强度

    vtkSmartPointer<vtkPiecewiseFunction> compositeOpacityMov = vtkSmartPointer<vtkPiecewiseFunction>::New();
    //Defines a piecewise function mapping.
    compositeOpacityMov->AddPoint(60, 0.00);
    compositeOpacityMov->AddPoint(140, 0.40);
    compositeOpacityMov->AddPoint(230, 0.60);

    volumePropertyMov->SetScalarOpacity(compositeOpacityRes);

    vtkSmartPointer<vtkColorTransferFunction> colorMov = vtkSmartPointer<vtkColorTransferFunction>::New();
    colorMov->AddRGBPoint(0, 0, 0, 0);
    colorMov->AddRGBPoint(64, 1, 0.52, 0.30);
    colorMov->AddRGBPoint(190.0, 1, 1, 1);
    colorMov->AddRGBPoint(220, 0.2, 0.2, 0.2);

    volumePropertyMov->SetColor(colorMov);

    vtkSmartPointer<vtkVolume> volumeMov = vtkSmartPointer<vtkVolume>::New();
    volumeMov->SetMapper(volumeMapperMov);
    volumeMov->SetProperty(volumePropertyMov);

    vtkSmartPointer<vtkRenderer> rendererVolume = vtkSmartPointer<vtkRenderer>::New();

    rendererVolume->AddVolume(volumeRes);
    rendererVolume->AddVolume(volumeMov);
    renderWindow->AddRenderer(rendererVolume);
    iren->SetRenderWindow(renderWindow);

    renderWindow->Render();
    iren->Start();
}

#ifndef EDIT_OPENCV_H
#define EDIT_OPENCV_H
#include "mainwindow_OpenCV.h"
#include "ui_mainwindow_OpenCV.h"
#include <QMainWindow>
#include <math.h>
#include <QtMath>
#include <QCameraImageProcessing>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
QImage Brightness (Mat image, int sliderPos);
QImage Contrast (Mat image, int sliderPos);
QImage Color (Mat image, int sliderPos);
QImage Hue (Mat image, int sliderPos);
QImage Sharpness (Mat image, int sliderPos);
QImage Resize (Mat image, int sliderPos);
QImage Mat2QImage (cv::Mat src);

#endif // EDIT_OPENCV_H

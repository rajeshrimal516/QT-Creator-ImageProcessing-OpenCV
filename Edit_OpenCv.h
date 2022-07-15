/**
 * @file Edit_OpenCv.h
 * @author Rajesh Rimal (rajeshrimal516@gmail.com)
 * @brief Header file for the image propcessing functions in Edit_OpenCv.cpp
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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


/**********************************************************************************
 * @brief Function for changing the brightness in the image
 * 
 * @param inImage Image in cv Mat format
 * @param sliderPos Position of the slider from (-100 to 100)
 * @return QImage
 *********************************************************************************/
QImage Brightness (Mat image, int sliderPos);



/**********************************************************************************
 * Function for changing the Contrast in the image
 * 
 * @param inImage Image in cv Mat format
 * @param sliderPos Position of the slider from (-100 to 100)
 * @return QImage 
 *********************************************************************************/
QImage Contrast (Mat image, int sliderPos);



/**********************************************************************************
 * @brief Function for changing the Color in the image
 * 
 * @param image Image in cv Mat format
 * @param sliderPos Position of the slider from (-100 to 100)
 * @return QImage 
 *********************************************************************************/
QImage Color (Mat image, int sliderPos);



/**********************************************************************************
 * @brief Function for changing the Hue in the image
 * 
 * @param image Image in cv Mat format
 * @param sliderPos Position of the slider from (-100 to 100)
 * @return QImage 
 *********************************************************************************/
QImage Hue (Mat image, int sliderPos);



/**********************************************************************************
 * @brief Function for sharpning or bluring the image
 * 
 * @param image Image in cv Mat format
 * @param sliderPos Position of the slider from (-100 to 100)
 * @return QImage 
 *********************************************************************************/
QImage Sharpness (Mat image, int sliderPos);



/**********************************************************************************
 * @brief Function for resizing the image
 * 
 * @param image Image in cv Mat format
 * @param sliderPos Position of the slider from (-100 to 100)
 * @return QImage 
 **********************************************************************************/
QImage Resize (Mat image, int sliderPos);



/**********************************************************************************
 * @brief Function for converting Mat format to QImage
 * 
 * @param inImage Image in cv Mat format
 * @return QImage 
 *********************************************************************************/
QImage Mat2QImage (cv::Mat inImage);/

#endif // EDIT_OPENCV_H

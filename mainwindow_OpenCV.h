#ifndef MAINWINDOW_OPENCV_H
#define MAINWINDOW_OPENCV_H

#include <QMainWindow>
#include "ui_mainwindow_OpenCV.h"
#include "Edit_OpenCv.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>
#include <QFile>
#include <QDebug>
#include <QThread>
#include <QIODevice>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QAction>
#include <QDateTime>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QMessageBox>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/mat.hpp"
#include <QElapsedTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void onToggleFullScreen(bool fs);

    ~MainWindow();

private slots:

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionBrightess_triggered();

    void on_Upload_clicked();

    void on_Brightness_clicked();

    void on_actionContrast_triggered();

    void on_actionColor_triggered();

    void on_Contrast_clicked();

    void on_Color_clicked();

    void on_horizontalSlider_valueChanged(int sliderPos);

    void on_actionHue_triggered();

    void on_Hue_clicked();

    void on_Sharpness_clicked();

    void on_Resize_clicked();

    void on_actionSharpness_triggered();

    void on_actionResize_triggered();

    void on_actionImage_Display_triggered(QPixmap image);

    void on_Save_clicked();

    void on_Exit_clicked();

    void on_Camera_clicked();

    void on_Tab_tabBarClicked(int index);

    void on_actionUpload_Image_triggered();

public:
     Ui::MainWindow *ui;


private:
     QCamera* mCam;
     QCameraViewfinder* mCamvf;
     QCameraImageCapture* mCamCap;
     QVBoxLayout *mLayout;

     QPixmap original_img;
     QPixmap converted_original_img;
     QPixmap processed_img;

     QString filename_open;
     QString filename_save;
     QString filename_copy;
     QElapsedTimer timer;

     QImage Image;

     cv::Mat original_matrix;
     cv::Mat processed_matrix;
     cv::Mat show_matrix;

     int edit_mode;
     bool ismodified=false;
};
#endif // MAINWINDOW_OPENCV_H

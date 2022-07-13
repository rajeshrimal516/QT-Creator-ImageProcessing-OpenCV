#include "Edit_OpenCv.h"
QElapsedTimer timer;
using namespace cv;
using namespace std;
QImage Brightness(Mat image , int sliderPos)
{
    Mat new_image = Mat::zeros(image.size(), image.type());
    double factor = sliderPos * 2;
    timer.start();
    for(int rowIdx = 0; rowIdx < image.rows; rowIdx++)
    {
        for(int colIdx = 0; colIdx < image.cols; colIdx++)
        {
            for(int c = 0; c < image.channels(); c++)
            {
                new_image.at<Vec3b>(rowIdx,colIdx)[c] = saturate_cast<uchar>(image.at<Vec3b>(rowIdx,colIdx)[c] + factor);
            }
         }
     }
    qDebug()<<"Brightness Loop Exectuion Time: "<< timer.elapsed()<<endl;
    cvtColor(new_image, new_image,COLOR_BGR2RGB);
    QImage final = Mat2QImage(new_image);
    return final;
}

QImage Contrast (Mat image, int sliderPos)
{
    Mat new_image = Mat::zeros(image.size(), image.type() );
    double factor = (double)(259*(255+(sliderPos)))/(255*(259-(sliderPos)));
    timer.start();
    for(int rowIdx = 0; rowIdx < image.rows; rowIdx++)
    {
        for(int colIdx = 0; colIdx < image.cols; colIdx++)
        {
            for(int c = 0; c < image.channels(); c++)
            {
                new_image.at<Vec3b>(rowIdx,colIdx)[c] = saturate_cast<uchar>(factor*(image.at<Vec3b>(rowIdx,colIdx)[c]-128)+128);
            }
        }
    }
    qDebug()<<"Contrast Loop Exectuion Time: "<< timer.elapsed()<<endl;
    cvtColor(new_image, new_image,COLOR_BGR2RGB);
    QImage final = Mat2QImage(new_image);
    return final;
}

QImage Color(Mat image, int sliderPos)
{

    Mat hsv = Mat::zeros(image.size(), image.type());
    Mat new_image = Mat::zeros(image.size(), image.type());
    double factor = (double)(1 + (double)sliderPos/100);
    cv :: cvtColor(image,hsv,COLOR_BGR2HSV);
    timer.start();
    for( int rowIdx = 0; rowIdx < image.rows; rowIdx++ )
    {
        for( int colIdx = 0; colIdx < image.cols; colIdx++)
        {
            new_image.at<Vec3b>(rowIdx,colIdx)[0] = saturate_cast<uchar>(hsv.at<Vec3b>(rowIdx,colIdx)[0]);
            new_image.at<Vec3b>(rowIdx,colIdx)[1] = saturate_cast<uchar>(factor * hsv.at<Vec3b>(rowIdx,colIdx)[1]);
            new_image.at<Vec3b>(rowIdx,colIdx)[2] = saturate_cast<uchar>(hsv.at<Vec3b>(rowIdx,colIdx)[2]);
        }
    }
    qDebug()<<"Color Loop Exectuion Time: "<< timer.elapsed()<<endl;
    cv :: cvtColor(new_image,new_image,COLOR_HSV2RGB);
    QImage final = Mat2QImage(new_image);
    return final;
}

QImage Hue(Mat image, int sliderPos)
{
    Mat hsv = Mat::zeros(image.size(), image.type());
    Mat new_image = Mat::zeros(image.size(), image.type());
    double factor = (double)(1 + (double)sliderPos/100);
    cv :: cvtColor(image,hsv,COLOR_BGR2HSV);
    timer.start();
    for(int rowIdx = 0; rowIdx < image.rows; rowIdx++)
    {
        for(int colIdx = 0; colIdx < image.cols; colIdx++)
        {

                 new_image.at<Vec3b>(rowIdx,colIdx)[0] = saturate_cast<uchar>(factor*hsv.at<Vec3b>(rowIdx,colIdx)[0]);
                 new_image.at<Vec3b>(rowIdx,colIdx)[1] = saturate_cast<uchar>(hsv.at<Vec3b>(rowIdx,colIdx)[1]);
                 new_image.at<Vec3b>(rowIdx,colIdx)[2] = saturate_cast<uchar>(hsv.at<Vec3b>(rowIdx,colIdx)[2]);
        }
    }
    qDebug()<<"Hue Loop Exectuion Time: "<< timer.elapsed()<<endl;
    cv :: cvtColor(new_image,new_image,COLOR_HSV2RGB);
    QImage final = Mat2QImage(new_image);
    return final;
}

QImage Sharpness(Mat inImage, int sliderPos)
{
    Mat outImage = Mat::zeros(inImage.size(), inImage.type() );
    double factor = (double)(1 - (double)sliderPos/(10));
    Mat blur = cv::getGaussianKernel(9 ,factor);

    //Size size=cv::Size(3,3);
    timer.start();
    if(sliderPos>0)
    {
        if(sliderPos<15)
        {
            Mat sharpenKernel = (Mat_<double>(3, 3) << 0,-1,0,-1,5.0,-1 ,0,-1,0);
            cv::filter2D(inImage,outImage,-1,sharpenKernel);
        }
        if(sliderPos>=15 && sliderPos<30)
        {
            Mat sharpenKernel=(Mat_<double>(3, 3) <<0,-2,0,-2,9.0,-2,0,-2,0);
            cv::filter2D(inImage,outImage,-1,sharpenKernel);
        }
        if(sliderPos>=30 && sliderPos<45)
        {
            Mat sharpenKernel=(Mat_<double>(3, 3) <<-1,-1,-1,-1,9.0,-1,-1,-1,-1);
            cv::filter2D(inImage,outImage,-1,sharpenKernel);
        }
        if(sliderPos>=45 && sliderPos<60)
        {
            Mat sharpenKernel=(Mat_<double>(3, 3) <<0,-3,0,-3,13.0,-3,0,-3,0);
            cv::filter2D(inImage,outImage,-1,sharpenKernel);
        }
        if(sliderPos>=60 && sliderPos<=75)
        {
            Mat sharpenKernel=(Mat_<double>(3, 3) <<-2,-2,-2,-2,17.0,-2,-2,-2,-2);
            cv::filter2D(inImage,outImage,-1,sharpenKernel);
        }
        if(sliderPos>75 && sliderPos<=90)
        {
            Mat sharpenKernel=(Mat_<double>(3, 3) <<-3,-3,-3,-3,25.0,-3,-3,-3,-3);
            cv::filter2D(inImage,outImage,-1,sharpenKernel);
        }
        if(sliderPos>90)
        {
            Mat sharpenKernel=(Mat_<double>(3, 3) <<-4,-4,-4,-4,33.0,-4 , -4,-4,-4);
            cv::filter2D(inImage,outImage,-1,sharpenKernel);
        }
}

    else if(sliderPos<0)
    {   cout<< "SLider Pos: "<<sliderPos<<"Standard Dev:"<<factor<<endl;
        cout << "Blur = " << endl << " "  << blur << endl << endl;
        cv::filter2D(inImage,outImage,-1,blur);}

    else outImage = inImage;
    //qDebug()<<"Sharpness/Blur Loop Exectuion Time: "<< timer.elapsed()<<endl;

    cvtColor(outImage, outImage,COLOR_BGR2RGB);
    QImage final = Mat2QImage(outImage);

    return final;
}

QImage Resize(Mat image, int sliderPos)
{
    sliderPos=sliderPos==-100?-99:sliderPos;
    double factor=(double)(1 + (double)sliderPos/(100));
    Mat new_image;
    timer.start();
    cv::resize(image, new_image, cv::Size(image.cols * factor,image.rows * factor), 0, 0, INTER_NEAREST);
    qDebug()<<"Resize Loop Exectuion Time: "<< timer.elapsed()<<endl;
    cvtColor(new_image, new_image,COLOR_BGR2RGB);
    QImage final = Mat2QImage(new_image);
    return final;

}

QImage Mat2QImage(cv::Mat image)
{
    QImage dest(image.cols, image.rows, QImage::Format_ARGB32);
    for (int i = 0; i < image.rows; ++i)
    {
        for (int j = 0; j < image.cols; ++j)
        {
            cv::Vec3b bgr = image.at<cv::Vec3b>(i, j);
            dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
        }
    }
    return dest;
}


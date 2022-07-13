#include "mainwindow_OpenCV.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mCam = new QCamera(this);
    mCamvf = new QCameraViewfinder(this);
    mCamCap = new QCameraImageCapture(mCam,this);
    mLayout = new QVBoxLayout;
    mCamvf->show();
    mCam->setViewfinder(mCamvf);
    mLayout->addWidget(mCamvf);
    ui   ->CameraView->setLayout(mLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if(ismodified)
    {
        on_actionExit_triggered();
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    onToggleFullScreen(!isFullScreen());
}

void MainWindow::onToggleFullScreen(bool fs)
{
    if (fs)
    {
        showFullScreen();
        ui->quitAction->setVisible(true);
    }
    else
    {
        ui->quitAction->setVisible(false);
        showNormal();
    }
}

void MainWindow::on_Tab_tabBarClicked(int index)
{
    if(index==1)  {

        if(!filename_open.isEmpty()&& ismodified)
            {
                QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image?",
                                                                       QMessageBox:: Save|QMessageBox:: Discard);
                if(reply== QMessageBox::Save)
                {

                   on_Save_clicked();

                }

                }
        mCam->start();
    }
    else
    {
        mCam->stop();
    }

}

void MainWindow::on_actionUpload_Image_triggered()
{
    if(ismodified)
        {
            QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image?",
                                                                   QMessageBox:: Save|QMessageBox:: Discard);

            if(reply== QMessageBox::Save)
            {

             on_actionSave_triggered();

            }

            }
    filename_open = QFileDialog::getOpenFileName(this,"Open an image",QDir::homePath(),
                                                 "Images(*.jpg *.jpeg *.JPG *.png *.PNG *.bmp *.BMP );;""JPG (*.jpg *.jpeg *.JPG);;""PNG"
                                                 "(*.png *.PNG);;""BMP (*.bmp *.BMP)");
    if(!filename_open.isEmpty())
     {
        original_matrix = cv::imread(filename_open.toStdString().c_str(), 1);
        if( ! original_matrix.data )
            return;

        QImage image = QImage((uchar*)original_matrix.data, original_matrix.cols,original_matrix.rows,
                              original_matrix.step,QImage::Format_RGB888);
        if( image.isNull() )
            return;
        original_img = QPixmap::fromImage(image);
        cv :: cvtColor(original_matrix,show_matrix,COLOR_BGR2RGB);
        processed_matrix=original_matrix.clone();
        QImage converted_image = QImage( (uchar*)show_matrix.data, show_matrix.cols, show_matrix.rows,
                                                 show_matrix.step, QImage::Format_RGB888 );
        converted_original_img = QPixmap::fromImage( converted_image );
        filename_copy=filename_open;
        QGraphicsScene *scene=new QGraphicsScene;
        QGraphicsPixmapItem *item= new QGraphicsPixmapItem(converted_original_img);
        scene->addItem(item);
        ui->editView->setScene(scene);
        ui->editView->show();
        ui->editView->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);
        ui->editlabel->setText("Original Image");
        ui->statusBar->showMessage("Original Image Uploaded");
        ui->horizontalSlider->setValue(0);
        ui->label->setText(QLocale().toString(0));
        edit_mode=7;
    }
    else if(!filename_copy.isEmpty())
    {
        filename_open=filename_copy;
    }
}

void MainWindow::on_Camera_clicked()
{
    QDateTime now = QDateTime::currentDateTime();
    QString timestamp = now.toString(QLatin1String("yyyyMMdd-hhmmss"));
    filename_open = QString::fromLatin1("C:/Users/ASUS/Desktop/QtImageSave/Img-%1.jpg").arg(timestamp);
    mCam->setCaptureMode(QCamera::CaptureStillImage);
    mCamCap->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    mCam->searchAndLock();
    mCamCap->capture(filename_open);
    mCam->unlock();
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Image is Captured","Do you want to capture again?",
                                                              QMessageBox:: Yes | QMessageBox:: No);
    if(reply== QMessageBox::Yes)
    {
        mCam->start();
    }

    if(reply== QMessageBox::No)
    {

        original_matrix = cv::imread(filename_open.toStdString().c_str(), 1);
        if( ! original_matrix.data )
            return;
        QImage image = QImage((uchar*)original_matrix.data, original_matrix.cols, original_matrix.rows,
                                      original_matrix.step, QImage::Format_RGB888);
        if( image.isNull() )
            return;
        original_img = QPixmap::fromImage(image);

        cv :: cvtColor(original_matrix,show_matrix,COLOR_RGB2BGR);
        processed_matrix=original_matrix.clone();
        QImage converted_image = QImage( (uchar*)show_matrix.data, show_matrix.cols, show_matrix.rows,
                                                 show_matrix.step, QImage::Format_RGB888 );
        converted_original_img = QPixmap::fromImage( converted_image );
        QGraphicsScene *scene=new QGraphicsScene;
        QGraphicsPixmapItem *item= new QGraphicsPixmapItem(converted_original_img);
        scene->addItem(item);
        ui->editView->setScene(scene);
        ui->editView->show();
        ui->editView->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);
        ui->editlabel->setText("Original Image");
        ui->statusBar->showMessage("Image Captured");
        ui->horizontalSlider->setValue(0);
        ui->label->setText(QLocale().toString(0));
        edit_mode=7;

     }
}

void MainWindow::on_actionSave_triggered()
{

    QFile file(filename_open);
    if(!file.exists(filename_open))
    {
        QMessageBox::warning(this,"Error","No File to Save");
        qDebug() << "File not open" << file.error();
    }
    else
    {
        if(ismodified)
        {
            const QDateTime now = QDateTime::currentDateTime();
            const QString timestamp = now.toString(QLatin1String("yyyyMMdd-hhmmss"));
            const QString filename = QString::fromLatin1("C:/Users/ASUS/Desktop/QTimage_save/Img-%1.jpg").arg(timestamp);
            filename_save = QFileDialog::getSaveFileName(this,"Save an Image",filename,"Images "
                                                                    "(*.jpg *.jpeg *.JPG *.png *.PNG *.bmp *.BMP );;""JPG "
                                                                    "(*.jpg *.jpeg *.JPG);;" "PNG (*.png *.PNG);;""BMP (*.bmp *.BMP)");

        if(!filename_save.isEmpty())
        {
            processed_img.save(filename_save);
            QMessageBox::information(this, "Image Saved Successfully",filename_save);
            ismodified=false;
        }
        }
    }
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before closing?",
                                                                                        QMessageBox:: Save|QMessageBox:: Discard);
    if(reply== QMessageBox::Discard)
        QApplication::quit();
    if(reply== QMessageBox::Save )
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Save");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            if(ismodified)
            {
                const QDateTime now = QDateTime::currentDateTime();
                const QString timestamp = now.toString(QLatin1String("yyyyMMdd-hhmmss"));
                const QString filename = QString::fromLatin1("C:/Users/rrajesh/Desktop/QTimage_save/Img-%1.jpg").arg(timestamp);
                filename_save = QFileDialog::getSaveFileName(this,"Save an Image",filename,"Images "
                                                                        "(*.jpg *.jpeg *.JPG *.png *.PNG *.bmp *.BMP )"
                                                                        ";;""JPG (*.jpg *.jpeg *.JPG);;""PNG (*.png *.PNG)"
                                                                        ";;""BMP (*.bmp *.BMP)");
                if(!filename_save.isEmpty())
                {
                    processed_img.save(filename_save);
                    QMessageBox::information(this, "Image Saved Successfully",filename_save);
                    ismodified=false;
                    QApplication::quit();
                }
            }
        }
    }
}

void MainWindow::on_actionBrightess_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                          QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            QFile file(filename_open);
            if(!file.exists(filename_open))
            {
                QMessageBox::warning(this,"Error","No File to Save");
                qDebug() << "File not open" << file.error();
            }
            else on_actionSave_triggered();
        }
    }

    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Edit Brightness?",
                                                                           QMessageBox::Yes|QMessageBox::No);
    if(msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Brightness Editing");
            ui->statusBar->showMessage("Editing View: Brightness Editing");
            Image = Mat2QImage(processed_matrix);
            processed_img = QPixmap::fromImage(Image);
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_mode=1;
            ismodified=true;
        }
    }
}

void MainWindow::on_actionContrast_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
     }
    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Edit Contrast?",
                                                                    QMessageBox::Yes|QMessageBox::No);
    if(msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Contrast Editing");
            ui->statusBar->showMessage("Editing View: Contrast Editing");
            Image = Mat2QImage(processed_matrix);
            processed_img = QPixmap::fromImage(Image);
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_mode=2;
            ismodified=true;
        }
    }
}

void MainWindow::on_actionColor_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
     }
    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Edit Color?",
                                                                    QMessageBox::Yes|QMessageBox::No);
    if(msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Color Editing");
            ui->statusBar->showMessage("Editing View: Color Editing");
            Image = Mat2QImage(processed_matrix);
            processed_img = QPixmap::fromImage(Image);
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_mode=3;
            ismodified=true;
        }
    }
}

void MainWindow::on_actionHue_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
     }
    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Edit Hue?",
                                                                    QMessageBox::Yes|QMessageBox::No);
    if(msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Hue Editing");
            ui->statusBar->showMessage("Editing View: Hue Editing");
            Image = Mat2QImage(processed_matrix);
            processed_img = QPixmap::fromImage(Image);
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_mode=4;
            ismodified=true;
        }
    }
}

void MainWindow::on_actionSharpness_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
     }
    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Edit Sharpness?",
                                                                    QMessageBox::Yes|QMessageBox::No);
    if(msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Sharpness/Blur Editing");
            ui->statusBar->showMessage("Editing View: Sharpness/Blur Editing");
            Image = Mat2QImage(processed_matrix);
            processed_img = QPixmap::fromImage(Image);
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_mode=5;
            ismodified=true;
        }
    }
}

void MainWindow::on_actionResize_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
     }
    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Resize Image?",
                                                                    QMessageBox::Yes|QMessageBox::No);
    if(msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Resizing Image");
            ui->statusBar->showMessage("Editing View: Resizing Editing");
            Image = Mat2QImage(processed_matrix);
            processed_img = QPixmap::fromImage(Image);
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_mode=6;
            ismodified=true;
        }
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int sliderPos)
{
    QImage send = converted_original_img.copy().toImage();
    Mat send_matrix = show_matrix.clone();
    QImage returned;
    qint64 time = 0;
    switch(edit_mode)
    {
    case 1:
        ui->label->setText(QLocale().toString(sliderPos));
        timer.start();
        returned =Brightness(send_matrix,sliderPos);
        time = timer.elapsed();
        ui->statusBar->showMessage("Brightness loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;

    case 2:
        ui->label->setText(QLocale().toString(sliderPos));
        timer.start();
        returned =Contrast(send_matrix,sliderPos);
        time = timer.elapsed();
        ui->statusBar->showMessage("Contrast loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;

    case 3:
        ui->label->setText(QLocale().toString(sliderPos));
        timer.start();
        returned =Color(send_matrix,sliderPos);
        time = timer.elapsed();
        ui->statusBar->showMessage("Color loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;


     case 4:
        ui->label->setText(QLocale().toString(sliderPos));
        timer.start();
        returned =Hue(send_matrix,sliderPos);
        time = timer.elapsed();
        ui->statusBar->showMessage("Hue loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;

    case 5:
        ui->label->setText(QLocale().toString(sliderPos));
        timer.start();
        returned =Sharpness(send_matrix,sliderPos);
        time = timer.elapsed();
        ui->statusBar->showMessage("Sharpness loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;

    case 6:
       timer.start();
       returned = Resize(send_matrix,sliderPos);
       ui->label->setText(QLocale().toString(sliderPos)+"\n Image Size:" +
                          QLocale().toString(returned.width())+ "x"+ QLocale().toString(returned.height()));
       time = timer.elapsed();
       ui->statusBar->showMessage("Resize loop Execution Time: "+QLocale().toString(time)+" milliseconds");
       break;

    case 7:
        returned = send;
        ui->label->setText(QLocale().toString(sliderPos));
        break;
     }
    processed_img = processed_img.fromImage(returned);
    on_actionImage_Display_triggered(processed_img);
    if(!filename_open.isEmpty())
        ismodified=true;
}

void MainWindow::on_actionImage_Display_triggered(QPixmap image)
{
    QGraphicsScene *scene=new QGraphicsScene;
    QGraphicsPixmapItem *item= new QGraphicsPixmapItem(image);
    scene->addItem(item);
    ui->editView->setScene(scene);
    ui->editView->show();
    ui->editView->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);
}

void MainWindow::on_Upload_clicked()
{
    on_actionUpload_Image_triggered();
}

void MainWindow::on_Save_clicked()
{
    on_actionSave_triggered();
}

void MainWindow::on_Exit_clicked()
{
    on_actionExit_triggered();
}

void MainWindow::on_Brightness_clicked()
{
    on_actionBrightess_triggered();
}

void MainWindow::on_Contrast_clicked()
{
    on_actionContrast_triggered();
}

void MainWindow::on_Color_clicked()
{
    on_actionColor_triggered();
}

void MainWindow::on_Hue_clicked()
{
    on_actionHue_triggered();
}

void MainWindow::on_Sharpness_clicked()
{
    on_actionSharpness_triggered();
}

void MainWindow::on_Resize_clicked()
{
    on_actionResize_triggered();
}


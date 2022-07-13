QT       += core gui multimedia multimediawidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Edit_OpenCv.cpp \
    main.cpp \
    mainwindow_OpenCV.cpp

HEADERS += \
    Edit_OpenCv.h \
    mainwindow_OpenCV.h

FORMS += \
    mainwindow_OpenCV.ui
      INCLUDEPATH += C:\opencv\build\include

LIBS += C:\opencv-build\bin\libopencv_core320.dll
LIBS += C:\opencv-build\bin\libopencv_highgui320.dll
LIBS += C:\opencv-build\bin\libopencv_imgcodecs320.dll
LIBS += C:\opencv-build\bin\libopencv_imgproc320.dll
LIBS += C:\opencv-build\bin\libopencv_features2d320.dll
LIBS += C:\opencv-build\bin\libopencv_calib3d320.dll
INCLUDEPATH += $$(OPENCV_SDK_DIR)/include
LIBS += -lstdc++fs
        #LIBS += -L$$(OPENCV_SDK_DIR)/x86/mingw/lib
         #      -lopencv_core320
         #      -lopencv_highgui320
         #      -lopencv_imgcodecs320
         #      -lopencv_imgproc320
         #     -lopencv_features2d320
         #      -lopencv_calib3d320

    RESOURCES += \
    resources.qrc



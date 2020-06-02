QT       += core gui xml network xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    lib/client.cpp \
    lib/device_management/capabilities.cpp \
    lib/device_management/networkinterfaces.cpp \
    lib/device_management/networkprotocols.cpp \
    lib/device_management/systemdateandtime.cpp \
    lib/device_management/systemfactorydefault.cpp \
    lib/device_management/systemreboot.cpp \
    lib/device_management/user.cpp \
    lib/devicemanagement.cpp \
    lib/devicesearcher.cpp \
    lib/media_management/audioencoderconfiguration.cpp \
    lib/media_management/audioencoderconfigurationoptions.cpp \
    lib/media_management/audioencoderconfigurations.cpp \
    lib/media_management/audiosourceconfiigurations.cpp \
    lib/media_management/profile.cpp \
    lib/media_management/profiles.cpp \
    lib/media_management/streamuri.cpp \
    lib/media_management/videoencoderconfiguration.cpp \
    lib/media_management/videoencoderconfigurationoptions.cpp \
    lib/media_management/videoencoderconfigurations.cpp \
    lib/media_management/videosourceconfiguration.cpp \
    lib/media_management/videosourceconfigurations.cpp \
    lib/mediamanagement.cpp \
    lib/message.cpp \
    lib/messageparser.cpp \
    lib/ptz_management/absolutemove.cpp \
    lib/ptz_management/configuration.cpp \
    lib/ptz_management/configurations.cpp \
    lib/ptz_management/continuousmove.cpp \
    lib/ptz_management/gotohomeposition.cpp \
    lib/ptz_management/gotopreset.cpp \
    lib/ptz_management/node.cpp \
    lib/ptz_management/nodes.cpp \
    lib/ptz_management/preset.cpp \
    lib/ptz_management/presets.cpp \
    lib/ptz_management/relativemove.cpp \
    lib/ptz_management/removepreset.cpp \
    lib/ptz_management/stop.cpp \
    lib/ptzmanagement.cpp \
    lib/service.cpp \
    main.cpp \
    mainwindow.cpp \
    networkdialog.cpp

HEADERS += \
    aboutdialog.h \
    lib/client.h \
    lib/device_management/capabilities.h \
    lib/device_management/networkinterfaces.h \
    lib/device_management/networkprotocols.h \
    lib/device_management/systemdateandtime.h \
    lib/device_management/systemfactorydefault.h \
    lib/device_management/systemreboot.h \
    lib/device_management/user.h \
    lib/devicemanagement.h \
    lib/devicesearcher.h \
    lib/media_management/audioencoderconfiguration.h \
    lib/media_management/audioencoderconfigurationoptions.h \
    lib/media_management/audioencoderconfigurations.h \
    lib/media_management/audiosourceconfigurations.h \
    lib/media_management/profile.h \
    lib/media_management/profiles.h \
    lib/media_management/streamuri.h \
    lib/media_management/videoencoderconfiguration.h \
    lib/media_management/videoencoderconfigurationoptions.h \
    lib/media_management/videoencoderconfigurations.h \
    lib/media_management/videosourceconfiguration.h \
    lib/media_management/videosourceconfigurations.h \
    lib/mediamanagement.h \
    lib/message.h \
    lib/messageparser.h \
    lib/ptz_management/absolutemove.h \
    lib/ptz_management/configuration.h \
    lib/ptz_management/configurations.h \
    lib/ptz_management/continuousmove.h \
    lib/ptz_management/gotohomeposition.h \
    lib/ptz_management/gotopreset.h \
    lib/ptz_management/node.h \
    lib/ptz_management/nodes.h \
    lib/ptz_management/preset.h \
    lib/ptz_management/presets.h \
    lib/ptz_management/relativemove.h \
    lib/ptz_management/removepreset.h \
    lib/ptz_management/stop.h \
    lib/ptzmanagement.h \
    lib/service.h \
    mainwindow.h \
    networkdialog.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

FORMS += \
    aboutdialog.ui \
    mainwindow.ui \
    networkdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android-sources/AndroidManifest.xml

linux:!android {
    # using pkg-config
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

contains(QMAKE_PLATFORM, win32) {
    message("Setting for win32 $$QMAKE_PLATFORM]")
    #INCLUDEPATH += C:\Qt\opencv-4.1.0\build\install\include

    #LIBS += C:\Qt\opencv-4.1.0\build\install\x64\mingw\bin\libopencv_core410.dll
    #LIBS += C:\Qt\opencv-4.1.0\build\install\x64\mingw\bin\libopencv_highgui410.dll
    #LIBS += C:\Qt\opencv-4.1.0\build\install\x64\mingw\bin\libopencv_imgcodecs410.dll
    #LIBS += C:\Qt\opencv-4.1.0\build\install\x64\mingw\bin\libopencv_imgproc410.dll
    #LIBS += C:\Qt\opencv-4.1.0\build\install\x64\mingw\bin\libopencv_features2d410.dll
    #LIBS += C:\Qt\opencv-4.1.0\build\install\x64\mingw\bin\libopencv_calib3d410.dll
    #LIBS += C:\Qt\opencv-4.1.0\build\install\x64\mingw\bin\libopencv_videoio410.dll
}

equals(ANDROID_TARGET_ARCH, arm64-v8a) {
    message("setting arm64-v8a OPENCV libs [$$QMAKE_PLATFORM]")

#OPENCVSDKNATIVE = C:\Qt\OpenCV-android-sdk\sdk\native
#INCLUDEPATH += C:\Qt\OpenCV-android-sdk\sdk\native\jni\include

    # OPENCV LIBS
#LIBS +=\
#    -L"$$OPENCVSDKNATIVE/3rdparty/libs/arm64-v8a/" \
#    -L"$$OPENCVSDKNATIVE/staticlibs/arm64-v8a/" \
#     -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -littnotify -llibtiff -llibjpeg-turbo -llibjasper -llibpng -lIlmImf -llibprotobuf -llibwebp -ltbb -lcpufeatures -ltegra_hal
#    ANDROID_EXTRA_LIBS += $$OPENCVSDKNATIVE/libs/arm64-v8a/libopencv_java4.so
}

equals(ANDROID_TARGET_ARCH, x86_64) {
#    message("setting x86_64 OPENCV libs [$$QMAKE_PLATFORM]")

#OPENCVSDKNATIVE = C:\Qt\OpenCV-android-sdk\sdk\native
#INCLUDEPATH += C:\Qt\OpenCV-android-sdk\sdk\native\jni\include

    # OPENCV LIBS
#LIBS +=\
#    -L"$$OPENCVSDKNATIVE/3rdparty/libs/x86_64/" \
#    -L"$$OPENCVSDKNATIVE/staticlibs/x86_64/" \
#     -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -littnotify -llibtiff -llibjpeg-turbo -llibjasper -llibpng -lIlmImf -llibprotobuf -llibwebp -ltbb -lcpufeatures -lippiw -lippicvi
#    ANDROID_EXTRA_LIBS += $$OPENCVSDKNATIVE/libs/x86_64/libopencv_java4.so
}

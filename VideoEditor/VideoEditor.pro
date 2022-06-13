QT += quick

SOURCES += \
        VideoEditorViewModel.cpp \
        main.cpp \
        test.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    VideoEditorViewModel.h \
    VideoInfo.h \
    test.h

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lavcodec
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lavcodecd
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -lavcodec

#INCLUDEPATH += $$PWD/../ffmpeg/lib
#DEPENDPATH += $$PWD/../ffmpeg/lib

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lavdevice
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lavdeviced
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -lavdevice

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lavfilter
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lavfilterd
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -lavfilter

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lavformat
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lavformatd
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -lavformat

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lavutil
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lavutild
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -lavutil

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibavcodec.dll
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibavcodec.dlld
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -llibavcodec.dll

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibavdevice.dll
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibavdevice.dlld
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -llibavdevice.dll

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibavfilter.dll
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibavfilter.dlld
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -llibavfilter.dll

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibavformat.dll
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibavformat.dlld
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -llibavformat.dll

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibavutil.dll
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibavutil.dlld
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -llibavutil.dll

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibswresample.dll
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibswresample.dlld
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -llibswresample.dll

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibswscale.dll
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibswscale.dlld
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -llibswscale.dll

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibswscale.dll
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -llibswscale.dlld
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -llibswscale.dll

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lswresample
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lswresampled
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -lswresample

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lswscale
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ffmpeg/lib/ -lswscaled
#else:unix: LIBS += -L$$PWD/../ffmpeg/lib/ -lswscale

#INCLUDEPATH += $$PWD/../ffmpeg/include
#DEPENDPATH += $$PWD/../ffmpeg/include

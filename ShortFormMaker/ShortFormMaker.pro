QT += quick

SOURCES += \
        Controller.cpp \
        VideoEditorViewModel.cpp \
        interface.cpp \
        main.cpp \
        test.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources \
            VideoPlayer.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Test.qml \
    Timeline.qml \
    VideoPlayer.qml \
    right-arrow.png

HEADERS += \
    Controller.h \
    Editor.h \
    VideoEditorViewModel.h \
    interface.h \
    test.h \
    videoInfo.h

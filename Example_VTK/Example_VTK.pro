QT       += core gui

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
    ../../../CCAD/CCAD/Polygonica/PolygonicaManager.cpp \
    ../../../CCAD/CCAD/VTK/VTKManager.cpp \
    main.cpp \
    dialog.cpp \
    ModelWindow.cpp \
    modelwidget_test.cpp

HEADERS += \
    ../../../CCAD/CCAD/Polygonica/PolygonicaManager.h \
    ../../../CCAD/CCAD/VTK/VTKManager.h \
    dialog.h \
    ModelWindow.h \
    modelwidget_test.h

FORMS += \
    dialog.ui

#QMAKE_CXXFLAGS += /Zc:strictStrings-

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$PWD/../../../External/VTK82/include/vtk-8.2
INCLUDEPATH += $$PWD/../../../External/Polygonica/include/pg

LIBS += -L$$PWD/../../../External/VTK82/lib
#Debug: LIBS += -L$$PWD/../../External/Polygonica/lib/debug -lpg
#Release: LIBS += -L$$PWD/../../External/Polygonica/lib/release -lpg

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../External/Polygonica/lib/release/ -lpg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../External/Polygonica/lib/debug/ -lpg

LIBS += -lkernel32
LIBS += -luser32
LIBS += -lgdi32
LIBS += -lwinspool
LIBS += -lcomdlg32
LIBS += -ladvapi32
LIBS += -lshell32
LIBS += -lole32
LIBS += -loleaut32
LIBS += -luuid
LIBS += -lodbc32
LIBS += -lodbccp32

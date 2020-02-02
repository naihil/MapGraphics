#-------------------------------------------------
#
# Project created by QtCreator 2012-03-03T10:50:47
#
#-------------------------------------------------

TARGET = MapGraphics
TEMPLATE = lib

CONFIG += c++11

QT += network sql widgets

DEFINES += MAPGRAPHICS_LIBRARY

HEADERS += \
    guts/CompositeTileSourceConfigurationWidget.h \
    guts/Conversions.h \
    guts/MapGraphicsNetwork.h \
    guts/MapTileGraphicsObject.h \
    guts/MapTileLayerListModel.h \
    guts/MapTileSourceDelegate.h \
    guts/PrivateQGraphicsInfoSource.h \
    guts/PrivateQGraphicsObject.h \
    guts/PrivateQGraphicsScene.h \
    guts/PrivateQGraphicsView.h \
    tileSources/CompositeTileSource.h \
    tileSources/GridTileSource.h \
    tileSources/OSMTileSource.h \
    CircleObject.h \
    LineObject.h \
    MapGraphics_global.h \
    MapGraphicsObject.h \
    MapGraphicsScene.h\
    MapGraphicsView.h \
    MapTileSource.h \
    PolygonObject.h \
    Position.h \

SOURCES += \
    guts/CompositeTileSourceConfigurationWidget.cpp \
    guts/Conversions.cpp \
    guts/MapGraphicsNetwork.cpp \
    guts/MapTileGraphicsObject.cpp \
    guts/MapTileLayerListModel.cpp \
    guts/MapTileSourceDelegate.cpp \
    guts/PrivateQGraphicsInfoSource.cpp \
    guts/PrivateQGraphicsObject.cpp \
    guts/PrivateQGraphicsScene.cpp \
    guts/PrivateQGraphicsView.cpp \
    tileSources/CompositeTileSource.cpp \
    tileSources/GridTileSource.cpp \
    tileSources/OSMTileSource.cpp \
    CircleObject.cpp \
    LineObject.cpp \
    MapGraphicsObject.cpp \
    MapGraphicsScene.cpp \
    MapGraphicsView.cpp \
    MapTileSource.cpp \
    PolygonObject.cpp \
    Position.cpp \

FORMS += \
    guts/CompositeTileSourceConfigurationWidget.ui \

RESOURCES += resources.qrc

unix {
    target.path = /usr/lib
    INSTALLS += target
}

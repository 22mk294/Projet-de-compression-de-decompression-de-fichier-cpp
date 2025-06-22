TEMPLATE = app
TARGET = Projet-de-compression-de-decompression-de-fichier-cpp

QT += widgets

SOURCES += main.cpp \
           mainwindow.cpp \
           compressor.cpp \
           decompressor.cpp

HEADERS += mainwindow.h \
           compressor.h \
           decompressor.h

LIBS += -lz

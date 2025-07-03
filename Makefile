# Makefile pour Chiffrement DeFichiers

#chemin vers Qt 6.6.3 + MinGW 64-bit
QT_DIR = C:/Qt/6.6.3/mingw_64

CXX = g++
CIBLE = ChiffrementDeFichiers.exe
MOC = "$(QT_DIR)/bin/moc.exe"
UIC = "$(QT_DIR)/bin/uic.exe"

SOURCES = main.cpp mainwindow.cpp crypteur.cpp moc_mainwindow.cpp
OBJECTS = $(SOURCES:.cpp=.o)
UI_FILE = mainwindow.ui
UI_HEADER = ui_mainwindow.h
MOC_SOURCE = moc_mainwindow.cpp

CXXFLAGS = -std=c++17 -fPIC -I. \
-I"$(QT_DIR)/include" \
-I"$(QT_DIR)/include/QtCore" \
-I"$(QT_DIR)/include/QtGui" \
-I"$(QT_DIR)/include/QtWidgets"

LDFLAGS = -L"$(QT_DIR)/lib" -lQt6Widgets -lQt6Gui -lQt6Core -mwindows

all: $(CIBLE)

$(CIBLE): $(OBJECTS)
	$(CXX) -o $(CIBLE) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(UI_HEADER): $(UI_FILE)
	$(UIC) -o $(UI_HEADER) $(UI_FILE)

$(MOC_SOURCE): mainwindow.h
	$(MOC) -o $(MOC_SOURCE) mainwindow.h

mainwindow.o: $(UI_HEADER)
main.o: mainwindow.h

clean:
	-del $(CIBLE) $(OBJECTS) $(UI_HEADER) $(MOC_SOURCE) 2>nul

.PHONY: all clean

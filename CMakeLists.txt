cmake_minimum_required(VERSION 3.5)

project(CrypteurDeFichiers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Active les fonctionnalités automatiques de Qt pour CMake
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Trouve les paquets Qt nécessaires
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Ajoute les fichiers sources à l'exécutable
add_executable(CrypteurDeFichiers
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    crypteur.cpp
    crypteur.h
)

# Lie les bibliothèques Qt à votre projet
target_link_libraries(CrypteurDeFichiers PRIVATE Qt6::Widgets)

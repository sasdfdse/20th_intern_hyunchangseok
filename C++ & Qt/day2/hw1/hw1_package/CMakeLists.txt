cmake_minimum_required(VERSION 3.5)

project(hw1_package VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    ui/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hw1_package
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_add_ui(UI_HEADERS ui/mainwindow.ui)  # Qt6에서는 이렇게 사용

else()
    qt5_wrap_ui(UI_HEADERS ui/mainwindow.ui)  # Qt5에서는 이 방법을 사용
    add_executable(hw1_package ${PROJECT_SOURCES})
endif()

target_link_libraries(hw1_package PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(hw1_package PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(hw1_package)
endif()

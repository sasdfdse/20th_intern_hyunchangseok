cmake_minimum_required(VERSION 3.5)

project(hw1_package VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/mNetAssistWidget.cpp
    src/mTcpClientSocket.cpp
    src/mTcpServer.cpp
    include/mNetAssistWidget.h
    include/mdefine.h
    include/mTcpClientSocket.h
    include/mTcpServer.h
    ui/mNetAssistWidget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hw1_package
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_add_ui(UI_HEADERS ui/mNetAssistWidget.ui)

else()
    qt5_wrap_ui(UI_HEADERS ui/mNetAssistWidget.ui)
    add_executable(hw1_package ${PROJECT_SOURCES})
endif()

target_include_directories(hw1_package PUBLIC include)

target_link_libraries(hw1_package PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

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

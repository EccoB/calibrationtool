cmake_minimum_required(VERSION 3.5)

project(calibrationtool VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/ui/uimain.cpp
        src/ui/uimain.h
        src/ui/uimain.ui
        src/userstrings.h
        src/userstrings.cpp
        src/ui/imageview.h
        src/ui/imageview.cpp
        src/helperfunctions.h
        src/helperfunctions.cpp
        src/camera.h
        src/camera.cpp
        src/objplanar.h
        src/objplanar.cpp
        src/testing.h
        src/testing.cpp
        src/camerapose.h
        src/camerapose.cpp
)
set(PROJECT_DIRECTORIES
       ./src
       ./src/ui
)
include_directories(src)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(calibrationtool
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET calibrationtool APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(calibrationtool SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(calibrationtool
            ${PROJECT_SOURCES}
        )
    endif()
endif()

## Open CV ##
SET("OPENCV_DIR" "/usr/share/OpenCV")
find_package( OpenCV REQUIRED )

MESSAGE(STATUS "Open CV in ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "OPENCV LIBS: ${OpenCV_LIBS}")
##


target_link_libraries(calibrationtool PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})

set_target_properties(calibrationtool PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calibrationtool)
endif()

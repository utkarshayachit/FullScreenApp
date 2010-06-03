cmake_minimum_required(VERSION 2.6)

project(FullScreenApp)

FIND_PACKAGE(ParaView REQUIRED)
INCLUDE(${PARAVIEW_USE_FILE})

# Variables that need to be set for installation code to work correctly.
SET (BUILD_SHARED_LIBS ${PARAVIEW_BUILD_SHARED_LIBS}) # enable shared builds.

SET (SOURCE_FILES
  CustomMainWindow.cxx
  CustomMainWindow.h
)

QT4_WRAP_CPP(MOC_SRCS
  CustomMainWindow.h
)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR})


#------------------------------------------------------------------------------
# Build the client
build_paraview_client(fullscreenapp
    TITLE "FullScreen ParaView"
    ORGANIZATION  "Kitware Inc"
    VERSION_MAJOR 1
    VERSION_MINOR 0
    VERSION_PATCH 0
    PVMAIN_WINDOW CustomMainWindow
    PVMAIN_WINDOW_INCLUDE CustomMainWindow.h
    SOURCES ${SOURCE_FILES} ${MOC_SRCS} ${UI_BUILT_SOURCES}
)


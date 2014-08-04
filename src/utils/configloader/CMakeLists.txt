cmake_minimum_required (VERSION 2.8.7)

project(configloader)
set(configloader_VERSION_MAJOR 0)
set(configloader_VERSION_MINOR 1)
set(configloader_VERSION_PATCH 0)
set(XSD_PATH ../../../src/utils/configloader/resources)

#find_package(Xerces)
include_directories(/usr/include/python2.7)



# look for Qt4 libs
find_package(Qt4 REQUIRED  QtCore QtGui QtXml)
#set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
message(QT-Includes: ${QT_INCLUDES})
message(QT-Libs: ${QT_LIBRARIES})
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})


# set up paths and configuration
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/deploy/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/deploy/lib)
set(SOURCE_WILDCARDS *.h *.H *.hpp *.hh *.hxx *.c *.C *.cpp *.cc *.cxx)
set(CMAKE_BUILD_TYPE Debug)

configure_file (
  "${PROJECT_SOURCE_DIR}/configloaderConfig.h.in"
  "${PROJECT_BINARY_DIR}/configloaderConfig.h"
  )

# Add resources
add_subdirectory(./resources/)
#QT4_ADD_RESOURCES(ResourceSources resources/resources.qrc)

# Add testdata
add_subdirectory(./testdata/)

set(SOURCES configloader.cpp
    loaderexception.h
    configloadererrorhandler.cpp
    loaders/t2fitgfconfigloader.cpp
    loaders/datasetconfigloader.cpp
    configs/configbuilder.cpp
    configs/lmconfig.cpp
    configs/sliceprofileconfig.cpp
    configs/msedataconfig.cpp
    configs/datasetconfig.h
    ../conversion/datatypeconverter.cpp)

# configloader library
add_library(configloader ${SOURCES} ${ResourceSources})
target_link_libraries(configloader xerces-c ${QT_LIBRARIES})


# demo programm
add_executable(demo demo.cpp
    ${resources}
    ${testdata})
target_link_libraries(demo xerces-c configloader boost_python python2.7)

# install program
#INSTALL(FILES configloader.h DESTINATION ${PROJECT_SOURCE_DIR}/deploy/include)
INSTALL(FILES ${resources} DESTINATION ${PROJECT_SOURCE_DIR}/deploy/resources)
INSTALL(FILES ${testdata} DESTINATION ${PROJECT_SOURCE_DIR}/deploy/testdata)



#add_custom_command(TARGET demo
#                   COMMAND ${CMAKE_COMMAND} -E copy_directory
#                   ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:demo>/resources)

#add_custom_command(TARGET demo
 #                  COMMAND ${CMAKE_COMMAND} -E copy_directory
 #                      ${PROJECT_SOURCE_DIR}/testdata $<TARGET_FILE_DIR:demo>/testdata)

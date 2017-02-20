project(Super_Peinture)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SOURCE_LIST)

# headers
set(HEADER_LIST ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -ggdb -O0 -Wall -Wextra")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# output dirs
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib-debug)
  set(LIB_INSTALL_DIR ${CMAKE_SOURCE_DIR}/lib-debug)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin-debug)
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
  set(LIB_INSTALL_DIR ${CMAKE_SOURCE_DIR}/lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
endif()

find_package(OpenGL REQUIRED)
find_package(Qt4 REQUIRED)

set(Qt4_LIBRARIES Qt4::QtGui Qt4::QtCore Qt4::QtOpenGL Qt4::QtXml)
set(mixer_SOURCES ${CMAKE_SOURCE_DIR}/src/mixer.cpp)
set(mixer_HEADERS ${CMAKE_SOURCE_DIR}/include/mixer.h)
set(mixer_FORMS ${CMAKE_SOURCE_DIR}/src/mixer.ui)

QT4_WRAP_CPP(mixer_HEADERS_MOCS ${mixer_HEADERS})
QT4_WRAP_UI(mixer_FORMS_HEADERS ${mixer_FORMS})

FILE(GLOB folder_project_include include/*.* include/*/*.*)

include_directories(${OPENGL_INCLUDE_DIR}
		    ${Qt5Widgets_INCLUDE_DIRS}
		    ${HEADER_LIST})

add_executable(${PROJECT_NAME}
	       ${SOURCE_LIST}  
	       ${folder_project_include}
	       ${mixer_HEADERS_MOC}
	       ${mixer_FORMS_HEADERS})

target_link_libraries(${PROJECT_NAME} 
	              ${Qt4_LIBRARIES} 
                      ${OPENGL_LIBRARIES})

message(${SOURCE_LIST} ${HEADER_LIST})

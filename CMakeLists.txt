cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(graph2  VERSION 0.0  DESCRIPTION "graph2 Windows/Linux"  LANGUAGES C CXX)

set(TARGET_NAME "graph2")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lX11 -Wall" )
endif (UNIX)
if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP5" )
endif (WIN32)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


if (WIN32)
    set(QT5_PATH  "D:\\Qt5\\5.15.2\\msvc2019_64")
    list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH})
    set(OpenCV_DIR "D:\\repo\\opencv-4.10.0-build")
    set(QMAKE_EXE  "D:\\Qt5\\5.15.2\\msvc2019_64\\bin\\qmake.exe")
endif (WIN32)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(OpenCV REQUIRED)

include_directories( "../processing2/src" )
include_directories( "../processing2/include" )

include_directories( "src" )
include_directories( "include" )

include_directories( "../utils2/src" )
include_directories( "../utils2/include" )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SRC
src/case.cpp
src/graph.cpp
)

set(HEADERS
include/case.hpp
include/graph.hpp
include/graph_global.h
)

set(SRC_HEADERS_TEST
	gtest/gtest.cpp
	gtest/gtest_graph.cpp
	gtest/gtest_graph.hpp
)

macro(copy_json jsonname jsonpath)
    configure_file(${jsonpath}${jsonname} ${CMAKE_CONFIGURATION_TYPES}/${jsonname})
    configure_file(${jsonpath}${jsonname} ${CMAKE_BINARY_DIR}/${CMAKE_CONFIGURATION_TYPES}/${jsonname})
endmacro()

copy_json("test.json" "gtest/")
copy_json("test_graph.json" "gtest/")
copy_json("test_graph2.json" "gtest/")
copy_json("test_graph_config.json" "gtest/")

MESSAGE(STATUS "graph2 CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
MESSAGE(STATUS "graph2 CMAKE_CONFIGURATION_TYPES ${CMAKE_CONFIGURATION_TYPES}")

add_library(${PROJECT_NAME}_lib STATIC
    ${SRC} ${HEADERS}
)

target_link_libraries(
    ${PROJECT_NAME}_lib
    Qt::Core
    Threads::Threads
    ${OpenCV_LIBS}
    utils2_lib
    processing2_lib
)

install(TARGETS ${PROJECT_NAME}_lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
install(TARGETS ${PROJECT_NAME}_lib EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

MESSAGE(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
MESSAGE(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
MESSAGE(STATUS "CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")

add_executable(${PROJECT_NAME}_test ${SRC_HEADERS_TEST})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib gtest gmock)


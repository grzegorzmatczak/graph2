cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(graph2  VERSION 0.0  DESCRIPTION "graph2 Windows/Linux"  LANGUAGES C CXX)

set(TARGET_NAME "graph2")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_OPTIONS}")
list(APPEND CMAKE_PREFIX_PATH ${Qt5_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(OpenCV REQUIRED)

#include_directories( "../processing2/src" )
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
    configure_file(${jsonpath}${jsonname} ${CMAKE_BUILD_TYPE}/${jsonname})
    configure_file(${jsonpath}${jsonname} ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${jsonname})
endmacro()

copy_json("test.json" "gtest/")
copy_json("test_graph.json" "gtest/")
copy_json("test_graph2.json" "gtest/")
copy_json("test_graph_config.json" "gtest/")

add_library(${PROJECT_NAME} STATIC
    ${SRC} ${HEADERS}
)

target_link_libraries(
    ${PROJECT_NAME}
    Qt::Core
    Threads::Threads
    ${OpenCV_LIBS}
    utils2
    processing2
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

MESSAGE(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
MESSAGE(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
MESSAGE(STATUS "CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")

add_executable(${PROJECT_NAME}_test ${SRC_HEADERS_TEST})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME} gtest gmock)


cmake_minimum_required(VERSION 2.8)
project(MOOCDataTransformation)

include_directories(lib/jsoncpp/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(JSONCPP_FILES
        lib/jsoncpp/json/json.h
        lib/jsoncpp/json/json-forwards.h
        lib/jsoncpp/jsoncpp.cpp)

set(SOURCE_FILES
        src/main.cpp
        src/TabularData.h
        src/TabularData.cpp
        src/ColumnData.h
        src/BlockData.h
        src/DataConfig.h
        src/source/JsonSource.h
        src/source/JsonSource.cpp)

add_executable(MOOCDataTransformation ${SOURCE_FILES} ${JSONCPP_FILES})

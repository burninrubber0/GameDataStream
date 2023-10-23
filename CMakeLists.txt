cmake_minimum_required(VERSION 3.14)
project(DataStream CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(DATASTREAM_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(DATASTREAM_SOURCES
	${DATASTREAM_SOURCES}
	src/binary-io/data-stream.cpp
	)

set(DATASTREAM_HEADERS
	${DATASTREAM_HEADERS}
	include/binary-io/data-stream.h
	)

add_library(DataStream STATIC ${DATASTREAM_SOURCES} ${DATASTREAM_HEADERS})
find_package(Qt6 COMPONENTS Core REQUIRED)
target_include_directories(DataStream PUBLIC ${DATASTREAM_ROOT}/include)
target_link_libraries(DataStream PRIVATE Qt6::Core)
set_property(TARGET DataStream PROPERTY POSITION_INDEPENDENT_CODE ON)

# VS stuff
set_property(DIRECTORY ${DATASTREAM_ROOT} PROPERTY VS_STARTUP_PROJECT DataStream)
source_group(TREE ${DATASTREAM_ROOT} FILES ${DATASTREAM_SOURCES} ${DATASTREAM_HEADERS})

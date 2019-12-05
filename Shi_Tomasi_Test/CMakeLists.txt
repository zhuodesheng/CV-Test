cmake_minimum_required(VERSION 2.6)
project(shi_tomasi_test)

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3" )

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

################### dependencied ###################
# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(shi_tomasi_test main.cpp)

TARGET_LINK_LIBRARIES(shi_tomasi_test ${OpenCV_LIBRARIES})

# install(TARGETS shi_tomasi_test RUNTIME DESTINATION bin)

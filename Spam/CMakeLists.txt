cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (1-spam)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(training src/training.cc)
add_executable(classify src/classify.cc)
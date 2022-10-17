cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

project ("Experiment_1")

aux_source_directory(. CPP_LIST)

FILE(GLOB SC_FILES "*.cpp" "*.h")

add_executable(${PROJECT_NAME} ${CPP_LIST} ${SC_FILES})
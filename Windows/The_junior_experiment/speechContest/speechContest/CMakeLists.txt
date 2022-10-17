
cmake_minimum_required (VERSION 3.8)

aux_source_directory(. CPP_LIST)

FILE(GLOB SC_FILES "*.cpp" "*.h")

add_executable (speechContest ${CPP_LIST} ${SC_FILES}  "list.txt")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET speechContest PROPERTY CXX_STANDARD 20)
endif()

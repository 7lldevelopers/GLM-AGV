cmake_minimum_required(VERSION 3.10)
project(AGVproject)

set(CMAKE_CXX_STANDARD 11)

add_executable(myagv src/main.cpp src/map.txt src/agv.cpp src/agv.h  src/Jop.cpp src/position.h src/openai.hpp)
find_package(CURL REQUIRED)

# Add include directories for libcurl
target_include_directories(myagv PRIVATE ${CURL_INCLUDE_DIRS})

# Link libcurl library
target_link_libraries(myagv PRIVATE ${CURL_LIBRARIES})
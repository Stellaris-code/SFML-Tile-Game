project(SFMLTileGame)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(./src SRC_LIST)
include_directories(./include)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(Boost REQUIRED)
find_package(SFML REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE HPP_FILES ./include/*.hpp)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HPP_FILES})


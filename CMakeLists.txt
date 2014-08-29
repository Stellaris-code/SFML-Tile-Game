project(SFMLTileGame)
cmake_minimum_required(VERSION 2.8)

include_directories(./include)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE CPP_FILES ./src/*.cpp)
file(GLOB_RECURSE HPP_FILES ./include/*.hpp)

add_executable(${PROJECT_NAME} ${HPP_FILES} ${CPP_FILES})

find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED system window graphics)

include_directories(${OPENGL_INCLUDE_DIR})

include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})


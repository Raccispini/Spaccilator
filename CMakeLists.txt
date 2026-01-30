cmake_minimum_required(VERSION 4.2.3)
project(Calcolatrice)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCE "src/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC include)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

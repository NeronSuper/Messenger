
cmake_minimum_required(VERSION 3.1)

project(Messanger LANGUAGES CXX)

add_executable(run main.cpp)
target_link_libraries(run stdc++fs)
cmake_minimum_required(VERSION 3.1)

project(Messanger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17) 

add_executable(run main.cpp)


target_compile_features(run PUBLIC cxx_std_17)
target_link_libraries(run wsock32 ws2_32)


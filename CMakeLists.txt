#cmake_minimum_required(VERSION 3.20)
#set(CMAKE_CXX_STANDARD 20)


#project(myserver)



add_executable(main main.cpp)
target_link_libraries(main PRIVATE serverlib)


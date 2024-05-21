add_executable(tests tests.cpp)




find_package(Boost REQUIRED COMPONENTS system filesystem)



target_link_libraries(tests server ${Boost_LIBRARIES})
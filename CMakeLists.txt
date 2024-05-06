cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)


#find_package(PQXX REQUIRED)
# find_package(libpq REQUIRED)
# find_package(PostgreSQL REQUIRED)
# include_directories(${PQXX_INCLUDE_DIRS})
# include_directories(${PostgreSQL_INCLUDE_DIRS})
#find_package(libpqxx REQUIRED)


if(CMAKE_SYSTEM MATCHES Windows)
set(CMAKE_TOOLCHAIN_FILE C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
endif()
project(server)

if(CMAKE_SYSTEM MATCHES Windows)
find_package(nlohmann_json 3.11.3 REQUIRED)

##target_link_libraries(foo PRIVATE nlohmann_json::nlohmann_json)   


set(Boost_INCLUDE_DIR C:/boost_1_84_0)
set(Boost_LIBRARY_DIR C:/boost_1_84_0/stage/lib)

find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO bin.relwithdbg)

add_subdirectory(server)
add_subdirectory(courier)
add_subdirectory(order)
add_subdirectory(routes)



add_executable(main main.cpp)
target_link_libraries(main server)



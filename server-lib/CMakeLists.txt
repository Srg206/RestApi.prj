#cmake_minimum_required(VERSION 3.20)
#set(CMAKE_CXX_STANDARD 20)


#find_package(PQXX REQUIRED)
# find_package(libpq REQUIRED)
# include_directories(${PQXX_INCLUDE_DIRS})
# include_directories(${PostgreSQL_INCLUDE_DIRS})


#project(server)

#find_package(PostgreSQL REQUIRED)
#find_package(libpqxx REQUIRED)
find_package(PkgConfig)
pkg_search_module(PQXX REQUIRED libpqxx)


find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)



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
add_library(serverlib server.cpp server.hpp)

target_include_directories(serverlib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)


target_link_libraries(serverlib PRIVATE server ${PQXX_LINK_LIBRARIES} )



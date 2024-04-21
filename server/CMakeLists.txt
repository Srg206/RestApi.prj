add_library(server server.cpp server.hpp)
set_property(TARGET server PROPERTY CXX_STANDARD 20)
target_include_directories(server PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)

add_subdirectory(tests)
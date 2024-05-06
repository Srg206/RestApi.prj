add_library(courier courier.cpp courier.hpp)
set_property(TARGET courier PROPERTY CXX_STANDARD 20)
target_include_directories(courier PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)

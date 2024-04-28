add_library(order order.cpp order.hpp)
set_property(TARGET order PROPERTY CXX_STANDARD 20)
target_include_directories(order PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)

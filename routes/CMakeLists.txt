add_library(All_routes All_routes.hpp post_couriers.cpp)
set_property(TARGET All_routes PROPERTY CXX_STANDARD 20)
target_include_directories(All_routes PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(All_routes courier)
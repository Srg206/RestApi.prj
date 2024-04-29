add_library(server server.cpp server.hpp)
set_property(TARGET server PROPERTY CXX_STANDARD 20)
target_include_directories(server PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
if(CMAKE_SYSTEM MATCHES Windows)
target_link_libraries(server PRIVATE All_routes  nlohmann_json::nlohmann_json)
else()
target_link_libraries(server All_routes)
endif()

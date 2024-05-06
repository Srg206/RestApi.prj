add_library(server server.cpp server.hpp)
set_property(TARGET server PROPERTY CXX_STANDARD 20)
target_include_directories(server PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(server All_routes )
#target_link_libraries(serverlib PRIVATE server ${PQXX_LINK_LIBRARIES} )

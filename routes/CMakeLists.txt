add_library(All_routes All_routes.hpp post_couriers.cpp get_couriers.cpp get_couriers_id.cpp get_orders_id.cpp
 get_orders.cpp post_couriers.cpp post_orders_complete.cpp post_orders.cpp utils.cpp)

set_property(TARGET All_routes PROPERTY CXX_STANDARD 20)
target_include_directories(All_routes PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)

find_package(PkgConfig)
pkg_search_module(PQXX 6.4.5 REQUIRED libpqxx)
find_package(nlohmann_json REQUIRED)
#find_package(Boost REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)


#target_compile_features(All_routes cxx_std_20)

target_link_libraries(All_routes  courier order nlohmann_json::nlohmann_json ${PQXX_LINK_LIBRARIES} ${Boost_LIBRARIES})
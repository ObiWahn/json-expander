cmake_minimum_required(VERSION 3.11)
project(expander)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/json" EXCLUDE_FROM_ALL)

add_executable(json-expander expander.cpp)
target_link_libraries(json-expander PRIVATE
    taocpp::json
 )

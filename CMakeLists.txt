cmake_minimum_required(VERSION 3.0.0)
project(wxSample VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(modules/wxWidgets)
add_subdirectory(modules/DiligentCore)

add_executable(wxSample src/main.cpp)
target_link_libraries(wxSample wx::net wx::core wx::base Diligent-Common
                                                         #Diligent-GraphicsEngineD3D12-static
                                                         #Diligent-GraphicsEngineVk-static
                                                         Diligent-GraphicsEngineOpenGL-static
                                                         )

target_include_directories(wxSample PRIVATE ${CMAKE_SOURCE_DIR}/modules/DiligentCore/ ${GTK3_INCLUDE_DIRS})

target_precompile_headers(wxSample PRIVATE src/pch.hpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

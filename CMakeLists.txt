cmake_minimum_required(VERSION 3.0.0)
project(wxSample VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(modules/wxWidgets)

add_executable(wxSample src/main.cpp)
target_link_libraries(wxSample wx::net wx::core wx::base)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

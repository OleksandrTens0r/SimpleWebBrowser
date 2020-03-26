cmake_minimum_required(VERSION 3.10.2)

include(FindPkgConfig)

project(browser)

set(CMAKE_CXX_STANDARD 17)

pkg_check_modules(LIBS REQUIRED gdkmm-3.0 gtkmm-3.0 libcurl webkit2gtk-4.0)

link_directories(${LIBS_LIBRARY_DIRS})
include_directories(${LIBS_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} "main.cpp" "browser_wnd.cpp" "browser_wnd.h" "html_loader.cpp" "html_loader.h")

target_link_libraries(${PROJECT_NAME} ${LIBS_LIBRARIES})

cmake_minimum_required(VERSION 3.10.2)

include(FindPkgConfig)

set(CMAKE_CXX_STANDARD 17)
project(browser_tests)

pkg_check_modules(LIBS REQUIRED gdkmm-3.0 gtkmm-3.0 libcurl webkit2gtk-4.0)
include_directories(${LIBS_INCLUDE_DIRS})

add_library(tested_code STATIC ../browser/html_loader.h ../browser/html_loader.cpp ../browser/browser_wnd.h ../browser/browser_wnd.cpp)

add_subdirectory(gtest/googletest)
enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(browser_tests test.cpp)

target_link_libraries(browser_tests gtest gtest_main)
target_link_libraries(browser_tests tested_code ${LIBS_LIBRARIES})
add_test(AllTests test)

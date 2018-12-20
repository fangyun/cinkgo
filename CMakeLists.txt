cmake_minimum_required (VERSION 3.1)
include(GNUInstallDirs)

project (cgo)

set(Boost_MIN_VERSION "1.58.0")
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.58.0 REQUIRED program_options filesystem)

add_executable(cgo cgo.cpp)

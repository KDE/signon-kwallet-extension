project(kwalletsignon)
set(kwalletsignon_VERSION_MAJOR 0)
set(kwalletsignon_VERSION_MINOR 9)
set(kwalletsignon_VERSION_RELEASE 0)
set(kwalletsignon_VERSION "0.9.0")

cmake_minimum_required(VERSION 2.6)
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

find_package(Qt4 REQUIRED)
find_package(KDE4 REQUIRED)
find_package(SignOnExtension REQUIRED)

add_definitions (${KDE4_DEFINITIONS} -fexceptions -DQT_NO_KEYWORDS -Wno-missing-field-initializers -fno-rtti)

include(KDE4Defaults)

add_subdirectory(src)
add_subdirectory(tests)
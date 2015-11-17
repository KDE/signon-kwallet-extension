project(kwalletsignon5)

set(KDE_APPLICATIONS_VERSION_MAJOR "15")
set(KDE_APPLICATIONS_VERSION_MINOR "11")
set(KDE_APPLICATIONS_VERSION_MICRO "80")
set(kwalletsignon_VERSION "${KDE_APPLICATIONS_VERSION_MAJOR}.${KDE_APPLICATIONS_VERSION_MINOR}.${KDE_APPLICATIONS_VERSION_MICRO}")

cmake_minimum_required(VERSION 2.8.12)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

find_package(Qt5 5.2.0 CONFIG REQUIRED Core DBus)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(FeatureSummary)
include(ECMInstallIcons)
include(KDEFrameworkCompilerSettings)

find_package(KF5 5.0 REQUIRED Wallet)

find_package(SignOnExtension REQUIRED)

add_subdirectory(src)
# add_subdirectory(tests)

if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  feature_summary(WHAT ALL   FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()

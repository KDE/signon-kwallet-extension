cmake_minimum_required(VERSION 3.0)

project(kwalletsignon5)

set(KDE_APPLICATIONS_VERSION_MAJOR "19")
set(KDE_APPLICATIONS_VERSION_MINOR "12")
set(KDE_APPLICATIONS_VERSION_MICRO "3")
set(kwalletsignon_VERSION "${KDE_APPLICATIONS_VERSION_MAJOR}.${KDE_APPLICATIONS_VERSION_MINOR}.${KDE_APPLICATIONS_VERSION_MICRO}")

find_package(ECM 5.18.0 REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

find_package(Qt5 5.6.0 CONFIG REQUIRED Core)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(FeatureSummary)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

find_package(KF5 5.18.0 REQUIRED Wallet)

find_package(SignOnExtension REQUIRED)

add_subdirectory(src)
# add_subdirectory(tests)

feature_summary(WHAT ALL   FATAL_ON_MISSING_REQUIRED_PACKAGES)

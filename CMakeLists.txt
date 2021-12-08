cmake_minimum_required(VERSION 3.16)

project(kwalletsignon5)

set(RELEASE_SERVICE_VERSION_MAJOR "22")
set(RELEASE_SERVICE_VERSION_MINOR "03")
set(RELEASE_SERVICE_VERSION_MICRO "70")
set(kwalletsignon_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")
set(KF5_MIN_VERSION "5.18.0")
set(QT_REQUIRED_VERSION "5.6.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(FeatureSummary)

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Core)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED Wallet)

find_package(SignOnExtension REQUIRED)

add_subdirectory(src)
# add_subdirectory(tests)

feature_summary(WHAT ALL   FATAL_ON_MISSING_REQUIRED_PACKAGES)

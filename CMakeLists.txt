cmake_minimum_required(VERSION 3.16)

set(RELEASE_SERVICE_VERSION_MAJOR "25")
set(RELEASE_SERVICE_VERSION_MINOR "11")
set(RELEASE_SERVICE_VERSION_MICRO "70")
set(kwalletsignon_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

project(kwalletsignon5 VERSION ${kwalletsignon_VERSION})

set(KF_MIN_VERSION "6.0.0")
set(QT_REQUIRED_VERSION "6.5.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMDeprecationSettings)

include(FeatureSummary)

find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Core)

find_package(KF6 ${KF_MIN_VERSION} REQUIRED Wallet)

find_package(SignOnExtension REQUIRED)

ecm_set_disabled_deprecation_versions(QT 6.9.0
     KF 6.16.0
    )


add_subdirectory(src)
# add_subdirectory(tests)

feature_summary(WHAT ALL   FATAL_ON_MISSING_REQUIRED_PACKAGES)

cmake_minimum_required(VERSION 3.16)

set(RELEASE_SERVICE_VERSION_MAJOR "24")
set(RELEASE_SERVICE_VERSION_MINOR "05")
set(RELEASE_SERVICE_VERSION_MICRO "0")
set(kwalletsignon_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

project(kwalletsignon5 VERSION ${kwalletsignon_VERSION})

set(KF5_MIN_VERSION "5.91.0")
set(QT_REQUIRED_VERSION "5.15.2")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMDeprecationSettings)

include(FeatureSummary)

find_package(Qt${QT_MAJOR_VERSION} ${QT_REQUIRED_VERSION} CONFIG REQUIRED Core)

find_package(KF${QT_MAJOR_VERSION} ${KF5_MIN_VERSION} REQUIRED Wallet)

find_package(SignOnExtension REQUIRED)

ecm_set_disabled_deprecation_versions(QT 5.15.2
     KF 5.101.0
    )


add_subdirectory(src)
# add_subdirectory(tests)

feature_summary(WHAT ALL   FATAL_ON_MISSING_REQUIRED_PACKAGES)

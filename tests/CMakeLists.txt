remove_definitions(-DQT_NO_CAST_FROM_ASCII)
include(ECMAddTests)

find_package(Qt5Test ${REQUIRED_QT_VERSION} CONFIG QUIET)

if(NOT Qt5Test_FOUND)
    message(STATUS "Qt5Test not found, autotests will not be built.")
    return()
endif()

include_directories(${SIGNONEXTENSION_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src)

set(testextension_SRCS
    testextension.cpp
    ../src/keyringplugin.cpp
    ../src/secretsstorage.cpp
)


ecm_add_tests(${testextension_SRCS}
              LINK_LIBRARIES Qt5::Test Qt5::Core KF5::Wallet ${SIGNONEXTENSION_LIBRARIES})

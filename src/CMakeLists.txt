add_definitions (-fexceptions -DQT_NO_KEYWORDS -Wno-missing-field-initializers -fno-rtti)
include_directories(${SIGNONEXTENSION_INCLUDE_DIRS})

set(kwalletsignon5_SRCS
    keyringplugin.cpp
    secretsstorage.cpp
)

add_library(libkeyring-kwallet MODULE ${kwalletsignon5_SRCS})

set_target_properties(libkeyring-kwallet PROPERTIES PREFIX "")
target_link_libraries(libkeyring-kwallet
    Qt5::Core
    KF5::Wallet
    ${SIGNONEXTENSION_LIBRARIES})

install(TARGETS libkeyring-kwallet DESTINATION ${SIGNONEXTENSION_PLUGINDIR})

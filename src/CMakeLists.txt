add_definitions (-fexceptions -DQT_NO_KEYWORDS -Wno-missing-field-initializers -fno-rtti)
include_directories(${SIGNONEXTENSION_INCLUDE_DIRS})

set(kwalletsignon5_SRCS
    keyringplugin.cpp
    secretsstorage.cpp
)

add_library(libkeyring-kwallet MODULE ${kwalletsignon5_SRCS})

set_target_properties(libkeyring-kwallet PROPERTIES PREFIX "")
target_link_libraries(libkeyring-kwallet
    Qt::Core
    KF5::Wallet
    ${SIGNONEXTENSION_LIBRARIES})

if(INSTALL_BROKEN_SIGNON_EXTENSION)
  set(OVERRIDDEN_SIGNONEXTENSION_PLUGINDIR ${CMAKE_INSTALL_PREFIX}/lib/signon/extensions/)
  if (NOT OVERRIDDEN_SIGNONEXTENSION_PLUGINDIR STREQUAL SIGNONEXTENSION_PLUGINDIR)
    message(WARNING "INSTALL_BROKEN_SIGNON_EXTENSION is enabled. Files will be installed to ${OVERRIDDEN_SIGNONEXTENSION_PLUGINDIR} instead of ${SIGNONEXTENSION_PLUGINDIR}")
  endif()
  install(TARGETS libkeyring-kwallet DESTINATION ${OVERRIDDEN_SIGNONEXTENSION_PLUGINDIR})
else()
  install(TARGETS libkeyring-kwallet DESTINATION ${SIGNONEXTENSION_PLUGINDIR})
endif()

include_directories(${QT_INCLUDES} ${KDE4_INCLUDES} ${SIGNONEXTENSION_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_BUILD_DIR} ${QT_INCLUDES} )

set(kwalletsignon_SRCS
    keyringplugin.cpp
    secretsstorage.cpp
)

automoc4_add_library(keyring-kwallet MODULE ${kwalletsignon_SRCS})

set_target_properties(keyring-kwallet PROPERTIES PREFIX "")
target_link_libraries(keyring-kwallet ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY} ${KDE4_KUTILS_LIBS} ${SIGNONEXTENSION_LIBRARIES})

set_target_properties(keyring-kwallet PROPERTIES
    VERSION ${kwalletsignon_VERSION}
    SOVERSION ${kwalletsignon_VERSION_MAJOR}
)
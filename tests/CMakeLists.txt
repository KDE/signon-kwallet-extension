include_directories(${QT_INCLUDES} ${KDE4_INCLUDES} ${SIGNONEXTENSION_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_BUILD_DIR} ${QT_INCLUDES} )

set(testextension_SRCS
testextension.cpp
../src/keyringplugin.cpp
../src/secretsstorage.cpp
)

qt4_generate_moc(${testextension_SRCS})
kde4_add_unit_test(testextension ${testextension_SRCS})

target_link_libraries(testextension ${QT_QTTEST_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${KDE4_KUTILS_LIBS} ${SIGNONEXTENSION_LIBRARIES})

add_test(testextension ${CMAKE_CURRENT_BINARY_DIR}/testextension)
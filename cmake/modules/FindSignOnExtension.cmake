# - Try to find SignOnQt
# Once done this will define
#  SIGNONEXTENSION_FOUND - System has libsignon-qt
#  SIGNONEXTENSION_INCLUDE_DIRS - The libsignon-qt include directories
#  SIGNONEXTENSION_LIBRARIES - The libraries needed to use libsignon-qt

find_package(PkgConfig REQUIRED)

execute_process(
    COMMAND "${PKG_CONFIG_EXECUTABLE}" --variable=plugindir SignOnExtension
    OUTPUT_VARIABLE _pkgconfig_invoke_result
    RESULT_VARIABLE _pkgconfig_failed)
if (_pkgconfig_failed)
    message(FAILED " couldn-t find the plugindir for signonextension")
else()
    string(REGEX REPLACE "[\r\n]"                  " " _pkgconfig_invoke_result "${_pkgconfig_invoke_result}")
    string(REGEX REPLACE " +$"                     ""  _pkgconfig_invoke_result "${_pkgconfig_invoke_result}")
    set(SIGNONEXTENSION_PLUGINDIR ${_pkgconfig_invoke_result})
endif()

find_path(SIGNONEXTENSION_INCLUDE_DIR SignOn/AbstractSecretsStorage
          HINTS ${SIGNONEXTENSION_INCLUDEDIR} ${SIGNONEXTENSION_INCLUDE_DIRS}
          PATH_SUFFIXES signon-extension )

find_library(SIGNONEXTENSION_LIBRARY NAMES signon-extension libsignon-extension
             HINTS ${SIGNONEXTENSION_LIBDIR} ${SIGNONEXTENSION_LIBRARY_DIRS} )

set(SIGNONEXTENSION_LIBRARIES ${SIGNONEXTENSION_LIBRARY} )
set(SIGNONEXTENSION_INCLUDE_DIRS ${SIGNONEXTENSION_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set  SIGNONEXTENSION_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(SignOnExtension DEFAULT_MSG
                                  SIGNONEXTENSION_LIBRARY SIGNONEXTENSION_INCLUDE_DIR)

mark_as_advanced(SIGNONEXTENSION_INCLUDE_DIR SIGNONEXTENSION_LIBRARY )

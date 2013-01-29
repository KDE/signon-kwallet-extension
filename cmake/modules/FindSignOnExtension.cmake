# - Try to find SignOnQt
# Once done this will define
#  SIGNONEXTENSION_FOUND - System has libsignon-qt
#  SIGNONEXTENSION_INCLUDE_DIRS - The libsignon-qt include directories
#  SIGNONEXTENSION_LIBRARIES - The libraries needed to use libsignon-qt

find_package(PkgConfig)

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
find_package_handle_standard_args(libsignon-extension  DEFAULT_MSG
                                  SIGNONEXTENSION_LIBRARY SIGNONEXTENSION_INCLUDE_DIR)

mark_as_advanced(SIGNONEXTENSION_INCLUDE_DIR SIGNONEXTENSION_LIBRARY )
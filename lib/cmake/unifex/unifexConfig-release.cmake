#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unifex::unifex" for configuration "Release"
set_property(TARGET unifex::unifex APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(unifex::unifex PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libunifex.so.0.1.0"
  IMPORTED_SONAME_RELEASE "libunifex.so.0"
  )

list(APPEND _cmake_import_check_targets unifex::unifex )
list(APPEND _cmake_import_check_files_for_unifex::unifex "${_IMPORT_PREFIX}/lib/libunifex.so.0.1.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

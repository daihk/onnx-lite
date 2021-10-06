cmake_minimum_required(VERSION 3.12)

function(get_protobuf_version version include)
  file(STRINGS "${include}/google/protobuf/stubs/common.h" ver REGEX "#define GOOGLE_PROTOBUF_VERSION [0-9]+")
  string(REGEX MATCHALL "[0-9]+" ver ${ver})
  math(EXPR major "${ver} / 1000000")
  math(EXPR minor "${ver} / 1000 % 1000")
  math(EXPR patch "${ver} % 1000")
  set(${version} "${major}.${minor}.${patch}" PARENT_SCOPE)
endfunction()

unset(Protobuf_VERSION CACHE)
find_package(Protobuf QUIET)

# Backwards compatibility
# Define camel case versions of input variables
foreach(UPPER
        PROTOBUF_FOUND
        PROTOBUF_LIBRARY
        PROTOBUF_INCLUDE_DIR
        PROTOBUF_VERSION
        )
    if (DEFINED ${UPPER})
        string(REPLACE "PROTOBUF_" "Protobuf_" Camel ${UPPER})
        if (NOT DEFINED ${Camel})
            set(${Camel} ${${UPPER}})
        endif()
    endif()
endforeach()
# end of compatibility block

if(Protobuf_FOUND)
    if(TARGET protobuf::libprotobuf)
        add_library(libprotobuf INTERFACE IMPORTED)
        set_target_properties(libprotobuf PROPERTIES
            INTERFACE_LINK_LIBRARIES protobuf::libprotobuf
            )
    else()
        add_library(libprotobuf UNKNOWN IMPORTED)
        set_target_properties(libprotobuf PROPERTIES
            IMPORTED_LOCATION "${Protobuf_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${Protobuf_INCLUDE_DIR}"
            INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${Protobuf_INCLUDE_DIR}"
            )
        get_protobuf_version(Protobuf_VERSION "${Protobuf_INCLUDE_DIR}")
    endif()
    set(HAVE_PROTOBUF TRUE)
endif()

if(HAVE_PROTOBUF AND PROTOBUF_UPDATE_FILES AND NOT COMMAND PROTOBUF_GENERATE_CPP)
  find_package(Protobuf QUIET)
  if(NOT COMMAND PROTOBUF_GENERATE_CPP)
    message(FATAL_ERROR "PROTOBUF_GENERATE_CPP command is not available")
  endif()
endif()

find_path(TOL_INCLUDE_DIR NAMES tiny_obj_loader.h)
find_library(TOL_LIBRARY NAMES tiny_obj_loader)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(TOL DEFAULT_MSG TOL_INCLUDE_DIR TOL_LIBRARY)

if(TOL_FOUND)
	set(TOL_INCLUDE_DIRS ${TOL_INCLUDE_DIR})
	set(TOL_LIBRARIES ${TOL_LIBRARY})
endif()

mark_as_advanced(TOL_INCLUDE_DIR TOL_LIBRARY)
find_path(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h)
find_library(GLFW_LIBRARY NAMES glfw3)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_INCLUDE_DIR GLFW_LIBRARY)

if(GLFW_FOUND)
	set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
	set(GLFW_LIBRARIES ${GLFW_LIBRARY})
endif()

mark_as_advanced(GLFW_INCLUDE_DIR GLFW_LIBRARY)
find_path(STBI_INCLUDE_DIR NAMES stb_image.c)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(STBI DEFAULT_MSG STBI_INCLUDE_DIR)

if(STBI_FOUND)
	set(STBI_INCLUDE_DIRS ${STBI_INCLUDE_DIR})
endif()

mark_as_advanced(STBI_INCLUDE_DIR)
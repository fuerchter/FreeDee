cmake_minimum_required(VERSION 2.8)

project(glstart)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "-DGLEW_STATIC -std=c++11")

find_package(GLEW REQUIRED)

if(GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	set(LIBRARIES ${LIBRARIES} ${GLEW_LIBRARIES})
endif()

find_package(GLFW REQUIRED)

if(GLFW_FOUND)
	include_directories(${GLFW_INCLUDE_DIRS})
	set(LIBRARIES ${LIBRARIES} ${GLFW_LIBRARIES})
endif()

find_package(GLM REQUIRED)

if(GLM_FOUND)
	include_directories(${GLM_INCLUDE_DIRS})
endif()

find_package(TOL REQUIRED)

if(TOL_FOUND)
	include_directories(${TOL_INCLUDE_DIRS})
	set(LIBRARIES ${LIBRARIES} ${TOL_LIBRARIES})
endif()

find_package(STBI REQUIRED)

if(STBI_FOUND)
	include_directories(${STBI_INCLUDE_DIRS})
endif()

set(LIBRARIES ${LIBRARIES} OpenGL32)

file(GLOB EXECUTABLES "*.h" "*.cpp")

add_executable(glstart ${EXECUTABLES})
target_link_libraries(glstart ${LIBRARIES})
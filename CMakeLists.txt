# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("StellarNurseryEngine")

set (CMAKE_CXX_STANDARD 17)

set(PLATFORM_EXTERNALS_PREFIX ${PROJECT_SOURCE_DIR}/external/Windows/amd64)

add_executable(StellarNurseryEngine)

# link Vulkan
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIR})
target_link_libraries(StellarNurseryEngine ${Vulkan_LIBRARY})

# link GLFW
set(GLFW_LIB_DIR ${PLATFORM_EXTERNALS_PREFIX}/glfw-3.4/lib-vc2022)
set(GLFW_LIB_NAME glfw3.lib)
include_directories(${PLATFORM_EXTERNALS_PREFIX}/glfw-3.4/include)
target_link_libraries(StellarNurseryEngine ${GLFW_LIB_DIR}/${GLFW_LIB_NAME})

# link GLM
include_directories(external/glm-1.0.1)

# Include sub-projects.
add_subdirectory ("src")

target_link_libraries(StellarNurseryEngine main_obj)

#*******************Compile Shaders*******************

set(SRC_SHADERS_DIR "${PROJECT_SOURCE_DIR}/resources/shaders")
set(DEST_SHADERS_DIR "${CMAKE_BINARY_DIR}/resources/shaders")
file(MAKE_DIRECTORY ${DEST_SHADERS_DIR})

file(GLOB SRC_SHADER_FILES "${SRC_SHADERS_DIR}/*")

#add_custom_target(CompileShaders)

foreach(SRC_SHADER_FILE ${SRC_SHADER_FILES})

	get_filename_component(FILE_NAME ${SRC_SHADER_FILE} NAME)
	add_custom_command(TARGET StellarNurseryEngine
			POST_BUILD
			COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${SRC_SHADER_FILE} -o ${DEST_SHADERS_DIR}/${FILE_NAME}.spv)

	#get_filename_component(EXTENSION ${SRC_SHADER_FILE} EXT)
	#if(${EXTENSION} STREQUAL ".vert")
	#	message("vertex shader: ${SRC_SHADER_FILE}")
	#elseif(${EXTENSION} STREQUAL ".frag")
	#	message("fragment shader: ${SRC_SHADER_FILE}")
	#endif()
endforeach()

#*****************Compile Shaders end*****************


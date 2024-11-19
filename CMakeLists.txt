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


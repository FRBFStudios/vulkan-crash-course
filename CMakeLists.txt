cmake_minimum_required(VERSION 3.31)
project(vulkan_crash_course LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

find_package(Vulkan REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glm::glm
        Vulkan::Vulkan
)
cmake_minimum_required (VERSION 3.31)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (TEMPLATE_NAME "vulkan-crash-course")

project (${TEMPLATE_NAME})


find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)
find_package(tinyobjloader REQUIRED)

find_program(SLANGC_EXECUTABLE slangc HINTS $ENV{VULKAN_SDK}/bin REQUIRED)

set(TEMPLATE_DIR ${CMAKE_BINARY_DIR}/${TEMPLATE_NAME})
set(RESOURCE_DIR ${TEMPLATE_DIR}/resources)

add_executable (${TEMPLATE_NAME}
        src/main.cpp
)
set_target_properties (${TEMPLATE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEMPLATE_DIR})
target_link_libraries (${TEMPLATE_NAME}
        glfw
        Vulkan::Vulkan
)
target_include_directories (${TEMPLATE_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Define VULKAN_HPP_HANDLE_ERROR_OUT_OF_DATE_AS_SUCCESS to treat VK_ERROR_OUT_OF_DATE_KHR as a success code
target_compile_definitions(${TEMPLATE_NAME} PRIVATE "VULKAN_HPP_HANDLE_ERROR_OUT_OF_DATE_AS_SUCCESS" )

if(WIN32)
    if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
        set_target_properties(${TEMPLATE_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${TEMPLATE_DIR})
    endif()
endif()

# Slang shader
set (SHADER_TARGET ${TEMPLATE_NAME}Shader)
set (SHADERS_DIR ${RESOURCE_DIR}/shaders)

set (SHADER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/shader.slang")
set (ENTRY_POINTS -entry vertMain -entry fragMain)
add_custom_command(OUTPUT ${SHADERS_DIR} COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADERS_DIR})
add_custom_command(
        OUTPUT  ${SHADERS_DIR}/slang.spv
        COMMAND ${SLANGC_EXECUTABLE} ${SHADER_SOURCES} -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name ${ENTRY_POINTS} -o ${SHADERS_DIR}/slang.spv
        WORKING_DIRECTORY ${SHADERS_DIR}
        DEPENDS ${SHADERS_DIR} ${SHADER_SOURCES}
        COMMENT "Compiling Slang Shaders"
        VERBATIM
)
add_custom_target(${SHADER_TARGET} DEPENDS ${SHADERS_DIR}/slang.spv)
add_dependencies(${TEMPLATE_NAME} ${SHADER_TARGET})

# Assets
# set (ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../assets/")
# file (COPY ${ASSET_DIR}/viking_room.obj DESTINATION ${TEMPLATE_DIR}/models)
# file (COPY ${ASSET_DIR}/viking_room.png DESTINATION ${TEMPLATE_DIR}/textures)
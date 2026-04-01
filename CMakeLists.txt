cmake_minimum_required(VERSION 3.29)
project(Arisen.RHI.Vulkan.Test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect code files
file(GLOB_RECURSE ALL_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Collect shader and asset files to include in SLN
file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Shader/*")
file(GLOB_RECURSE ASSET_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Assets/*")

# Prevent IDE from trying to compile shaders with default tools
set_source_files_properties(${SHADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(${ASSET_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

# Organize files in IDE solution
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Shader" PREFIX "Shader" FILES ${SHADER_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Assets" PREFIX "Assets" FILES ${ASSET_FILES})

# The output must be a DLL for the Arisen Test Runner to bridge
add_library(Arisen.RHI.Vulkan.Test SHARED
    ${ALL_SOURCE_FILES}
    ${SHADER_FILES}
    ${ASSET_FILES}
)

# Use POST_BUILD to ensure assets are copied when building in IDEs
# These will go into the profile's bin folder (e.g., .arisen/bin/Testing/Debug/Assets)
get_property(OUTPUT_DIR TARGET Arisen.RHI.Vulkan.Test PROPERTY RUNTIME_OUTPUT_DIRECTORY)
if(NOT OUTPUT_DIR)
    set(OUTPUT_DIR "${CMAKE_BINARY_DIR}")
endif()

add_custom_command(TARGET Arisen.RHI.Vulkan.Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "${OUTPUT_DIR}/Assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Shader" "${OUTPUT_DIR}/Shader"
    COMMENT "Copying internal package assets and shaders to output directory"
)

# Includes for RHI and Core
target_include_directories(Arisen.RHI.Vulkan.Test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/cgltf
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/image
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../ArisenKernel/Native # Hypothetical path, need to verify
)

# Links
target_link_libraries(Arisen.RHI.Vulkan.Test PRIVATE 
    Arisen.Core.Native # Assuming core native is available
    Arisen.RHI.Vulkan.Native
)

# Export macros if needed
target_compile_definitions(Arisen.RHI.Vulkan.Test PRIVATE ARISEN_RHI_VULKAN_TEST_EXPORT)

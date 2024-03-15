set(PROJECT_NAME Testing)
#cmake_minimum_required(VERSION 3.28)
#project(Testing)
#include("${PROJECT_SOURCE_DIR}/../CMake/Utils.cmake")
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_COMPILER_ID "MSVC")
#set(CMAKE_CXX_COMPILER_VERSION "19.latest")
#add_compile_definitions(OPENGL_EXPORTS)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "src/Advanced/TestAdvancedLighting.cpp"
    "src/Advanced/TestAdvancedLighting.h"
    "src/Advanced/TestCubeMap.cpp"
    "src/Advanced/TestCubeMap.h"
    "src/Advanced/TestFontRender.cpp"
    "src/Advanced/TestFontRender.h"
    "src/Advanced/TestLightCasters.cpp"
    "src/Advanced/TestLightCasters.h"
    "src/Advanced/TestMaterialMaps.cpp"
    "src/Advanced/TestMaterialMaps.h"
    "src/Advanced/TestPostProcessing.cpp"
    "src/Advanced/TestPostProcessing.h"
    "src/Advanced/TestStencilOutline.cpp"
    "src/Advanced/TestStencilOutline.h"
    "src/Basic/TestBatchedTextured.cpp"
    "src/Basic/TestBatchedTextured.h"
    "src/Basic/TestClearColor.cpp"
    "src/Basic/TestClearColor.h"
    "src/Basic/TestCubeRender.cpp"
    "src/Basic/TestCubeRender.h"
    "src/Basic/TestDynamicQuadGeometry.cpp"
    "src/Basic/TestDynamicQuadGeometry.h"
    "src/Basic/TestDynamicVertexGeometry.cpp"
    "src/Basic/TestDynamicVertexGeometry.h"
    "src/Demos/DemoFlappyBird.cpp"
    "src/Demos/DemoFlappyBird.h"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "src/Test.h"
    "src/TestingFramework.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "src/TestMenu.cpp"
    "Testing.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Testing)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/${CMAKE_VS_PLATFORM_NAME}/out/${PROJECT_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/${CMAKE_VS_PLATFORM_NAME}/out/${PROJECT_NAME}/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/${CMAKE_VS_PLATFORM_NAME}/out/${PROJECT_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/${CMAKE_VS_PLATFORM_NAME}/out/${PROJECT_NAME}/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/Debug;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/Graphics/GLs;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/Graphics/Graphicals;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/Graphics/Primitives;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/Graphics/Meshes;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/Graphics/Utils/Textures;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/Graphics/Utils/Fonts;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/Graphics/Utils/Model Loading;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/IO;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/Maths;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/vendor/imgui;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/vendor/freetype;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../OpenGL/src/stdu;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLEW/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLFW/include"
)

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()
set_source_files_properties(src/Advanced/TestAdvancedLighting.cpp PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC"
)
set_source_files_properties(src/Advanced/TestFontRender.cpp PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC"
)
set_source_files_properties(src/Advanced/TestPostProcessing.cpp PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC"
)
set_source_files_properties(src/Basic/TestBatchedTextured.cpp PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC"
)
set_source_files_properties(src/Basic/TestClearColor.cpp PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC"
)
set_source_files_properties(src/Basic/TestCubeRender.cpp PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC"
)
set_source_files_properties(src/Basic/TestDynamicQuadGeometry.cpp PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC"
)
set_source_files_properties(src/Basic/TestDynamicVertexGeometry.cpp PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC"
)
set_source_files_properties(src/Demos/DemoFlappyBird.cpp PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC"
)
set_source_files_properties(src/TestMenu.cpp PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "OpenGL"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
)

cmake_minimum_required(VERSION 3.30)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-D DEBUG)
endif ()

# 初始化编译器类型标记
set(GNUC 0)
set(CLANG 0)
set(MSVC 0)
if (("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang"))
    set(CLANG 1)
endif ()
if (("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU") OR (${CLANG}))
    set(GNUC 1)
endif ()
if (("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC") OR ("${CMAKE_C_SIMULATE_ID}" STREQUAL "MSVC"))
    set(MSVC 1)
endif ()

if (GNUC)
    set(COMPILER_SUFFIX "mingw")
elseif (MSVC)
    set(COMPILER_SUFFIX "vs")
endif ()

file(GLOB ASSETS ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/bin/glfw_${COMPILER_SUFFIX}/*)

file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

include_directories(
        SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
)

link_directories(
        SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib/glfw_${COMPILER_SUFFIX}"
)

add_subdirectory(thirdParty)
add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)

#add_definitions(-D STB_IMAGE_IMPLEMENTATION)

aux_source_directory(./ MAIN_SRCS) # 找到所有的源文件 不递归

add_executable(glStudy ${MAIN_SRCS})

target_link_libraries(glStudy glfw3dll glad wrapper application gl_framework)

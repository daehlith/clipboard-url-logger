cmake_minimum_required(VERSION 3.21)

# Ensure our cmake scripts are available
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# it's useful to have the print helpers around for debugging purposes
include(CMakePrintHelpers)

# Source information from vcpkg.json
include(VcpkgHelpers)
load_vcpkg_json_information()

project(${VCPKG_PROJECT_NAME}
    VERSION ${VCPKG_PROJECT_VERSION}
    DESCRIPTION ${VCPKG_PROJECT_DESCRIPTION}
    HOMEPAGE_URL ${VCPKG_PROJECT_HOMEPAGE_URL}
    LANGUAGES CXX)

# Expose project and version information to C++ code
include(VersionInfo)

# Boilerplate for automated testing
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} WIN32 src/main.cpp src/clipboardurllogger.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} Qt6::Widgets)

set(_SRC_PLATFORM_DIR ${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/Qt6/plugins/platforms/)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm -Rf $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/platforms/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${_SRC_PLATFORM_DIR} $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/platforms/
)

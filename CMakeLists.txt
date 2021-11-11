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

qt_add_executable(${CMAKE_PROJECT_NAME} WIN32 MACOSX_BUNDLE src/main.cpp src/clipboardurllogger.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Widgets)

install(TARGETS ${CMAKE_PROJECT_NAME} BUNDLE DESTINATION .)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(_WINDEPLOYQT_COMMAND "${QT6_INSTALL_PREFIX}/tools/Qt6/bin/windeployqt")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(_WINDEPLOYQT_COMMAND "${QT6_INSTALL_PREFIX}/tools/Qt6/bin/windeployqt.debug")
    endif()
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME}
        POST_BUILD
        COMMAND "${_WINDEPLOYQT_COMMAND}" "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>"
        VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
    include(CPack)

    set(MACOSX_BUNDLE_ICON_FILE appicon.icns)
    set_source_files_properties(res/appicon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE res/appicon.icns)
endif()

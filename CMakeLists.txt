#-----------------------------------------------------------------------------
# Umicom Web Studio Module
# File: CMakeLists.txt
#
# PURPOSE:
#   Build a thin C23 product composition over Framework-owned application
#   experience, runtime and workbench contracts.
#
# Created by: Sammy Hegab
# Organisation: Umicom Foundation
# Licence: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)

project(
    UmicomWebStudioModule
    VERSION 0.1.0
    DESCRIPTION "Thin Umicom Web Studio composition over Umicom Framework"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(UMICOM_WEB_STUDIO_BUILD_CONSOLE
       "Build the native Umicom Web Studio verification console"
       ON)

include(CTest)
include(GNUInstallDirs)

if(NOT TARGET Umicom::Framework)
    find_package(UmicomFramework CONFIG REQUIRED)
endif()
if(NOT TARGET Umicom::application)
    message(FATAL_ERROR
        "Umicom Web Studio requires Framework target Umicom::application")
endif()

if(NOT COMMAND umicom_apply_warnings)
    function(umicom_apply_warnings target)
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        else()
            target_compile_options(${target} PRIVATE
                -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endfunction()
endif()
if(NOT COMMAND umicom_apply_sanitizers)
    function(umicom_apply_sanitizers target)
    endfunction()
endif()

add_library(umicom_web_studio_module STATIC
    src/application.c
    src/workspace.c
)
add_library(Umicom::web_studio_module ALIAS umicom_web_studio_module)

target_include_directories(umicom_web_studio_module PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(umicom_web_studio_module PUBLIC
    Umicom::Framework
    Umicom::application
)

if(COMMAND umicom_apply_warnings)
    umicom_apply_warnings(umicom_web_studio_module)
endif()
if(COMMAND umicom_apply_sanitizers)
    umicom_apply_sanitizers(umicom_web_studio_module)
endif()

if(UMICOM_WEB_STUDIO_BUILD_CONSOLE)
    add_executable(umicom-web-studio-console
        src/console/main.c)
    target_link_libraries(umicom-web-studio-console PRIVATE
        Umicom::web_studio_module)
    if(COMMAND umicom_apply_warnings)
        umicom_apply_warnings(umicom-web-studio-console)
    endif()
    if(COMMAND umicom_apply_sanitizers)
        umicom_apply_sanitizers(umicom-web-studio-console)
    endif()
endif()

if(BUILD_TESTING)
    add_executable(umicom_web_studio_module-test
        tests/test_application.c)
    target_link_libraries(umicom_web_studio_module-test PRIVATE
        Umicom::web_studio_module)
    if(COMMAND umicom_apply_warnings)
        umicom_apply_warnings(umicom_web_studio_module-test)
    endif()
    if(COMMAND umicom_apply_sanitizers)
        umicom_apply_sanitizers(umicom_web_studio_module-test)
    endif()
    add_test(
        NAME web-studio.module.application
        COMMAND umicom_web_studio_module-test)
endif()

install(TARGETS umicom_web_studio_module
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
if(TARGET umicom-web-studio-console)
    install(TARGETS umicom-web-studio-console
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES application.umicom.yaml
    DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/web-studio)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
    install(FILES README.md
        DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/web-studio)
endif()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    install(FILES LICENSE
        DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/web-studio)
endif()

message(STATUS "Umicom Web Studio Module version: ${PROJECT_VERSION}")
message(STATUS "Umicom Web Studio uses Framework-owned thin-client composition")

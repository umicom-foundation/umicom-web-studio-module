#-----------------------------------------------------------------------------
# Umicom Web Studio Module
# File: CMakeLists.txt
#
# PURPOSE:
#   Build a thin C23 product composition over Framework-owned application
#   experience, runtime and workbench contracts.
#
# AUTHOR AND ORGANISATION:
#   Sammy Hegab
#   Umicom Foundation
#
# LICENCE:
#   MIT
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

# Load the dependency only when the parent build has not already provided its target.
if(NOT TARGET Umicom::Framework)
    find_package(UmicomFramework CONFIG REQUIRED)
endif()
# Load the dependency only when the parent build has not already provided its target.
if(NOT TARGET Umicom::application)
    message(FATAL_ERROR
        "Umicom Web Studio requires Framework target Umicom::application")
endif()

# Define the local fallback only when the parent build did not provide the shared helper.
if(NOT COMMAND umicom_apply_warnings)
    # Define the apply warnings build helper so parent and application projects apply one
    # consistent rule.
    function(umicom_apply_warnings target)
        # Select the warning options understood by the active compiler.
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        # Use this fallback path when the earlier condition does not apply.
        else()
            target_compile_options(${target} PRIVATE
                -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endfunction()
endif()
# Define the local fallback only when the parent build did not provide the shared helper.
if(NOT COMMAND umicom_apply_sanitizers)
    # Define the apply sanitizers build helper so parent and application projects apply one
    # consistent rule.
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

# Use the shared build helper when it is available from the parent composition.
if(COMMAND umicom_apply_warnings)
    umicom_apply_warnings(umicom_web_studio_module)
endif()
# Use the shared build helper when it is available from the parent composition.
if(COMMAND umicom_apply_sanitizers)
    umicom_apply_sanitizers(umicom_web_studio_module)
endif()

include(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomThinApplicationRuntime.cmake")
umicom_extend_thin_application_runtime(
    NAME "web-studio"
    TARGET "umicom_web_studio_module")

# Create this optional product surface only when its build option is enabled.
if(UMICOM_WEB_STUDIO_BUILD_CONSOLE)
    add_executable(umicom-web-studio-console
        src/console/main.c)
    target_link_libraries(umicom-web-studio-console PRIVATE
        Umicom::web_studio_module)
    # Use the shared build helper when it is available from the parent composition.
    if(COMMAND umicom_apply_warnings)
        umicom_apply_warnings(umicom-web-studio-console)
    endif()
    # Use the shared build helper when it is available from the parent composition.
    if(COMMAND umicom_apply_sanitizers)
        umicom_apply_sanitizers(umicom-web-studio-console)
    endif()
endif()

# Register verification targets only when the developer has enabled testing.
if(BUILD_TESTING)
    add_executable(umicom_web_studio_module-test
        tests/test_application.c)
    target_link_libraries(umicom_web_studio_module-test PRIVATE
        Umicom::web_studio_module)
    # Use the shared build helper when it is available from the parent composition.
    if(COMMAND umicom_apply_warnings)
        umicom_apply_warnings(umicom_web_studio_module-test)
    endif()
    # Use the shared build helper when it is available from the parent composition.
    if(COMMAND umicom_apply_sanitizers)
        umicom_apply_sanitizers(umicom_web_studio_module-test)
    endif()
    add_test(
        NAME web-studio.module.application
        COMMAND umicom_web_studio_module-test)

    add_executable(umicom_web_studio_workspace-test
        tests/test_workspace.c)
    target_link_libraries(umicom_web_studio_workspace-test PRIVATE
        Umicom::web_studio_module)
    # Use the shared build helper when it is available from the parent composition.
    if(COMMAND umicom_apply_warnings)
        umicom_apply_warnings(umicom_web_studio_workspace-test)
    endif()
    # Use the shared build helper when it is available from the parent composition.
    if(COMMAND umicom_apply_sanitizers)
        umicom_apply_sanitizers(umicom_web_studio_workspace-test)
    endif()
    add_test(
        NAME web-studio.module.workspace
        COMMAND umicom_web_studio_workspace-test)
endif()

install(TARGETS umicom_web_studio_module
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# Configure the optional target only when its feature has created it.
if(TARGET umicom-web-studio-console)
    install(TARGETS umicom-web-studio-console
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES application.umicom.yaml
    DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/web-studio)
# Use the optional file only when it is present in this checkout.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
    install(FILES README.md
        DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/web-studio)
endif()
# Use the optional file only when it is present in this checkout.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    install(FILES LICENSE
        DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/web-studio)
endif()

message(STATUS "Umicom Web Studio Module version: ${PROJECT_VERSION}")
message(STATUS "Umicom Web Studio uses Framework-owned thin-client composition")

include(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomApplicationProductisationContribution.cmake")
umicom_add_application_productisation_contribution(
    NAME "web-studio"
    TARGET umicom_web_studio_productisation
    SOURCE "src/productisation_contribution.c"
    TEST_SOURCE "tests/test_productisation_contribution.c")

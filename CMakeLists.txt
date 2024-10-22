cmake_minimum_required(VERSION 3.21)
project(my_application LANGUAGES CXX)

find_package(Slint QUIET)

add_executable(my_application src/main.cpp)
target_link_libraries(my_application PRIVATE Slint::Slint)
slint_target_sources(my_application ui/app-window.slint)
# On Windows, copy the Slint DLL next to the application binary so that it's found.
if (WIN32)
    add_custom_command(TARGET my_application POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:my_application> $<TARGET_FILE_DIR:my_application> COMMAND_EXPAND_LISTS)
endif()

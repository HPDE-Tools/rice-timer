# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(rice-timer-firmware)

# target_link_libraries(${project_elf} stdc++fs)  # this does not work (yet)

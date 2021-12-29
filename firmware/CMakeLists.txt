cmake_minimum_required(VERSION 3.5)

# enable explicit component dependency
set(COMPONENTS
esptool_py
main
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(rice-timer-firmware)

# target_link_libraries(${project_elf} stdc++fs)  # this does not work (yet)

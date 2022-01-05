cmake_minimum_required(VERSION 3.5)

# enable explicit component dependency
set(COMPONENTS
esptool_py
main
)

set(TEST_COMPONENTS main)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(rice-timer-firmware)

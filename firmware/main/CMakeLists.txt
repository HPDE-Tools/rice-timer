set(srcs
"app_main.cpp"
"lvgl_tick.c"

"app/analysis/checkpoint_detector.cpp"
"app/analysis/lap_timer.cpp"
"app/analysis/onboard_analysis.cpp"
"app/analysis/onboard_analysis_instance.cpp"
"app/can_instance.cpp"
"app/device_id.cpp"
"app/gps_instance.cpp"
"app/imu_instance.cpp"
"app/logger_instance.cpp"
"app/sd_card_instance.cpp"
"app/shared_i2c_bus.cpp"
"app/shared_spi_bus.cpp"
"common/line_buffer_mpsc.cpp"
"common/perf.cpp"
"device/can.cpp"
"device/capture_manager.cpp"
"device/encoder.cpp"
"device/gps_daemon.cpp"
"device/gps_driver_mtk.cpp"
"device/gps_driver_ublox.cpp"
"device/gps_utils.cpp"
"device/imu_driver_lsm6dsr.cpp"
"device/oled_ssd1309.cpp"
"io/autobaud.cpp"
"io/fs_utils.cpp"
"io/logger.cpp"
"io/sd_card_daemon.cpp"
"io/uart_line_reader.cpp"
"localization/gps_collector.cpp"
"localization/localizer.cpp"
"map/map.cpp"
"map/map_index.cpp"
"ui/controller.cpp"
"ui/display.cpp"
"ui/encoder_button_input.cpp"
"ui/model.cpp"
"ui/style.cpp"
)
file(GLOB fonts "ui/fonts/*.c")
file(GLOB my_fbs_src "${COMPONENT_DIR}/../../flatbuffers/*.fbs")

set(requires
# System
esp_adc_cal
fatfs
nvs_flash
sdmmc
vfs

# Project
eigen
flatbuffers
fmtlib
geographiclib
lvgl
minmea
ringbuf
scope_guard
span
unity
)

idf_component_register(
    SRCS ${srcs} ${fonts}
    INCLUDE_DIRS "."
    REQUIRES ${requires}
)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++2a -Wno-deprecated-declarations -Wno-multichar)
target_compile_options(${COMPONENT_LIB} PUBLIC -DLV_LVGL_H_INCLUDE_SIMPLE)
if(TEST_COMPONENTS)
  target_compile_options(${COMPONENT_LIB} PRIVATE -DTEST=1)
else()
  target_compile_options(${COMPONENT_LIB} PRIVATE -DTEST=0)
endif()



#######################
# flatbuffers codegen
#######################
find_program(FLATBUFFERS_FLATC_EXECUTABLE NAMES flatc)
function(FLATBUFFERS_GENERATE_C_HEADERS Name Dir)
set(FLATC_OUTPUTS)
foreach(FILE ${ARGN})
  get_filename_component(FLATC_OUTPUT ${FILE} NAME_WE)
  set(FLATC_OUTPUT
    "${Dir}/${FLATC_OUTPUT}_generated.h")
  list(APPEND FLATC_OUTPUTS ${FLATC_OUTPUT})

  add_custom_command(OUTPUT ${FLATC_OUTPUT}
    COMMAND ${FLATBUFFERS_FLATC_EXECUTABLE}
    ARGS --cpp --cpp-std c++17 --scoped-enums -o "${Dir}/" ${FILE}
    DEPENDS ${FILE}
    COMMENT "Building C++ header for ${FILE}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
set(${Name}_OUTPUTS ${FLATC_OUTPUTS} PARENT_SCOPE)
endfunction()

FLATBUFFERS_GENERATE_C_HEADERS(my_fbs "proto" ${my_fbs_src})
message(WARNING "flatbuffers source: ${my_fbs_src}")
message(WARNING "generated flatbuffers headers: ${my_fbs_OUTPUTS}")
add_custom_target(my_fbs_target DEPENDS ${my_fbs_OUTPUTS})
add_dependencies(${COMPONENT_LIB} my_fbs_target)

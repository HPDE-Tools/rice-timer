set(srcs
"app_main.cpp"
"lvgl_tick.c"

"app/can_instance.cpp"
"app/device_id.cpp"
"app/encoder_button_input.cpp"
"app/gps_instance.cpp"
"app/imu_instance.cpp"
"app/lap_timer.cpp"
"app/logger_instance.cpp"
"app/oled_instance.cpp"
"app/sd_card_instance.cpp"
"app/shared_i2c_bus.cpp"
"app/shared_spi_bus.cpp"
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
"ui/model.cpp"
"ui/view.cpp"
)
file(GLOB fonts "ui/fonts/*.c")

idf_component_register(
    SRCS ${srcs} ${fonts}
    INCLUDE_DIRS "."
)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++2a -Wno-deprecated-declarations)
target_compile_options(${COMPONENT_LIB} PUBLIC -DLV_LVGL_H_INCLUDE_SIMPLE)
# target_link_libraries(${COMPONENT_LIB} PUBLIC stdc++fs)

set(srcs
"app_main.cpp"
"can.cpp"
"capture_manager.cpp"
"common.cpp"
"display.cpp"
"gps.cpp"
"imu.cpp"
"logger.cpp"
"pps.cpp"
)
idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS ""
)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++2a)
# target_link_libraries(${COMPONENT_LIB} PUBLIC stdc++fs)

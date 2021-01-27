set(srcs
"app_main.cpp"
"can.cpp"
"capture_manager.cpp"
"gps.cpp"
"logger.cpp"
"nmea_parser.c"
"pps.cpp"
"io/autobaud.cpp"
"io/uart_line_reader.cpp"
"ui/model.cpp"
"ui/view.cpp"
)
idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS "."
)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++2a)
# target_link_libraries(${COMPONENT_LIB} PUBLIC stdc++fs)

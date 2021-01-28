set(srcs
"app_main.cpp"
"can.cpp"
"capture_manager.cpp"
"filesystem.cpp"
"logger.cpp"

"device/gps.cpp"
"io/autobaud.cpp"
"io/uart_line_reader.cpp"
"ui/model.cpp"
"ui/view.cpp"
)
idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS "."
)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++2a -Wno-deprecated-declarations)
# target_link_libraries(${COMPONENT_LIB} PUBLIC stdc++fs)

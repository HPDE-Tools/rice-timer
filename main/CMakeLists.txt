set(srcs
"app_main.cpp"
"arduino_wrapper.cpp"
)

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS ""
)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++17)

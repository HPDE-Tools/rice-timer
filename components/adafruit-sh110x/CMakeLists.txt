set(root "Adafruit_SH110X")
set(srcs
"${root}/Adafruit_SH110X.cpp"
)
set(includedirs
"${root}"
)
set(requires
arduino
adafruit-gfx-library
adafruit-busio
)
set(priv_requires
)
idf_component_register(
    INCLUDE_DIRS ${includedirs}
    SRCS ${srcs}
    REQUIRES ${requires}
    PRIV_REQUIRES ${priv_requires}
)

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-narrowing)

set(root "Adafruit_LED_Backpack")
set(srcs
"${root}/Adafruit_LEDBackpack.cpp"
)
set(includedirs
"${root}"
)
set(requires
adafruit-gfx-library
)
idf_component_register(
    INCLUDE_DIRS ${includedirs}
    SRCS ${srcs}
    REQUIRES ${requires}
)

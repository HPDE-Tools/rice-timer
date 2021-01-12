set(root "Adafruit_LED_Backpack")
set(srcs
"${root}/Adafruit_LEDBackpack.cpp"
)
set(includedirs
"${root}"
)
set(requires
arduino
adafruit-gfx-library
)
set(priv_requires
)
idf_component_register(
    INCLUDE_DIRS ${includedirs}
    SRCS ${srcs}
    REQUIRES ${requires}
    PRIV_REQUIRES ${priv_requires}
)

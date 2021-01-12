set(root "Adafruit-GFX-Library")
set(srcs
"${root}/Adafruit_GFX.cpp"
"${root}/Adafruit_GrayOLED.cpp"
"${root}/Adafruit_SPITFT.cpp"
"${root}/glcdfont.c"
)
set(includedirs
"${root}"
"${root}/Fonts"
)
set(requires
arduino
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

set(root "Adafruit_BNO055")
set(srcs
"${root}/Adafruit_BNO055.cpp"
)
set(includedirs
"${root}"
)
set(requires
arduino
adafruit-sensor
)
set(priv_requires
)
idf_component_register(
    INCLUDE_DIRS ${includedirs}
    SRCS ${srcs}
    REQUIRES ${requires}
    PRIV_REQUIRES ${priv_requires}
)

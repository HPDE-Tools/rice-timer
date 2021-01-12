set(root "Adafruit_Sensor")
set(srcs
"${root}/Adafruit_Sensor.cpp"
)
set(includedirs
"${root}"
)
set(requires
arduino
)
set(priv_requires
)
idf_component_register(
    INCLUDE_DIRS ${includedirs}
    SRCS ${srcs}
    REQUIRES ${requires}
    PRIV_REQUIRES ${priv_requires}
)

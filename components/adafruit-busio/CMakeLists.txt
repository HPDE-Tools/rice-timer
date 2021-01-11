set(root "Adafruit_BusIO")
set(srcs
"${root}/Adafruit_BusIO_Register.cpp"
"${root}/Adafruit_I2CDevice.cpp"
"${root}/Adafruit_SPIDevice.cpp"
)
set(includedirs
"${root}"
)
idf_component_register(
    INCLUDE_DIRS ${includedirs}
    SRCS ${srcs}
)

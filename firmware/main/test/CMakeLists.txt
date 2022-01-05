idf_component_register(
SRC_DIRS
"."
"common"

INCLUDE_DIRS "."
REQUIRES unity
PRIV_REQUIRES main)
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++2a -Wno-deprecated-declarations -Wno-multichar)

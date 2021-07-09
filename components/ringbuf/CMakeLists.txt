set(srcs
"ringbuf_c/ringbuf.c"
)
set(includedirs
"."
)
set(requires
)
set(priv_requires
)
idf_component_register(
    INCLUDE_DIRS ${includedirs}
    SRCS ${srcs}
    REQUIRES ${requires}
    PRIV_REQUIRES ${priv_requires}
)
target_compile_options(${COMPONENT_LIB} PRIVATE -Dtimegm=mktime)

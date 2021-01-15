set(root "fmt")
set(srcs
"${root}/src/format.cc"
"${root}/src/os.cc"
)
set(includedirs
"${root}/include"
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

set(root "flatbuffers")
set(srcs
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

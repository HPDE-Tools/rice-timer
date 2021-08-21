set(root "geographiclib")

# NOTE: enable only the modules we need
set(srcs
# geographiclib/src/Accumulator.cpp
# geographiclib/src/AlbersEqualArea.cpp
# geographiclib/src/AzimuthalEquidistant.cpp
# geographiclib/src/CassiniSoldner.cpp
# geographiclib/src/CircularEngine.cpp
# geographiclib/src/DMS.cpp
# geographiclib/src/Ellipsoid.cpp
# geographiclib/src/EllipticFunction.cpp
# geographiclib/src/GARS.cpp
# geographiclib/src/Geocentric.cpp
# geographiclib/src/GeoCoords.cpp
geographiclib/src/Geodesic.cpp
# geographiclib/src/GeodesicExactC4.cpp
# geographiclib/src/GeodesicExact.cpp
# geographiclib/src/GeodesicLine.cpp
# geographiclib/src/GeodesicLineExact.cpp
# geographiclib/src/Geohash.cpp
# geographiclib/src/Geoid.cpp
# geographiclib/src/Georef.cpp
# geographiclib/src/Gnomonic.cpp
geographiclib/src/GravityCircle.cpp
geographiclib/src/GravityModel.cpp
# geographiclib/src/LambertConformalConic.cpp
# geographiclib/src/LocalCartesian.cpp
# geographiclib/src/MagneticCircle.cpp
# geographiclib/src/MagneticModel.cpp
geographiclib/src/Math.cpp
# geographiclib/src/MGRS.cpp
# geographiclib/src/NormalGravity.cpp
# geographiclib/src/OSGB.cpp
geographiclib/src/PolarStereographic.cpp
# geographiclib/src/PolygonArea.cpp
# geographiclib/src/Rhumb.cpp
# geographiclib/src/SphericalEngine.cpp
geographiclib/src/TransverseMercator.cpp
# geographiclib/src/TransverseMercatorExact.cpp
geographiclib/src/Utility.cpp
geographiclib/src/UTMUPS.cpp
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

INCLUDE_DIRECTORIES(
     .
     ${CMAKE_BINARY_DIR}
     ${CMAKE_BINARY_DIR}/plugins/Autoscope/src
)

LINK_DIRECTORIES(${BUILD_DIR}/src)

SET(Autoscope_SRCS
     Autoscope.hpp
     Autoscope.cpp
)

SET(AUTOSCOPE_RES ../resources/Autoscope.qrc)
QT5_ADD_RESOURCES(AUTOSCOPE_RES_CXX ${AUTOSCOPE_RES})

ADD_LIBRARY(Autoscope-static STATIC ${Autoscope_SRCS} ${AUTOSCOPE_RES_CXX})
# The library target "HelloStelModule-static" has a default OUTPUT_NAME of "HelloStelModule-static", so change it.
SET_TARGET_PROPERTIES(Autoscope-static PROPERTIES OUTPUT_NAME "Autoscope")
TARGET_LINK_LIBRARIES(Autoscope-static Qt5::Core Qt5::Gui Qt5::Widgets)
SET_TARGET_PROPERTIES(Autoscope-static PROPERTIES COMPILE_FLAGS "-DQT_STATICPLUGIN")
ADD_DEPENDENCIES(AllStaticPlugins Autoscope-static)

SET_TARGET_PROPERTIES(Autoscope-static PROPERTIES FOLDER "plugins/Autoscope")

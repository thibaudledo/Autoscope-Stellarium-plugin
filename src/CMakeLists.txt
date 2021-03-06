INCLUDE_DIRECTORIES(
     	.
	gui
     	${CMAKE_BINARY_DIR}
     	${CMAKE_BINARY_DIR}/plugins/Autoscope/src
     	${CMAKE_BINARY_DIR}/plugins/Autoscope/src/network
	${CMAKE_BINARY_DIR}/plugins/Autoscope/src/gui
)

LINK_DIRECTORIES(${BUILD_DIR}/src)

SET(Autoscope_SRCS
     	Autoscope.hpp
     	Autoscope.cpp
        gui/AutoscopeWindowForm.hpp
        gui/AutoscopeWindowForm.cpp
        gui/AutoscopePictureWindowForm.hpp
        gui/AutoscopePictureWindowForm.cpp
        gui/AutoscopeFtpDialog.hpp
        gui/AutoscopeFtpDialog.cpp
	network/tcp_client.cpp
	network/tcp_client.hpp
	network/tcp_server.cpp
	network/tcp_server.hpp
        network/CommandParser.cpp
        network/CommandParser.hpp

)

SET(AUTOSCOPE_UIS
        gui/AutoscopeWindowForm.ui
        gui/AutoscopePictureWindowForm.ui
        gui/AutoscopeFtpDialog.ui
)

QT5_WRAP_UI(AUTOSCOPE_UIS_H ${AUTOSCOPE_UIS})

SET(AUTOSCOPE_RES ../resources/Autoscope.qrc)
QT5_ADD_RESOURCES(AUTOSCOPE_RES_CXX ${AUTOSCOPE_RES})

ADD_LIBRARY(Autoscope-static STATIC ${Autoscope_SRCS} ${AUTOSCOPE_RES_CXX} ${AUTOSCOPE_UIS_H})
# The library target "HelloStelModule-static" has a default OUTPUT_NAME of "HelloStelModule-static", so change it.
SET_TARGET_PROPERTIES(Autoscope-static PROPERTIES OUTPUT_NAME "Autoscope")
find_package(Qt5Ftp REQUIRED)
TARGET_LINK_LIBRARIES(Autoscope-static Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::Ftp)
SET_TARGET_PROPERTIES(Autoscope-static PROPERTIES COMPILE_FLAGS "-DQT_STATICPLUGIN")
ADD_DEPENDENCIES(AllStaticPlugins Autoscope-static)

SET_TARGET_PROPERTIES(Autoscope-static PROPERTIES FOLDER "plugins/Autoscope")

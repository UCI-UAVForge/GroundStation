SET(QT_USE_QTOPENGL TRUE)
SET( QT_WRAP_CPP TRUE )

FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtNetwork REQUIRED)

INCLUDE (${QT_USE_FILE})

cmake_minimum_required(VERSION 3.0)

ADD_DEFINITIONS (${QT_DEFINITIONS})

PROJECT(UAV-Forge-New)

SET(uavforge_SOURCES main.cpp mainwindow.cpp mapplanning.cpp mapexecution.cpp missionrecap.cpp options.cpp popwindowmp.cpp tutorial.cpp qcomboboxdelegate.cpp tablemodel.cpp)

SET(uavforge_HEADERS mainwindow.h mappplanning.h mapexecution.h missionrecap.h options.h popwindowmp.h tutorial.h qcomboboxdelegate.h tablemodel.h)

SET(uavforge_FORMS mainwindow.ui mapplanning.ui mapexecution.ui missionrecap.ui options.ui popwindowmp.ui tutorial.ui)

QT4_WRAP_CPP(uavforge_HEADERS_MOC ${uavforge_HEADERS})

QT4_WRAP_UI(uavforge_FORMS_HEADERS ${uavforge_FORMS})

ADD_EXECUTABLE(UAV-Forge-New ${uavforge_SOURCES} 
	${uavforge_HEADERS_MOC}
    ${uavforge_FORMS_HEADERS})
	
TARGET_LINK_LIBRARIES(UAV-Forge-New ${QT_LIBRARIES})

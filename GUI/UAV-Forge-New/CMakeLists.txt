set( CMAKE_C_FLAGS "-Wall -g" )
SET(uavforge_SOURCES main.cpp mainwindow.cpp mapplanning.cpp mapexecution.cpp missionrecap.cpp options.cpp popwindowmp.cpp tutorial.cpp qcomboboxdelegate.cpp tablemodel.cpp)
SET(uavforge_HEADERS mainwindow.h mapplanning.h mapexecution.h missionrecap.h options.h popwindowmp.h tutorial.h qcomboboxdelegate.h tablemodel.h)
SET(uavforge_FORMS mainwindow.ui mapplanning.ui mapexecution.ui missionrecap.ui options.ui popwindowmp.ui tutorial.ui)
# SET(uavforge_RESOURCES images.qrc)
ADD_EXECUTABLE(UAV-Forge-New ${uavforge_SOURCES} 
    ${uavforge_HEADERS}
    ${uavforge_FORMS})

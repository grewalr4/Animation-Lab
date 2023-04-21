project(LaboratoryLib)

set(SOURCE_FILES
        pch.h
        Laboratory.h Laboratory.cpp LaboratoryFactory.cpp LaboratoryFactory.h LaboratoryStandin.cpp LaboratoryStandin.h
        Polygon.cpp Polygon.h
        LaboratoryDialog.cpp LaboratoryDialog.h include/laboratory-api.h GraphicsHelper.cpp GraphicsHelper.h Sparky.cpp Sparky.h LaboratoryActual.cpp LaboratoryActual.h WorkingLaboratory.cpp WorkingLaboratory.h Laboratory1Factory.cpp Laboratory1Factory.h Laboratory2Factory.cpp Laboratory2Factory.h Component.cpp Component.h Shape.cpp Shape.h EquipmentRack.cpp EquipmentRack.h ZPM.cpp ZPM.h Light.cpp Light.h PowerSource.cpp PowerSource.h PowerSink.cpp PowerSink.h Switch.cpp Switch.h Event.cpp Event.h DistributionPanel.cpp DistributionPanel.h Equipment.cpp Equipment.h Cable.cpp Cable.h Endpoint.cpp Endpoint.h CableFactory.cpp CableFactory.h SparkingOrb.cpp SparkingOrb.h Winch.cpp Winch.h MotionSource.cpp MotionSource.h MotionSink.cpp MotionSink.h ElectricWinch.cpp ElectricWinch.h Rheostat.cpp Rheostat.h RotarySwitch.cpp RotarySwitch.h)

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
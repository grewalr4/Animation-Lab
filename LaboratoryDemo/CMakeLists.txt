#
# Do not modify this file!
#

project(LaboratoryDemo)

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

if(EXISTS ${LaboratoryDemo_SOURCE_DIR}/LaboratoryDemoLib)
    add_subdirectory(LaboratoryDemoLib)
else()
    # Fetch LaboratoryDemoLib from Github
    include(FetchContent)
    FetchContent_Declare(
            LaboratoryDemoLib
            GIT_REPOSITORY https://github.com/charles-owen/LaboratoryDemo.git
            GIT_TAG main
    )

    FetchContent_MakeAvailable(LaboratoryDemoLib)
endif()

include_directories("../${LABORATORY_LIBRARY}/include" ${LaboratoryDemoLib_SOURCE_DIR})

# This sets the Mac icon for the program
set(MACOSX_BUNDLE_ICON_FILE frank-icon.icns)
set_source_files_properties(${MACOSX_BUNDLE_ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# Define a variable containing a list of source files for the project
set(SOURCE_FILES main.cpp LaboratoryIsolator.h ${LaboratoryDemoLib_SOURCE_DIR}/resources/LaboratoryDemo.rc  ${MACOSX_BUNDLE_ICON_FILE})

# Define the build target for the executable
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${LABORATORY_LIBRARY} LaboratoryDemoLib)

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

# Copy resources into output directory
# Use both the root directory reesources and those in LaboratoryLib
file(COPY ${LaboratoryDemoLib_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ../${LABORATORY_LIBRARY}/resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

if(APPLE)
    # When building for MacOS, also copy resources into the bundle resources
    set(RESOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources)
    file(COPY ${LaboratoryDemoLib_SOURCE_DIR}/resources/ DESTINATION ${RESOURCE_DIR}/)
    file(COPY ../${LABORATORY_LIBRARY}/resources/ DESTINATION ${RESOURCE_DIR}/)
endif()


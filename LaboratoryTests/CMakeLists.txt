project(LaboratoryTests)

set(TEST_FILES
    gtest_main.cpp
        LaboratoryTest.cpp ComponentTest.cpp WorkingLaboratoryTest.cpp ZPMTest.cpp SwitchTest.cpp)

# Include the LaboratoryLib source directory to support testing of any classes there
include_directories("../${LABORATORY_LIBRARY}")

# Get Google Tests
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directories we need for Google Test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Tests_run target
add_executable(${PROJECT_NAME}_run ${TEST_FILES})

# linking Tests_run with library which will be tested and wxWidgets
target_link_libraries(${PROJECT_NAME}_run ${LABORATORY_LIBRARY} ${wxWidgets_LIBRARIES} )

# linking Tests_run with the Google Test libraries
target_link_libraries(${PROJECT_NAME}_run gtest)

target_precompile_headers(${PROJECT_NAME}_run PRIVATE "../${LABORATORY_LIBRARY}/pch.h")

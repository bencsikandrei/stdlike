project(libtest)

message("-- Tests enabled")

include(
    ${CMAKE_SOURCE_DIR}/cmake/Testing.cmake
)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

set(TEST_SRC 
    testMain.cpp
    algorithm/TestHysteresisComparator.cpp
    algorithm/TestFindAll.cpp
    algorithm/TestTransformIf.cpp
    traits/TestHasCertainMethod.cpp
)

add_gtest(TCNAME ${PROJECT_NAME} SOURCE_FILES ${TEST_SRC} LIBS stdlike gtest gmock pthread)

add_test(NAME ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test
    COMMAND ./${PROJECT_NAME}
)
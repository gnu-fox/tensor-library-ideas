find_package(GTest REQUIRED CONFIG)
include(GoogleTest)

add_executable(${PROJECT_NAME}Tests test_array)
target_link_libraries(${PROJECT_NAME}Tests PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main GTest::gmock)
target_compile_features(${PROJECT_NAME}Tests PRIVATE cxx_std_23)
gtest_add_tests(TARGET ${PROJECT_NAME}Tests)
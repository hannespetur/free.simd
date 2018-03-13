# Add catch
add_library(catch SHARED main.cpp)
set_property(TARGET catch PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(catch INTERFACE ${CMAKE_SOURCE_DIR}/test/include)

## Add test folder
add_subdirectory(api)
#add_subdirectory(doc)
#add_subdirectory(architecture)
#add_subdirectory(constant)
#add_subdirectory(function)
#add_subdirectory(regression)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose DEPENDS test_api)
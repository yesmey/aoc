add_executable(day08 main.cpp)
target_include_directories(day08 PRIVATE ${CMAKE_SOURCE_DIR}/include include)
configure_file(input ${CMAKE_CURRENT_BINARY_DIR}/input)
configure_file(test_input ${CMAKE_CURRENT_BINARY_DIR}/test_input)
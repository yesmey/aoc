add_executable(day01 main.cpp)
target_include_directories(day01 PRIVATE ${CMAKE_SOURCE_DIR}/include include)
configure_file(input ${CMAKE_CURRENT_BINARY_DIR}/input)
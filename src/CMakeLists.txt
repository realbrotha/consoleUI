project(ConsoleTest)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

set(INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/output_bin)

set(MODULE_NAME ConsoleTest)
set(SOURCES
        main.cpp
        include/ConsoleGUI.cpp
        include/ConsoleImpl.hpp)

include_directories(${INC_PATH})

add_executable(${MODULE_NAME} ${SOURCES})

set_property(TARGET ${MODULE_NAME} PROPERTY OUTPUT_NAME ${MODULE_NAME})

install(
        TARGETS ${MODULE_NAME}
        RUNTIME DESTINATION ${BIN_PATH})
project(ConsoleUI)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

set(INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(MODULE_NAME con)
set(SOURCES
        main.cpp)

include_directories(${INC_PATH})

add_executable(${MODULE_NAME} ${SOURCES})

set_property(TARGET ${MODULE_NAME} PROPERTY OUTPUT_NAME ${MODULE_NAME})

install(
        TARGETS ${MODULE_NAME}
        RUNTIME DESTINATION ${BIN_PATH})
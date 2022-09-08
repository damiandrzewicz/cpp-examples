cmake_minimum_required(VERSION 3.12)
project(main)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${PROJECT_DIR}/*.cpp
)

add_executable(${EXECUTABLE}
    ${PROJECT_SOURCES}
)

# target_compile_options(${EXECUTABLE} PRIVATE
# ${CPU_PARAMETERS}
#     -Wall
#     -Wextra
#     -Wpedantic
#     -Wshadow
#     -Wdouble-promotion
#     -Wformat=2 -Wformat-truncation
#     -Wundef
#     -fno-common
#     -Wno-unused-parameter
#     $<$<COMPILE_LANGUAGE:CXX>:
#         -Wconversion # STM libraries!
#         -Wno-volatile
#         -Wold-style-cast
#         -Wuseless-cast
#         -Wsuggest-override>
#     $<$<CONFIG:Debug>:-Og -g3 -ggdb>
#     $<$<CONFIG:Release>:-Og -g0>)

# target_link_options(${EXECUTABLE} PRIVATE
#     -T${MCU_LINKER_SCRIPT}
#     ${CPU_PARAMETERS}
#     -Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE}.map
#     --specs=nosys.specs
#     -Wl,--start-group
#     -lc
#     -lm
#     -lstdc++
#     -Wl,--end-group
#     -Wl,--print-memory-usage
# )


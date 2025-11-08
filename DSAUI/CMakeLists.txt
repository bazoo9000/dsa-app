file(GLOB_RECURSE UIMAIN_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(DSAUI ${UIMAIN_SOURCES})

target_include_directories(DSAUI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(DSAUI PRIVATE DataStructuresAndAlgorithms)

target_include_directories(DSAUI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendors/json/single_include/nlohmann/
)
# add_subdirectory(vendors/lib) # if has cmake
# target_link_libraries(DSAUI PRIVATE someLib anotherLib)
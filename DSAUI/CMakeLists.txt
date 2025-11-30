file(GLOB_RECURSE UIMAIN_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(DSAUI ${UIMAIN_SOURCES})

target_include_directories(DSAUI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# DSA CORE
target_link_libraries(DSAUI PRIVATE DataStructuresAndAlgorithms)

# NLOHMANN JSON
target_include_directories(DSAUI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendors/json/single_include/nlohmann/
)

# OPENGL (GLAD)
target_include_directories(DSAUI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendors/glad/include/
)

target_sources(DSAUI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendors/glad/src/glad.c
)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendors/glfw/)
target_link_libraries(DSAUI PRIVATE glfw)

# IMGUI
set(IMGUI_SOURCES
    vendors/imgui/imgui.cpp
    vendors/imgui/imgui_draw.cpp
    vendors/imgui/imgui_tables.cpp
    vendors/imgui/imgui_widgets.cpp
    vendors/imgui/imgui_demo.cpp
    vendors/imgui/backends/imgui_impl_glfw.cpp
    vendors/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(DSAUI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendors/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/vendors/imgui/backends
)

target_sources(DSAUI PRIVATE ${IMGUI_SOURCES})

# add_subdirectory(vendors/lib) # if has cmake
# target_link_libraries(DSAUI PRIVATE someLib anotherLib)
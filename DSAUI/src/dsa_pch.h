#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

// STL
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

#include <cstdio>
#include <cstdarg>
#include <cstdint>

#include <utility>
#include <memory>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <random>

#include <type_traits>

// Vendor
#include "json.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#define IMGUI_DEFINE_MATH_OPERATORS // WARNING! IF ADDING GLM IN THE FUTURE REMOVE THIS!!!!
#include "imgui.h"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_opengl3_loader.h"
#include "backends/imgui_impl_glfw.h"
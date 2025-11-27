#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

// STL
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>

#include <cstdio>
#include <cstdarg>
#include <cstdint>

#include <utility>
#include <memory>
#include <algorithm>
#include <functional>

#include <type_traits>

// Vendor
#include "json.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_opengl3_loader.h"
#include "backends/imgui_impl_glfw.h"
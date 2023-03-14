#pragma once

//All core libraries to be included

//std
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <map>
#include <unordered_map>

//custom
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

#include <glad/gl.h>

//in-engine
#include <engine/utils/EngineUtils.h>

#define _USE_MATH_DEFINES

#ifndef GLAD_ONLY_HEADERS
#define GLAD_GL_IMPLEMENTATION
#endif

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
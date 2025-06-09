#pragma once

// Librerías  
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>

#include <SFML/Graphics.hpp>

// Libera de forma segura un puntero y lo pone en nullptr
#define SAFE_PTR_RELEASE(x) if (x != nullptr) { delete x; x = nullptr; }

// Macro para mostrar un mensaje de creación de recurso
#define MESSAGE(classObj, method, state)                           \
{                                                                  \
    std::ostringstream os_;                                        \
    os_ << classObj << "::" << method << " : "                     \
        << "[CREATION OF RESOURCE: " << state << "]\n";            \
    std::cerr << os_.str();                                        \
}

// Macro para mostrar errores en consola y cerrar la aplicación
#define ERROR(classObj, method, errorMSG)                          \
{                                                                  \
    std::ostringstream os_;                                        \
    os_ << "ERROR : " << classObj << "::" << method << " : "       \
        << "Error in data from params [" << errorMSG << "]\n";     \
    std::cerr << os_.str();                                        \
    exit(1);                                                       \
}

// Enumeraciones 

enum
  ShapeType
{
  EMPTY = 0,
  CIRCLE = 1,
  RECTANGLE = 2,
  TRIANGLE = 3,
  POLYGON = 4
};

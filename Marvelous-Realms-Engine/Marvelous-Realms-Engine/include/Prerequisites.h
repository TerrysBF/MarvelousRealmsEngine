#pragma once

/// @file
/// @brief Definiciones comunes, macros y enumeraciones para el proyecto.

// Librerías estándar
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>

// Librerías de terceros
#include <SFML/Graphics.hpp>

/// @brief Libera de forma segura un puntero asignado dinámicamente y lo establece en nullptr.
/// @param x Puntero a liberar.
#define SAFE_PTR_RELEASE(x) if (x != nullptr) { delete x; x = nullptr; }

/// @brief Muestra un mensaje en consola indicando la creación de un recurso.
/// @param classObj Nombre de la clase donde ocurre.
/// @param method Nombre del método donde se llama.
/// @param state Estado del recurso (por ejemplo: "OK", "FAILED").
#define MESSAGE(classObj, method, state)                           \
{                                                                  \
    std::ostringstream os_;                                        \
    os_ << classObj << "::" << method << " : "                     \
        << "[CREATION OF RESOURCE: " << state << "]\n";            \
    std::cerr << os_.str();                                        \
}

/// @brief Muestra un mensaje de error en consola, incluye detalles del parámetro con error, y finaliza el programa.
/// @param classObj Nombre de la clase donde ocurre el error.
/// @param method Nombre del método donde se detecta el error.
/// @param errorMSG Descripción del error detectado.
#define ERROR(classObj, method, errorMSG)                          \
{                                                                  \
    std::ostringstream os_;                                        \
    os_ << "ERROR : " << classObj << "::" << method << " : "       \
        << "Error in data from params [" << errorMSG << "]\n";     \
    std::cerr << os_.str();                                        \
    exit(1);                                                       \
}

/// @enum ShapeType
/// @brief Enumeración que define los tipos de figuras geométricas que se pueden crear o renderizar.
enum ShapeType {
  EMPTY = 0,      ///< Valor por defecto, sin figura.
  CIRCLE = 1,     ///< Figura de tipo círculo.
  RECTANGLE = 2,  ///< Figura de tipo rectángulo.
  TRIANGLE = 3,   ///< Figura de tipo triángulo.
  POLYGON = 4     ///< Figura de tipo polígono con múltiples vértices.
};
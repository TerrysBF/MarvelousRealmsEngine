#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <map>
#include <fstream>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include "Memory/TSharedPointer.h"
#include "Memory/TWeakPointer.h"
#include "Memory/TStaticPtr.h"
#include "Memory/TUniquePtr.h"

/**
 * @brief Libera memoria de un puntero y lo pone en nullptr.
 * @param x Puntero a liberar.
 *
 * Uso seguro para punteros crudos (no smart pointers):
 * @code
 * SAFE_PTR_RELEASE(miPuntero);
 * @endcode
 */
#define SAFE_PTR_RELEASE(x) if (x != nullptr) { delete x; x = nullptr; }

 /**
  * @brief Mensaje de creación de recurso para debug.
  * @param classObj Nombre de la clase.
  * @param method   Nombre del método.
  * @param state    Estado o descripción.
  */
#define MESSAGE(classObj, method, state)                       \
{                                                              \
    std::ostringstream os_;                                    \
    os_ << classObj << "::" << method << " : "                  \
        << "[CREATION OF RESOURCE: " << state << "]\n";         \
    std::cerr << os_.str();                                     \
}

  /**
   * @brief Mensaje de error crítico con cierre de programa.
   * @param classObj Nombre de la clase.
   * @param method   Nombre del método.
   * @param errorMSG Mensaje descriptivo del error.
   *
   * Llama a exit(1) tras imprimir el error.
   */
#define ERROR(classObj, method, errorMSG)                           \
{                                                                   \
    std::ostringstream os_;                                         \
    os_ << "ERROR : " << classObj << "::" << method << " : "        \
        << "Error in data from params [" << errorMSG << "]\n";      \
    std::cerr << os_.str();                                         \
    exit(1);                                                        \
}

   /**
    * @brief Tipos de forma disponibles para CShape.
    */
enum ShapeType {
  EMPTY = 0,    ///< Sin forma asignada.
  CIRCLE = 1,   ///< Círculo (sf::CircleShape).
  RECTANGLE = 2,///< Rectángulo (sf::RectangleShape).
  TRIANGLE = 3, ///< Triángulo (sf::ConvexShape de 3 puntos).
  POLYGON = 4   ///< Polígono genérico.
};

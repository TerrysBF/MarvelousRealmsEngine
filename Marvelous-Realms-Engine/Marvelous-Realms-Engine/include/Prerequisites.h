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
#include "Memory\TSharedPointer.h"
#include "Memory\TWeakPointer.h"
#include "Memory\TStaticPtr.h"
#include "Memory\TUniquePtr.h"

// ImGui
#include <imgui.h>
#include <imgui-SFML.h>

// ==============================
// ?? Macros de utilidad
// ==============================

/**
 * @brief Libera un puntero y lo pone en `nullptr` de forma segura.
 * @param x Puntero a liberar.
 */
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

 /**
  * @brief Macro para mostrar un mensaje de creación de recurso.
  * @param classObj Nombre de la clase.
  * @param method Nombre del método.
  * @param state Estado o descripción.
  */
#define MESSAGE(classObj, method, state)                      \
{                                                             \
    std::ostringstream os_;                                   \
    os_ << classObj << "::" << method << " : "                 \
        << "[CREATION OF RESOURCE: " << state << "]\n";        \
    std::cerr << os_.str();                                   \
}

  /**
   * @brief Macro para mostrar un mensaje de error y finalizar el programa.
   * @param classObj Nombre de la clase.
   * @param method Nombre del método.
   * @param errorMSG Descripción del error.
   */
#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
    std::ostringstream os_;                                       \
    os_ << "ERROR : " << classObj << "::" << method << " : "      \
        << "  Error in data from params [" << errorMSG << "]\n";  \
    std::cerr << os_.str();                                       \
    exit(1);                                                      \
}

   // ==============================
   // ?? Enumeraciones globales
   // ==============================

   /**
    * @enum ShapeType
    * @brief Tipos de formas soportadas por el motor.
    */
enum ShapeType {
  EMPTY = 0,    ///< Sin forma.
  CIRCLE = 1,   ///< Círculo.
  RECTANGLE = 2,///< Rectángulo.
  TRIANGLE = 3, ///< Triángulo.
  POLYGON = 4   ///< Polígono genérico.
};

/**
 * @enum ConsolErrorType
 * @brief Tipos de mensaje que se pueden mostrar en consola.
 */
enum ConsolErrorType {
  INFO = 0,     ///< Mensaje informativo.
  WARNING = 1,  ///< Advertencia.
  ERROR = 2     ///< Error.
};

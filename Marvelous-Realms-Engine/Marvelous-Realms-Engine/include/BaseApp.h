#pragma once

#include <Prerequisites.h>
#include "Window.h"

/**
 * @class BaseApp
 * @brief Clase principal encargada de manejar el ciclo de vida de la aplicación.
 */
class
  BaseApp {
public:
  /**
   * @brief Constructor por defecto.
   */
  BaseApp() = default;

  /**
   * @brief Destructor.
   */
  ~BaseApp();

  /**
   * @brief Ejecuta el ciclo principal de la aplicación.
   * @return Código de salida (0 si finaliza correctamente).
   */
  int run();

  /**
   * @brief Inicializa los recursos de la aplicación.
   * @return true si la inicialización fue exitosa, false en caso contrario.
   */
  bool init();

  /**
   * @brief Actualiza la lógica de la aplicación por frame.
   */
  void update();

  /**
   * @brief Renderiza los elementos gráficos.
   */
  void render();

  /**
   * @brief Libera recursos y cierra la aplicación.
   */
  void destroy();

private:
  Window* m_window = nullptr;         ///< Ventana principal
  sf::CircleShape* m_circle = nullptr; ///< Elemento gráfico de ejemplo
};
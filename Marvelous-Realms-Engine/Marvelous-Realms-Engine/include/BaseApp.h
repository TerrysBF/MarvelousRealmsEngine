#pragma once

#include <Prerequisites.h>
#include "Window.h"

// Clase principal de la aplicación.
// Encargada de inicializar, ejecutar, actualizar y renderizar el contenido.
class
  BaseApp {
public:
  BaseApp() = default;
  ~BaseApp();

  // Ejecuta la aplicación desde main.
  int run();

  // Inicializa los componentes necesarios.
  bool init();

  // Actualización por frame.
  void update();

  // Renderizado de elementos gráficos.
  void render();

  // Libera recursos y finaliza la aplicación.
  void destroy();

private:
  Window* m_window = nullptr;        // Ventana principal de la aplicación
  sf::CircleShape* m_circle = nullptr; // Elemento gráfico de ejemplo
};

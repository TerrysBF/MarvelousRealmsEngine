#pragma once

#include <Prerequisites.h>
#include "Window.h"

// Clase principal de la aplicaci�n.
// Encargada de inicializar, ejecutar, actualizar y renderizar el contenido.
class
  BaseApp {
public:
  BaseApp() = default;
  ~BaseApp();

  // Ejecuta la aplicaci�n desde main.
  int run();

  // Inicializa los componentes necesarios.
  bool init();

  // Actualizaci�n por frame.
  void update();

  // Renderizado de elementos gr�ficos.
  void render();

  // Libera recursos y finaliza la aplicaci�n.
  void destroy();

private:
  Window* m_window = nullptr;        // Ventana principal de la aplicaci�n
  sf::CircleShape* m_circle = nullptr; // Elemento gr�fico de ejemplo
};

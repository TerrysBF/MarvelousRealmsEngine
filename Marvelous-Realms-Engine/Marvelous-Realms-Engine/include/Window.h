#pragma once

#include "Prerequisites.h"

// Clase encargada de manejar la ventana principal de la aplicación.
class
  Window {
public:
  Window() = default;

  // Constructor con tamaño y título
  Window(int width, int height, const std::string& title);

  ~Window();

  // Maneja los eventos del sistema (teclado, ratón, etc.)
  void handleEvents();

  // Verifica si la ventana está abierta
  bool isOpen() const;

  // Limpia la pantalla con un color específico
  void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

  // Dibuja un objeto en pantalla
  void draw(const sf::Drawable& drawable, const 
    sf::RenderStates& states = sf::RenderStates::Default);

  // Muestra el contenido actual en la ventana
  void display();

  // Cierra la ventana y libera recursos
  void destroy();

private:
  sf::RenderWindow* m_window = nullptr; // Ventana renderizada con SFML
};

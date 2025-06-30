#pragma once

#include "Prerequisites.h"

/**
 * @class Window
 * @brief Clase encargada de manejar una ventana gráfica usando SFML.
 */
class
  Window {
public:
  /**
   * @brief Constructor por defecto.
   */
  Window() = default;

  /**
   * @brief Constructor que inicializa la ventana con dimensiones y título.
   * @param width Ancho de la ventana.
   * @param height Alto de la ventana.
   * @param title Título que aparecerá en la barra superior.
   */
  Window(int width, int height, const std::string& title);

  /**
   * @brief Destructor.
   */
  ~Window();

  /**
   * @brief Maneja eventos del sistema como teclado y ratón.
   */
  void 
  handleEvents();

  /**
   * @brief Verifica si la ventana sigue abierta.
   * @return true si la ventana está abierta, false en caso contrario.
   */
  bool 
  isOpen() const;

  /**
   * @brief Limpia la ventana con un color determinado.
   * @param color Color de fondo (por defecto negro opaco).
   */
  void 
  clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

  /**
   * @brief Dibuja un objeto en la ventana.
   * @param drawable Objeto que puede ser renderizado.
   * @param states Opcionales estados de renderizado (por defecto: RenderStates::Default).
   */
  void 
  draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

  /**
   * @brief Muestra el contenido renderizado en pantalla.
   */
  void 
  display();

  /**
   * @brief Libera recursos y cierra la ventana.
   */
  void 
  destroy();

private:
  EngineUtilities::TUniquePtr<sf::RenderWindow> m_windowPtr;
  sf::RenderWindow* m_window = nullptr; ///< Puntero a la ventana renderizada por SFML
};

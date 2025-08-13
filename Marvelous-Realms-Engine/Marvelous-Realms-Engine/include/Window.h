#pragma once
#include "Prerequisites.h"

class EngineGUI;

/**
 * @brief Wrapper de sf::RenderWindow que integra el sistema de GUI y utilidades del engine.
 *
 * Ofrece:
 *  - Creación y manejo de la ventana principal.
 *  - Gestión de eventos (con reenvío a EngineGUI).
 *  - Ciclo de dibujado (`clear`, `draw`, `display`).
 *  - Control de deltaTime.
 */
class Window {
public:
  /// Constructor por defecto (no crea la ventana todavía).
  Window() = default;

  /**
   * @brief Crea la ventana con dimensiones y título dados.
   * @param width  Ancho en píxeles.
   * @param height Alto en píxeles.
   * @param title  Título de la ventana.
   */
  Window(int width, int height, const std::string& title);

  /// Destructor: asegura liberar la ventana.
  ~Window();

  /**
   * @brief Procesa eventos SFML y los reenvía a EngineGUI.
   * @param engineGUI Referencia al motor de GUI para propagarle los eventos.
   */
  void handleEvents(EngineGUI& engineGUI);

  /**
   * @brief Indica si la ventana sigue abierta.
   */
  bool isOpen() const;

  /**
   * @brief Limpia el frame buffer con un color dado.
   * @param color Color de limpieza (por defecto negro opaco).
   */
  void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

  /**
   * @brief Dibuja un objeto SFML en la ventana.
   * @param drawable Objeto que hereda de sf::Drawable.
   * @param states   Estados de render opcionales.
   */
  void draw(const sf::Drawable& drawable,
    const sf::RenderStates& states = sf::RenderStates::Default);

  /// Presenta en pantalla todo lo dibujado desde el último `clear()`.
  void display();

  /// Actualiza lógica interna (control de tiempo, entrada, etc.).
  void update();

  /// Función opcional para centralizar renderizado.
  void render();

  /// Cierra y libera recursos de la ventana.
  void destroy();

private:
  /// Vista SFML asociada a la ventana (controla zoom, desplazamiento, etc.).
  sf::View m_view;

public:
  /// Puntero único a la ventana SFML real.
  EngineUtilities::TUniquePtr<sf::RenderWindow> m_windowPtr;

  /// Tiempo transcurrido entre frames (delta time).
  sf::Time deltaTime;

  /// Reloj para medir delta time.
  sf::Clock clock;
};

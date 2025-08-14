#pragma once
#include "Prerequisites.h"
class EngineGUI;

/**
 * @class Window
 * @brief Encapsula una ventana SFML y operaciones básicas de renderizado.
 *
 * @details
 * - Administra un `sf::RenderWindow` usando `TUniquePtr`.
 * - Proporciona funciones para eventos, dibujo y ciclo de renderizado.
 * - Calcula `deltaTime` en cada `update()` para lógica dependiente del tiempo.
 */
class Window {
public:
  Window() = default;

  /**
   * @brief Crea una ventana con tamaño y título especificados.
   * @param width Ancho en píxeles.
   * @param height Alto en píxeles.
   * @param title Texto del título de la ventana.
   */
  Window(int width, int height, const std::string& title);

  /// Destructor: libera la ventana.
  ~Window();

  /**
   * @brief Procesa eventos y los pasa a la GUI.
   * @param engineGUI Referencia a la interfaz EngineGUI para manejar eventos.
   */
  void 
    handleEvents(EngineGUI& engineGUI);

  /**
   * @brief Indica si la ventana sigue abierta.
   * @return `true` si está abierta, `false` en caso contrario.
   */
  bool 
    isOpen() const;

  /**
   * @brief Limpia la ventana con un color dado.
   * @param color Color de limpieza (por defecto negro).
   */
  void 
    clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

  /**
   * @brief Dibuja un elemento en la ventana.
   * @param drawable Objeto SFML dibujable.
   * @param states Estados de render opcionales (por defecto, ninguno).
   */
  void 
    draw(const sf::Drawable& drawable,
    const sf::RenderStates& states = sf::RenderStates::Default);

  /// Muestra en pantalla todo lo dibujado.
  void 
    display();

  /// Calcula deltaTime para el frame actual.
  void 
    update();

  /// Punto para lógica de renderizado adicional (vacío por defecto).
  void 
    render();

  /// Libera y destruye la ventana.
  void 
    destroy();

private:
  sf::View m_view; ///< Vista de la cámara utilizada en la ventana.

public:
  EngineUtilities::TUniquePtr<sf::RenderWindow> m_windowPtr; ///< Puntero único a la ventana SFML.
  sf::Time deltaTime; ///< Tiempo transcurrido entre frames.
  sf::Clock clock; ///< Reloj para calcular deltaTime.
};

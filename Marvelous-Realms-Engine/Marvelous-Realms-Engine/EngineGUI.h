#pragma once
#include "Prerequisites.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/System/Time.hpp>
#include <map>
#include <vector>
#include <string>

class Window;
class Actor;

/**
 * @brief Capa de UI del engine basada en ImGui (con integración SFML).
 *
 * Responsabilidades:
 *  - Inicializar/actualizar/renderizar ImGui por frame.
 *  - Propagar eventos de SFML hacia ImGui.
 *  - Ventanas comunes: barra de menú, outliner, inspector, consola.
 *  - Widgets utilitarios (ej. vec2Control).
 *
 * Uso típico por frame:
 *  - processEvent(...) por cada evento de SFML.
 *  - update(window, dt) para construir la UI.
 *  - render(window) para dibujarla.
 *  - destroy() al cerrar la app.
 */
class EngineGUI {
public:
  /// Constructor/Destructor triviales: init/destroy hacen el trabajo real.
  EngineGUI() = default;
  ~EngineGUI() = default;

  /**
   * @brief Inicializa ImGui y la integración con SFML.
   * @param window Ventana del engine (wrapper de SFML).
   */
  void init(const EngineUtilities::TSharedPointer<Window>& window);

  /**
   * @brief Inicia un frame de ImGui y construye las ventanas de UI.
   * @param window Ventana activa (necesaria para el backend de ImGui-SFML).
   * @param deltaTime Tiempo transcurrido desde el último frame.
   */
  void update(const EngineUtilities::TSharedPointer<Window>& window,
    sf::Time deltaTime);

  /**
   * @brief Renderiza la UI acumulada del frame actual.
   * @param window Ventana destino del dibujado.
   */
  void render(const EngineUtilities::TSharedPointer<Window>& window);

  /// @brief Apaga ImGui y libera recursos asociados a la UI.
  void destroy();

  /**
   * @brief Reenvía un evento de SFML a ImGui (teclado, mouse, etc.).
   * @param window Referencia a la ventana SFML subyacente.
   * @param event  Evento SFML recibido en el loop de eventos.
   *
   * Debe llamarse por cada evento capturado en el game loop.
   */
  void processEvent(const sf::Window& window, const sf::Event& event);

  /// @brief Aplica un estilo gris claro a la UI.
  void setupGreyGUIStyle();

  /// @brief Aplica un estilo oscuro (dark) a la UI.
  void setupDarkGUIStyle();

  /// @brief Barra de menú (File, View, Help…).
  void barMenu();

  /**
   * @brief Panel Outliner: lista de actores para selección.
   * @param actors Vector de actores manejados por la escena.
   */
  void outliner(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

  /**
   * @brief Panel de consola: mensajes por tipo de error/estado.
   * @param programMessages Mapa de tipo ? lista de strings.
   */
  void console(const std::map<ConsolErrorType, std::vector<std::string>>& programMessages);

  /**
   * @brief Panel Inspector: edita/visualiza propiedades del actor seleccionado.
   * @param actors Vector de actores disponibles.
   */
  void inspector(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

  /**
   * @brief Control reusable para editar un vec2 (dos floats) con reset.
   * @param label        Título del control.
   * @param values       Apunta a dos floats consecutivos (x,y).
   * @param resetValues  Valor a aplicar al presionar "Reset".
   * @param columnWidth  Ancho de columna para el label.
   */
  void vec2Control(const std::string& label,
    float* values,
    float resetValues = 0.0f,
    float columnWidth = 100.0f);

private:
  /// Índice del actor seleccionado en el outliner (-1 si ninguno).
  int selectedActorIndex = -1;
};

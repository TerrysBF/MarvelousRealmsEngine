#pragma once
#include "Prerequisites.h"

/**
 * @file EngineGUI.h
 * @brief Definición de la clase EngineGUI para la interfaz gráfica en el motor.
 *
 * Esta clase encapsula toda la lógica y configuración de la interfaz de usuario
 * usando ImGui, incluyendo menús, paneles, consola y controles personalizados.
 */

 // ==============================
 // ?? Declaraciones adelantadas
 // ==============================
class Window;
class Actor;

/**
 * @class EngineGUI
 * @brief Sistema de interfaz gráfica para depuración y edición en tiempo real.
 *
 * Maneja menús, paneles, consola y controles dentro de la aplicación utilizando ImGui.
 * Permite inspeccionar actores, mostrar mensajes de consola y modificar propiedades
 * en tiempo de ejecución.
 */
class 
  EngineGUI {
public:
  EngineGUI() = default;               ///< Constructor por defecto.
  ~EngineGUI() = default;              ///< Destructor por defecto.

  /**
   * @brief Inicializa el sistema de GUI con una ventana de render.
   * @param window Puntero compartido a la ventana del motor.
   */
  void 
    init(const EngineUtilities::TSharedPointer<Window>& window);

  /**
   * @brief Actualiza el estado de la GUI.
   * @param window Puntero compartido a la ventana del motor.
   * @param deltaTime Tiempo transcurrido desde el último frame.
   */
  void 
    update(const EngineUtilities::TSharedPointer<Window>& window,
    sf::Time deltaTime);

  /**
   * @brief Renderiza la interfaz gráfica en la ventana.
   * @param window Puntero compartido a la ventana del motor.
   */
  void 
    render(const EngineUtilities::TSharedPointer<Window>& window);

  /**
   * @brief Libera recursos y destruye el sistema de GUI.
   */
  void 
    destroy();

  /**
   * @brief Procesa eventos de la ventana (por ejemplo, entradas de teclado o ratón).
   * @param window Referencia a la ventana SFML.
   * @param event Evento capturado por SFML.
   */
  void 
    processEvent(const sf::Window& window, const sf::Event& event);

  /**
   * @brief Aplica un estilo de GUI gris personalizado.
   */
  void 
    setupGreyGUIStyle();

  /**
   * @brief Aplica un estilo de GUI oscuro.
   */
  void 
    setupDarkGUIStyle();

  /**
   * @brief Muestra y gestiona la barra de menú principal.
   */
  void 
    barMenu();

  /**
   * @brief Muestra la lista de actores en la escena.
   * @param actors Vector con punteros compartidos a los actores.
   */
  void 
    outliner(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

  /**
   * @brief Muestra la consola con mensajes de diferentes tipos.
   * @param programMessages Mapa con listas de mensajes clasificados por tipo de error.
   */
  void 
    console(const std::map<ConsolErrorType, std::vector<std::string>>& programMessages);

  /**
   * @brief Muestra el panel inspector para ver y editar propiedades de actores.
   * @param actors Vector con punteros compartidos a los actores.
   */
  void 
    inspector(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

  /**
   * @brief Control de entrada para modificar valores Vector2.
   * @param label Etiqueta del control.
   * @param values Puntero a los valores (x, y) que se van a modificar.
   * @param resetValues Valor por defecto para restablecer.
   * @param columnWidth Ancho de la columna de la etiqueta.
   */
  void 
    vec2Control(const std::string& label,
    float* values,
    float resetValues = 0.0f,
    float columnWidth = 100.0f);

private:
  int selectedActorIndex = -1; ///< Índice del actor actualmente seleccionado en el inspector.
};

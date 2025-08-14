#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include "ECS/Actor.h"
#include "EngineGUI.h"

/**
 * @class BaseApp
 * @brief Clase principal de la aplicación que gestiona la ventana, actores, GUI y lógica de carrera.
 *
 * Esta clase encapsula el ciclo de vida principal de la aplicación:
 * - Inicialización de recursos y sistemas.
 * - Actualización de lógica por frame.
 * - Renderizado de todos los elementos.
 * - Gestión de waypoints, meta, vueltas y tiempos de carrera.
 */
class BaseApp {
public:
  /**
   * @brief Constructor por defecto.
   */
  BaseApp() = default;

  /**
   * @brief Destructor.
   * Libera recursos y destruye la aplicación.
   */
  ~BaseApp();

  /**
   * @brief Ejecuta la aplicación desde el `main`.
   * @return Código de salida (0 = éxito).
   */
  int 
    run();

  /**
   * @brief Inicializa la aplicación, creando ventana, actores y sistemas.
   * @return `true` si la inicialización fue exitosa.
   */
  bool 
    init();

  /**
   * @brief Actualiza la lógica de la aplicación cada frame.
   */
  void 
    update();

  /**
   * @brief Renderiza todos los elementos gráficos.
   */
  void 
    render();

  /**
   * @brief Libera recursos y destruye la aplicación.
   */
  void 
    destroy();

private:
  /** Lista de actores en la escena. */
  std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors;

  /** Puntero a la ventana principal. */
  EngineUtilities::TSharedPointer<Window> m_windowPtr;

  /** Actor para representar un círculo de ejemplo. */
  EngineUtilities::TSharedPointer<Actor> m_ACirlce;

  /** Actor que representa la pista. */
  EngineUtilities::TSharedPointer<Actor> m_track;

  /** Sistema de interfaz gráfica. */
  EngineGUI m_engineGUI;

  /** Posiciones iniciales (spawn) para cada actor. */
  std::vector<sf::Vector2f> m_spawnPositions;

  /** Controla si los actores y el cronómetro están congelados. */
  bool 
    m_freezeActors = false;

  /**
   * @brief Restaura a todos los actores a sus posiciones iniciales.
   */
  void 
    resetActorsToSpawn();

  // --- Waypoints ---
  /** Lista de puntos de la trayectoria. */
  std::vector<sf::Vector2f> m_waypoints;

  /** Índice del waypoint actual. */
  int 
    m_currentWaypointIndex = 0;

  /** Formas para representar los waypoints visualmente. */
  std::vector<EngineUtilities::TSharedPointer<CShape>> 
    m_waypointMarkers;

  /** Control para mostrar u ocultar los marcadores de waypoint. */
  bool 
    m_drawWaypointMarkers = true;

  /**
   * @brief Carga los waypoints desde un archivo CSV.
   * @param path Ruta al archivo CSV.
   * @return `true` si la carga fue exitosa.
   */
  bool 
    loadWaypointsCSV(const std::string& path);

  /**
   * @brief Inicializa una pista por defecto con waypoints predefinidos.
   */
  void 
    initWaypoints_DefaultTrack();

  /**
   * @brief Construye los marcadores visuales de los waypoints.
   */
  void 
    buildWaypointMarkers();

  // --- Meta y vueltas ---
  /** Posición de la esquina superior izquierda de la meta. */
  sf::Vector2f m_finishPos{ 32.f, 329.f };

  /** Tamaño (ancho, alto) de la meta. */
  sf::Vector2f m_finishSize{ 40.f, 40.f };

  /** Número total de vueltas. */
  int 
    m_totalLaps = 3;

  /** Indica si la carrera ha comenzado. */
  bool 
    m_raceStarted = false;

  /** Indica si la carrera ha terminado. */
  bool 
    m_raceFinished = false;

  /** Tiempo total de la carrera en segundos. */
  float 
    m_raceTime = 0.f;

  /** Vueltas completadas por cada actor. */
  std::vector<int> m_laps;

  /** Estado previo de cada actor respecto a si estaba en la meta. */
  std::vector<bool> m_prevInsideFinish;

  /** Tiempo actual de vuelta para cada actor. */
  std::vector<float> m_currLapTime;

  /** Mejor tiempo de vuelta por actor. */
  std::vector<float> m_bestLapTime;

  /** Muestra la línea de meta para depuración. */
  bool 
    m_showFinishLine = true;

  /** Actor usado para dibujar la meta en depuración. */
  EngineUtilities::TSharedPointer<Actor> m_finishLineDebug;

  /**
   * @brief Verifica si un punto está dentro del área de meta.
   * @param p Punto a verificar.
   * @return `true` si el punto está dentro.
   */
  inline bool 
    isInsideFinish(const sf::Vector2f& p) const {
    return (p.x >= m_finishPos.x && p.x <= m_finishPos.x + m_finishSize.x &&
      p.y >= m_finishPos.y && p.y <= m_finishPos.y + m_finishSize.y);
  }

  /**
   * @brief Inicializa las variables y estructuras para el sistema de carrera.
   */
  void 
    initRaceSystems();

  /**
   * @brief Actualiza la lógica de la carrera (vueltas, tiempos, meta).
   * @param dt Tiempo transcurrido desde el último frame.
   */
  void 
    updateRaceSystems(float dt);

  /**
   * @brief Convierte un tiempo en segundos a formato mm:ss.ms.
   * @param s Tiempo en segundos.
   * @return Cadena formateada.
   */
  static std::string formatTime(float s);
};

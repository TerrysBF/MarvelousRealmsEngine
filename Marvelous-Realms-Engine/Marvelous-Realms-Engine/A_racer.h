#pragma once
#include "ECS/Actor.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <string>

/**
 * @class A_Racer
 * @brief Actor especializado que representa un corredor en la pista.
 *
 * Implementa comportamiento de IA para seguir una ruta de waypoints,
 * gestionar vueltas, meta y parámetros de movimiento.
 */
class 
  A_Racer : public Actor {
public:
  /**
   * @brief Constructor del corredor.
   * @param name Nombre del actor.
   * @param playerId ID del jugador (0 por defecto).
   */
  explicit 
    A_Racer(const std::string& name, int playerId = 0);

  /**
   * @brief Inicializa el actor.
   * (En este caso no realiza acciones adicionales).
   */
  void 
    start() override {}

  /**
   * @brief Actualiza la lógica del corredor.
   * @param dt Delta time (segundos desde el último frame).
   */
  void 
    update(float dt) override;

  // ======================
  //   Configuración Ruta
  // ======================

  /**
   * @brief Define la ruta que seguirá el corredor.
   * @param pathPoints Vector de puntos (waypoints) en coordenadas del mundo.
   */
  void 
    setPath(const std::vector<sf::Vector2f>& pathPoints);

  /**
   * @brief Reinicia el estado del corredor (vuelta 0, waypoint inicial).
   */
  void 
    reset();

  // ======================
  //   Meta / Vueltas
  // ======================

  /**
   * @brief Asigna el área de la línea de meta.
   * @param rect Rectángulo de la meta.
   */
  void 
    setFinishLine(const sf::FloatRect& rect) { m_finishLine = rect; }

  /**
   * @brief Define el número total de vueltas requeridas.
   * @param laps Número de vueltas.
   */
  void 
    setTotalLaps(int laps) { m_totalLaps = laps; }

  /**
   * @brief Obtiene la vuelta actual del corredor.
   */
  int 
    getCurrentLap() const { return m_currentLap; }

  /**
   * @brief Obtiene el número total de vueltas configuradas.
   */
  int 
    getTotalLaps() const { return m_totalLaps; }

  /**
   * @brief Indica si el corredor ha completado la carrera.
   */
  bool 
    isFinished() const { return m_currentLap >= m_totalLaps; }

  // ======================
  //   Parámetros de Movimiento
  // ======================

  /**
   * @brief Define la velocidad máxima.
   * @param s Velocidad máxima en unidades por segundo.
   */
  void 
    setMaxSpeed(float s) { m_maxSpeed = s; }

  /**
   * @brief Define la distancia de anticipación al buscar el siguiente waypoint.
   * @param d Distancia en unidades.
   */
  void 
    setLookahead(float d) { m_lookaheadDistance = d; }

  /**
   * @brief Define el radio de llegada a un waypoint.
   * @param r Distancia mínima para considerar alcanzado el punto.
   */
  void 
    setArriveRadius(float r) { m_arriveRadius = r; }

  /**
   * @brief Define el desplazamiento lateral (simula carriles).
   * @param px Desplazamiento en píxeles.
   */
  void 
    setLateralOffset(float px) { m_lateralOffset = px; }

  /**
   * @brief Configura el "jitter" o variación aleatoria de velocidad.
   * @param pct Porcentaje de variación (+/-).
   * @param every Intervalo de tiempo para recalcular la variación.
   */
  void 
    setJitter(float pct, float every) 
    { m_jitterPct = pct; m_jitterInterval = every; }

  /**
   * @brief Obtiene la velocidad máxima configurada.
   */
  float 
    getMaxSpeed() const { return m_maxSpeed; }

  /**
   * @brief Devuelve el progreso en la vuelta actual (0 a 1).
   * @return Progreso como valor flotante.
   */
  float 
    getProgress() const;

private:
  /**
   * @brief Lógica de seguimiento de ruta (path following).
   * @param dt Delta time en segundos.
   */
  void 
    doPathFollowing(float dt);

  // Ruta y navegación
  std::vector<sf::Vector2f> m_path;   ///< Lista de waypoints.
  int m_currentWaypointIndex = 0;     ///< Índice del waypoint actual.

  // Parámetros de steering
  float m_lookaheadDistance = 140.f;  ///< Distancia de anticipación.
  float m_arriveRadius = 26.f;        ///< Radio de llegada.
  float m_maxSpeed = 200.f;           ///< Velocidad máxima.

  // IA / Ajustes visuales
  float m_lateralOffset = 0.f;        ///< Desplazamiento lateral (carril).
  float m_jitterPct = 0.0f;           ///< Variación porcentual de velocidad.
  float m_jitterInterval = 1.5f;      ///< Intervalo para recalcular jitter.
  float m_jitterTimer = 0.0f;         ///< Temporizador interno de jitter.
  float m_jitterScale = 1.0f;         ///< Escala actual de velocidad por jitter.

  // Gestión de vueltas
  sf::FloatRect m_finishLine{};       ///< Área de la meta.
  int  m_currentLap = 0;              ///< Vuelta actual.
  int  m_totalLaps = 3;               ///< Vueltas totales requeridas.
  bool m_crossedLastFrame = false;    ///< Estado previo de cruce de meta.
};

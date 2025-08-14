#pragma once

#include "ECS/Actor.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <string>

/**
 * @brief NPC/Player con Path Following (pure pursuit + arrive),
 *        conteo de vueltas y estado de carrera.
 */
class A_Racer : public Actor {
public:
  explicit A_Racer(const std::string& name, int playerId = 0);

  void start() override {}                // no usado por ahora
  void update(float deltaTime) override;  // ver .cpp

  // Asigna el path a seguir (normalmente m_waypoints de BaseApp)
  void setPath(const std::vector<sf::Vector2f>& pathPoints);

  // Reinicia a la posición inicial y estado de carrera
  void reset();

  // Línea de meta y vueltas
  void setFinishLine(const sf::FloatRect& rect) { m_finishLine = rect; }
  void setTotalLaps(int laps) { m_totalLaps = laps; }
  int  getCurrentLap() const { return m_currentLap; }
  int  getTotalLaps()  const { return m_totalLaps; }
  bool isFinished()    const { return m_currentLap >= m_totalLaps; }

  // Velocidad máxima (para diferenciar corredores)
  void  setMaxSpeed(float s) { m_maxSpeed = s; }
  float getMaxSpeed() const { return m_maxSpeed; }

  // Progreso aproximado dentro de la vuelta actual [0..1]
  float getProgress() const;

private:
  void doPathFollowing(float dt);   // steering hacia objetivo de persecución

  // --- Ruta ---
  std::vector<sf::Vector2f> m_path;
  int   m_currentWaypointIndex = 0;

  // --- Parámetros de steering ---
  float m_lookaheadDistance = 140.f;  // distancia de persecución (pure pursuit)
  float m_arriveRadius = 26.f;   // radio para “llegar” y pasar al siguiente
  float m_maxSpeed = 140.f;  // px/s

  // --- Meta / vueltas ---
  sf::FloatRect m_finishLine{};
  int  m_currentLap = 0;
  int  m_totalLaps = 3;
  bool m_crossedLastFrame = false;

  // --- Info opcional ---
  int  m_playerIndex = 0;
};

#include "A_Racer.h"
#include "ECS/Transform.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>

/**
 * @brief Magnitud (longitud) de un vector 2D.
 */
static inline float vlen(const sf::Vector2f& v) {
  return std::sqrt(v.x * v.x + v.y * v.y);
}

/**
 * @brief Normaliza un vector 2D (longitud 1). Si el vector es casi cero, regresa (0,0).
 */
static inline sf::Vector2f vnorm(const sf::Vector2f& v) {
  float L = vlen(v);
  return (L > 1e-5f) ? sf::Vector2f{ v.x / L, v.y / L } : sf::Vector2f{ 0.f,0.f };
}

/**
 * @brief Restringe un valor al rango [0,1].
 */
static inline 
float clamp01(float x) { return std::max(0.f, std::min(1.f, x)); }

/**
 * @brief Crea un corredor con nombre. El playerId se ignora en esta implementación.
 */
A_Racer::A_Racer(const std::string& name, int /*playerId*/)
  : Actor(name) {}

/**
 * @brief Define la ruta (lista de waypoints) que seguirá el corredor.
 * @details
 * - Sitúa al corredor en el primer punto de la ruta.
 * - Ajusta el índice de waypoint actual para evitar apuntar al mismo punto de spawn.
 * - Llama a Actor::update(0) para sincronizar el estado visual.
 */
void 
A_Racer::setPath(const std::vector<sf::Vector2f>& pathPoints) {
  m_path = pathPoints;

  if (!m_path.empty()) {
    if (auto xf = getComponent<Transform>()) {
      xf->setPosition(m_path.front());
      xf->setRotation(sf::Vector2f(0.f, 0.f)); // <- tu Transform usa Vector2f para rotación
    }
  }
  m_currentWaypointIndex = (m_path.size() > 1 ? 1 : 0);
  Actor::update(0.f);
}

/**
 * @brief Reinicia variables de carrera del corredor y lo regresa al inicio de la ruta.
 */
void 
A_Racer::reset() {
  m_currentLap = 0;
  m_crossedLastFrame = false;

  if (!m_path.empty()) {
    if (auto xf = getComponent<Transform>()) {
      xf->setPosition(m_path.front());
      xf->setRotation(sf::Vector2f(0.f, 0.f));
    }
  }
  m_currentWaypointIndex = (m_path.size() > 1 ? 1 : 0);
  Actor::update(0.f);
}

/**
 * @brief Progreso del corredor a lo largo de la ruta en [0,1).
 * @details
 * Calcula el porcentaje del segmento actual recorrido (proyectando la posición
 * sobre el tramo A->B) y suma el índice de A, todo normalizado por la cantidad
 * de segmentos. Útil para orden de posiciones.
 */
float 
A_Racer::getProgress() const {
  const int N = (int)m_path.size();
  if (N < 2) return 0.f;

  auto xf = const_cast<A_Racer*>(this)->getComponent<Transform>();
  sf::Vector2f pos = xf ? xf->getPosition() : m_path.front();

  const 
    int cur = (m_currentWaypointIndex % N);
  const 
    int prev = (cur + N - 1) % N;

  const 
    sf::Vector2f A = m_path[prev];
  const 
    sf::Vector2f B = m_path[cur];

  const 
    float segLen = std::max(1e-4f, vlen(B - A));
  // t = 0 en A, t = 1 en B (estimación por distancia restante a B)
  const 
    float t = 1.f - clamp01(vlen(B - pos) / segLen);
  return clamp01((prev + t) / float(N));
}

/**
 * @brief Actualiza la IA de seguimiento de ruta y (opcional) cruces de meta/laps.
 * @param dt Delta time.
 */
void 
A_Racer::update(float dt) {
  if (m_path.size() >= 2) {
    doPathFollowing(dt);

    // Detección simple de cruce de meta usando un rectángulo/forma (m_finishLine)
    bool inside = m_finishLine.contains(getComponent<Transform>()->getPosition());
    if (inside && !m_crossedLastFrame) ++m_currentLap;  
    m_crossedLastFrame = inside;
  }
  Actor::update(dt);
}

/**
 * @brief Algoritmo de path-following tipo "pursuit" con ajuste de velocidad por curvatura.
 * @details
 * Pasos principales:
 * 1) Determina el segmento actual A->B según m_currentWaypointIndex.
 * 2) Proyecta la posición del corredor sobre A->B para saber dónde está (t).
 * 3) Si ya pasaste B o te acercaste lo suficiente, avanza al siguiente segmento.
 * 4) Calcula un punto de persecución adelante sobre A->B usando m_lookaheadDistance.
 * 5) Aplica un offset lateral (carril) perpendicular a A->B.
 * 6) Estima curvatura local (ángulo entre AB y el siguiente tramo) para reducir velocidad.
 * 7) Aplica “jitter” a la velocidad (pequeña variación aleatoria) para romper patrones rígidos.
 * 8) Llama a Transform::seek hacia el punto objetivo con la velocidad local resultante.
 */
void 
A_Racer::doPathFollowing(float dt) {
  auto xf = getComponent<Transform>();
  if (!xf || m_path.size() < 2) return;

  sf::Vector2f pos = xf->getPosition();

  const int N = (int)m_path.size();
  int i = m_currentWaypointIndex;
  sf::Vector2f A = m_path[i];
  sf::Vector2f B = m_path[(i + 1) % N];
  sf::Vector2f AB = B - A;

  float 
    abLen2 = AB.x * AB.x + AB.y * AB.y;
  if (abLen2 < 1e-6f) {
    
    m_currentWaypointIndex = (i + 1) % N;
    return;
  }
  float 
    abLen = std::sqrt(abLen2);


  sf::Vector2f AP = pos - A;
  float 
    t = (AP.x * AB.x + AP.y * AB.y) / abLen2;

  float 
    distToB = std::hypot(pos.x - B.x, pos.y - B.y);
  if (t > 1.f || distToB < m_arriveRadius) {
    m_currentWaypointIndex = (i + 1) % N;
    i = m_currentWaypointIndex;
    A = m_path[i];
    B = m_path[(i + 1) % N];
    AB = B - A;
    abLen2 = AB.x * AB.x + AB.y * AB.y;
    if (abLen2 < 1e-6f) return;
    abLen = std::sqrt(abLen2);
    AP = pos - A;
    t = (AP.x * AB.x + AP.y * AB.y) / abLen2;
  }

  // Punto de persecución un poco por delante en el segmento
  float 
    s = std::clamp(t + (m_lookaheadDistance / std::max(abLen, 1e-3f)), 0.f, 1.f);
  sf::Vector2f pursue = A + AB * s;

  // Offset lateral 
  sf::Vector2f perp = vnorm(sf::Vector2f{ -AB.y, AB.x }); 
  pursue += perp * m_lateralOffset;

  sf::Vector2f NEXT = m_path[(i + 2) % N] - B;
  float 
    dot = AB.x * NEXT.x + AB.y * NEXT.y;
  float 
    m1 = std::max(1e-4f, vlen(AB));
  float 
    m2 = std::max(1e-4f, vlen(NEXT));
  float 
    cosang = std::clamp(dot / (m1 * m2), -1.f, 1.f);
  float 
    turn = std::acos(cosang);               
  float 
    curveFactor = 1.0f - 0.4f * (turn / 3.14159265f); 

  // “Jitter” de velocidad: ruido leve para que no se vean todos idénticos
  m_jitterTimer -= dt;
  if (m_jitterTimer <= 0.f) {
    m_jitterTimer = m_jitterInterval;
    float 
      r = (std::rand() / float(RAND_MAX)) * 2.f - 1.f; 
    m_jitterScale = 1.f + r * m_jitterPct;               
  }

  // Velocidad tope local = velocidad máxima * factor de curva * jitter
  float 
    localMax = m_maxSpeed * curveFactor * m_jitterScale;

  xf->seek(pursue, localMax, dt, m_arriveRadius);
}

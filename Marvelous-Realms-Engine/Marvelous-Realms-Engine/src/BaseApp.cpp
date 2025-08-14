#include "BaseApp.h"
#include "ResourceManager.h"
#include "EngineGUI.h"

#include "ECS/Actor.h"
#include "CShape.h"
#include "ECS/Transform.h"
#include "ECS/Texture.h"

#include "A_Racer.h"

#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <limits>

/**
 * @file BaseApp.cpp
 * @brief Lógica principal de la app: inicialización, bucle de juego, render y sistemas de carrera.
 *
 * @details
 * Contiene:
 * - Carga y construcción de waypoints (desde CSV o por defecto).
 * - Inicialización de pista, jugador y NPCs.
 * - Sistema de carrera (vueltas, tiempos por vuelta, meta).
 * - Integración con ImGui para HUD y paneles (Outliner/Inspector).
 * - Ciclo principal: handleEvents ? update ? render.
 */

 /**
  * @brief Carga waypoints desde un CSV con formato "x,y" (admite ';' y líneas comentadas con '#').
  * @param path Ruta al archivo CSV.
  * @return true si se cargaron puntos válidos; false si hubo error o archivo vacío.
  *
  * @note Si el archivo queda vacío, se retorna false y más adelante se usa una lista por defecto.
  */
bool 
BaseApp::loadWaypointsCSV(const std::string& path) {
  m_waypoints.clear();

  std::ifstream in(path);
  if (!in.is_open()) {
    std::cerr << "[Waypoints] No se pudo abrir: " << path << "\n";
    return false;
  }

  std::string line;
  while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#') continue;             // ignora comentarios
    for (char& c : line) if (c == ';') c = ',';                // soporta ';' como separador

    std::stringstream ss(line);
    float x, y; char comma;
    if (ss >> x >> comma >> y) {
      m_waypoints.emplace_back(x, y);
    }
  }

  if (m_waypoints.empty()) {
    std::cerr << "[Waypoints] Archivo vacío: " << path << "\n";
    return false;
  }
  m_currentWaypointIndex = (m_waypoints.size() > 1 ? 1 : 0);
  return true;
}

/**
 * @brief Convierte segundos a formato "mm:ss.mmm".
 * @param s Segundos (puede ser float).
 * @return Cadena formateada.
 */
std::string BaseApp::formatTime(float s) {
  if (s < 0.f) s = 0.f;
  int ms = int(std::round(s * 1000.f));
  int m = (ms / 1000) / 60;
  int sec = (ms / 1000) % 60;
  int mil = ms % 1000;
  char buf[32];
  std::snprintf(buf, sizeof(buf), "%02d:%02d.%03d", m, sec, mil);
  return std::string(buf);
}

/**
 * @brief Inicializa estructuras y estados del sistema de carrera (vueltas, tiempos, meta).
 *
 * @details
 * - Prepara los contadores por corredor (vueltas, mejor tiempo, etc.).
 * - Calcula el estado de “estaba dentro de meta” para evitar contar vuelta inmediata.
 * - Crea un actor de depuración para ver la línea de meta como rectángulo translúcido.
 */
void 
BaseApp::initRaceSystems() {
  const 
    size_t N = m_actors.size();
  m_laps.assign(N, 0);
  m_prevInsideFinish.assign(N, false);
  m_currLapTime.assign(N, 0.f);
  m_bestLapTime.assign(N, std::numeric_limits<float>::infinity());
  m_raceTime = 0.f;
  m_raceStarted = false;
  m_raceFinished = false;

  // Inicializa estado "prevInside" para no contar una vuelta inmediata
  for (size_t i = 0; i < N; ++i) {
    if (m_actors[i].isNull()) continue;
    auto xf = m_actors[i]->getComponent<Transform>();
    if (!xf) continue;
    m_prevInsideFinish[i] = isInsideFinish(xf->getPosition());

  }

  // Actor de línea de meta 
  m_finishLineDebug = EngineUtilities::MakeShared<Actor>("FinishLineDebug");
  m_finishLineDebug->getComponent<CShape>()->createShape(RECTANGLE);
  m_finishLineDebug->getComponent<CShape>()->setFillColor(sf::Color(0, 255, 0, 60));
  m_finishLineDebug->getComponent<Transform>()->setPosition(m_finishPos);
  m_finishLineDebug->getComponent<Transform>()->setScale(m_finishSize);
}

/**
 * @brief Actualiza el sistema de carrera (conteo de vueltas, mejores tiempos, fin de carrera).
 * @param dt Delta time del frame.
 *
 * @details
 * Cuenta una vuelta cuando hay transición de “fuera de meta” ? “dentro de meta”.
 * También actualiza tiempos de vuelta y marca la carrera como terminada cuando
 * todos alcanzan m_totalLaps.
 */
void 
BaseApp::updateRaceSystems(float dt) {
  if (m_raceStarted) {
    m_raceTime += dt;
  }

  for (size_t i = 0; i < m_actors.size(); ++i) {
    auto& a = m_actors[i];
    if (a.isNull()) continue;
    auto xf = a->getComponent<Transform>();
    if (!xf) continue;

    if (m_raceStarted) m_currLapTime[i] += dt;

    const 
      sf::Vector2f pos = xf->getPosition();
    const 
      bool inside = isInsideFinish(pos);

    // Conteo de vuelta: transición de fuera -> dentro
    if (m_raceStarted && inside && !m_prevInsideFinish[i]) {
      m_laps[i] += 1;

      // Mejor vuelta (evita micro-vuelta inicial)
      if (m_currLapTime[i] > 0.2f) {
        if (m_currLapTime[i] < m_bestLapTime[i]) {
          m_bestLapTime[i] = m_currLapTime[i];
        }
      }
      m_currLapTime[i] = 0.f;

      // Fin de carrera global simple (si todos llegaron a m_totalLaps)
      int finishedCount = 0;
      for (size_t k = 0; k < m_laps.size(); ++k)
        if (m_laps[k] >= m_totalLaps) ++finishedCount;
      if (finishedCount == (int)m_laps.size()) m_raceFinished = true;
    }

    m_prevInsideFinish[i] = inside;
  }
}

/**
 * @brief Inicializa una lista de waypoints por defecto (por si falla el CSV).
 * @details Ajusta estos puntos a la geometría de tu pista.
 */
void BaseApp::initWaypoints_DefaultTrack() {
  m_waypoints.clear();
  m_waypoints.push_back(sf::Vector2f(32.f, 483.f));
  m_waypoints.push_back(sf::Vector2f(30.f, 214.f));
  m_waypoints.push_back(sf::Vector2f(35.f, 110.f));
  m_waypoints.push_back(sf::Vector2f(72.f, 66.f));
  m_waypoints.push_back(sf::Vector2f(113.f, 37.f));
  m_waypoints.push_back(sf::Vector2f(195.f, 26.f));
  m_waypoints.push_back(sf::Vector2f(310.f, 38.f));
  m_waypoints.push_back(sf::Vector2f(354.f, 118.f));
  m_waypoints.push_back(sf::Vector2f(388.f, 212.f));
  m_waypoints.push_back(sf::Vector2f(424.f, 268.f));
  m_waypoints.push_back(sf::Vector2f(465.f, 261.f));
  m_waypoints.push_back(sf::Vector2f(523.f, 261.f));
  m_waypoints.push_back(sf::Vector2f(586.f, 253.f));
  m_waypoints.push_back(sf::Vector2f(622.f, 165.f));
  m_waypoints.push_back(sf::Vector2f(639.f, 92.f));
  m_waypoints.push_back(sf::Vector2f(665.f, 55.f));
  m_waypoints.push_back(sf::Vector2f(723.f, 32.f));
  m_waypoints.push_back(sf::Vector2f(864.f, 121.f));
  m_waypoints.push_back(sf::Vector2f(894.f, 183.f));
  m_waypoints.push_back(sf::Vector2f(908.f, 243.f));
  m_waypoints.push_back(sf::Vector2f(913.f, 295.f));
  m_waypoints.push_back(sf::Vector2f(894.f, 363.f));
  m_waypoints.push_back(sf::Vector2f(858.f, 405.f));
  m_waypoints.push_back(sf::Vector2f(792.f, 434.f));
  m_waypoints.push_back(sf::Vector2f(609.f, 478.f));
  m_waypoints.push_back(sf::Vector2f(412.f, 524.f));
  m_waypoints.push_back(sf::Vector2f(366.f, 551.f));
  m_waypoints.push_back(sf::Vector2f(367.f, 589.f));
  m_waypoints.push_back(sf::Vector2f(432.f, 643.f));
  m_waypoints.push_back(sf::Vector2f(530.f, 641.f));
  m_waypoints.push_back(sf::Vector2f(678.f, 633.f));
  m_waypoints.push_back(sf::Vector2f(745.f, 633.f));
  m_waypoints.push_back(sf::Vector2f(882.f, 648.f));
  m_waypoints.push_back(sf::Vector2f(899.f, 675.f));
  m_waypoints.push_back(sf::Vector2f(919.f, 717.f));
  m_waypoints.push_back(sf::Vector2f(912.f, 780.f));
  m_waypoints.push_back(sf::Vector2f(888.f, 858.f));
  m_waypoints.push_back(sf::Vector2f(802.f, 886.f));
  m_waypoints.push_back(sf::Vector2f(695.f, 897.f));
  m_waypoints.push_back(sf::Vector2f(649.f, 802.f));
  m_waypoints.push_back(sf::Vector2f(548.f, 793.f));
  m_waypoints.push_back(sf::Vector2f(468.f, 801.f));
  m_waypoints.push_back(sf::Vector2f(189.f, 931.f));
  m_waypoints.push_back(sf::Vector2f(35.f, 839.f));
  m_waypoints.push_back(sf::Vector2f(64.f, 558.f));
  m_currentWaypointIndex = (m_waypoints.size() > 1 ? 1 : 0);
}

/**
 * @brief Crea marcadores visuales (círculos) para depurar la ruta de waypoints.
 * @details Útil para ver el trazado real en pantalla.
 */
void 
BaseApp::buildWaypointMarkers() {
  m_waypointMarkers.clear();
  for (const auto& wp : m_waypoints) {
    auto marker = EngineUtilities::MakeShared<CShape>();
    marker->createShape(ShapeType::CIRCLE);
    marker->setFillColor(sf::Color(255, 255, 0, 180));
    marker->setPosition(wp);
    marker->setScale(sf::Vector2f(1.f, 1.f));
    m_waypointMarkers.push_back(marker);
  }
}

// -------------------------------- Ciclo de vida --------------------------------

/**
 * @brief Destructor por defecto.
 */
BaseApp::~BaseApp() {}

/**
 * @brief Punto de entrada del bucle principal.
 * @return Código de salida (0 si todo OK).
 */
int 
BaseApp::run() {
  if (!init()) {
    ERROR("BaseApp", "run", "Error al iniciar");
  }

  // Bucle principal: eventos ? lógica ? render
  while (m_windowPtr->isOpen()) {
    m_windowPtr->handleEvents(m_engineGUI);
    update();
    render();
  }

  destroy();
  return 0;
}

/**
 * @brief Inicializa ventana, GUI, pista, waypoints, jugador, NPCs y sistema de carrera.
 * @return true si todo se configuró correctamente.
 */
bool 
BaseApp::init() {
  ResourceManager& resourceMan = ResourceManager::getInstance();

  // Ventana
  m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "Marvelous-Realms-Engine");
  if (!m_windowPtr) {
    ERROR("BaseApp", "init", "Error con los puntadores");
    return false;
  }

  // ImGui
  m_engineGUI.init(m_windowPtr);

  // Fondo
  m_track = EngineUtilities::MakeShared<Actor>("Track");
  if (m_track) {
    m_track->getComponent<CShape>()->createShape(RECTANGLE);
    m_track->getComponent<CShape>()->setFillColor(sf::Color::White);
    m_track->getComponent<Transform>()->setPosition(sf::Vector2f(0.f, 0.f));

    if (!resourceMan.loadTexture("Sprites/mapa", "png")) {
      MESSAGE("BaseApp", "Init", "No hay fondo");
    }
    m_track->setTexture(resourceMan.getTexture("Sprites/mapa"));

    // Ajusta la escala de la pista al tamaño de la ventana
    const 
      sf::Vector2u winSize = m_windowPtr->m_windowPtr->getSize();
    const 
      sf::Vector2u texSize = resourceMan.getTexture("Sprites/mapa")->getTexture().getSize();

    const 
      float sx = static_cast<float>(winSize.x) / static_cast<float>(texSize.x);
    const 
      float sy = static_cast<float>(winSize.y) / static_cast<float>(texSize.y);
    m_track->getComponent<Transform>()->setScale(sf::Vector2f(sx, sy));
  }

  // Waypoints 
  if (!loadWaypointsCSV("assets/tracks/oval.waypoints.csv")) {
    initWaypoints_DefaultTrack();       // fallback si no hay archivo
  }
  buildWaypointMarkers();               

  //  Player 
  m_ACirlce = EngineUtilities::MakeShared<Actor>("Player");
  if (m_ACirlce) {
    m_ACirlce->getComponent<CShape>()->createShape(CIRCLE);
    m_ACirlce->getComponent<CShape>()->setFillColor(sf::Color::White);

    // Posición inicial: primer waypoint si existe, si no una posición fija
    if (!m_waypoints.empty()) {
      m_ACirlce->getComponent<Transform>()->setPosition(m_waypoints.front());
      m_currentWaypointIndex = (m_waypoints.size() > 1 ? 1 : 0);
    }
    else {
      m_ACirlce->getComponent<Transform>()->setPosition(sf::Vector2f(200.f, 150.f));
    }
    m_ACirlce->getComponent<Transform>()->setScale(sf::Vector2f(6.f, 6.f));

    if (!resourceMan.loadTexture("Sprites/bowser", "png")) {
      MESSAGE("BaseApp", "Init", "No textura");
    }
    m_ACirlce->setTexture(resourceMan.getTexture("Sprites/bowser"));
    m_actors.push_back(m_ACirlce);

  }
  else {
    ERROR("BaseApp", "init", "Fallo con el actor");
    return false;
  }

  //  NPCs 
  // NPC 1
  {
    auto npc = EngineUtilities::MakeShared<A_Racer>("NPC_Mario");
    npc->getComponent<CShape>()->createShape(CIRCLE);
    npc->getComponent<CShape>()->setFillColor(sf::Color::White);
    npc->getComponent<Transform>()->setScale(sf::Vector2f(6.f, 6.f));
    npc->setPath(m_waypoints);    // IA seguirá los waypoints
    npc->setMaxSpeed(240.f);
    resourceMan.loadTexture("Sprites/Mario", "png");
    npc->setTexture(resourceMan.getTexture("Sprites/Mario"));
    m_actors.push_back(npc);
  }

  // NPC 2
  {
    auto npc = EngineUtilities::MakeShared<A_Racer>("NPC_Luigi");
    npc->getComponent<CShape>()->createShape(CIRCLE);
    npc->getComponent<CShape>()->setFillColor(sf::Color::White);
    npc->getComponent<Transform>()->setScale(sf::Vector2f(6.f, 6.f));
    npc->setPath(m_waypoints);
    npc->setMaxSpeed(200.f);
    resourceMan.loadTexture("Sprites/Luigi", "png");
    npc->setTexture(resourceMan.getTexture("Sprites/Luigi"));
    m_actors.push_back(npc);
  }

  // Inicializa sistema de carrera 
  initRaceSystems();

  return true;
}

/**
 * @brief Actualiza GUI, jugador, NPCs y sistema de carrera. También dibuja un HUD de carrera con ImGui.
 */
void 
BaseApp::update() {
  if (!m_windowPtr.isNull()) {
    m_windowPtr->update(); // actualiza deltaTime
  }

  m_engineGUI.update(m_windowPtr, m_windowPtr->deltaTime);
  m_engineGUI.outliner(m_actors);
  m_engineGUI.inspector(m_actors);

  const 
    float dt = m_windowPtr->deltaTime.asSeconds();

  // Player con seek simple y sincroniza este frame
  if (!m_waypoints.empty() && !m_ACirlce.isNull()) {
    const 
      sf::Vector2f pos = m_ACirlce->getComponent<Transform>()->getPosition();
    const 
      sf::Vector2f target = m_waypoints[m_currentWaypointIndex];

    const 
      float dx = target.x - pos.x;
    const 
      float dy = target.y - pos.y;
    const 
      float distance = std::sqrt(dx * dx + dy * dy);

    // Cuando está lo suficientemente cerca, avanza al siguiente waypoint (loop)
    const float arriveRadius = 12.0f;
    if (distance < arriveRadius) {
      m_currentWaypointIndex = (m_currentWaypointIndex + 1) %
        static_cast<int>(m_waypoints.size());
    }

    // Mueve al jugador hacia el waypoint actual
    m_ACirlce->getComponent<Transform>()->seek(
      m_waypoints[m_currentWaypointIndex],
      200.0f,
      dt,
      10.0f
    );
    m_ACirlce->update(0.f);
  }

  //  Resto de actores 
  for (auto& actor : m_actors) {
    if (actor.isNull()) continue;
    if (actor.get() == m_ACirlce.get()) continue; 
    actor->update(dt);
  }

  // Sistema de carrera
  updateRaceSystems(dt);

  // HUD de carrera 
  ImGui::Begin("Race HUD");
  ImGui::Text("Total Laps: %d", m_totalLaps);
  ImGui::Text("Race Time: %s", formatTime(m_raceTime).c_str());

  if (!m_raceStarted) {
    if (ImGui::Button("Start Race")) {
      // Reinicia tiempos y vueltas pero no reposiciona
      for (auto& t : m_currLapTime) t = 0.f;
      for (auto& l : m_laps) l = 0;
      for (auto& b : m_bestLapTime) b = std::numeric_limits<float>::infinity();
      for (size_t i = 0; i < m_actors.size(); ++i) {
        auto xf = m_actors[i]->getComponent<Transform>();
        m_prevInsideFinish[i] = xf ? isInsideFinish(xf->getPosition()) : false;
      }
      m_raceTime = 0.f;
      m_raceStarted = true;
      m_raceFinished = false;
    }
  }
  else {
    if (ImGui::Button("Stop")) {
      m_raceStarted = false;
    }
  }
  ImGui::SameLine();
  if (ImGui::Button("Reset")) {
    initRaceSystems();
  }

  ImGui::Checkbox("Show Waypoints", &m_drawWaypointMarkers);
  ImGui::SameLine();
  ImGui::Checkbox("Show Finish Line", &m_showFinishLine);

  ImGui::Separator();
  for (size_t i = 0; i < m_actors.size(); ++i) {
    ImGui::Text("Racer %zu | Lap: %d | LapTime: %s | Best: %s",
      i + 1,
      m_laps[i],
      formatTime(m_currLapTime[i]).c_str(),
      std::isinf(m_bestLapTime[i]) ? "--:--.---" : formatTime(m_bestLapTime[i]).c_str()
    );
  }
  ImGui::End();
}

/**
 * @brief Render en orden: limpiar, pista, meta (debug), waypoints (debug), actores, GUI, display.
 */
void BaseApp::render() {
  if (!m_windowPtr) return;

  m_windowPtr->clear();

  // Fondo 
  if (!m_track.isNull()) {
    m_track->getComponent<CShape>()->render(m_windowPtr);
  }

  // Debug: línea de meta
  if (m_showFinishLine && !m_finishLineDebug.isNull()) {
    m_finishLineDebug->getComponent<CShape>()->render(m_windowPtr);
  }

  //  Marcadores de waypoints 
  if (m_drawWaypointMarkers) {
    for (const auto& marker : m_waypointMarkers) {
      marker->render(m_windowPtr);
    }
  }

  //  Todos los actores 
  for (auto& actor : m_actors) {
    if (!actor.isNull()) actor->getComponent<CShape>()->render(m_windowPtr);
  }

  m_windowPtr->render();

  // ImGui al final
  m_engineGUI.render(m_windowPtr);

  m_windowPtr->display();
}

/**
 * @brief Libera/Apaga los sistemas globales (GUI, etc.).
 */
void 
BaseApp::destroy() {
  m_engineGUI.destroy();
}

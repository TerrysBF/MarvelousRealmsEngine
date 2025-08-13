#pragma once
#include "Prerequisites.h"
#include "ECS/Texture.h"

/**
 * @brief Gestor global de recursos (singleton).
 *
 * Actualmente gestiona texturas:
 *  - Carga texturas desde archivo (`loadTexture`).
 *  - Devuelve punteros compartidos (`getTexture`) para reutilizar texturas ya cargadas.
 *
 * Uso:
 * @code
 * ResourceManager::getInstance().loadTexture("player", "png");
 * auto tex = ResourceManager::getInstance().getTexture("player");
 * @endcode
 */
class ResourceManager {
private:
  ResourceManager() = default;
  ~ResourceManager() = default;

public:
  /// Prohíbe copia y asignación para mantener singleton.
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  /**
   * @brief Devuelve la única instancia del ResourceManager.
   */
  static ResourceManager& getInstance() {
    static ResourceManager instance;
    return instance;
  }

  /**
   * @brief Carga una textura desde archivo y la guarda en el mapa.
   * @param fileName  Nombre base del archivo (sin extensión).
   * @param extension Extensión del archivo (png, jpg, etc.).
   * @return true si la carga fue exitosa, false si falló.
   */
  bool loadTexture(const std::string& fileName, const std::string& extension);

  /**
   * @brief Obtiene una textura ya cargada.
   * @param fileName Nombre base del archivo usado al cargar.
   * @return Puntero compartido a la textura, o nullptr si no existe.
   */
  EngineUtilities::TSharedPointer<Texture> getTexture(const std::string& fileName);

private:
  /// Mapa de nombre de textura ? puntero compartido a Texture.
  std::unordered_map<std::string, EngineUtilities::TSharedPointer<Texture>> m_textures;
};

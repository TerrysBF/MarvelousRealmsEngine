#pragma once
#include "Prerequisites.h"
#include "ECS\Texture.h"

/**
 * @class ResourceManager
 * @brief Administra y almacena recursos como texturas.
 *
 * @details
 * - Implementado como singleton.
 * - Evita cargas duplicadas guardando recursos en caché.
 * - Permite obtener texturas por nombre y extensión.
 */
class ResourceManager {
private:
  /// Constructor privado (patrón Singleton).
  ResourceManager() = default;

  /// Destructor privado.
  ~ResourceManager() = default;

public:
  ResourceManager(const ResourceManager&) = delete; ///< Evita copia.
  ResourceManager& operator=(const ResourceManager&) = delete; ///< Evita asignación.

  /**
   * @brief Obtiene la instancia única del ResourceManager.
   * @return Referencia a la instancia.
   */
  static 
    ResourceManager& getInstance() {
    static 
      ResourceManager instance;
    return instance;
  }

  /**
   * @brief Carga una textura y la guarda en caché si no existe.
   * @param fileName Nombre del archivo sin extensión.
   * @param extension Extensión del archivo (por defecto "png").
   * @return `true` si la carga fue exitosa o ya estaba cargada.
   */
  bool 
    loadTexture(const std::string& fileName, const std::string& extension);

  /**
   * @brief Obtiene una textura previamente cargada.
   * @param fileName Nombre del archivo sin extensión.
   * @return Puntero compartido a la textura.
   */
  EngineUtilities::TSharedPointer<Texture> getTexture(const std::string& fileName);

private:
  std::unordered_map<std::string, EngineUtilities::TSharedPointer<Texture>> m_textures; ///< Caché de texturas.
};

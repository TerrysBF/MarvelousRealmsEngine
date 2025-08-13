#pragma once
#include "Prerequisites.h"
#include "Component.h"

/*
 * Clase Texture
 * =============
 *
 * Este componente representa una textura que puede ser usada por otros
 * elementos gráficos del motor (por ejemplo, un sprite o un shape con textura).
 *
 * Hereda de Component, así que sigue el mismo ciclo de vida que cualquier
 * otro componente: start(), update(), render(), destroy(). En este caso,
 * la lógica de esos métodos está vacía porque la textura en sí no se
 * “actualiza” ni “dibuja” por sí sola; es más un recurso que otros usan.
 *
 * Cosas importantes:
 * ------------------
 * - Se guarda internamente un sf::Texture de SFML.
 * - El constructor puede recibir un nombre de archivo y una extensión
 *   (por defecto "png") para intentar cargar la textura directamente.
 * - Si la carga falla, imprime un mensaje de error en consola.
 * - Puedes acceder a la textura con getTexture() para asignarla a un sprite, shape, etc.
 */
class Texture : public Component {
public:
  // Constructor vacío: crea un componente de textura sin cargar nada.
  Texture() = default;

  /*
   * Constructor con parámetros:
   * ---------------------------
   * Recibe el nombre base del archivo (sin extensión) y opcionalmente la extensión.
   * Intenta cargar el archivo <nombre>.<extensión> usando SFML.
   * Si falla, imprime un mensaje de error.
   *
   * Ejemplo:
   * Texture tex("player"); // intentará cargar "player.png"
   */
  Texture(const std::string& textureName, const std::string& extension = "png") :
    m_textureName(textureName),
    m_extension(extension),
    Component(ComponentType::TEXTURE)
  {
    if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
      std::cout << "Error de carga de textura: "
        << m_textureName << "." << m_extension << std::endl;
    }
  }

  // Destructor virtual: no necesita liberar nada especial (SFML maneja su memoria).
  virtual ~Texture() = default;

  /*
   * start(), update(), render(), destroy():
   * ---------------------------------------
   * Métodos del ciclo de vida de Component.
   * Aquí están vacíos porque la textura como recurso no requiere
   * inicialización dinámica ni actualizaciones frame a frame.
   */
  void start() override {};
  void update(float deltaTime) override {};
  void render(const EngineUtilities::TSharedPointer<Window>& window) override {};
  void destroy() override {};

  /*
   * getTexture()
   * ------------
   * Devuelve una referencia al sf::Texture interno.
   * Esto permite que otras clases (por ejemplo un sprite) usen esta textura.
   */
  sf::Texture& getTexture() {
    return m_texture;
  }

private:
  sf::Texture m_texture;       // Textura real de SFML.
  std::string m_textureName;   // Nombre base del archivo (sin extensión).
  std::string m_extension;     // Extensión del archivo (png, jpg, etc.).
};

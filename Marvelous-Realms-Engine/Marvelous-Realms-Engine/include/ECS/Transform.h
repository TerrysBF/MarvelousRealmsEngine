#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/**
 * @file Transform.h
 * @brief Define el componente Transform para gestionar la posición, rotación y escala.
 */
class
  Transform : public Component {
public:
  Transform() : position(0.0f, 0.0f),
    rotation(0.0f, 0.0f),
    scale(1.0f, 1.0f),
    Component(ComponentType::TRANSFORM) {}

  /**
   * @brief Destructor virtual por defecto de Transform
   * Asegura la correcta liberación de recursos cuando una instancia de Transform
   * es destruida, especialmente útil para herencia
   */
  virtual
    ~Transform() = default;

  /**
   * @brief Método de inicialización del componente Transform
   * Sobrescribe el método 'start' de la clase base Component
   */
  void
    start() override {}

  /**
   * @brief Actualiza el componente de malla.
   * @param deltaTime El tiempo transcurrido desde la última actualización.
   */
  void
    update(float deltaTime) override {}

  /**
   * @brief Renderiza el componente de malla.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  void
    render(const EngineUtilities::TSharedPointer<Window>& window) override {}

  /**
   * @brief Método de destrucción del componente Transform
   * Sobrescribe el método 'destroy' de la clase base Component
   */
  void
    destroy() {}

  void
    seek(const sf::Vector2f& targetPosition,
      float speed,
      float deltaTime,
      float range) {
    sf::Vector2f direction = targetPosition - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > range) {
      direction /= length;  // Normaliza el vector
      position += direction * speed * deltaTime;
    }
  }

  void
    setPosition(const sf::Vector2f& _position) {
    position = _position;
  }

  void
    setRotation(const sf::Vector2f& _rotation) {
    rotation = _rotation;
  }

  void
    setScale(const sf::Vector2f& _scale) {
    scale = _scale;
  }

  sf::Vector2f&
    getPosition() {
    return position;
  }


  sf::Vector2f&
    getRotation() {
    return rotation;
  }

  sf::Vector2f&
    getScale() {
    return scale;
  }

  float*
    getPosData() {
    return &position.x;
  }

  float*
    getRotData() {
    return &rotation.x;
  }

  float*
    getScaData() {
    return &scale.x;
  }
private:
  sf::Vector2f position;  // Posición del objeto
  sf::Vector2f rotation;  // Rotación del objeto
  sf::Vector2f scale;     // Escala del objeto
};
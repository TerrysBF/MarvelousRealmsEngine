#pragma once
#include "../Prerequisites.h"
#include "Entity.h"
#include "Cshape.h"
#include "Transform.h"

/**
 * @file Actor.h
 * @brief Representa una entidad del juego que puede tener componentes y lógica propia.
 */
class
  Actor : Entity {
public:
  Actor() = default;
  Actor(const std::string& actorName);
  virtual ~Actor() = default;

  /// Inicializa el actor.
  void 
    start() override {};

  /// Actualiza el actor.
  void 
    update(float deltaTime) override;

  /// Renderiza el actor.
  void 
    render(const EngineUtilities::TSharedPointer<Window>& window) override;

  /// Libera recursos del actor.
  void 
    destroy() override {};

  /// Asigna una textura al actor.
  void 
    setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

  /// Devuelve el nombre del actor.
  std::string getName() {
    return m_name;
  }

  /**
   * @brief Obtiene un componente específico del actor.
   * @tparam T Tipo del componente.
   * @return Puntero compartido o nullptr si no se encuentra.
   */
  template <typename T>
  EngineUtilities::TSharedPointer<T> getComponent();

private:
  std::string m_name = "Actor"; ///< Nombre del actor.
};

template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
  for (auto& component : components) {
    EngineUtilities::TSharedPointer<T> 
      specificComponent = component.template dynamic_pointer_cast<T>();
    if (specificComponent) {
      return specificComponent;
    }
  }
  return EngineUtilities::TSharedPointer<T>();
}

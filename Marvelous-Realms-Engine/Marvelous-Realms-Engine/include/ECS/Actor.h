#pragma once
#include "../Prerequisites.h"
#include "Entity.h"
#include "Cshape.h"
#include "Transform.h"

/**
 * @file Actor.h
 * @brief Define la clase Actor, una entidad fundamental en el motor de juego
 */
class
  Actor : Entity {
public:

  /**
   * @brief Constructor por defecto de Actor
   * Utiliza el constructor por defecto generado por el compilador
   */
  Actor() = default;

  /**
   * @brief Constructor de Actor con un nombre específico
   * @param actorName El nombre deseado para este actor
   */
  Actor(const std::string& actorName);

  /**
   * @brief Destructor virtual por defecto de Actor.
   * Asegura la correcta destrucción de los actores y sus componentes derivados
   */
  virtual
    ~Actor() = default;

  /**
   * @brief Método de inicialización del actor
   * Sobrescribe el método 'start' de la clase base Entity
   */
  void
    start() override {};

  /**
  * @brief Método de actualización del actor por fotograma
  * Sobrescribe el método 'update' de la clase base Entity
  * @param deltaTime El tiempo transcurrido desde el último fotograma, en segundos
  */
  void
    update(float deltaTime) override;

  /**
   * @brief Método de renderizado del actor.
   * Sobrescribe el método 'render' de la clase base Entity
   * @param window Un puntero compartido al objeto Window donde se renderizará el actor.
   */
  void
    render(const EngineUtilities::TSharedPointer<Window>& window) override;


  /**
   * @brief Método de destrucción del acto
   * Sobrescribe el método 'destroy' de la clase base Entity
   * Actualmente, está vacío y puede ser implementado en clases derivadas
   */
  void
    destroy() override {};

  /**
   * @brief Obtiene un componente específico del actor.
   * @tparam T Tipo del componente que se va a obtener.
   * @return Puntero compartido al componente T, o nulo  si no se encuentra.
   */
  template <typename T>
  EngineUtilities::TSharedPointer<T>
    getComponent();

private:
  std::string m_name = "Actor";
};

/**
 * @brief El propósito de esta función es buscar y devolver un componente específico de un actor,
 * @tparam utilizando el tipo de componente especificado como argumento de la plantilla.
 *  @return Si el componente no se encuentra, la función devuelve nulo.
 */
template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
  for (auto& component : components) 
  {
    EngineUtilities::TSharedPointer<T> specificComponent = 
      component.template dynamic_pointer_cast<T>();
    if (specificComponent) 
    {
      return specificComponent;
    }
  }
  // Devuelve un TSharedPointer vacío si no se encuentra el componente
  return EngineUtilities::TSharedPointer<T>();
}
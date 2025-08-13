#pragma once
#include "../Prerequisites.h"
#include "Entity.h"
#include "CShape.h"
#include "Transform.h"

/*
 * Clase Actor
 * ===========
 *
 * Un Actor es una de las piezas centrales dentro del motor.
 * Básicamente, representa cualquier objeto "vivo" en la escena:
 * puede tener forma, posición, comportamiento y uno o más componentes
 * que le dan sus capacidades.
 *
 * Hereda de Entity, así que comparte el ciclo de vida típico:
 * - start(): se llama al comienzo de su existencia.
 * - update(): corre cada frame para actualizar su estado.
 * - render(): se encarga de dibujarse.
 * - destroy(): se invoca cuando debe limpiar sus recursos.
 *
 * Además, Actor sabe buscar entre sus componentes y devolverte uno
 * específico si lo necesitas (getComponent<T>).
 */
class Actor : Entity {
public:

  // Constructor sin parámetros: crea un Actor genérico con el nombre por defecto.
  Actor() = default;

  // Constructor con nombre: útil para identificarlo en depuración o edición.
  Actor(const std::string& actorName);

  // Destructor virtual: asegura que si hay clases derivadas, se limpien bien.
  virtual ~Actor() = default;

  /*
   * start()
   * -------
   * Método que arranca la vida del Actor.
   * Aquí podrías inicializar estados, preparar animaciones, etc.
   * En este caso no hace nada porque probablemente la lógica se defina en clases hijas.
   */
  void start() override {};

  /*
   * update(deltaTime)
   * -----------------
   * Este se llama cada frame y recibe el tiempo transcurrido desde el último.
   * Sirve para mover al actor, revisar colisiones, IA, etc.
   */
  void update(float deltaTime) override;

  /*
   * render(window)
   * --------------
   * Aquí se dibuja el actor usando la ventana que le pases.
   * Ideal para delegar el renderizado a sus componentes gráficos.
   */
  void render(const EngineUtilities::TSharedPointer<Window>& window) override;

  /*
   * destroy()
   * ---------
   * Se invoca cuando el Actor va a ser destruido.
   * Aquí puedes liberar recursos o eliminar referencias.
   * En esta versión queda vacío.
   */
  void destroy() override {};

  /*
   * getComponent<T>()
   * -----------------
   * Busca entre todos los componentes que este Actor tiene
   * y devuelve el que coincida con el tipo que le pidas.
   * Si no existe, regresa un puntero vacío.
   *
   * Ejemplo:
   * auto shape = myActor.getComponent<CShape>();
   */
  template <typename T>
  EngineUtilities::TSharedPointer<T> getComponent();

private:
  // Nombre interno del actor, por defecto "Actor".
  std::string m_name = "Actor";
};

/*
 * Implementación de getComponent<T>()
 * -----------------------------------
 * Recorre el vector "components" (heredado de Entity)
 * y trata de convertir cada elemento al tipo solicitado T
 * usando dynamic_pointer_cast. Si encuentra uno válido, lo devuelve.
 * Si no, devuelve un puntero compartido vacío.
 */
template<typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent() {
  for (auto& component : components) {
    EngineUtilities::TSharedPointer<T> specificComponent =
      component.template dynamic_pointer_cast<T>();
    if (specificComponent) {
      return specificComponent;
    }
  }
  return EngineUtilities::TSharedPointer<T>(); // no encontrado
}

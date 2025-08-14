#include "ECS/Actor.h"

/**
 * @file Actor.cpp
 * @brief Implementación base de un Actor: crea componentes esenciales y sincroniza CShape con Transform.
 *
 * @details
 * Un Actor nace con:
 * - **CShape**: la figura dibujable (rectángulo, círculo, etc.).
 * - **Transform**: posición, rotación y escala en 2D.
 *
 * En cada `update`, el Actor copia los valores del Transform al CShape para que
 * lo que se dibuja refleje el estado lógico del Actor. El render delega a sus
 * componentes dibujables. `setTexture` permite asignar una textura al shape.
 */

 /**
	* @brief Construye un Actor con nombre y agrega sus componentes básicos.
	* @param actorName Nombre visible/identificador del Actor.
	*/
Actor::Actor(const std::string& actorName) {
	// Nombre del actor
	m_name = actorName;

	// Crea y agrega el componente de Shape (lo que se va a dibujar)
	EngineUtilities::TSharedPointer<CShape> shape = EngineUtilities::MakeShared<CShape>();
	addComponent(shape);

	// Crea y agrega el componente de Transform (posición/rotación/escala)
	EngineUtilities::TSharedPointer<Transform> transform = 
		EngineUtilities::MakeShared<Transform>();
	addComponent(transform);
}

/**
 * @brief Sincroniza el CShape con el Transform en cada frame.
 * @param deltaTime Tiempo transcurrido desde el último frame (no se usa aquí).
 *
 * @details
 * - Posición: `shape <- transform.position`
 * - Rotación: `shape <- transform.rotation.x` (se usa el eje X como ángulo)
 * - Escala:   `shape <- transform.scale`
 */
void
Actor::update(float deltaTime) {
	auto transform = getComponent<Transform>();
	auto shape = getComponent<CShape>();

	if (transform && shape) {
		// Copia de estado lógico (Transform) al visual (CShape)
		shape->setPosition(transform->getPosition());
		shape->setRotation(transform->getRotation().x); // tu rotación está modelada como Vector2f
		shape->setScale(transform->getScale());
	}
}

/**
 * @brief Renderiza los componentes dibujables del Actor.
 * @param window Ventana donde se dibuja.
 *
 * @details
 * Recorre la lista de componentes y, para los que sean `CShape`, llama a su `render`.
 */
void
Actor::render(const EngineUtilities::TSharedPointer<Window>& window) {
	for (unsigned int i = 0; i < components.size(); i++) {
		auto shape = components[i].dynamic_pointer_cast<CShape>();
		if (shape) {
			shape->render(window);
		}
	}
}

/**
 * @brief Asigna una textura al shape principal del Actor y registra el recurso como componente.
 * @param texture Textura compartida (no nula) a aplicar.
 *
 * @details
 * - Si hay un `CShape` y la textura es válida, la aplica.
 * - También añade el `Texture` como componente para mantener referencia (evita que se libere).
 */
void
Actor::setTexture(const EngineUtilities::TSharedPointer<Texture>& texture) {
	auto shape = getComponent<CShape>();
	if (shape) {
		if (!texture.isNull()) {
			shape->setTexture(texture);  // Aplica textura al shape
			addComponent(texture);       // Guarda la textura como componente (lifetime management)
		}
	}
}

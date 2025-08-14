#pragma once
#include "../Prerequisites.h"
#include "Component.h"

class Window;

/**
 * @file Entity.h
 * @brief Clase base para todas las entidades del motor.
 */
class
	Entity {
public:
	/// Destructor virtual.
	virtual ~Entity() = default;

	/// Inicializa la entidad.
	virtual void 
		start() = 0;

	/// Actualiza la entidad.
	virtual void 
		update(float deltaTime) = 0;

	/// Renderiza la entidad.
	virtual void 
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

	/// Libera los recursos de la entidad.
	virtual void 
		destroy() = 0;

	/**
	 * @brief Agrega un componente a la entidad.
	 * @tparam T Tipo del componente (debe heredar de Component).
	 */
	template<typename T>
	void addComponent(EngineUtilities::TSharedPointer<T> component) {
		static_assert(std::is_base_of<Component, T>::value, 
			"T must be derived from Component");
		components.push_back(component.template dynamic_pointer_cast<Component>());
	}

	/**
	 * @brief Obtiene un componente específico.
	 * @tparam T Tipo del componente.
	 * @return Puntero compartido o nullptr si no existe.
	 */
	template<typename T>
	EngineUtilities::TSharedPointer<T> getComponent() {
		for (auto& component : components) {
			EngineUtilities::TSharedPointer<T>
				specificComponent = component.template dynamic_pointer_cast<T>();
			if (specificComponent) {
				return specificComponent;
			}
		}
		return EngineUtilities::TSharedPointer<T>();
	}

protected:
	bool isActive; ///< Estado de la entidad.
	uint32_t id; ///< Identificador único.
	std::vector<EngineUtilities::TSharedPointer<Component>> components; ///< Lista de componentes.
};

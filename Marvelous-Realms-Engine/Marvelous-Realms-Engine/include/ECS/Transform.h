#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/**
 * @file Transform.h
 * @brief Define el componente Transform para gestionar la posición, rotación y escala.
 *
 * @details
 * Este componente es el “GPS” básico de cualquier actor/entidad: guarda y expone
 * su posición, rotación y escala en 2D, además de utilidades simples como
 * moverse hacia un objetivo (seek). Hereda de Component para integrarse al
 * ciclo de vida del motor (start, update, render, destroy).
 */

 /**
  * @class Transform
  * @brief Componente 2D para posición, rotación y escala.
  *
  * @details
  * - **position**: dónde está el objeto en el mundo/escena.
  * - **rotation**: rotación en 2D (convención libre; aquí es un `sf::Vector2f`).
  * - **scale**: escala por eje X/Y.
  *
  * Métodos clave:
  * - `seek(...)`: interpola la posición hacia un objetivo con velocidad y rango.
  * - Setters/Getters básicos para manipular los tres atributos.
  *
  * @note Este Transform está pensado para 2D (usa `sf::Vector2f`).
  * @warning No realiza validaciones de unidad/ángulos; tú decides cómo interpretar la rotación.
  */
class
  Transform : public Component {
public:
  /**
   * @brief Construye un Transform con valores por defecto.
   * @details position = (0,0), rotation = (0,0), scale = (1,1).
   */
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
   * @details Se llama una sola vez al activarse el componente. Aquí no hace nada,
   * pero es el lugar ideal para cachear referencias o preparar estados.
   * Sobrescribe el método 'start' de la clase base Component
   */
  void
    start() override {}

  /**
   * @brief Actualiza el componente de malla.
   * @param deltaTime El tiempo transcurrido desde la última actualización.
   * @details En este Transform no hay lógica por frame. Si agregas animaciones
   * o efectos dependientes del tiempo, este es el hook correcto.
   */
  void
    update(float deltaTime) override {}

  /**
   * @brief Renderiza el componente de malla.
   * @param window Referencia compartida a la ventana para operaciones gráficas.
   * @details Normalmente un Transform no dibuja nada; se deja por si quieres
   * depurar (por ejemplo, renderizar un gizmo o un punto).
   */
  void
    render(const EngineUtilities::TSharedPointer<Window>& window) override {}

  /**
   * @brief Método de destrucción del componente Transform
   * @details Limpia recursos si fuera necesario (aquí no hace nada).
   * Sobrescribe el método 'destroy' de la clase base Component
   */
  void
    destroy() {}

  /**
   * @brief Mueve la posición gradualmente hacia un objetivo (seek).
   * @param targetPosition Posición destino a la que se quiere llegar.
   * @param speed Velocidad de movimiento en unidades/segundo.
   * @param deltaTime Tiempo transcurrido desde el último frame.
   * @param range Distancia mínima para “considerar” que ya llegaste; si estás
   * por dentro de este rango, no se mueve.
   * @details Calcula la dirección normalizada hacia el objetivo y avanza en línea
   * recta. Útil para perseguir puntos o hacer interpolaciones simples.
   * @note Si `length <= range`, no habrá movimiento este frame.
   */
  void
    seek(const sf::Vector2f& targetPosition,
      float speed,
      float deltaTime,
      float range) {
    sf::Vector2f direction = targetPosition - position;
    float length = std::sqrt
    (direction.x * direction.x + direction.y * direction.y);

    if (length > range) {
      direction /= length;  // Normaliza el vector
      position += direction * speed * deltaTime;
    }
  }

  /**
   * @brief Fija la posición absoluta del objeto.
   * @param _position Nueva posición (x, y).
   */
  void
    setPosition(const sf::Vector2f& _position) {
    position = _position;
  }

  /**
   * @brief Fija la rotación del objeto.
   * @param _rotation Nueva rotación (x, y). La interpretación depende de tu motor.
   */
  void
    setRotation(const sf::Vector2f& _rotation) {
    rotation = _rotation;
  }

  /**
   * @brief Fija la escala del objeto.
   * @param _scale Nueva escala (x, y). Usualmente (1,1) es sin escalado.
   */
  void
    setScale(const sf::Vector2f& _scale) {
    scale = _scale;
  }

  /**
   * @brief Obtiene una referencia a la posición.
   * @return Referencia modificable a `position`.
   * @warning Se devuelve por referencia; modifícalo con cuidado.
   */
  sf::Vector2f&
    getPosition() {
    return position;
  }

  /**
   * @brief Obtiene una referencia a la rotación.
   * @return Referencia modificable a `rotation`.
   */
  sf::Vector2f&
    getRotation() {
    return rotation;
  }

  /**
   * @brief Obtiene una referencia a la escala.
   * @return Referencia modificable a `scale`.
   */
  sf::Vector2f&
    getScale() {
    return scale;
  }

  /**
   * @brief Obtiene un puntero crudo al primer componente de la posición.
   * @return Puntero a `position.x` (útil para APIs que esperan `float*` contiguos).
   * @note Úsalo para pasar datos a funciones C/GL que requieren memoria contigua.
   */
  float*
    getPosData() {
    return &position.x;
  }

  /**
   * @brief Obtiene un puntero crudo al primer componente de la rotación.
   * @return Puntero a `rotation.x`.
   */
  float*
    getRotData() {
    return &rotation.x;
  }

  /**
   * @brief Obtiene un puntero crudo al primer componente de la escala.
   * @return Puntero a `scale.x`.
   */
  float*
    getScaData() {
    return &scale.x;
  }
private:
  sf::Vector2f position;  ///< Posición del objeto (x, y).
  sf::Vector2f rotation;  ///< Rotación del objeto (convención libre).
  sf::Vector2f scale;     ///< Escala del objeto (x, y).
};

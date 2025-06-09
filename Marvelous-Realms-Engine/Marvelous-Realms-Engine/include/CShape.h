#pragma once

#include "Prerequisites.h"

class Window;

/**
 * @class CShape
 * @brief Representa una figura gráfica con propiedades como posición, color y escala.
 */
class
  CShape {
public:
  /**
   * @brief Constructor por defecto.
   */
  CShape() = default;

  /**
   * @brief Constructor que inicializa el tipo de figura.
   * @param shapeType Tipo de figura (círculo, rectángulo, etc.).
   */
  CShape(ShapeType shapeType) : m_shape(nullptr), m_shapeType(ShapeType::EMPTY) {}

  /**
   * @brief Destructor.
   */
  ~CShape() = default;

  /**
   * @brief Crea una figura gráfica del tipo especificado.
   * @param shapeType Tipo de figura a crear.
   * @return Puntero a la figura creada.
   */
  sf::Shape* createShape(ShapeType shapeType);

  /**
   * @brief Actualiza el estado de la figura según el tiempo transcurrido.
   * @param deltaTime Tiempo desde el último frame.
   */
  void update(float deltaTime);

  /**
   * @brief Renderiza la figura en la ventana proporcionada.
   * @param window Ventana donde se dibuja la figura.
   */
  void render(Window& window);

  /**
   * @brief Establece la posición de la figura mediante coordenadas.
   * @param x Coordenada X.
   * @param y Coordenada Y.
   */
  void setPosition(float x, float y);

  /**
   * @brief Establece la posición de la figura mediante un vector.
   * @param position Vector con coordenadas X e Y.
   */
  void setPosition(const sf::Vector2f& position);

  /**
   * @brief Cambia el color de relleno de la figura.
   * @param color Color a aplicar.
   */
  void setFillColor(const sf::Color& color);

  /**
   * @brief Establece el ángulo de rotación de la figura.
   * @param angle Ángulo en grados.
   */
  void setRotation(float angle);

  /**
   * @brief Escala la figura en X y Y.
   * @param scl Vector de escala.
   */
  void setScale(const sf::Vector2f& scl);

  /**
   * @brief Devuelve un puntero a la figura actual.
   * @return Puntero a sf::Shape.
   */
  sf::Shape* getShape() {
    return m_shape;
  }

private:
  sf::Shape* m_shape = nullptr;           ///< Figura gráfica principal
  ShapeType m_shapeType = ShapeType::EMPTY; ///< Tipo de figura
  sf::VertexArray* m_line = nullptr;      ///< Línea auxiliar para polígonos, si aplica
};

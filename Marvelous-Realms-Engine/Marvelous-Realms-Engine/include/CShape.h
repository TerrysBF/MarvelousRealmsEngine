#pragma once

#include "Prerequisites.h"

class Window;

// Clase encargada de representar una figura gráfica y sus propiedades.
class
  CShape {
public:
  CShape() = default;

  // Constructor con tipo de figura
  CShape(ShapeType shapeType) : m_shape(nullptr), m_shapeType(ShapeType::EMPTY) {}

  ~CShape() = default;

  // Crea una figura del tipo especificado
  sf::Shape* createShape(ShapeType shapeType);

  // Actualiza la figura con el tiempo delta
  void update(float deltaTime);

  // Renderiza la figura en la ventana proporcionada
  void render(Window& window);

  // Establece la posición con coordenadas
  void setPosition(float x, float y);

  // Establece la posición con vector
  void setPosition(const sf::Vector2f& position);

  // Cambia el color de relleno de la figura
  void setFillColor(const sf::Color& color);

  // Establece el ángulo de rotación
  void setRotation(float angle);

  // Cambia la escala de la figura
  void setScale(const sf::Vector2f& scl);

  // Devuelve un puntero a la figura
  sf::Shape* getShape() {
    return m_shape;
  }

private:
  sf::Shape* m_shape = nullptr;           // Figura gráfica principal
  ShapeType m_shapeType = ShapeType::EMPTY; // Tipo de figura
  sf::VertexArray* m_line = nullptr;      // Línea auxiliar para polígonos, si aplica
};

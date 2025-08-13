#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"
#include <SFML/Graphics.hpp>

class Window;

/**
 * @brief Componente gráfico que administra una figura de SFML (sf::Shape).
 *
 * Se encarga de crear una figura según un ShapeType (círculo, rect, etc.),
 * actualizar estados sencillos y dibujarla en la ventana.
 *
 * Notas:
 * - sf::Shape es abstracta ? se crean derivadas (Circle/Rectangle/Convex).
 * - Este componente NO carga texturas; solo color/transformaciones básicas.
 */
class CShape : public Component {
public:
  /// Constructor por defecto: componente tipo SHAPE, sin figura creada aún.
  CShape()
    : Component(ComponentType::SHAPE)
    , m_shapePtr(nullptr)
    , m_shapeType(ShapeType::EMPTY)
    , m_line(nullptr) {}

  /**
   * @brief Constructor que recibe el tipo de figura a crear.
   * @param shapeType Tipo de figura (CIRCLE, RECT, etc.).
   *
   * Importante: crea la figura de inmediato para dejar al componente listo.
   */
  explicit CShape(ShapeType shapeType)
    : Component(ComponentType::SHAPE)
    , m_shapePtr(nullptr)
    , m_shapeType(ShapeType::EMPTY)
    , m_line(nullptr) {
    createShape(shapeType);
  }

  /// Destructor virtual: asegura liberar recursos propios si aplica.
  virtual ~CShape() = default;

  /**
   * @brief Crea la figura a partir del tipo indicado.
   * @param shapeType Tipo de figura a crear.
   *
   * Si ya existía una figura previa, se reemplaza.
   * Inicializa transformaciones por defecto (ej. origin centrado).
   */
  void createShape(ShapeType shapeType);

  /// @brief Llamado una vez cuando el componente entra en juego.
  void start() override;

  /// @brief Llamado cada frame para actualizar lógica simple del shape.
  /// @param deltaTime Tiempo entre frames (segundos).
  void update(float deltaTime) override;

  /**
   * @brief Dibuja la figura en la ventana.
   * @param window Ventana destino (wrapper propio del engine).
   */
  void render(const EngineUtilities::TSharedPointer<Window>& window) override;

  /// @brief Limpia recursos propios si es necesario.
  void destroy() override;

  /// @name Setters de transformación/estilo
  /// @{
  void setPosition(float x, float y);
  void setPosition(const sf::Vector2f& position);
  void setFillColor(const sf::Color& color);
  void setRotation(float angle);
  void setScale(const sf::Vector2f& scl);
  /// @}

private:
  /// Puntero compartido a la figura SFML (derivadas de sf::Shape).
  EngineUtilities::TSharedPointer<sf::Shape> m_shapePtr;

  /// Tipo de figura actual (EMPTY si no hay figura).
  ShapeType m_shapeType;

  /// Línea opcional para debug/contornos (usa smart pointer si la activas).
  sf::VertexArray* m_line;
  // Sugerencia:
  // std::unique_ptr<sf::VertexArray> m_line;
};

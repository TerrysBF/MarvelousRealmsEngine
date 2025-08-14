#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"
#include "ECS/Texture.h"

// Declaración adelantada
class Window;

/**
 * @class CShape
 * @brief Componente gráfico que representa una figura geométrica (Shape) en pantalla.
 *
 * Esta clase encapsula un `sf::Shape` de SFML y permite configurarlo, dibujarlo
 * y aplicarle propiedades como posición, rotación, escala, color y textura.
 * Forma parte del sistema ECS como un componente de tipo SHAPE.
 */
class 
  CShape : public Component {
public:
  /**
   * @brief Constructor por defecto.
   */
  CShape() = default;

  /**
   * @brief Constructor que inicializa el componente como tipo SHAPE.
   * @param shapeType Tipo de forma geométrica a crear (CIRCLE, RECTANGLE, etc.).
   */
  CShape(ShapeType shapeType)
    : m_shapePtr(nullptr),
    m_shapeType(ShapeType::EMPTY),
    Component(ComponentType::SHAPE) {}

  /**
   * @brief Destructor virtual por defecto.
   */
  virtual 
    ~CShape() = default;

  /**
   * @brief Crea una forma geométrica según el tipo especificado.
   * @param shapeType Tipo de figura a generar.
   */
  void 
    createShape(ShapeType shapeType);

  /**
   * @brief Método llamado al iniciar el componente.
   */
  void 
    start() override;

  /**
   * @brief Actualiza el componente cada frame.
   * @param deltaTime Tiempo transcurrido desde el último frame.
   */
  void 
    update(float deltaTime) override;

  /**
   * @brief Dibuja la figura en la ventana.
   * @param window Puntero compartido a la ventana donde se renderiza.
   */
  void 
    render(const EngineUtilities::TSharedPointer<Window>& window) override;

  /**
   * @brief Libera los recursos asociados al componente.
   */
  void 
    destroy() override;

  /**
   * @brief Establece la posición de la figura.
   * @param x Coordenada X.
   * @param y Coordenada Y.
   */
  void 
    setPosition(float x, float y);

  /**
   * @brief Establece la posición de la figura.
   * @param position Vector con coordenadas (x, y).
   */
  void 
    setPosition(const sf::Vector2f& position);

  /**
   * @brief Cambia el color de relleno de la figura.
   * @param color Color a aplicar.
   */
  void 
    setFillColor(const sf::Color& color);

  /**
   * @brief Establece la rotación de la figura.
   * @param angle Ángulo en grados.
   */
  void 
    setRotation(float angle);

  /**
   * @brief Escala la figura.
   * @param scl Vector de escala (x, y).
   */
  void 
    setScale(const sf::Vector2f& scl);

  /**
   * @brief Asigna una textura a la figura.
   * @param texture Puntero compartido a la textura a aplicar.
   */
  void 
    setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

private:
  EngineUtilities::TSharedPointer<sf::Shape> m_shapePtr; ///< Puntero inteligente a la figura SFML.
  ShapeType m_shapeType; ///< Tipo de figura actual.
  sf::VertexArray* m_line = nullptr; ///< Línea auxiliar para depuración o formas especiales.
};

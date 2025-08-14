#pragma once
#include "Prerequisites.h"
#include "ECS\Component.h"
#include "ECS\Texture.h"
class Window;

class
	CShape : public Component {
public:
	CShape() = default;

	CShape(ShapeType shapeType) : m_shapePtr(nullptr),
		m_shapeType(ShapeType::EMPTY),
		Component(ComponentType::SHAPE) { }

	virtual
		~CShape() = default;

	/**
		* @Brief: This method is in charge of creating a shape based on the type provided.
		* @Param: shapeType: The type of shape to create.
		*/
	void
		createShape(ShapeType shapeType);

	void
		start() override;

	void
		update(float deltaTime) override;

	void
		render(const EngineUtilities::TSharedPointer<Window>& window) override;

	void
		destroy() override;

	void
		setPosition(float x, float y);

	void
		setPosition(const sf::Vector2f& position);

	void
		setFillColor(const sf::Color& color);

	void
		setRotation(float angle);

	void
		setScale(const sf::Vector2f& scl);

	void
		setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

private:
	EngineUtilities::TSharedPointer<sf::Shape> m_shapePtr;
	//sf::Shape* m_shape;
	ShapeType m_shapeType;
	sf::VertexArray* m_line;
};
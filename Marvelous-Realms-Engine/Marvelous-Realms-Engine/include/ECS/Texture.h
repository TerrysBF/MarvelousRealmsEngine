#pragma once
#include "Prerequisites.h"
#include "Component.h"

/**
 * @file Texture.h
 * @brief Componente para manejar texturas en el motor.
 *
 * Se encarga de cargar, almacenar y dar acceso a una textura.
 */
class
	Texture : public Component {
public:
	/**
	 * @brief Constructor por defecto.
	 */
	Texture() = default;

	/**
	 * @brief Constructor que carga una textura desde archivo.
	 * @param textureName Nombre del archivo sin extensión.
	 * @param extension Extensión del archivo (por defecto "png").
	 */
	Texture(const std::string& textureName, const std::string& extension = "png") :
		m_textureName(textureName), m_extension(extension), Component(ComponentType::TEXTURE) {
		if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
			std::cout << "Error de carga de textura: " 
				<< m_textureName << "." << m_extension << std::endl;
		}
	}

	/**
	 * @brief Destructor por defecto.
	 */
	virtual
		~Texture() = default;

	/// Inicializa el componente.
	void 
		start() override {};

	/// Actualiza el componente.
	void 
		update(float deltaTime) override {};

	/// Renderiza el componente.
	void 
		render(const EngineUtilities::TSharedPointer<Window>& window) override {};

	/// Libera recursos del componente.
	void 
		destroy() override {};

	/**
	 * @brief Obtiene la textura interna.
	 * @return Referencia a la textura SFML.
	 */
	sf::Texture&
		getTexture() {
		return m_texture;
	}

private:
	sf::Texture m_texture;      ///< Textura cargada.
	std::string m_textureName;  ///< Nombre de la textura.
	std::string m_extension;    ///< Extensión del archivo.
};

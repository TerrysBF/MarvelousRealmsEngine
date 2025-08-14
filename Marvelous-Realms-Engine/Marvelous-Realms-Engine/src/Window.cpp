#include "window.h"
#include "EngineGUI.h"

/**
 * @brief Constructor que crea la ventana principal.
 * @param width Ancho en píxeles.
 * @param height Alto en píxeles.
 * @param title Título de la ventana.
 */
Window::Window(int width, int height, const std::string& title) {
	m_windowPtr = EngineUtilities::MakeUnique<sf::RenderWindow>(
		sf::VideoMode({ static_cast<unsigned int>(width),
										static_cast<unsigned int>(height) }),
		title,
		sf::Style::Default
	);

	if (!m_windowPtr.isNull()) {
		m_windowPtr->setFramerateLimit(60);
		MESSAGE("Window", "Window", "Window created successfully");
	}
	else {
		ERROR("Window", "Window", "Failed to create window");
	}
}

/// Destructor que libera la ventana.
Window::~Window() {
	m_windowPtr.release();
}

/**
 * @brief Maneja eventos de la ventana y los pasa a la interfaz gráfica.
 */
void 
Window::handleEvents(EngineGUI& engineGUI) {
	while (const std::optional event = m_windowPtr->pollEvent()) {
		engineGUI.processEvent(*m_windowPtr, *event);
		if (event->is<sf::Event::Closed>())
			m_windowPtr->close();
	}
}

/**
 * @brief Verifica si la ventana está abierta.
 */
bool 
Window::isOpen() const {
	if (!m_windowPtr.isNull()) {
		return m_windowPtr->isOpen();
	}
	else {
		ERROR("Window", "isOpen", "Window is null");
		return false;
	}
}

/**
 * @brief Limpia la ventana con un color.
 */
void 
Window::clear(const sf::Color& color) {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->clear(color);
	}
	else {
		ERROR("Window", "clear", "Window is null");
	}
}

/**
 * @brief Dibuja un elemento en la ventana.
 */
void 
Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->draw(drawable, states);
	}
	else {
		ERROR("Window", "draw", "Window is null");
	}
}

/**
 * @brief Muestra en pantalla todo lo dibujado.
 */
void Window::display() {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->display();
	}
	else {
		ERROR("Window", "display", "Window is null");
	}
}

/**
 * @brief Actualiza el deltaTime.
 */
void 
Window::update() {
	deltaTime = clock.restart();
}

/// Método vacío para futuras operaciones de renderizado.
void 
Window::render() {}

/// Libera los recursos de la ventana.
void 
Window::destroy() {
	m_windowPtr.release();
}

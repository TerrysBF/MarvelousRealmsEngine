#pragma once
#include <Prerequisites.h>

class BaseApp {
public:
	BaseApp() = default;
	~BaseApp();

	//Función encargada de ejecutar la aplicación en main
	int run();

	//Función de inicialización
	bool init();

	//Función que se actualiza por frame
	void update();

	//Función de renderizado
	void render();

	void destroy();

	void handleEvents();

private:
	sf::RenderWindow* m_window;
	sf::CircleShape* m_circle;
};
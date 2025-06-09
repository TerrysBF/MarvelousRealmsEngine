#pragma once
#include <Prerequisites.h>

class BaseApp {
public:
	BaseApp() = default;
	~BaseApp();

	//Funci�n encargada de ejecutar la aplicaci�n en main
	int run();

	//Funci�n de inicializaci�n
	bool init();

	//Funci�n que se actualiza por frame
	void update();

	//Funci�n de renderizado
	void render();

	void destroy();

	void handleEvents();

private:
	sf::RenderWindow* m_window;
	sf::CircleShape* m_circle;
};
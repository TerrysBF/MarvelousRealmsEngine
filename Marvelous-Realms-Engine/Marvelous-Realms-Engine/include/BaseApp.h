#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include "ECS\Actor.h"
#include "EngineGUI.h"

class
	BaseApp {
public:
	BaseApp() = default;
	~BaseApp();

	// Funcion encargada de ejecutar la aplicacion en main
	int
		run();

	// Funcion de inicializacion
	bool
		init();

	// Funcion que se actualiza por frame
	void
		update();

	// Funcion de renderizado
	void
		render();

	void
		destroy();


private:
	std::vector< EngineUtilities::TSharedPointer<Actor>> m_actors;

	EngineUtilities::TSharedPointer<Window> m_windowPtr;

	EngineUtilities::TSharedPointer<Actor> m_ACirlce;

	EngineGUI m_engineGUI;



};
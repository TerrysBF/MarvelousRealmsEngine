#include "BaseApp.h"

BaseApp::~BaseApp()
{
}

int BaseApp::run() {
    if (!init()) {
        ERROR("BaseApp",
            "run",
            "Initializes result on a false statement, check method validations");
    }

    while (m_window->isOpen()) {
        m_window->handleEvents();
        update();
        render();
    }

    destroy();
    return 0;
}


bool BaseApp::init()
{
    m_window = new Window(1920, 1080, "Marvelous Realm Engine");
    m_circle = new sf::CircleShape(100.0f); // radio 100
    m_circle->setFillColor(sf::Color::Green);
    m_circle->setPosition(200.f, 150.f);
	return true;
}

void BaseApp::update()
{
}

void BaseApp::render()
{
    m_window->clear();
    m_window->draw(*m_circle);
    m_window->display();
}

void BaseApp::destroy()
{
    m_window->destroy();
    delete m_circle;
}
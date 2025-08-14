#pragma once
#include "Prerequisites.h"

class Window;
class Actor;
// Imgui
//#include <imgui.h>
//#include <imgui-SFML.h>

class
	EngineGUI {
public:
	EngineGUI() = default;
	~EngineGUI() = default;

	void
		init(const EngineUtilities::TSharedPointer<Window>& window);

	void
		update(const EngineUtilities::TSharedPointer<Window>& window,
			sf::Time deltaTime);

	void
		render(const EngineUtilities::TSharedPointer<Window>& window);

	void
		destroy();

	void
		processEvent(const sf::Window& window, const sf::Event& event);

	void
		setupGreyGUIStyle();

	void
		setupDarkGUIStyle();

	void
		barMenu();

	void
		outliner(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

	void
		console(const std::map<ConsolErrorType, std::vector<std::string>>& programMessages);

	void
		inspector(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

	void
		vec2Control(const std::string& label,
			float* values,
			float resetValues = 0.0f,
			float columnWidth = 100.0f);
private:
	int selectedActorIndex = -1;

};
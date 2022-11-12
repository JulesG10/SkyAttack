#pragma once
#include "SKGui.h"

class SKScrollList : public SKGui
{
public:
	SKScrollList(SKState* state, Rectangle size, Color fg, Color bg);
	~SKScrollList();

	void SetList(std::vector<std::string>);
	std::pair<int, std::string> GetSelected();
	
	void SetEnableSelection(bool active);
	bool UpdateFrame() override;
private:
	void UpdateItems();

	const int m_fontSize = 20;
	const int m_borderSize = 2;

	std::vector<std::string> m_list;
	std::vector<std::pair<Rectangle, Vector2>> m_positions;
	
	Rectangle m_rect;
	Vector2 m_itemSize;

	int m_selected;
	bool m_selection;

	int m_maxItem;
	int m_scroll;

	Color m_background;
	Color m_foreground;
};


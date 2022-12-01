#include "SKScrollList.h"


SKScrollList::SKScrollList(SKState* state, Rectangle rect, Color fg, Color bg) : SKGui(state), m_rect(rect), m_list({}), m_selected(-1), m_selection(true), m_foreground(fg), m_background(bg)
{
	this->m_itemSize = {
		rect.width,
		(float)this->m_fontSize * 2
	};
	this->m_scroll = 0;
	this->m_maxItem = (int)(rect.height / this->m_itemSize.y);
}

SKScrollList::~SKScrollList()
{
}

void SKScrollList::SetList(std::vector<std::string> list)
{
	this->m_list = list;
	this->UpdateItems();
}

std::pair<int, std::string> SKScrollList::GetSelected()
{
	return std::make_pair(this->m_selected, this->m_selected != -1 ? this->m_list[this->m_selected] : "");
}

void SKScrollList::SetEnableSelection(bool active)
{
	this->m_selection = active;
}

bool SKScrollList::UpdateFrame()
{

	int move = GetMouseWheelMove();
	if (move)
	{
		this->m_scroll += move;
		if (this->m_scroll >= this->m_list.size())
		{
			this->m_scroll = 0;
		}
		this->UpdateItems();
	}


	bool selected = false;
	bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	
	for (size_t i = this->m_scroll; i < this->m_list.size(); i++)
	{
		if (i >= this->m_scroll + this->m_maxItem)
		{
			break;
		}

		int posIndex = i - this->m_scroll;
		DrawRectangleRec(this->m_positions[posIndex].first, this->m_background);
		DrawText(this->m_list[i].c_str(), this->m_positions[posIndex].second.x, this->m_positions[posIndex].second.y, this->m_fontSize, this->m_foreground);

		if (mouseDown && CheckCollisionPointRec(this->m_state->GetMouse(), this->m_positions[posIndex].first))
		{
			selected = true;
			this->m_selected = i;
		}

		if (this->m_selected == i)
		{
			DrawRectangleLinesEx(this->m_positions[posIndex].first, 2, WHITE);
		}
	}

	if (this->m_selected != -1 && mouseDown && !selected)
	{
		this->m_clearNextFrame = true;
	}

	if (IsMouseButtonUp(MOUSE_BUTTON_LEFT) && this->m_clearNextFrame)
	{
		this->m_clearNextFrame = false;
		this->m_selected = -1;
	}

	DrawRectangleLinesEx(this->m_rect, this->m_borderSize, this->m_foreground);
	return selected;
}

void SKScrollList::UpdateItems()
{
	this->m_positions.clear();
	for (size_t i = this->m_scroll; i < this->m_list.size(); i++)
	{
		if (i >= this->m_scroll + this->m_maxItem)
		{
			break;
		}

		int posIndex = i - this->m_scroll;
		int y = this->m_rect.y + (this->m_itemSize.y * posIndex) + (this->m_borderSize * posIndex);
		Rectangle itemRect = {
			this->m_rect.x + this->m_borderSize, y,
			this->m_itemSize.x - this->m_borderSize, this->m_itemSize.y
		};

		int textX = MeasureText(this->m_list[i].c_str(), this->m_fontSize);
		Vector2 textPosition = {
			 this->m_rect.x + (this->m_rect.width - ((this->m_borderSize*2) + textX)) / 2.f,
			 y + this->m_fontSize / 2.f
		};

		this->m_positions.push_back(std::make_pair(itemRect, textPosition));
	}
}

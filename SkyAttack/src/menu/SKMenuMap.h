#pragma once

#include "../../stdafx.h"

#include "SKMenuPage.h"

#include "../game/SKMapEditor.h"

#include "../gui/SKScrollList.h"
#include "../gui/SKButton.h"
#include "../gui/SKLabel.h"
#include "../gui/SKInput.h"

class SKMenuMap : public SKMenuPage
{
public:
	SKMenuMap(SKState* state, SKMenuTransition* transition, SKMenuPages* page);
	~SKMenuMap();

	void UpdateFrame() override;
private:
	void UpdatePageFrame() override;
	void UpdateMapList();

	SKLabel* m_textMap;
	SKButton* m_create;
	SKButton* m_load;
	SKButton* m_delete;
	SKButton* m_goBack;

	SKScrollList* m_maps;
	
	SKButton* m_rename;
	SKInput* m_inputRename;

	SKMapEditor* m_editor;
};


#include "SKMenuMap.h"

SKMenuMap::SKMenuMap(SKState* state, SKMenuTransition* transition, SKMenuPages* page) : SKMenuPage(state, transition, page)
{
	this->m_editor = SK_NEW SKMapEditor(this->m_state);
	this->m_editor->SetAvailable(false);

	this->m_load = SK_NEW SKButton(state, "Load",
		SKGui::CenterObject({ 800, 200, 200, 40 }, state->m_renderSize, { 1, 0 }),
		WHITE, BLANK);
	this->m_load->SetEnable(false);

	this->m_delete = SK_NEW SKButton(state, "Delete",
		SKGui::CenterObject({ 800, 300, 200, 40 }, state->m_renderSize, { 1, 0 }),
		WHITE, BLANK);
	this->m_delete->SetEnable(false);


	this->m_create = SK_NEW SKButton(state, "Create",
		SKGui::CenterObject({ 800, 400, 200, 40 }, state->m_renderSize, { 1, 0 }),
		WHITE, BLANK);

	this->m_rename = SK_NEW SKButton(state, "Rename",
		SKGui::CenterObject({ 800, 650, 200, 40 }, state->m_renderSize, { 1, 0 }),
		WHITE, BLANK);
	this->m_rename->SetEnable(false);


	this->m_inputRename = SK_NEW SKInput(state,
		SKGui::CenterObject({ 800, 550, 200, 40 }, state->m_renderSize, { 1, 0 }),
		WHITE, BLANK, "New file name");
	
	this->m_goBack = SK_NEW SKButton(state, "Go Back",
		SKGui::CenterObject({ 0, 500, 200, 40 }, state->m_renderSize, { 1, 1 }),
		WHITE, BLANK);

	this->m_textMap = SK_NEW SKLabel("Maps", { this->m_state->m_renderSize.x/2.f, 60 }, 60, WHITE, { 1, 1 });

	this->m_maps = SK_NEW SKScrollList(state,
		SKGui::CenterObject({ 0, 200, 500, 500 }, state->m_renderSize, { 1, 0 }),
		WHITE, { 0,0,0,100 });

	this->UpdateMapList();

	//TODO rename button + input
}

SKMenuMap::~SKMenuMap()
{
	delete this->m_textMap;
	delete this->m_create;
	delete this->m_load;
	delete this->m_delete;
	delete this->m_goBack;
	delete this->m_maps;

	delete this->m_editor;
	delete this->m_rename;
	delete this->m_inputRename;
}

void SKMenuMap::UpdateFrame()
{
	if (this->m_editor->IsAvailable())
	{
		this->m_editor->UpdateFrame();
		if (this->m_editor->HasQuit())
		{
			this->UpdateMapList();
		}
		return;
	}
	SKMenuPage::UpdateFrame();
}

void SKMenuMap::UpdatePageFrame()
{
	this->m_textMap->UpdateFrame();

	if (this->m_create->UpdateFrame())
	{
		this->m_editor->SetAvailable(true);
		this->m_editor->Clear();
	}

	if (this->m_delete->UpdateFrame())
	{
		std::string file = this->m_editor->GetMapDir() + "\\" + this->m_maps->GetSelected().second + ".sk";
		if (DeleteFileA(file.c_str()))
		{
			this->UpdateMapList();
		}
	}

	if (this->m_rename->UpdateFrame())
	{
		if (this->m_inputRename->GetText().length() > 0)
		{
			std::string file = this->m_editor->GetMapDir() + "\\" + this->m_maps->GetSelected().second + ".sk";
			std::string newname = this->m_editor->GetMapDir() + "\\" + this->m_inputRename->GetText() + ".sk";

			if (rename(file.c_str(), newname.c_str()) == 0)
			{
				this->UpdateMapList();
			}
			this->m_inputRename->SetText("");
		}
	}

	if (this->m_load->UpdateFrame())
	{
		this->m_editor->Clear();
		this->m_editor->SetAvailable(false);

		if (this->m_editor->LoadMap(this->m_editor->GetMapDir() + "\\" + this->m_maps->GetSelected().second + ".sk"))
		{
			this->m_editor->SetAvailable(true);
		}
		else {
			this->m_editor->Clear();
		}
	}

	this->m_maps->UpdateFrame();
	if (this->m_maps->GetSelected().first != -1)
	{
		this->m_load->SetEnable(true);
		this->m_delete->SetEnable(true);
	}
	else {
		this->m_delete->SetEnable(false);
		this->m_load->SetEnable(false);
		this->m_rename->SetEnable(false);
	}

	this->m_inputRename->UpdateFrame();
	if (this->m_inputRename->GetText().length() > 0 && this->m_maps->GetSelected().first != -1)
	{
		this->m_rename->SetEnable(true);
	}

	if (this->m_goBack->UpdateFrame())
	{
		this->ChangePage(SKMenuPages::PAGE_HOME);
	}
}

void SKMenuMap::UpdateMapList()
{
	std::vector<std::string> dirmaps = GetDirFiles(this->m_editor->GetMapDir(), false);
	std::for_each(dirmaps.begin(), dirmaps.end(), [](std::string& file) {
		size_t lastindex = file.find_last_of(".");
			if (lastindex != std::string::npos)
			{
				file = file.substr(0, lastindex);
			}
	});
	this->m_maps->SetList(dirmaps);
}

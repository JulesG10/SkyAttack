#include "SKPlayerShip.h"

SKPlayerShip::SKPlayerShip(SKState* state) : SKShip(state)
{
}

SKPlayerShip::~SKPlayerShip()
{
}

void SKPlayerShip::UpdateFrame()
{
	if (this->m_state->m_loading)
	{
		return;
	}


}

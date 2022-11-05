#pragma once
#include "../stdafx.h"

template <typename... Args>
class SKAnimation {
public:
	SKAnimation(void (*func)(Args...), float frequence) : m_active(false), m_timer(0.f), m_frequence(0.f), m_func(nullptr)
	{
		this->m_active = true;
		this->m_frequence = frequence;
		this->m_func = func;
	}

	~SKAnimation()
	{

	}

	void Stop()
	{
		this->m_active = false;
	}

	void Reset(float frequence = -1)
	{
		if (frequence != -1)
		{
			this->m_frequence = frequence;
		}
		this->m_active = true;
		this->m_timer = 0.f;
	}


	template<typename... Args>
	void Update(Args... args)
	{
		if (!this->m_active || this->m_func == nullptr  || this->m_frequence == 0.f)
		{
			return;
		}
		this->m_timer += GetFrameTime() * 1000.f;
		if (this->m_timer >= this->m_frequence)
		{
			this->m_func(args...);
			this->m_timer = 0.f;
		}
	}
private:
	float m_timer;
	float m_frequence;
	bool m_active;

	void (*m_func)(Args...);
};
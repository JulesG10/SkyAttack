#pragma once

#include "../../stdafx.h"

typedef struct SKBulletOptions {
	Vector2 position;
	Vector2 velocity;

	float reducingFactor;
	int damage;

	Vector2 origin;
	Vector2 size;
	float scale;

	float angle;

	SKTextureId texture;
} SKBulletOptions;

class SKBullet 
{
public:
	SKBullet(SKState* state, SKBulletOptions options);

	void SetOptions(SKBulletOptions options);
	SKBulletOptions GetOptions();

	Rectangle GetView();
	bool UpdateFrame();
private:
	void Reduce(float*);
	SKBulletOptions m_options;
	SKState* m_state;
};


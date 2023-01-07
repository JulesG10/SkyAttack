#pragma once

#include "../../stdafx.h"

typedef struct SKBulletOptions {
	Vector2 position;
	Vector2 velocity;

	float maxDistance;
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
	static Vector2 CalculateVelocity(float force, float angle);

	void SetOptions(SKBulletOptions options);
	SKBulletOptions GetOptions();

	Rectangle GetView();
	Rectangle GetBounds();
	bool UpdateFrame(bool isInView);
private:
	float m_distance;
	SKBulletOptions m_options;
	SKState* m_state;
};


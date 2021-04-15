#pragma once
#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include "resource.h"
#pragma comment( lib, "winmm.lib" ) // TimeGetTime : 부팅 후 시간
#pragma warning( disable : 4244 )

enum STATE {
	IDLE, WALK, JUMP, DROP, ATTACK, HIT, KICK
};

enum DIRECTION {
	LEFT, RIGHT
};

enum OBJECTS {
	HERO, ENEMY, BULLET, BGA
};

enum HITTYPE {
	HT_BULLET, HT_KICK
};

struct CGPosition{
	float x;
	float y;
};

struct VectorInformation {
	CGPosition	vec;
	float		distance;
};

struct EffectInfo {
	HBITMAP		resource;
	CGPosition	srcSize;
	int			MaxFrame;
	float		delay;
	CGPosition	offset;
	float		anotherDirectionPos;
};

struct HitInform
{
	HITTYPE		type;
	float		groggyDelay;
	float		outDis;
};

CGPosition MakePosition(float _x, float _y);
#define ccp(__x, __y) MakePosition(__x, __y)

#define VELOCITY		700
#define GRAVITY		1400	
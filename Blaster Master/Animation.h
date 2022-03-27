#pragma once
#include <unordered_map>
#include "Sprite.h"

using namespace std;

class AnimationFrame {
public:
	LPSPRITE sprite;
	long time;
	long dtime;
	D3DXVECTOR2 movement;
	D3DXVECTOR2 size;
	AnimationFrame(LPSPRITE sprite, D3DXVECTOR2 movement, DWORD dtime, DWORD time);
	~AnimationFrame();
};
typedef AnimationFrame* PLANIMATIONFRAME;


class Animation {
private:
	std::vector<PLANIMATIONFRAME> listFrames;
	bool isRepeat;
	bool isRunning;
	bool isPausing;
	bool isDone;
	int currentFrameId;
	int nextAnimationId;
	int mode;
	bool continues = true;
	long time;
public:
	Animation();
	void Add(LPSPRITE sprite, DWORD time);
	void Add(LPSPRITE sprite, D3DXVECTOR2 movement, DWORD time);
	void Start();
	void Restart();
	void Start(unsigned int frameID, int mode);
	void Stop();
	void Pause();
	void Resume(int mode);
	void Repeat(bool isRepeat);
	void Update(DWORD dt);
	bool IsPausing();
	bool IsRunning();
	bool IsLastFrame();
	bool IsFirstFrame();
	bool IsDone();
	void SetNextAnimationID(int aniID);
	void Render(D3DXVECTOR2 position, float opacity = 1.0f);
	D3DXVECTOR2 GetSize();
	int GetMode();
	unsigned int GetCurrentFrameID();
	int GetNextAnimationID();
	~Animation();
};
typedef Animation* LPANIMATION;



class Animations {
private:
	vector<LPANIMATION> listAnimations;
	int currentAnimationId;
	bool continues = true;
public:
	Animations();
	void Add(LPANIMATION animation);
	void Start(unsigned int id);
	void Restart(unsigned int animationID);
	void Start(unsigned int animationID, unsigned int frameID);
	void Pause();
	void Resume(int mode);
	void Stop();
	void Stop(unsigned int animationID);
	void Update(DWORD dt);
	void Render(D3DXVECTOR2 position, float opacity = 1.0f);
	bool IsLastFrame();
	bool IsFirstFrame();
	D3DXVECTOR2 GetSize();
	LPANIMATION GetCurrentAnimation();
	LPANIMATION GetAnimation(int id);
	int GetCurrentAnimationID();
	~Animations();
};
typedef Animations* LPANIMATIONS;
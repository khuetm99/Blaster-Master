#include "Animation.h"
#include "Debug.h"



AnimationFrame::AnimationFrame(LPSPRITE sprite, D3DXVECTOR2 movement, DWORD dtime, DWORD time)
{
	this->sprite = sprite;
	this->dtime = dtime;
	this->movement = movement;
	this->time = time;
	this->size = sprite->Size();
}

AnimationFrame::~AnimationFrame()
{
}



Animation::Animation()
{
	listFrames.clear();
	isRepeat = false;
	isRunning = false;
	isDone = false;
	nextAnimationId = -1;
	currentFrameId = 0;
	DWORD time = 0;
	mode = 1;
}

void Animation::Add(LPSPRITE sprite, DWORD dtime)
{
	if (sprite != NULL) {
		PLANIMATIONFRAME frame;
		if (listFrames.size() == 0)
			frame = new AnimationFrame(sprite, D3DXVECTOR2(0,0), dtime, 0);
		else
			frame = new AnimationFrame(sprite, D3DXVECTOR2(0, 0), dtime, listFrames.back()->time + listFrames.back()->dtime);
		listFrames.push_back(frame);
	}
}

void Animation::Add(LPSPRITE sprite, D3DXVECTOR2 movement,  DWORD dtime)
{
	if (sprite != NULL) {
		PLANIMATIONFRAME frame;
		if (listFrames.size() == 0) {
			frame = new AnimationFrame(sprite, movement, dtime, 0);
		}	
		else {
			frame = new AnimationFrame(sprite, movement, dtime, listFrames.back()->time + listFrames.back()->dtime);
		}

		listFrames.push_back(frame);
	}
}



void Animation::Start()
{
	if (isRunning==false) {
		mode = 1;
		currentFrameId = 0;
		isRunning = true;
		isPausing = false;
		isDone = false;
		time = 0;
	}
}

void Animation::Restart()
{
	mode = 1;
	currentFrameId = 0;
	isRunning = true;
	isPausing = false;
	isDone = false;
	time = 0;
}

void Animation::Start(unsigned int frameID, int mode)
{
	if (this->listFrames.size() > 0) {
		this->mode = mode;
		this->currentFrameId = frameID;
		this->isRunning = true;
		this->isPausing = false;
		this->isDone = false;

		if (mode == 1) {
			this->time = listFrames[currentFrameId]->time;
		}
		else
		if(mode == -1){
			this->time = listFrames[currentFrameId]->time + listFrames[currentFrameId]->dtime;
		}
	}
}


void Animation::Stop()
{
	mode = 1;
	currentFrameId = 0;
	isRunning = false;
	isPausing = false;
	time = 0;
}

void Animation::Pause()
{
	isPausing = true;
}

void Animation::Resume(int mode)
{	
	if (isRunning == true && isPausing == true) {
		if (currentFrameId < listFrames.size()) {
			if (mode == 1) {
				this->mode = 1;
				this->isPausing = false;
				this->isRunning = true;
				this->isDone = false;
				this->time = listFrames[currentFrameId]->time;
			}
			else 
			if(mode == -1){
				this->mode = -1;
				this->isPausing = false;
				this->isRunning = true;
				this->isDone = false;
				this->time = listFrames[currentFrameId]->time + listFrames[currentFrameId]->dtime;
			}
		}
	}
}

void Animation::Repeat(bool isRepeat)
{
	this->isRepeat = isRepeat;
}

void Animation::Update(DWORD dt)
{
	if (isRunning && !isPausing) {
		if (mode == 1) {
			//update id
			if (time > listFrames[currentFrameId]->time + listFrames[currentFrameId]->dtime) {
				currentFrameId++;
				if (isRepeat == false) { // dont' repeat
					if (currentFrameId >= listFrames.size()) { //
						currentFrameId = listFrames.size() - 1;
						isDone = true;
						Pause();
					}
				}
				else { // repeat
					if (currentFrameId >= listFrames.size()) {
						currentFrameId = 0;
						time = 0;
					}
				}
			}

			time = time + dt;

		}
		else
		if(mode == -1){
			//DebugOut(L"id %d time %d currtime %d = %d\n ", currentFrameId, time, listFrames[currentFrameId]->time, time < listFrames[currentFrameId]->time);
			//update id
			if (time < listFrames[currentFrameId]->time) {
				currentFrameId--;
				if (isRepeat == false) { // dont' repeat
					if (currentFrameId < 0) {
						currentFrameId = 0;
						isDone = true;
						Pause();
					}
				}
				else { // repeat
					if (currentFrameId < 0) {
						currentFrameId = listFrames.size() - 1;
						time = listFrames.back()->time + listFrames.back()->dtime;
					}
				}
			}

			time = time - dt;
		}
	}
}

bool Animation::IsPausing()
{
	return isPausing;
}


bool Animation::IsRunning()
{
	return isRunning;
}

bool Animation::IsLastFrame()
{
	if (this->currentFrameId == listFrames.size() - 1) {
		return true;
	}
	return false;
}

bool Animation::IsFirstFrame()
{
	if (this->currentFrameId == 0) {
		return true;
	}
	return false;
}

bool Animation::IsDone()
{
	return isDone;
}

void Animation::SetNextAnimationID(int aniID)
{
	this->nextAnimationId = aniID;
}

void Animation::Render(D3DXVECTOR2 position, float opacity)
{
	if (listFrames.size() > 0) {
		if (isRunning) {
			PLANIMATIONFRAME frame = listFrames[currentFrameId];
			frame->sprite->Draw(position + frame->movement, opacity);
		}	
	}
}

D3DXVECTOR2 Animation::GetSize()
{
	if (currentFrameId < listFrames.size()) {
		return  listFrames[currentFrameId]->size;
	}
}

int Animation::GetMode()
{
	return this->mode;
}

unsigned int Animation::GetCurrentFrameID()
{
	return this->currentFrameId;
}

int Animation::GetNextAnimationID()
{
	return nextAnimationId;
}

Animation::~Animation()
{
}





Animations::Animations()
{
	listAnimations.clear();
	currentAnimationId = 0;
}

void Animations::Add(LPANIMATION animation)
{
	if (animation != NULL) {
		listAnimations.push_back(animation);
	}
}

void Animations::Start(unsigned int animationID)
{
	if (animationID >= 0 && animationID < listAnimations.size()) {
		this->currentAnimationId = animationID;
		listAnimations.at(animationID)->Start();
	}
}

void Animations::Start(unsigned int animationID, unsigned int frameID)
{
	if (animationID >= 0 && animationID < listAnimations.size()) {
		if (currentAnimationId != animationID)
		{
			this->listAnimations[currentAnimationId]->Stop();
			this->currentAnimationId = animationID;
			this->listAnimations.at(animationID)->Start(frameID, this->listAnimations[currentAnimationId]->GetMode());
		}
	}
}

void Animations::Restart(unsigned int animationID)
{
	if (animationID >= 0 && animationID < listAnimations.size()) {
		this->currentAnimationId = animationID;
		listAnimations.at(animationID)->Restart();
	}
}


void Animations::Pause()
{
	if (currentAnimationId < listAnimations.size()) {
		listAnimations[currentAnimationId]->Pause();
	}
}


void Animations::Resume(int mode)
{
	if (currentAnimationId < listAnimations.size()) {
		listAnimations[currentAnimationId]->Resume(mode);
	}
}

void Animations::Stop()
{
	if (currentAnimationId < listAnimations.size()) {
		listAnimations[currentAnimationId]->Stop();
	}
}

void Animations::Stop(unsigned int animationID)
{
	if (animationID >= 0 && animationID < listAnimations.size()) {
		this->listAnimations.at(animationID)->Stop();
	}
}

void Animations::Update(DWORD dt)
{
	if (currentAnimationId < listAnimations.size()) {
		int next = listAnimations[currentAnimationId]->GetNextAnimationID();
		if (listAnimations[currentAnimationId]->IsDone() && next >= 0 && next < listAnimations.size()) {
			Restart(next);
			listAnimations[next]->Update(dt);
		}
		else {
			listAnimations[currentAnimationId]->Update(dt);
		}
	}
}

void Animations::Render(D3DXVECTOR2 position, float opacity)
{
	if (currentAnimationId < listAnimations.size()) {
		listAnimations[currentAnimationId]->Render(position, opacity);
	}
}

bool Animations::IsLastFrame()
{
	return listAnimations[currentAnimationId]->IsLastFrame();
}

bool Animations::IsFirstFrame()
{
	return listAnimations[currentAnimationId]->IsFirstFrame();
}

D3DXVECTOR2 Animations::GetSize()
{
	if (currentAnimationId < listAnimations.size()) {
		return listAnimations[currentAnimationId]->GetSize();
	}
	else
	{
		return D3DXVECTOR2();
	}
}

LPANIMATION Animations::GetCurrentAnimation()
{
	return this->listAnimations[currentAnimationId];
}

LPANIMATION Animations::GetAnimation(int id)
{
	if (id < listAnimations.size()) {
		return listAnimations[id];
	}
	return nullptr;
}

int Animations::GetCurrentAnimationID()
{
	return currentAnimationId;
}

Animations::~Animations()
{
}


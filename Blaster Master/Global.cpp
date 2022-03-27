#include "Global.h"

Global* Global::_instance = NULL;
double Global::_FPS = 120;
double Global::_G = 0.0005f;

Global* Global::GetInstance()
{
	if (_instance == NULL) _instance = new Global();
	return _instance;
}



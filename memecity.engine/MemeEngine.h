#ifndef _MEME_ENGINE_H
#define _MEME_ENGINE_H
#include <memory>
#include "MultimediaManager.h"
#include "InputManager.h"
#include "TimerFacade.h"
class MemeEngine
{
protected:
	std::shared_ptr<MultimediaManager> multimedia_manager;
	std::shared_ptr<InputManager> input_manager;
	std::shared_ptr<TimerFacade> timer;

	virtual bool Init();
	virtual void Handle();
public:
	int Run();
	MemeEngine();

};

#endif
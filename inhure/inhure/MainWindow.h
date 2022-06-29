#pragma once

#include"F_lib/include/Window.h"
#include "CustomInput.h"

F_lib_Fremworker::GameWindow* getthiswindow();

//
class MainWindow:public F_lib_Fremworker::GameWindow
{
public:
	void init()   override;

private:
	void Update() override;

	class CustomInput* input;

};


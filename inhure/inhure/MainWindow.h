#pragma once

#include"F_lib/include/Window.h"


F_lib_Fremworker::GameWindow* getthiswindow();

//
class MainWindow:public F_lib_Fremworker::GameWindow
{
public:
	void init();

};


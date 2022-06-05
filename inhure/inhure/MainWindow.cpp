#include "MainWindow.h"
#include "SceneManager_infure.h"
#include "input.h"

F_lib_Fremworker::GameWindow* mainwind;

F_lib_Fremworker::GameWindow* getthiswindow() { return mainwind; }

//----------------------------------------------------------------------

//
void MainWindow::init()
{
	mainwind = this;
	GameWindow::init();
	Scene = new SceneManeger_inhure(Engine);
	InitInput();

}

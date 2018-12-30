//---------------------------------------------------------
// 程序名称：推箱子
// 作者：Nomango
// 最后更新：2018-3-14
// 编译环境：Visual Studio 2017 / Easy2D v2.0.0-beta6
// 项目类型：Win32 Application
//---------------------------------------------------------

#include <easy2d.h>
#include "resource.h"
#include "StartScene.h"
#include "Data.h"

void Init();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 初始化游戏
	if (Game::init("推箱子", 640, 480, (LPCTSTR)IDI_ICON1, "PushBox-nomango")) 
	{
		// 初始化资源文件
		Init();

		// 进入开始场景
		auto scene = new StartScene();
		SceneManager::enter(scene);

		// 开始游戏
		Game::run();
	}
	
	// 回收游戏资源
	Game::uninit();
	return 0;
}

void Init()
{
	// 预加载音乐文件
	MusicManager::preload("res/background.wav");
	MusicManager::preload("res/boxmove.wav");
	MusicManager::preload("res/manmove.wav");
	// 循环播放背景音乐，255 表示循环播放
	MusicManager::get("res/background.wav")->play(255);
	// 从文件读取关卡信息，未读取到时默认为 1
	g_CurrentLevel = Data::getInt("level", 1);
	// 从文件读取声音开关信息，未读取到时默认为 1
	g_SoundOpen = Data::getBool("sound", true);
	if (!g_SoundOpen)
	{
		MusicManager::get("res/background.wav")->pause();
	}
}
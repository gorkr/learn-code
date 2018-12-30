//---------------------------------------------------------
// �������ƣ�������
// ���ߣ�Nomango
// �����£�2018-3-14
// ���뻷����Visual Studio 2017 / Easy2D v2.0.0-beta6
// ��Ŀ���ͣ�Win32 Application
//---------------------------------------------------------

#include <easy2d.h>
#include "resource.h"
#include "StartScene.h"
#include "Data.h"

void Init();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ��ʼ����Ϸ
	if (Game::init("������", 640, 480, (LPCTSTR)IDI_ICON1, "PushBox-nomango")) 
	{
		// ��ʼ����Դ�ļ�
		Init();

		// ���뿪ʼ����
		auto scene = new StartScene();
		SceneManager::enter(scene);

		// ��ʼ��Ϸ
		Game::run();
	}
	
	// ������Ϸ��Դ
	Game::uninit();
	return 0;
}

void Init()
{
	// Ԥ���������ļ�
	MusicManager::preload("res/background.wav");
	MusicManager::preload("res/boxmove.wav");
	MusicManager::preload("res/manmove.wav");
	// ѭ�����ű������֣�255 ��ʾѭ������
	MusicManager::get("res/background.wav")->play(255);
	// ���ļ���ȡ�ؿ���Ϣ��δ��ȡ��ʱĬ��Ϊ 1
	g_CurrentLevel = Data::getInt("level", 1);
	// ���ļ���ȡ����������Ϣ��δ��ȡ��ʱĬ��Ϊ 1
	g_SoundOpen = Data::getBool("sound", true);
	if (!g_SoundOpen)
	{
		MusicManager::get("res/background.wav")->pause();
	}
}
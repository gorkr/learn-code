#include "StartScene.h"
#include "PlayScene.h"
#include "Data.h"

StartScene::StartScene()
{
	// 添加背景图
	auto background = new Sprite("res/start.jpg");
	this->add(background);

	// 修改节点默认中心点位置
	Node::setDefaultPiovt(0.5, 0.5);

	// 创建字体
	auto fontNormal = new Font("新宋体", 28, Color::BLACK, FontWeight::BOLD);
	auto fontSelect = new Font("新宋体", 28, Color::BLUE, FontWeight::BOLD);
	auto fontDisable = new Font("新宋体", 28, Color::LIGHT_GRAY, FontWeight::BOLD);

	// 创建开始游戏按钮
	auto startBtn = new Button();
	startBtn->setNormal(new Text("新游戏", fontNormal));
	startBtn->setMouseOver(new Text("新游戏", fontSelect));
	// 设置按钮位置
	startBtn->setPos(Window::getWidth() / 2, 260);
	// 将 Start 函数设置为回调函数
	ButtonCallback bcStart = std::bind(&StartScene::Start, this);
	// 设置按钮回调函数
	startBtn->setCallback(bcStart);
	this->add(startBtn);

	// 继续游戏按钮
	resumeBtn = new Button();
	resumeBtn->setNormal(new Text("继续关卡", fontNormal));
	resumeBtn->setMouseOver(new Text("继续关卡", fontSelect));
	resumeBtn->setDisabled(new Text("继续关卡", fontDisable));
	// 设置按钮位置
	resumeBtn->setPos(Window::getWidth() / 2, 300);
	// 若当前关卡是第一关，禁用这个按钮
	if (g_CurrentLevel == 1) {
		resumeBtn->setEnable(false);
	}
	// 将 Continue 函数设置为回调函数
	ButtonCallback bcContinue = std::bind(&StartScene::Continue, this);
	// 设置按钮回调函数
	resumeBtn->setCallback(bcContinue);
	this->add(resumeBtn);

	// 创建退出按钮
	auto exitBtn = new Button();
	exitBtn->setNormal(new Text("退出", fontNormal));
	exitBtn->setMouseOver(new Text("退出", fontSelect));
	// 设置按钮位置
	exitBtn->setPos(Window::getWidth() / 2, 340);
	// 将 Exit 函数设置为回调函数
	ButtonCallback bcExit = std::bind(&StartScene::Exit, this);
	// 设置按钮回调函数
	exitBtn->setCallback(bcExit);
	this->add(exitBtn);

	// 创建声音开关按钮
	soundBtn = new ButtonToggle(
		new Sprite("res/soundon.png"),
		new Sprite("res/soundoff.png")
	);
	// 设置按钮位置
	soundBtn->setPos(50, 50);
	// 将 Sound 函数设置为回调函数
	ButtonCallback bcSound = std::bind(&StartScene::Sound, this);
	// 设置按钮回调函数
	soundBtn->setCallback(bcSound);
	this->add(soundBtn);

	// 恢复节点默认中心点位置
	Node::setDefaultPiovt(0, 0);
}

void StartScene::onEnter()
{
	// 判断声音是否打开，修改声音按钮的状态
	soundBtn->setState(g_SoundOpen);
	
	// 当前关卡不为 1 时，可以继续游戏
	if (g_CurrentLevel == 1) {
		resumeBtn->setEnable(false);
	}
	else {
		resumeBtn->setEnable(true);
	}
}

void StartScene::Start()
{
	// 创建 PlayScene 场景
	auto scene = new PlayScene(1);
	// 切换到 PlayScene 场景
	SceneManager::enter(scene);
}

void StartScene::Continue()
{
	// 创建 PlayScene 场景
	auto scene = new PlayScene(g_CurrentLevel);
	// 切换到 PlayScene 场景
	SceneManager::enter(scene);
}

void StartScene::Exit()
{
	// 退出游戏
	Game::quit();
}

void StartScene::Sound()
{
	// 获取音乐对象
	auto music = MusicManager::get("res/background.wav");
	// 获取按钮状态
	g_SoundOpen = soundBtn->getState();
	if (g_SoundOpen)
	{
		// 继续背景音乐
		music->resume();
	}
	else
	{
		// 暂停背景音乐
		music->pause();
	}
	// 保存信息到文件
	Data::saveBool("sound", g_SoundOpen);
}

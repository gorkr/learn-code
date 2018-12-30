#include "StartScene.h"
#include "PlayScene.h"
#include "Data.h"

StartScene::StartScene()
{
	// ��ӱ���ͼ
	auto background = new Sprite("res/start.jpg");
	this->add(background);

	// �޸Ľڵ�Ĭ�����ĵ�λ��
	Node::setDefaultPiovt(0.5, 0.5);

	// ��������
	auto fontNormal = new Font("������", 28, Color::BLACK, FontWeight::BOLD);
	auto fontSelect = new Font("������", 28, Color::BLUE, FontWeight::BOLD);
	auto fontDisable = new Font("������", 28, Color::LIGHT_GRAY, FontWeight::BOLD);

	// ������ʼ��Ϸ��ť
	auto startBtn = new Button();
	startBtn->setNormal(new Text("����Ϸ", fontNormal));
	startBtn->setMouseOver(new Text("����Ϸ", fontSelect));
	// ���ð�ťλ��
	startBtn->setPos(Window::getWidth() / 2, 260);
	// �� Start ��������Ϊ�ص�����
	ButtonCallback bcStart = std::bind(&StartScene::Start, this);
	// ���ð�ť�ص�����
	startBtn->setCallback(bcStart);
	this->add(startBtn);

	// ������Ϸ��ť
	resumeBtn = new Button();
	resumeBtn->setNormal(new Text("�����ؿ�", fontNormal));
	resumeBtn->setMouseOver(new Text("�����ؿ�", fontSelect));
	resumeBtn->setDisabled(new Text("�����ؿ�", fontDisable));
	// ���ð�ťλ��
	resumeBtn->setPos(Window::getWidth() / 2, 300);
	// ����ǰ�ؿ��ǵ�һ�أ����������ť
	if (g_CurrentLevel == 1) {
		resumeBtn->setEnable(false);
	}
	// �� Continue ��������Ϊ�ص�����
	ButtonCallback bcContinue = std::bind(&StartScene::Continue, this);
	// ���ð�ť�ص�����
	resumeBtn->setCallback(bcContinue);
	this->add(resumeBtn);

	// �����˳���ť
	auto exitBtn = new Button();
	exitBtn->setNormal(new Text("�˳�", fontNormal));
	exitBtn->setMouseOver(new Text("�˳�", fontSelect));
	// ���ð�ťλ��
	exitBtn->setPos(Window::getWidth() / 2, 340);
	// �� Exit ��������Ϊ�ص�����
	ButtonCallback bcExit = std::bind(&StartScene::Exit, this);
	// ���ð�ť�ص�����
	exitBtn->setCallback(bcExit);
	this->add(exitBtn);

	// �����������ذ�ť
	soundBtn = new ButtonToggle(
		new Sprite("res/soundon.png"),
		new Sprite("res/soundoff.png")
	);
	// ���ð�ťλ��
	soundBtn->setPos(50, 50);
	// �� Sound ��������Ϊ�ص�����
	ButtonCallback bcSound = std::bind(&StartScene::Sound, this);
	// ���ð�ť�ص�����
	soundBtn->setCallback(bcSound);
	this->add(soundBtn);

	// �ָ��ڵ�Ĭ�����ĵ�λ��
	Node::setDefaultPiovt(0, 0);
}

void StartScene::onEnter()
{
	// �ж������Ƿ�򿪣��޸�������ť��״̬
	soundBtn->setState(g_SoundOpen);
	
	// ��ǰ�ؿ���Ϊ 1 ʱ�����Լ�����Ϸ
	if (g_CurrentLevel == 1) {
		resumeBtn->setEnable(false);
	}
	else {
		resumeBtn->setEnable(true);
	}
}

void StartScene::Start()
{
	// ���� PlayScene ����
	auto scene = new PlayScene(1);
	// �л��� PlayScene ����
	SceneManager::enter(scene);
}

void StartScene::Continue()
{
	// ���� PlayScene ����
	auto scene = new PlayScene(g_CurrentLevel);
	// �л��� PlayScene ����
	SceneManager::enter(scene);
}

void StartScene::Exit()
{
	// �˳���Ϸ
	Game::quit();
}

void StartScene::Sound()
{
	// ��ȡ���ֶ���
	auto music = MusicManager::get("res/background.wav");
	// ��ȡ��ť״̬
	g_SoundOpen = soundBtn->getState();
	if (g_SoundOpen)
	{
		// ������������
		music->resume();
	}
	else
	{
		// ��ͣ��������
		music->pause();
	}
	// ������Ϣ���ļ�
	Data::saveBool("sound", g_SoundOpen);
}

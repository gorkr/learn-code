#include "SuccessScene.h"
#include "PlayScene.h"

SuccessScene::SuccessScene()
{
	// ����ͼƬ
	auto background = new Sprite("res/success.jpg");
	this->add(background);

	// �����˵���ť
	auto backBtn = new Button();
	backBtn->setNormal(new Text("�����˵�", "������", 28, Color::BLACK, FontWeight::BOLD));
	backBtn->setMouseOver(new Text("�����˵�", "������", 28, Color::BLUE, FontWeight::BOLD));
	backBtn->setPos(255, 350);
	// ���������ص�����
	backBtn->setCallback([]() { SceneManager::back(); });
	this->add(backBtn);
}

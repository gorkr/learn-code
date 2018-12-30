#include "SuccessScene.h"
#include "PlayScene.h"

SuccessScene::SuccessScene()
{
	// 背景图片
	auto background = new Sprite("res/success.jpg");
	this->add(background);

	// 回主菜单按钮
	auto backBtn = new Button();
	backBtn->setNormal(new Text("回主菜单", "新宋体", 28, Color::BLACK, FontWeight::BOLD));
	backBtn->setMouseOver(new Text("回主菜单", "新宋体", 28, Color::BLUE, FontWeight::BOLD));
	backBtn->setPos(255, 350);
	// 设置匿名回调函数
	backBtn->setCallback([]() { SceneManager::back(); });
	this->add(backBtn);
}

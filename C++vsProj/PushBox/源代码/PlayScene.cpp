#include "PlayScene.h"
#include "SuccessScene.h"


PlayScene::PlayScene(int level)
{
	// 创建字体
	auto font = new Font("新宋体", 28, Color::WHITE, FontWeight::BOLD);
	auto font2 = new Font("新宋体", 20, Color::WHITE, FontWeight::BOLD);

	// 当前关卡文字
	levelText = new Text("", font);
	levelText->setPos(520, 30);
	this->add(levelText);

	// 当前步数文字
	stepText = new Text("", font2);
	stepText->setPos(520, 100);
	this->add(stepText);

	// 最佳步数文字
	bestText = new Text("", font2);
	bestText->setPos(520, 140);
	this->add(bestText);

	// 按 ESC 退出提示文字
	auto exitText = new Text("按ESC返回", font2);
	exitText->setPos(520, 250);
	this->add(exitText);

	// 按回车重新开始提示文字
	auto restartText = new Text("按回车重开", font2);
	restartText->setPos(520, 290);
	this->add(restartText);

	// 添加地图部分
	mapLayer = new Node();
	this->add(mapLayer);

	// 设置关卡
	this->SetLevel(level);

	// 创建回调函数
	VoidFunction cb = CreateCallback(this, &PlayScene::GetInput);
	// 添加输入监听
	Input::add(cb);
}

void PlayScene::GetInput()
{
	// 按 ESC 返回上一场景
	if (Input::isKeyPress(KeyCode::ESC)) {
		SceneManager::back();
	}
	// 按回车重新开始
	if (Input::isKeyPress(KeyCode::ENTER)) {
		SetLevel(g_CurrentLevel);
	}

	// 按上下左右移动人物
	if (Input::isKeyPress(KeyCode::UP)) {
		Move(0, -1, 1);
	}
	else if (Input::isKeyPress(KeyCode::DOWN)) {
		Move(0, 1, 2);
	}
	else if (Input::isKeyPress(KeyCode::LEFT)) {
		Move(-1, 0, 3);
	}
	else if (Input::isKeyPress(KeyCode::RIGHT)) {
		Move(1, 0, 4);
	}
	else {
		// 忽略其他按键
		return;
	}

	// 刷新地图
	Flush();

	// 判断是否通关
	for (int i = 0; i < map.width; i++) {
		for (int j = 0; j < map.height; j++) {
			Piece p = map.value[j][i];
			if (p.type == TYPE::Box && p.isPoint == false) {
				// 存在未处于得分点上的箱子，则未通关
				return;
			}
		}
	}

	// 若所有箱子都在得分点上，结束这一关
	GameOver();
}

void PlayScene::Flush()
{
	// 清除原地图
	mapLayer->clearAllChildren();
	// 加载地图
	for (int i = 0; i < map.width; i++) {
		for (int j = 0; j < map.height; j++) {
			// 取出地图中的元素
			Piece piece = map.value[j][i];
			// 创建精灵
			auto sprite = new Sprite();

			// 根据不同类型加载不同图片
			// 1.墙
			if (piece.type == TYPE::Wall) {
				sprite->open("res/wall.gif");
			}
			// 2.得分点处的地面
			else if (piece.type == TYPE::Ground && piece.isPoint) {
				sprite->open("res/point.gif");
			}
			// 3.普通地面
			else if (piece.type == TYPE::Ground) {
				sprite->open("res/floor.gif");
			}
			// 4.得分点处的箱子
			else if (piece.type == TYPE::Box && piece.isPoint) {
				sprite->open("res/boxinpoint.gif");
			}
			// 5.普通箱子
			else if (piece.type == TYPE::Box) {
				sprite->open("res/box.gif");
			}
			// 6.正在推箱子的角色
			else if (piece.type == TYPE::Man && g_Pushing) {
				// 根据上下左右四个方向加载不同图片
				switch (g_Direct)
				{
				case 1:
					sprite->open("res/manhandup.gif");
					break;
				case 2:
					sprite->open("res/manhanddown.gif");
					break;
				case 3:
					sprite->open("res/manhandleft.gif");
					break;
				case 4:
					sprite->open("res/manhandright.gif");
					break;
				}
			}
			// 7.普通角色
			else if (piece.type == TYPE::Man) {
				switch (g_Direct)
				{
				case 1:
					sprite->open("res/manup.gif");
					break;
				case 2:
					sprite->open("res/mandown.gif");
					break;
				case 3:
					sprite->open("res/manleft.gif");
					break;
				case 4:
					sprite->open("res/manright.gif");
					break;
				}
			}
			else {
				continue;
			}
			// 设置图片位置
			sprite->setPosX(((12 - map.width) / 2 + i) * sprite->getWidth());
			sprite->setPosY(((12 - map.height) / 2 + j) * sprite->getHeight());
			// 显示这张图片
			mapLayer->addChild(sprite);
		}
	}
}

void PlayScene::SetLevel(int level)
{
	// 保存关卡等级
	::g_CurrentLevel = level;
	// 保存关卡信息到文件
	Data::saveInt("level", ::g_CurrentLevel);
	// 修改关卡信息文字
	levelText->setText("第" + String::toString(level) + "关");

	// 重置步数
	SetStep(0);
	// 获取最佳步数
	String strLevel;
	strLevel << "level" << level;
	int bestStep = Data::getInt(strLevel, 0);
	if (bestStep != 0) {
		bestText->setText("最佳" + String::toString(bestStep) + "步");
	}
	else {
		bestText->setText("");
	}
	
	// 获取关卡地图信息
	map = g_Maps[level - 1];
	// 初始化角色信息，角色方向朝下
	g_Direct = 2;
	// 角色不推箱子
	g_Pushing = false;
	// 载入地图
	Flush();
}

void PlayScene::Move(int x, int y, int direct)
{
	// 从地图中取出角色
	Piece role = map.value[map.roleY][map.roleX];
	x = x + map.roleX;
	y = y + map.roleY;
	g_Direct = direct;

	// 处理不同情况
	// 1. 前面是墙
	if (map.value[y][x].type == TYPE::Wall) {
		return;	// 什么都不做
	}
	// 2. 前面是地面
	else if (map.value[y][x].type == TYPE::Ground) {
		// 角色不在推箱子
		g_Pushing = false;
		// 将角色向前方移动一格
		map.value[map.roleY][map.roleX].type = TYPE::Ground;
		map.value[y][x].type = TYPE::Man;
		// 播放音效
		if (::g_SoundOpen) MusicManager::get("res/manmove.wav")->play();
	}
	// 3.前面是箱子
	else if (map.value[y][x].type == TYPE::Box) {
		// 角色正在推箱子
		g_Pushing = true;
		// 根据角色方向判断箱子前方是不是墙
		int boxX, boxY;
		if (g_Direct == 1) {
			boxX = x;
			boxY = y - 1;
		}
		else if (g_Direct == 2) {
			boxX = x;
			boxY = y + 1;
		}
		else if (g_Direct == 3) {
			boxX = x - 1;
			boxY = y;
		}
		else if (g_Direct == 4) {
			boxX = x + 1;
			boxY = y;
		}
		// 箱子前方是墙或者箱子就不移动
		if (map.value[boxY][boxX].type == TYPE::Wall ||
			map.value[boxY][boxX].type == TYPE::Box)
			return;
		// 箱子前方不是墙，就同时移动箱子和角色
		map.value[boxY][boxX].type = TYPE::Box;
		map.value[y][x].type = TYPE::Man;
		map.value[map.roleY][map.roleX].type = TYPE::Ground;
		// 播放音效
		if (::g_SoundOpen) MusicManager::get("res/boxmove.wav")->play();
	}
	// 重新保存角色位置
	map.roleX = x;
	map.roleY = y;
	// 步数加一
	SetStep(step + 1);
}

void PlayScene::SetStep(int step)
{
	// 保存步数
	this->step = step;
	// 修改步数文字
	stepText->setText("当前" + String::toString(step) + "步");
}

void PlayScene::GameOver()
{
	// 获取最佳步数
	String strLevel;
	strLevel << "level" << g_CurrentLevel;
	int bestStep = Data::getInt(strLevel, 0);
	// 重新保存最佳步数
	if (bestStep == 0 || step < bestStep) {
		Data::saveInt(strLevel, step);
	}
	// 若已经是最后一关，显示通关界面
	if (::g_CurrentLevel == MAX_LEVEL) {
		// 第二个参数 false 表示不会再返回当前场景
		SceneManager::enter(new SuccessScene(), false);
		return;
	}
	// 进入下一关
	SetLevel(::g_CurrentLevel + 1);
}

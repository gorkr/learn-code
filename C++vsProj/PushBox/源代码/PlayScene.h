#pragma once
#include <easy2d.h>
#include "Data.h"

class PlayScene :
	public Scene
{
public:
	PlayScene(int level);

	void GetInput();

	// 刷新画面
	void Flush();
	// 设置关卡
	void SetLevel(int level);
	// 修改当前步数
	void SetStep(int step);
	// 移动人物
	void Move(int x, int y, int direct);
	// 游戏结束
	void GameOver();

protected:
	int step;
	Map map;
	Text* levelText;
	Text* stepText;
	Text* bestText;
	Node* mapLayer;
};


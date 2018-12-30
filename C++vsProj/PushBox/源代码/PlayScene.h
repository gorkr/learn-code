#pragma once
#include <easy2d.h>
#include "Data.h"

class PlayScene :
	public Scene
{
public:
	PlayScene(int level);

	void GetInput();

	// ˢ�»���
	void Flush();
	// ���ùؿ�
	void SetLevel(int level);
	// �޸ĵ�ǰ����
	void SetStep(int step);
	// �ƶ�����
	void Move(int x, int y, int direct);
	// ��Ϸ����
	void GameOver();

protected:
	int step;
	Map map;
	Text* levelText;
	Text* stepText;
	Text* bestText;
	Node* mapLayer;
};


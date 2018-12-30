#include "PlayScene.h"
#include "SuccessScene.h"


PlayScene::PlayScene(int level)
{
	// ��������
	auto font = new Font("������", 28, Color::WHITE, FontWeight::BOLD);
	auto font2 = new Font("������", 20, Color::WHITE, FontWeight::BOLD);

	// ��ǰ�ؿ�����
	levelText = new Text("", font);
	levelText->setPos(520, 30);
	this->add(levelText);

	// ��ǰ��������
	stepText = new Text("", font2);
	stepText->setPos(520, 100);
	this->add(stepText);

	// ��Ѳ�������
	bestText = new Text("", font2);
	bestText->setPos(520, 140);
	this->add(bestText);

	// �� ESC �˳���ʾ����
	auto exitText = new Text("��ESC����", font2);
	exitText->setPos(520, 250);
	this->add(exitText);

	// ���س����¿�ʼ��ʾ����
	auto restartText = new Text("���س��ؿ�", font2);
	restartText->setPos(520, 290);
	this->add(restartText);

	// ��ӵ�ͼ����
	mapLayer = new Node();
	this->add(mapLayer);

	// ���ùؿ�
	this->SetLevel(level);

	// �����ص�����
	VoidFunction cb = CreateCallback(this, &PlayScene::GetInput);
	// ����������
	Input::add(cb);
}

void PlayScene::GetInput()
{
	// �� ESC ������һ����
	if (Input::isKeyPress(KeyCode::ESC)) {
		SceneManager::back();
	}
	// ���س����¿�ʼ
	if (Input::isKeyPress(KeyCode::ENTER)) {
		SetLevel(g_CurrentLevel);
	}

	// �����������ƶ�����
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
		// ������������
		return;
	}

	// ˢ�µ�ͼ
	Flush();

	// �ж��Ƿ�ͨ��
	for (int i = 0; i < map.width; i++) {
		for (int j = 0; j < map.height; j++) {
			Piece p = map.value[j][i];
			if (p.type == TYPE::Box && p.isPoint == false) {
				// ����δ���ڵ÷ֵ��ϵ����ӣ���δͨ��
				return;
			}
		}
	}

	// ���������Ӷ��ڵ÷ֵ��ϣ�������һ��
	GameOver();
}

void PlayScene::Flush()
{
	// ���ԭ��ͼ
	mapLayer->clearAllChildren();
	// ���ص�ͼ
	for (int i = 0; i < map.width; i++) {
		for (int j = 0; j < map.height; j++) {
			// ȡ����ͼ�е�Ԫ��
			Piece piece = map.value[j][i];
			// ��������
			auto sprite = new Sprite();

			// ���ݲ�ͬ���ͼ��ز�ͬͼƬ
			// 1.ǽ
			if (piece.type == TYPE::Wall) {
				sprite->open("res/wall.gif");
			}
			// 2.�÷ֵ㴦�ĵ���
			else if (piece.type == TYPE::Ground && piece.isPoint) {
				sprite->open("res/point.gif");
			}
			// 3.��ͨ����
			else if (piece.type == TYPE::Ground) {
				sprite->open("res/floor.gif");
			}
			// 4.�÷ֵ㴦������
			else if (piece.type == TYPE::Box && piece.isPoint) {
				sprite->open("res/boxinpoint.gif");
			}
			// 5.��ͨ����
			else if (piece.type == TYPE::Box) {
				sprite->open("res/box.gif");
			}
			// 6.���������ӵĽ�ɫ
			else if (piece.type == TYPE::Man && g_Pushing) {
				// �������������ĸ�������ز�ͬͼƬ
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
			// 7.��ͨ��ɫ
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
			// ����ͼƬλ��
			sprite->setPosX(((12 - map.width) / 2 + i) * sprite->getWidth());
			sprite->setPosY(((12 - map.height) / 2 + j) * sprite->getHeight());
			// ��ʾ����ͼƬ
			mapLayer->addChild(sprite);
		}
	}
}

void PlayScene::SetLevel(int level)
{
	// ����ؿ��ȼ�
	::g_CurrentLevel = level;
	// ����ؿ���Ϣ���ļ�
	Data::saveInt("level", ::g_CurrentLevel);
	// �޸Ĺؿ���Ϣ����
	levelText->setText("��" + String::toString(level) + "��");

	// ���ò���
	SetStep(0);
	// ��ȡ��Ѳ���
	String strLevel;
	strLevel << "level" << level;
	int bestStep = Data::getInt(strLevel, 0);
	if (bestStep != 0) {
		bestText->setText("���" + String::toString(bestStep) + "��");
	}
	else {
		bestText->setText("");
	}
	
	// ��ȡ�ؿ���ͼ��Ϣ
	map = g_Maps[level - 1];
	// ��ʼ����ɫ��Ϣ����ɫ������
	g_Direct = 2;
	// ��ɫ��������
	g_Pushing = false;
	// �����ͼ
	Flush();
}

void PlayScene::Move(int x, int y, int direct)
{
	// �ӵ�ͼ��ȡ����ɫ
	Piece role = map.value[map.roleY][map.roleX];
	x = x + map.roleX;
	y = y + map.roleY;
	g_Direct = direct;

	// ����ͬ���
	// 1. ǰ����ǽ
	if (map.value[y][x].type == TYPE::Wall) {
		return;	// ʲô������
	}
	// 2. ǰ���ǵ���
	else if (map.value[y][x].type == TYPE::Ground) {
		// ��ɫ����������
		g_Pushing = false;
		// ����ɫ��ǰ���ƶ�һ��
		map.value[map.roleY][map.roleX].type = TYPE::Ground;
		map.value[y][x].type = TYPE::Man;
		// ������Ч
		if (::g_SoundOpen) MusicManager::get("res/manmove.wav")->play();
	}
	// 3.ǰ��������
	else if (map.value[y][x].type == TYPE::Box) {
		// ��ɫ����������
		g_Pushing = true;
		// ���ݽ�ɫ�����ж�����ǰ���ǲ���ǽ
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
		// ����ǰ����ǽ�������ӾͲ��ƶ�
		if (map.value[boxY][boxX].type == TYPE::Wall ||
			map.value[boxY][boxX].type == TYPE::Box)
			return;
		// ����ǰ������ǽ����ͬʱ�ƶ����Ӻͽ�ɫ
		map.value[boxY][boxX].type = TYPE::Box;
		map.value[y][x].type = TYPE::Man;
		map.value[map.roleY][map.roleX].type = TYPE::Ground;
		// ������Ч
		if (::g_SoundOpen) MusicManager::get("res/boxmove.wav")->play();
	}
	// ���±����ɫλ��
	map.roleX = x;
	map.roleY = y;
	// ������һ
	SetStep(step + 1);
}

void PlayScene::SetStep(int step)
{
	// ���沽��
	this->step = step;
	// �޸Ĳ�������
	stepText->setText("��ǰ" + String::toString(step) + "��");
}

void PlayScene::GameOver()
{
	// ��ȡ��Ѳ���
	String strLevel;
	strLevel << "level" << g_CurrentLevel;
	int bestStep = Data::getInt(strLevel, 0);
	// ���±�����Ѳ���
	if (bestStep == 0 || step < bestStep) {
		Data::saveInt(strLevel, step);
	}
	// ���Ѿ������һ�أ���ʾͨ�ؽ���
	if (::g_CurrentLevel == MAX_LEVEL) {
		// �ڶ������� false ��ʾ�����ٷ��ص�ǰ����
		SceneManager::enter(new SuccessScene(), false);
		return;
	}
	// ������һ��
	SetLevel(::g_CurrentLevel + 1);
}

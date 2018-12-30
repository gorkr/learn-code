#pragma once

#define MAX_LEVEL 8

/* ��Ϸ�����ݽṹ */
// ��ͼԪ�����ͣ�TYPE������5�֣��ֱ����ˡ�ǽ�����桢���ӡ���
// ��ͼ�飨Piece���ṹ���� ����TYPE �������������
// ��ͼ��Map���ṹ���ɿ�ȸ߶ȡ���ɫ��ʼ���ꡢ�� Piece���� ���


// ��ͼԪ������
// Empty	��
// Wall		ǽ
// Ground	����
// Box		����
// Man		��
enum TYPE { Empty, Wall, Ground, Box, Man };

// ��ͼ��
struct Piece
{
	// ����
	TYPE type;

	// �������ƶ����������ʱ��isPoint��ʾ�õ��Ƿ��ǵ÷ֵ�
	bool isPoint;
};

// ��ͼ
struct Map
{
	// ��ͼ���
	int width;
	int height;
	// ��ɫ�ڵ�ͼ�е�λ��
	int roleX;
	int roleY;
	// ��ͼ
	Piece value[12][12];
};

// �����Ÿ��ؿ�
extern Map g_Maps[MAX_LEVEL];
// ��ǰ�ؿ�
extern int g_CurrentLevel;
// �����Ƿ��
extern bool g_SoundOpen;
// ���﷽��1234 �ֱ���� ��������
extern int g_Direct;
// ���Ƿ�����������
extern bool g_Pushing;
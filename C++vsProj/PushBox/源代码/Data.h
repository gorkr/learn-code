#pragma once

#define MAX_LEVEL 8

/* 游戏的数据结构 */
// 地图元素类型（TYPE）共有5种，分别是人、墙、地面、箱子、空
// 地图块（Piece）结构体由 属性TYPE 和其他属性组成
// 地图（Map）结构体由宽度高度、角色起始坐标、和 Piece数组 组成


// 地图元素类型
// Empty	空
// Wall		墙
// Ground	地面
// Box		箱子
// Man		人
enum TYPE { Empty, Wall, Ground, Box, Man };

// 地图块
struct Piece
{
	// 类型
	TYPE type;

	// 当箱子移动到这个块上时，isPoint表示该点是否是得分点
	bool isPoint;
};

// 地图
struct Map
{
	// 地图宽高
	int width;
	int height;
	// 角色在地图中的位置
	int roleX;
	int roleY;
	// 地图
	Piece value[12][12];
};

// 声明九个关卡
extern Map g_Maps[MAX_LEVEL];
// 当前关卡
extern int g_CurrentLevel;
// 声音是否打开
extern bool g_SoundOpen;
// 人物方向，1234 分别代表 上下左右
extern int g_Direct;
// 人是否正在推箱子
extern bool g_Pushing;
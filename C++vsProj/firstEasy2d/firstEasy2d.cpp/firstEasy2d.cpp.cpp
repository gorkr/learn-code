// firstEasy2d.cpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <easy2d.h>

int main()
{
	// 初始化游戏，可以指定窗口的名称、宽高等属性
	if (Game::init("Hello", 240, 100))
	{
		// 创建一个场景
		auto scene = new Scene();
		// 进入该场景
		SceneManager::enter(scene);
		// 创建一个文本
		auto text = new Text("Hello Easy2D!");
		// 将这个文本添加到场景中
		scene->add(text);
		// 开始游戏
		Game::run();
	}
	// 游戏结束，回收游戏资源
	Game::uninit();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

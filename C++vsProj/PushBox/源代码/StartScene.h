#include <easy2d.h>

class StartScene : 
	public Scene
{
public:
	StartScene();

	// ��������ڽ��볡��ʱ�Զ�ִ��
	void onEnter() override;

	// ����Ϸ
	void Start();
	// ������Ϸ
	void Continue();
	// �˳���Ϸ
	void Exit();

	// �򿪻�ر�����
	void Sound();

protected:
	// ��������
	ButtonToggle* soundBtn;
	// ������Ϸ��ť
	Button* resumeBtn;
};
#pragma once
#include "IAction.h"
#include <stack>
using namespace std;
class CActionManager
{
public:
	void undo();
	void redo();
	void InsertAction(IAction* pAction);
private:
	//�������������ݽṹ
	stack<IAction*>  m_stkToUndo;  //�ȴ�������
	stack<IAction*> m_stkToRedo;  //�ȴ�������

};


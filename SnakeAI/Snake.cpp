#include "pch.h"
#include "Snake.h"
#include "resource.h"
Snake::Snake()
{
	InitializeCriticalSection(&m_cs);
	EnterCriticalSection(&m_cs);
}

Snake::~Snake()
{
	LeaveCriticalSection(&m_cs);
	DeleteCriticalSection(&m_cs);
}

Snake::Snake(RECT rc, POINT po, SPEED sp)
{
	//�ٽ���
	InitializeCriticalSection(&m_cs);
	EnterCriticalSection(&m_cs);
	
	//���洫�����ֵ��˽�б���
	m_rc = rc;
	m_po = po;
	m_sp = sp;

	//int cx = m_rc.right - m_rc.left;
	//int cy = m_rc.bottom - m_rc.top;
	//if (cx < po.x || cy < po.y || cx % po.x != 0 || cy % po.y != 0)
	//{
	//	//�Ϸ��Լ��,����һ��Ĭ�ϵĶ���
	//	//....�˴���Ҫ�Ժ���ȷ��.
	//}

	//��ʼ��С��(ӵ�а���ͷ���ڵ�����ڵ�)
	for (auto i = m_rc.left; i < m_rc.left + m_po.x * 5; i += m_po.x)
	{
		SnakeNode node;
		node.rc.left = i;
		node.rc.top = m_rc.top;
		node.rc.right = i + m_po.x;
		node.rc.bottom = m_rc.top + m_po.y;
		node.curDire = DR_RIGHT;
		m_snake.push_back(node);
	}
}

bool Snake::SMove(DIRE dr, RECT food)
{
	//��Ҫ��Ϊ�������
	//--�Ե�ʳ����.
	//--û�Ե�ʳ��.

	SnakeNode shead = m_snake.back();//��ǰ��ͷ.

	//����ƶ�����͵�ǰ�����෴
	if ((dr == DR_UP && shead.curDire == DR_DOWN) ||
		(dr == DR_DOWN && shead.curDire == DR_UP) ||
		(dr == DR_LEFT && shead.curDire == DR_RIGHT) ||
		(dr == DR_RIGHT && shead.curDire == DR_LEFT))
		dr = shead.curDire;

	//Ȼ���ɵ�ǰ��ͷ���ֺ��ƶ�����������һ����ͷ����
	
	switch (dr)
	{
	case DR_LEFT:
		shead.rc.right = shead.rc.left;
		shead.rc.left -= m_po.x;
		break;
	case DR_RIGHT:
		shead.rc.left = shead.rc.right;
		shead.rc.right += m_po.x;
		break;
	case DR_UP:
		shead.rc.bottom = shead.rc.top;
		shead.rc.top -= m_po.y;
		break;
	case DR_DOWN:
		shead.rc.top = shead.rc.bottom;
		shead.rc.bottom += m_po.y;
		break;
	}
	shead.curDire = dr;
	m_snake.push_back(shead);


	if ((shead.rc.left == food.left )&& (shead.rc.top == food.top))
	{
	
		return true;
	}
	else
	{
		//ɾ��ͷ�ڵ�
		if (m_snake.size() == 0)
		{
			AfxMessageBox("ZERO!");
		}
		m_snake.pop_front();
		return false;
	}
	//return false;
}

bool Snake::GameOver()
{
	//��ͷ..
	//�����ͷ�ƶ�����һ��λ������Ϸ����֮�⣬���ж���Ϸ����
	SnakeNode shead = m_snake.back();
	if ((shead.rc.right - m_po.x + 10 <= m_rc.left && shead.curDire == DR_LEFT) ||
		(shead.rc.right + m_po.x >= m_rc.right && shead.curDire == DR_RIGHT) ||
		(shead.rc.top + m_po.y <= m_rc.top && shead.curDire == DR_UP) ||
		(shead.rc.bottom + m_po.y >= m_rc.bottom && shead.curDire == DR_DOWN))

	{



		return TRUE;
	}
	//�����ͷ�������Լ������壬���ж���Ϸ����
	list<SnakeNode>::iterator sIter = m_snake.begin();
	for (unsigned int i = 0; i < m_snake.size() - 1; i++, sIter++)
	{
		if (shead.rc.left == sIter->rc.left && shead.rc.top == sIter->rc.top)
		//if (shead.rc.right <= sIter->rc.left && shead.rc.top <= sIter->rc.top)
			
			
			return true;
	}
	//��������ĸ�������û���㣬�ͷ���FALSE
	//��Ϸ����
	return FALSE;
}
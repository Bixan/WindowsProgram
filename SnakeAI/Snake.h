#pragma once
//Snake.h
//̰���ߵ����ݽṹ�Լ�����������.

#include <Windows.h>
#include <ctime>
#include <list>
using std::list;

//��ض���
//--�����
#define DR_UP	 0
#define DR_DOWN	 1
#define DR_LEFT	 2
#define DR_RIGHT 3
typedef INT DIRE;	//��������

//--�ٶȺ�
#define SP_SLOW		1
#define SP_NORMAL	2
#define SP_FAST		3
#define SP_HIGN		4
typedef INT SPEED;	//�ٶ�����


//����ڵ�ṹ��,���εı�����ʾ���Ǹýڵ����ڵľ�������.
struct SnakeNode
{
	RECT rc;
	DIRE curDire;	//��Ǹýڵ㵱ǰ�ķ���
};

class Snake
{
public:
	Snake();
	~Snake();
	Snake(RECT rc, POINT po, SPEED sp);//���캯��:(��ͼ����,�ڵ��Ĵ�С,�ƶ��ٶ�)
	bool SMove(DIRE dr, RECT food);//�����ƶ�һ��:(����,ʳ���λ��)����ֵΪ�Ƿ�Ե�ʳ��.
	bool GameOver();//�ж���Ϸ�Ƿ����:

	list<SnakeNode> m_snake;//������.
	//��ͷΪlist�е����һ��Ԫ��.
	RECT m_rc;		//��ͼ����
	POINT m_po;		//�ߵĽڵ���С
	SPEED m_sp;		//�ߵ��ƶ��ٶ�
	CRITICAL_SECTION m_cs;
};


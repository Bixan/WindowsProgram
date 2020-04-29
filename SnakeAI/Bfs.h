#pragma once
//Bfs.h
//̰���߻���Ѱ·�㷨.

#ifndef BFS_H_H
#define BFS_H_H

#include <queue>
using std::queue;

struct XY
{
	int x;
	int y;
};

class Bfs
{
public:
	Bfs();									//��ʼ����ͼ��С								
	~Bfs();
	void InitBfs(bool** chess, XY size);	//��ʼ����ͼ�����ֵ.
	bool CalcBfs(XY st, XY en);				//����Bfs·��.
	void EetBfs(XY st, XY en);				//�õ�Bfs·��.
	void CalcQue(XY en);					//�������
	queue<XY> m_que;
private:
	bool** m_chess;		//�þ����ʾ��ͼ.
	bool** m_visit;		//�ڵ��Ƿ񱻷��ʹ�.
	XY** m_parent;		//ÿ�����ʹ��Ľڵ�ĸ��ڵ�.
	XY m_size;			//ͼ�Ĵ�С.
	CRITICAL_SECTION m_cs;
};

#endif //BFS_H_H

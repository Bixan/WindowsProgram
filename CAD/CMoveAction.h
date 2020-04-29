#pragma once
#include <afxwin.h>
#include "IShape.h"
#include "IAction.h"
class CMoveAction :public IAction
{
public:
    CMoveAction();
    CMoveAction(IShape * pShape,CPoint ptnew,CPoint ptold );
    ~CMoveAction();
    virtual void redo() override;
    virtual void undo() override;
private:
    CPoint m_ptOld;   //�ƶ��������
    CPoint m_ptNew;   //�ƶ�ǰ������
    IShape* m_pMoveShape; //�ƶ���ͼ��
};


#pragma once
#include "framework.h"
class IShape:public CObject
{
  
public:
    IShape();
    //����һ����ͼ��OnDraw���麯�����࣬���������ʵ�ֽ��������ͼ��ȥ���
    //��ֵ�������C++�Ķ�̬����װ���̳�
    //д�麯���ĵط�
    virtual void OnDraw(CDC* pDC) = 0;
    virtual BOOL IsSelect(CPoint pt) = 0;
    virtual void OnSelectDraw(CDC* pDC) = 0;
            

private:
    //����ͼ�ε���������㣬��갴�º͵��������
    CPoint m_ptBegin;
    CPoint m_ptEnd;
    //���ʵı���
    int m_nPenStyle;
    int m_nPenWith;
    COLORREF m_clrPenColor;

    //��ˢ�ı���
    int			m_nBrushStyle;
    int			m_nShadowStyle;
    COLORREF	m_varBrushColor;


public:
    //������Get��Set����
    void    SetBeginPt(CPoint point);
    CPoint  GetBeginPt() const;
    void    SetEndPt(CPoint point);
    CPoint  GetEndPt() const;

    /*��ͼ�λ�����ӹ��ڻ��ʵ����ݳ�Ա����ÿ��������ͼ���Լ�ѡ�������Լ��Ļ���ȥ��ͼ*/
    int GetPenStyle() const { return m_nPenStyle; }
    void SetPenStyle(int val) { m_nPenStyle = val; }
    int GetPenWith() const { return m_nPenWith; }
    void SetPenWith(int val) { m_nPenWith = val; }
    COLORREF GetClrPenColor() const { return m_clrPenColor; }
    void SetClrPenColor(COLORREF val) { m_clrPenColor = val; }

    int GetBrushStyle() const { return m_nBrushStyle; }
    void SetBrushStyle(int val) { m_nBrushStyle = val; }
    int GetShadowStyle() const { return m_nShadowStyle; }
    void SetShadowStyle(int val) { m_nShadowStyle = val; }
    COLORREF GetClrBrushColor() const { return m_varBrushColor; }
    void SetClrBrushColor(COLORREF val) { m_varBrushColor = val; }

    virtual void Serialize(CArchive& ar);
};

class IShapeFactory
{
public:

    virtual IShape* CreateIShape() = 0;
};





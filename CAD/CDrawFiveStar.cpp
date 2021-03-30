#include "pch.h"
#include "CDrawFiveStar.h"
IMPLEMENT_SERIAL(CDrawFiveStar, CObject, 1)
CDrawFiveStar::CDrawFiveStar()
{

}

void CDrawFiveStar::OnDraw(CDC* pDC)
{


    CPen ShapePen;
    ShapePen.CreatePen(GetPenStyle(), GetPenWith(), GetClrPenColor());
    pDC->SelectObject(&ShapePen);

    CBrush  ShapeBrush;
    LOGBRUSH   lbBrushStyle;
    lbBrushStyle.lbColor = GetClrBrushColor();
    lbBrushStyle.lbHatch = GetShadowStyle();
    lbBrushStyle.lbStyle = GetBrushStyle();
    ShapeBrush.CreateBrushIndirect(&lbBrushStyle);
    pDC->SelectObject(&ShapeBrush);

    FiveStar(pDC);
}

BOOL CDrawFiveStar::IsSelect(CPoint pt)
{


    //�߳�
    double dblPentagramSide = sqrt(((double)GetEndPt().x - (double)GetBeginPt().x) *
    ((double)GetEndPt().x - (double)GetBeginPt().x) + ((double)GetEndPt().y - (double)GetBeginPt().y) *
    ((double)GetEndPt().y - (double)GetBeginPt().y));

    //A->B
    //pDC->MoveTo(GetBeginPt());
    //pDC->LineTo(GetEndPt());

    //B->C
    CPoint C;//C��
    double dblABRadian = 0;//AB��ˮƽ�߼нǵĻ���
    double dblBCRadian = 0;//BC��ˮƽ�߼нǵĻ���

    //����AB����
    if ((GetEndPt().x - GetBeginPt().x) > 0)
    {
        if ((GetEndPt().y - GetBeginPt().y) > 0)
        {
            dblABRadian = atan(((double)GetEndPt().y - (double)GetBeginPt().y) / ((double)GetEndPt().x - (double)GetBeginPt().x));
        }
        else
        {
            dblABRadian = atan(((double)GetEndPt().y - (double)GetBeginPt().y) / ((double)GetEndPt().x - (double)GetBeginPt().x)) + ANGLE_TO_RADIAN(360);
        }
    }
    else if ((GetEndPt().x - GetBeginPt().x) < 0)
    {
        dblABRadian = atan(((double)GetEndPt().y - (double)GetBeginPt().y) / ((double)GetEndPt().x - (double)GetBeginPt().x)) + ANGLE_TO_RADIAN(180);
    }
    else
    {
        if ((GetEndPt().y - GetBeginPt().y) > 0)
        {
            dblABRadian = ANGLE_TO_RADIAN(90);
        }
        else
        {
            dblABRadian = ANGLE_TO_RADIAN(270);
        }
    }

    //����BC����
    dblBCRadian = (dblABRadian + ANGLE_TO_RADIAN(144));
    //����C������
    C.x = (double)GetEndPt().x + cos(dblBCRadian) * dblPentagramSide;
    C.y = (double)GetEndPt().y + sin(dblBCRadian) * dblPentagramSide;

    //��BC
   /* pDC->LineTo(C);*/

    //C->D
    CPoint D;//D��
    double dblCDRadian = 0;//CD��ˮƽ�߼нǵĻ���

    //����CD����
    dblCDRadian = (dblBCRadian + ANGLE_TO_RADIAN(144));

    //����D������
    D.x = (double)C.x + cos(dblCDRadian) * dblPentagramSide;
    D.y = (double)C.y + sin(dblCDRadian) * dblPentagramSide;

    //��CD
   /* pDC->LineTo(D);*/

    //D->E
    CPoint E;   //E��
    double dblDERadian = 0;//DE��ˮƽ�߼нǵĻ���

    //����DE����
    dblDERadian = (dblCDRadian + ANGLE_TO_RADIAN(144));

    //����E������
    E.x = (double)D.x + cos(dblDERadian) * dblPentagramSide;
    E.y = (double)D.y + sin(dblDERadian) * dblPentagramSide;

    //��DE
  /*  pDC->LineTo(E);*/

    //��EA
  /*  pDC->LineTo(GetBeginPt());*/
    CPoint pts[5];
    pts[0] = GetEndPt();
    pts[1] = C;
    pts[2] = D;
    pts[3] = E;
    pts[4] = GetBeginPt();

   // pDC->Polygon(pts, 5);
    CRgn   rgnStar;


    rgnStar.CreatePolygonRgn(pts, 5, WINDING);
   
    return rgnStar.PtInRegion(pt);

}

void CDrawFiveStar::OnSelectDraw(CDC* pDC)
{

    CPen pen;
    pen.CreatePen(GetPenStyle(), GetPenWith() + 5, GetClrPenColor());
    CPen* cOldpen = pDC->SelectObject(&pen);

    FiveStar(pDC);
    pDC->SelectObject(cOldpen);
}

void CDrawFiveStar::FiveStar(CDC* pDC)
{

  pDC->SetPolyFillMode(WINDING);
    //�߳�
    double dblPentagramSide = sqrt(((double)GetEndPt().x - (double)GetBeginPt().x) *
    ((double)GetEndPt().x - (double)GetBeginPt().x) + ((double)GetEndPt().y - (double)GetBeginPt().y) *
    ((double)GetEndPt().y - (double)GetBeginPt().y));

    //A->B
    //pDC->MoveTo(GetBeginPt());
    //pDC->LineTo(GetEndPt());

    //B->C
    CPoint C;//C��
    double dblABRadian = 0;//AB��ˮƽ�߼нǵĻ���
    double dblBCRadian = 0;//BC��ˮƽ�߼нǵĻ���

    //����AB����
    if ((GetEndPt().x - GetBeginPt().x) > 0)
    {
        if ((GetEndPt().y - GetBeginPt().y) > 0)
        {
            dblABRadian = atan(((double)GetEndPt().y - (double)GetBeginPt().y) / ((double)GetEndPt().x - (double)GetBeginPt().x));
        }
        else
        {
            dblABRadian = atan(((double)GetEndPt().y - (double)GetBeginPt().y) / ((double)GetEndPt().x - (double)GetBeginPt().x)) + ANGLE_TO_RADIAN(360);
        }
    }
    else if ((GetEndPt().x - GetBeginPt().x) < 0)
    {
        dblABRadian = atan(((double)GetEndPt().y - (double)GetBeginPt().y) / ((double)GetEndPt().x - (double)GetBeginPt().x)) + ANGLE_TO_RADIAN(180);
    }
    else
    {
        if ((GetEndPt().y - GetBeginPt().y) > 0)
        {
            dblABRadian = ANGLE_TO_RADIAN(90);
        }
        else
        {
            dblABRadian = ANGLE_TO_RADIAN(270);
        }
    }

    //����BC����
    dblBCRadian = (dblABRadian + ANGLE_TO_RADIAN(144));
    //����C������
    C.x = (double)GetEndPt().x + cos(dblBCRadian) * dblPentagramSide;
    C.y = (double)GetEndPt().y + sin(dblBCRadian) * dblPentagramSide;

    //��BC
   /* pDC->LineTo(C);*/

    //C->D
    CPoint D;//D��
    double dblCDRadian = 0;//CD��ˮƽ�߼нǵĻ���

    //����CD����
    dblCDRadian = (dblBCRadian + ANGLE_TO_RADIAN(144));

    //����D������
    D.x = (double)C.x + cos(dblCDRadian) * dblPentagramSide;
    D.y = (double)C.y + sin(dblCDRadian) * dblPentagramSide;

    //��CD
   /* pDC->LineTo(D);*/

    //D->E
    CPoint E;   //E��
    double dblDERadian = 0;//DE��ˮƽ�߼нǵĻ���

    //����DE����
    dblDERadian = (dblCDRadian + ANGLE_TO_RADIAN(144));

    //����E������
    E.x = (double)D.x + cos(dblDERadian) * dblPentagramSide;
    E.y = (double)D.y + sin(dblDERadian) * dblPentagramSide;

    //��DE
  /*  pDC->LineTo(E);*/

    //��EA
  /*  pDC->LineTo(GetBeginPt());*/
    CPoint pts[5];
    pts[0] = GetEndPt();
    pts[1] = C;
    pts[2] = D;
    pts[3] = E;
    pts[4] = GetBeginPt();
    
    pDC->Polygon(pts, 5);
}

IShape* CDrawFiveStarFactory::CreateIShape()
{
    return new CDrawFiveStar;
}


void CDrawFiveStar::Serialize(CArchive& ar)
{
    IShape::Serialize(ar);
}

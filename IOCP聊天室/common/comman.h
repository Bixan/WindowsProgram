#pragma once
enum DataType
{
    DT_LOGIN,           //��¼��
    DT_LOGIN_OK,        //��½�ɹ�
    DT_LOGINOUT,        //�˳�
    DT_MSG,             //�������ݰ�
    DT_HEART            //������
};
typedef struct tagPackageHeader
{
    int m_nDataLen;  //���ݵĳ���
    int m_nDataType; //���ݵ�����
}PACKAGEHEADER,*PPACKAGEHEADER ;
#pragma once
enum DataType
{
    DT_LOGIN,           //��¼��
    DT_LOGIN_OK,        //��½�ɹ�
    DT_LOGINOUT,        //�˳�
    DT_MSG,             //�������ݰ�
    DT_HEART,            //������
    DT_FLUSH_NAME,       //��������б������
    DT_ADD_NAME,        //��������б�����
    DT_DEL_NAME         //ɾ���б�����
};
typedef struct tagPackageHeader
{
    int m_nDataLen;  //���ݵĳ���
    int m_nDataType; //���ݵ�����
}PACKAGEHEADER,*PPACKAGEHEADER ;
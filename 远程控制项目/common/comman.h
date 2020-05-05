#pragma once
enum DataType
{
    DT_LOGIN,                  //��¼��
    DT_LOGIN_OK,               //��½�ɹ�
    DT_LOGINOUT,               //�˳�
    DT_MSG,                    //�������ݰ�
    DT_HEART,                  //������
    DT_GETDRIVERS,               //��ȡ�̷�
    DT_DRIVERS,                  //�����̷�
    DT_GETDIR,                   //��ȡĿ¼
    DT_DIR,                      //����Ŀ¼
    DT_GETCMD,                   //��ȡcmd��������
    DT_CMD,                      //����cmd���� 
    DT_GETPROCESS,               //��ȡ�����б�
    DT_PROCESS,                  //���ؽ����б�
    DT_GETTHREAD,                //��ȡ�߳�list
    DT_THREAD,                   //�����߳�list
    DT_TERPROCESS,               //��������
    DT_GETREG_ROOT,              //��ȡע���HKEY_CLASSES_ROOT����   
    DT_GETREG_CUR_USER,          //��ȡע���HKEY_CURRENT_USER���� 
    DT_GETREG_LOC_MACH,          //��ȡע���HKEY_LOCAL_MACHINE���� 
    DT_GETREG_USERS,             //��ȡע���HKEY_USERS���� 
    DT_GETREG_CUR_CONFIG,        //��ȡע���HKEY_CURRENT_CONFIG���� 
    DT_REG,                      //����ע����б�
    DT_GETITEM,                  //��ȡע����������
    DT_ITEM,                     //����ע����������

};
typedef struct tagPackageHeader
{
    int m_nDataLen;  //���ݵĳ���
    int m_nDataType; //���ݵ�����
}PACKAGEHEADER,*PPACKAGEHEADER ;

typedef struct Status
{
    BOOL  m_bIsExit = FALSE;
    int   m_nIndex;

}STATUS, * PSTATUS;
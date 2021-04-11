#pragma once
#include "InitSocket.h"
class UdpSocket
{
public:
    UdpSocket();
    ~UdpSocket();
public:
    SOCKET   CreateSocketUDP();
   BOOL   CloseSocketUDP();
   BOOL   BindUDP(const char* pIp ,u_short uPort);

public:
    SOCKET  _SokcetUDP = INVALID_SOCKET;



public:
    //��������Ĵ�����

};



//����־
enum ChatCommand
{
    C2S_LOGIN,      //����            �ͻ��˵ķ�������
    C2S_LOGOUT,     //����
    C2S_GROUP,      //Ⱥ�İ�
    C2S_PRIVATE,    //˽�İ�

    S2C_LOGIN,      //����            ����˵ķ�������  
    S2C_LOGOUT,     //����
    S2C_GROUP,      //Ⱥ�İ�
    S2C_PRIVATE,    //˽�İ�
};

//�û�����Ϣ
#define NICKLEN 128
typedef struct tagUserInfo
{
    WORD    _wPort;             //�û��Ķ˿ں�
    DWORD   _dwIp;              //�û���ip��ַ
    char    _szNick[NICKLEN];   //�û�������
}USERINFO, * PUSERINFO;

#define MSGLEN 256
typedef struct tagPackage
{
    ChatCommand     _nCommand;              //��������
    USERINFO        _ClientSend;                //������Ϣ�Ŀͻ���
    USERINFO        _uiTo;                  //˽���н�����Ϣ�Ŀͻ���
    char            _szMsg[MSGLEN];         //���͵���Ϣ
}PACKAGE, * PPACKAGE;


bool SentTo(SOCKET sock, USERINFO& ui, PACKAGE& pkg);

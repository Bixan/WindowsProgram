#pragma once

#include <WinSock2.h>

#include <windows.h>
#include <Mswsock.h>

#pragma comment(lib, "Mswsock.lib")
#include "CByteStreamBuff.h"
#include "Lock.h"
class CIocpSocket
{
public:
    enum IOCP_EVENT
    {
        IO_ACCEPT,
        IO_RECV,
        IO_SEND

    };
    struct SocketInfo
    {
        SOCKET     m_socket; //IOCP��ͻ��˹�����socket
        CByteStreamBuff  m_RecvBuffer; //��ȡ���ݵĻ����� ��iocp�����ݵĻ�����
        CByteStreamBuff  m_SendBuffer;//д�����ݵĻ����� ��iocp�����ݵĻ�����
        CLock m_locSend;
        CLock m_locRecv;
        SocketInfo(SOCKET sock) :m_socket(sock)
        {

        }
    };
    struct  MYOVERLAPPED
    {
        OVERLAPPED m_Overlapped; //��Ϊÿ��ͨ����OVERLAPPED����������ṹ����
        
        WSABUF m_wsaBuffRecv; //�����ݵĻ�����
        WSABUF m_wsaBuffSend;//�����ݵĻ�����
        DWORD m_ioEvent; //ö����ÿ�˲��������ͣ��������ӣ������ݣ�������
        char m_SendBuffTmp[MAXWORD];//�����ݵ���ʱ������
        SocketInfo* m_pSocketInfo;
        MYOVERLAPPED(SocketInfo* pSocketInfo, DWORD ioEvent)//����
            :m_pSocketInfo(pSocketInfo), m_ioEvent(ioEvent)
        {
            //OVERLAPPEDҪ���
            memset(&m_Overlapped, 0, sizeof(m_Overlapped));
            m_wsaBuffSend.buf = NULL;
            m_wsaBuffSend.len = 0;
        }
        ~MYOVERLAPPED()
        {
            if (m_wsaBuffSend.buf != NULL)
            {
                delete m_wsaBuffSend.buf;
            }
        }

    };
public:
    CIocpSocket();
    ~CIocpSocket();

    //����IOCP
    BOOL CreateIocp(char* szIp, u_short nProt);
    //��������
    BOOL PostAccept();
    //��������
    BOOL PostRecv(SocketInfo* pSocketInfo);
    //��������
    BOOL PostSend(SocketInfo* pSocketInfo);
    //�ȴ��¼�
    int WaitForEvent(SocketInfo*& pSocketInfo);
private:
    HANDLE m_hIocp;
    SOCKET m_sockServer;

};


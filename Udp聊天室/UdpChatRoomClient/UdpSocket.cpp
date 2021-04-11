
#include "pch.h"
#include "UdpSocket.h"
UdpSocket::UdpSocket()
{
    
}

UdpSocket::~UdpSocket()
{
   
}

SOCKET UdpSocket::CreateSocketUDP()
{
    //����һ��socket���
    _SokcetUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    return _SokcetUDP;
}

BOOL UdpSocket::CloseSocketUDP()
{
    //�ر�socket���
    if (_SokcetUDP)
    {
        closesocket(_SokcetUDP);
        _SokcetUDP = INVALID_SOCKET;
        return TRUE;
    }

    return FALSE;
}

BOOL UdpSocket::BindUDP(const char* pIp ,u_short uPort)
{

    sockaddr_in  si = { 0 };
    si.sin_family = AF_INET;
    si.sin_port = htons(uPort);
    si.sin_addr.S_un.S_addr = inet_addr(pIp);
    //�󶨶˿ں�ip
    int nRet = bind(_SokcetUDP, (sockaddr*)&si, sizeof(si));

    if (SOCKET_ERROR == nRet)
    {
        return FALSE;
    }
    return TRUE;
}



  
bool SentTo(SOCKET sock, USERINFO& ui, PACKAGE& pkg)
{
    sockaddr_in si = { 0 };
    si.sin_family = AF_INET;
    si.sin_port = ui._wPort;
    si.sin_addr.S_un.S_addr = ui._dwIp;
    int nRet = sendto(sock, (char*)&pkg, sizeof(pkg), 0, (sockaddr*)&si, sizeof(si));
    if (nRet == 0 || nRet == SOCKET_ERROR)
    {
        return false;
    }

    return true;
    
}

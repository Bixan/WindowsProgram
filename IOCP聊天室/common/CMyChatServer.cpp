#include "CMyChatServer.h"

BOOL CMyChatServer::CreateServer(char* szIp, u_short nPort)
{

    BOOL bRet = m_iocpSocket.CreateIocp(szIp, nPort);
    if (!bRet)
    {
        printf("socket ����ʧ��, ������!");
        return FALSE;
    }

    m_iocpSocket.PostAccept();
    return TRUE;
}

BOOL CMyChatServer::RunServer()
{
    //�������Կͻ��˵�����
    while (TRUE)
    {
        //�ȴ�iocp����������
        CIOCPSocket::SocketInfo* pSocketInfo = NULL;
        int nRetIoEvent = m_iocpSocket.WaitForIoEvent(pSocketInfo);

        //��Բ�ͬ������������
        switch (nRetIoEvent)
        {
        case CIOCPSocket::IO_RECV:
            HandleClientData(pSocketInfo);
        default:
            break;
        }

    }
    return TRUE;
}
DWORD CMyChatServer::HandleClientData(CIOCPSocket::SocketInfo* pSocketInfo)
{
    //�������ݰ�
    DATAPACKAGE pkgRecv;
    BOOL bRet = RecvPackage(pSocketInfo, &pkgRecv);
    if (!bRet)
    {
        //���ݰ�������, ��������
        return 0;
    }

    //�ж����ݵ�����
    switch (pkgRecv.m_hdr.m_nDataType)
    {


    case DT_LOGIN:	//�����¼
    {
        //�����¿ͻ��˵�����
         m_lstClients.push_back(new ClinentInfo(pSocketInfo));
        //��ͻ��˷��͵�¼���
         DATAPACKAGE package;
         package.m_hdr.m_nDataType = DT_FLUSH_NAME;
         package.m_hdr.m_nDataLen = 0;
         package.m_pBuff = NULL;
       
        for (auto ci : m_lstClients)
        {
            BOOL bRet = SendPackage(ci->m_pSocketInfo, &package);
           
        }
       

        break;
    }
    case DT_ADD_NAME:
    {
        for (auto ci : m_lstClients)
        {
            BOOL bRet = SendPackage(ci->m_pSocketInfo, &pkgRecv);
        }
        break;
    }
    case DT_DEL_NAME:
    {
        for (auto ci : m_lstClients)
        {
            BOOL bRet = SendPackage(ci->m_pSocketInfo, &pkgRecv);
        }
        break;
    }
    case DT_MSG:	//����������Ϣ
    {
        //�ж���Ⱥ������˽��
        neb::CJsonObject json;
        json.Parse(pkgRecv.m_pBuff);

        string strType;
        json.Get("type", strType);
        pkgRecv.m_hdr.m_nDataType = DT_MSG;
        if (strType == "public")//Ⱥ��
        {
            //����Ϣת���������ͻ���
            for (auto ci : m_lstClients)
            {
              
                BOOL bRet = SendPackage(ci->m_pSocketInfo, &pkgRecv);
            }
        }
        else if (strType == "private") //˽�� 
        {
          
            //����Ϣת���������ͻ���
            for (auto ci : m_lstClients)
            {
                BOOL bRet = SendPackage(ci->m_pSocketInfo, &pkgRecv);
            }
        }

        break;
    }

   
    case DT_LOGINOUT: //��������
    {
        //ɾ�����ߵĿͻ���
        for (auto itr = m_lstClients.begin(); itr != m_lstClients.end(); ++itr)
        {
            if ((*itr)->m_pSocketInfo->m_sock == pSocketInfo->m_sock)
            {
                m_lstClients.erase(itr);
                delete pSocketInfo;
                return 0;
            }
        }

        break;
    }
    }

    //ɾ��������
    if (pkgRecv.m_pBuff != NULL)
    {
        delete[] pkgRecv.m_pBuff;
        pkgRecv.m_pBuff = NULL;
    }
}
BOOL CMyChatServer::RecvPackage(CIOCPSocket::SocketInfo* pSocketInfo, DATAPACKAGE* pPackage)
{
    //�жϻ������е������Ƿ�һ��������
    pSocketInfo->m_lockRecv.Lock();
    if (pSocketInfo->m_buffRecv.GetSize() >= sizeof(PACKAGEHEADER))
    {
        pSocketInfo->m_buffRecv.Peek((char*)&pPackage->m_hdr, sizeof(pPackage->m_hdr));
        if (pSocketInfo->m_buffRecv.GetSize() >= pPackage->m_hdr.m_nDataLen + sizeof(pPackage->m_hdr))
        {
            //�ӻ�������ȡ��һ�����������ݰ�
            pSocketInfo->m_buffRecv.Read((char*)&pPackage->m_hdr, sizeof(pPackage->m_hdr));
            pPackage->m_pBuff = new char[pPackage->m_hdr.m_nDataLen];
            pSocketInfo->m_buffRecv.Read(pPackage->m_pBuff, pPackage->m_hdr.m_nDataLen);
            pSocketInfo->m_lockRecv.UnLock();
            return TRUE;
        }
    }
    pSocketInfo->m_lockRecv.UnLock();
    return FALSE;
}
BOOL CMyChatServer::SendPackage(CIOCPSocket::SocketInfo* pSocketInfo, DATAPACKAGE* pPackage)
{
    //������д�뷢�ͻ�������
    pSocketInfo->m_lockSend.Lock();
    pSocketInfo->m_buffSend.Write((char*)&pPackage->m_hdr, sizeof(pPackage->m_hdr));
    pSocketInfo->m_buffSend.Write(pPackage->m_pBuff, pPackage->m_hdr.m_nDataLen);
    pSocketInfo->m_lockSend.UnLock();

    //Ͷ��send����
    m_iocpSocket.PostSend(pSocketInfo);
    return TRUE;
}

#include "CMyChatServer.h"

BOOL CMyChatServer::CreateServer(char* szIp, u_short nPort)
{

    BOOL bRet = m_IocpSocket.CreateIocp(szIp,nPort);
    if (!bRet)
    {
        printf("����Iocpʧ�ܣ�\r\n");
        return FALSE;
    }
    m_IocpSocket.PostAccept();
    return TRUE;
}

BOOL CMyChatServer::RunServer()
{
    //��������
    while (true)
    {
       
        //�ȴ�iocp����������
        CIocpSocket::SocketInfo* pSocketInfo = NULL;
        int nRetIoEvent = m_IocpSocket.WaitForEvent(pSocketInfo);

        //��Բ�ͬ������������
        switch (nRetIoEvent)
        {
        case CIocpSocket::IO_RECV:
            HandleClientData(pSocketInfo);
            break;
        default:
            break;
        }
    }
   
    return TRUE;
}
BOOL CMyChatServer::RecvPackage(CIocpSocket::SocketInfo* pSocketInfo, DATAPACKAGE* pPackage)
{
    pSocketInfo->m_locRecv.Lock();
    if (pSocketInfo->m_RecvBuffer.GetSize() >= sizeof(PACKAGEHEADER))
    {
        pSocketInfo->m_RecvBuffer.Peek((char*)&pPackage->m_hdr, sizeof(pPackage->m_hdr));
        if (pSocketInfo->m_RecvBuffer.GetSize() >= pPackage->m_hdr.m_nDataLen + sizeof(pPackage->m_hdr))
        {
            pSocketInfo->m_RecvBuffer.Read((char*)&pPackage->m_hdr, sizeof(pPackage->m_hdr));
            pPackage->m_pBuff = new char[pPackage->m_hdr.m_nDataLen];
            pSocketInfo->m_RecvBuffer.Read(pPackage->m_pBuff, pPackage->m_hdr.m_nDataLen);
            pSocketInfo->m_locRecv.UnLock();
            return TRUE;
        }
    }
    pSocketInfo->m_locRecv.UnLock();
    return FALSE;
}
BOOL CMyChatServer::SendPackage(CIocpSocket::SocketInfo* pSocketInfo, DATAPACKAGE* pPackage)
{
    pSocketInfo->m_locRecv.Lock();
    pSocketInfo->m_SendBuffer.Write((char*)&pPackage->m_hdr, sizeof(pPackage->m_hdr));
    pSocketInfo->m_SendBuffer.Write(pPackage->m_pBuff, pPackage->m_hdr.m_nDataLen);
    pSocketInfo->m_locRecv.UnLock();

    m_IocpSocket.PostSend(pSocketInfo);

    return TRUE;
}
DWORD  CMyChatServer::HandleClientData(CIocpSocket::SocketInfo* pSocketInfo)
{

    DATAPACKAGE pkgRecv;

    BOOL bRet = RecvPackage(pSocketInfo,&pkgRecv);
    if (!bRet)
    {
        //���ݰ�������������
        return 0;
    }


    //�ж����ݵ�����
    switch (pkgRecv.m_hdr.m_nDataType)
    {

    case DT_LOGIN:	//�����¼
    {
        //�����¿ͻ��˵�����
       
        m_listClients.push_back(new ClinentInfo(pSocketInfo));
        //��ͻ��˷��͵�¼���
        DATAPACKAGE package;
        package.m_hdr.m_nDataType = DT_FLUSH_NAME;
        package.m_hdr.m_nDataLen = 0;
        package.m_pBuff = NULL;
        for (auto ci : m_listClients)
        {
            BOOL bRet = SendPackage(ci->m_pSocketInfo,&package);
        }
        

        break;
    }
    case DT_ADD_NAME:
    {
        for (auto ci : m_listClients)
        {
            BOOL bRet = SendPackage(ci->m_pSocketInfo, &pkgRecv);
        }
        break;
    }
    case DT_DEL_NAME:
    {
        for (auto ci : m_listClients)
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

        if (strType == "public")//Ⱥ��
        {
            //����Ϣת���������ͻ���
            for (auto ci : m_listClients)
            {
                BOOL bRet = SendPackage(ci->m_pSocketInfo, &pkgRecv);
            }
        }
        else if (strType == "private") //˽�� 
        {
            //����Ϣת���������ͻ���
            for (auto ci : m_listClients)
            {
                BOOL bRet = SendPackage(ci->m_pSocketInfo, &pkgRecv);
            }
        }

        break;
    }





    //case DT_LOGIN:
    //{
    //    m_listClients.push_back(new ClinentInfo(pSocketInfo));
    //    //��ͻ��˷��͵�½���
    //    DATAPACKAGE packageLogin;
    //    packageLogin.m_hdr.m_nDataType = DT_LOGIN_OK;
    //    packageLogin.m_hdr.m_nDataLen = 0;
    //    packageLogin.m_pBuff = NULL;
    //    SendPackage(pSocketInfo, &packageLogin);
    //    break;
    //}

    //case DT_MSG:
    //{
    //    //json�������ж�������public����private
    //    CJsonObject json;
    //    json.Parse(pkgRecv.m_pBuff);
    //    string strType;
    //    json.Get("type", strType);
    //    if (strType == "public") //Ⱥ��
    //    {
    //        for (auto ci : m_listClients)
    //        {
    //           // DATAPACKAGE pkgMsg;

    //            pkgRecv.m_hdr.m_nDataType = DT_MSG;
    //            BOOL bRet = SendPackage(ci->m_pSocketInfo, &pkgRecv);
    //            if (!bRet)
    //            {
    //                printf("������Ϣʧ�ܣ�\r\n");
    //            }
    //        }
    //    }
    //    if (strType == "private") //˽��
    //    {
    //        for (auto itr = m_listClients.begin(); itr != m_listClients.end(); ++itr)
    //        {
    //            if ((*itr)->m_pSocketInfo->m_socket == pSocketInfo->m_socket)
    //            {
    //                pkgRecv.m_hdr.m_nDataType = DT_MSG;
    //                BOOL bRet = SendPackage((*itr)->m_pSocketInfo, &pkgRecv);
    //                if (!bRet)
    //                {
    //                    printf("������Ϣʧ�ܣ�\r\n");
    //                }
    //            }
    //        }
    //    }
    //    if (pkgRecv.m_pBuff != NULL)
    //    {
    //        delete[] pkgRecv.m_pBuff;
    //    }
    //    break;
    //}
    //���տͻ����˳����ݰ�
    case DT_LOGINOUT:
    {
        for (auto itr = m_listClients.begin(); itr != m_listClients.end(); ++itr)
        {
            if ((*itr)->m_pSocketInfo->m_socket == pSocketInfo->m_socket)
            {
                m_listClients.erase(itr);
                delete pSocketInfo;
                break;
            }
        }
        
    }
    }
    //ɾ��������
    if (pkgRecv.m_pBuff != NULL)
    {
        delete[] pkgRecv.m_pBuff;
    }
    return TRUE;

}
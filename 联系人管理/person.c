#include <stdio.h>
#include<stdlib.h>
#include<windows.h>
#pragma warning(disable:4996)
void Add();//������ϵ��
void Del();//ɾ����ϵ��
void Alter();//�޸���ϵ��
void Que();//������ϵ��
void Count();//ͳ����ϵ��
void Resource();//��ϵ����Դ�ֲ�
void FragMent();//��Ƭ����
void Output();//�����ϵ��
void Show();//����ѡ��������
void WriteIn();//�����ڴ�
void Clean();//����g_szBuf
#define SIZE 1000
char g_szBuf[SIZE] = { 0 };
//����һ��ȫ�����ݣ������û���������ݣ�Ȼ��д���ļ�
int main()
{
    Show();
    //����������
    return 0;
}
void Clean()//������顣�Ա��ڽ����µ�����
{
    for (int i = 0; i < SIZE; i++)
        //������������
    {
        g_szBuf[i] = '\0';
        //��ÿ��ֵ���������
    }
}
void WriteIn()//�������������������д���ļ�
{
    FILE* fp = NULL;
    //�ļ�ָ��
    int nLen = 0;
    //��ϵ����������
    int nLen2 = 0;
    //��ϵ��ʽ����
    int nLen3 = 0;
    //�ܳ���
    int i = 0;
    //�ֲ�����i
    nLen = strlen(g_szBuf) + 1;
    //������ϵ����������
    nLen2 = 1 + strlen(&g_szBuf[strlen(g_szBuf) + 1]);
    //������ϵ��ʽ����
    nLen3 = nLen2 + nLen;
    //�����ܳ���
    for (i = 0; i < nLen3; i++)
    {
        fp = fopen("MyData2.bin", "ab+");
        //��׷�ӵķ�ʽ���ļ�
        if (fp == NULL)
            //�ļ���ʧ���ж�
        {
            printf("�ļ���ʧ��\r\n");
            //�ļ���ʧ����ʾ
            exit(1);
            //�˳�����
        }
        fwrite(&g_szBuf[i], sizeof(char), 1, fp);
        //д������
        fclose(fp);
        //�ر��ļ�ָ��
    }
}

void Add()//������ϵ�˹���
{
    char ChAdd[33] = {0};
    //��ϵ��������������
    char nTel[12] = { 0 };
    //�ֻ��Ž�������
    char c;
    //��������ձ���
    Clean();
    //���ԭ����
    printf("----------------�����ϵ��-----------------\r\n");
    printf("------���������������16������\r\n");
    printf("------�ֻ����������11λ\r\n");
    printf("$����Ҫ��ӵ���ϵ��������");
    //UI����
    scanf_s("%32s", ChAdd,sizeof(ChAdd));
    //������ϵ������������ֻ����16λ����
    while ((c = getchar()) != '\n' && c != EOF);
    //���������
    printf("$����Ҫ��ӵ���ϵ���ֻ����룺");
    scanf_s("%11s", nTel,sizeof(nTel));
    //�����ֻ����룬��������11λ�ֻ�����
    while ((c = getchar()) != '\n' && c != EOF);
    //���������
    Clean();
    //���ԭ����
    for (int i = 0; i < SIZE; i++)
    {
        //������ĵ�һ��λ�ò����ַ������ж�
         if (g_szBuf[i] == '\0' && g_szBuf[i + 1] == '\0' && i == 0)
         {
                g_szBuf[i] = -1;
                //��ϵ�˱�ͷ-1
                g_szBuf[ i+2 + strlen(ChAdd)] = -2;
                //�ֻ��ű�ͷ-2
                strcpy(&g_szBuf[i+1], ChAdd);
                //����ϵ�˲�������
                strcpy(&g_szBuf[i+ 3 + strlen(ChAdd)], nTel);
                //��ϵ��ʽ��������
                break;
                //����ѭ��
         }  
    }

    WriteIn();
    //������õ�����д���ļ�
    printf("д��ɹ�\r\n");
    //��ʾ���
    Clean();
    //���ԭ����
}
void Del()//ɾ����ϵ�˹���
{
    printf("--------------------ɾ����ϵ��--------------------\r\n");
    Clean();
    Output();
    //��ӡ����ͨѶ¼
    int nStrlen = 0;
    FILE* fp = NULL;
    //�ļ�ָ��
    int DeleteIn = 0;
    //����ɾ�����
    int nFileSize = 0;
    //ͨѶ¼����
    int i = 0;
    int nTally = 1;
    //�ֲ�����
    int nCount = 0;
    printf("$����������Ҫɾ������ϵ����ţ�");
    scanf("%d", &DeleteIn);
    //���ձ�ɾ�������
    fp = fopen("MyData2.bin", "rb");
    //������
    fseek(fp, 0, SEEK_END);
    //���ļ�ָ���ƶ����ļ�ĩβ
    nFileSize = ftell(fp);
    //�����ļ����ݳ���
    if (fp == NULL)
     //�ļ���ʧ���ж�����
    {
        printf("�ļ���ʧ��\r\n");
        //�ļ���ʧ����ʾ
        exit(1);
        //�˳�����
    }

    fseek(fp, 0, SEEK_SET);
    //�ļ�ָ���ƶ�����ǰ
    for (i = 0; i < nFileSize; i++)//����Ϣ�Ӷ������ļ����ȡ������
    {
        if (fread(&g_szBuf[i], sizeof(char), 1, fp) != 1)
        {
            goto EXIT_PROC;
            //����ļ���ȡʧ��
            //��ת��EXIT_PROC
            //�ر�ָ��
        }
    }
    for (i = 0; i < nFileSize; i++)//���������ҵ���Чֵ
    {
        if (g_szBuf[i] == -1)
            //��ϵ���ж�����
        {
            nCount++;
            //��¼��ϵ�˱��
            if (DeleteIn == nCount)
                //��ϵ�˱���뱻ɾ������ж�
            {
                g_szBuf[i] = -3;
                //��ϵ����Ϊɾ��
                g_szBuf[i + strlen(&g_szBuf[i]) + 1] = -3;
                //��ϵ��ʽ��Ϊɾ��
            }
           
        }
    }
    fclose(fp);
    //�ر�ָ��
    //д���ļ�
    for (i = 0; i < SIZE; i++)
    {
        if ((g_szBuf[i] == -1 && i==0) || (g_szBuf[i] == -2 && i == 0) || (g_szBuf[i] == -3 && i == 0))
            //д�������ж�����
        {
            if (nTally == 1)
            {
                fp = fopen("MyData2.bin", "wb");
                //��һ��д��������wb��ʽ��ͷ��ʼд
                nTally++;
            }
            if (fp == NULL)
                //�ļ���ʧ���ж�����
            {
                printf("�ļ���ʧ��\r\n");
                //�ļ�����ʾ
                exit(1);
                //�˳�����
            }
            fwrite(&g_szBuf[i], sizeof(char), strlen(&g_szBuf[i]) + 1, fp);
            fclose(fp);
            
        }
        else if ((g_szBuf[i] == -1 && g_szBuf[i- 1]  == '\0') ||
                    (g_szBuf[i] == -2 && g_szBuf[i- 1] == '\0') || 
                    (g_szBuf[i] == -3 && g_szBuf[i -1] == '\0')  )
        {
            if (nTally == 1)
            {
                fp = fopen("MyData2.bin", "wb");
                nTally++;
            }
            else
            {
                fp = fopen("MyData2.bin", "ab+");
            }
            if (fp == NULL)
            {
                printf("�ļ���ʧ��\r\n");
                exit(1);
            }
            fwrite(&g_szBuf[i], sizeof(char), strlen(&g_szBuf[i]) + 1, fp);
            fclose(fp);
        }
    }   
   //���ݽ���λ��

EXIT_PROC:
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }
    Clean();
}
void Alter()//�޸���ϵ�˹���
{
    Clean();
    int AlterIn = 0;
    char AlterName[32] = { 0 };
    char c;
    int nChange = 0;
    FILE* fp = NULL;
    int nFileSize = 0;
    int i = 0;
    int nCount = 0;
    int nTally = 1;
    fp = fopen("MyData2.bin", "rb");
    fseek(fp, 0, SEEK_END);
    nFileSize = ftell(fp);
    if (fp == NULL)
    {
        printf("�ļ���ʧ��\r\n");
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < nFileSize; i++)//����Ϣ�Ӷ������ļ����ȡ������
    {
        if (fread(&g_szBuf[i], sizeof(char), 1, fp) != 1)
        {
            goto EXIT_PROC;//���ʧ�ܣ��ر��ļ�ָ��
        }
    }
    fclose(fp);//�ر�ָ��
    printf("------------------�޸���ϵ��-------------------\r\n");
    printf("------------1������---------\r\n");
    printf("------------2���ֻ�����-------\r\n");
    printf("��ѡ��");
    scanf("%d" ,&AlterIn);
    if (AlterIn == 1)//ֻ�޸�����
    {
        Output();
        while ((c = getchar()) != '\n' && c != EOF);
        printf("$��������������");
        scanf("%32s", AlterName);
        while ((c = getchar()) != '\n' && c != EOF);
        printf("$��ѡ���滻��λ��:");
        scanf("%d", &nChange);


        for (i = 0; i < nFileSize; i++)//���������ҵ���Чֵ
        {
            if (g_szBuf[i] == -1)//�ҵ���Ч����-��ϵ��
            {
                nCount++;//�±�+1
                if (nCount== nChange)//�ҵ��޸�λ��
                {
                    if (strlen(AlterName) == strlen(&g_szBuf[i + 1]))
                        //����޸ĵ����ֺ�ԭ���ַ�����Сһ�£���ԭ���޸�
                        //��ͷ��ԭ��һ�������Բ��øı�
                    {
                            strcpy(&g_szBuf[i + 1], AlterName);
                            break;
                    }

                    else  if (strlen(AlterName) < strlen(&g_szBuf[i + 1]))
                        //����޸ĵ�����С��ԭ���ַ�������ԭ���޸�
                        //��ͷ��ԭ��һ�������Բ��øı�
                    {
                            memset(&g_szBuf[i + 1], 0, strlen(&g_szBuf[i + 1]));
                            //���ԭ���ַ���
                            strcpy(&g_szBuf[i + 1], AlterName);
                            break;
                    }
                    else  if (strlen(AlterName) > strlen(&g_szBuf[i + 1]))
                            //����޸ĵ����ִ���ԭ���ַ�������ԭ���޸�
                            //��ԭ������ϵ�˱�ͷ��Ϊ-3
                    {
                             //���ֱ�ͷ��Ϊ-1
                               g_szBuf[nFileSize] = -1;
                              //��ԭ��ͷ��Ϊ-3
                               g_szBuf[i] = -3;
                               //���ַ���ĩβ����µ���ϵ��
                               strcpy(&g_szBuf[nFileSize+1], AlterName);
                               //���ԭ��Ӧ����ϵ�˵绰����
                               strcpy(&g_szBuf[nFileSize + 2+strlen(AlterName)], 
                                   &g_szBuf[i + 1 + strlen(&g_szBuf[i])]);
                               //����ԭ����ϵ�˵��ֻ�����Ҳ��Ϊ-3
                               g_szBuf[i + 1 + strlen(&g_szBuf[i])] = -3;
                               break;
                    } 
                }
            }
        }
    }
    else if (AlterIn == 2)//ֻ�޸��ֻ���
    {
        Output();
        while ((c = getchar()) != '\n' && c != EOF);
        printf("$�������µ���ϵ��ʽ��");
        scanf("%11s", AlterName);
        while ((c = getchar()) != '\n' && c != EOF);
        printf("$��ѡ���滻��λ��");
        scanf("%d", &nChange);

        for (i = 0; i < nFileSize; i++)//���������ҵ���Чֵ
        {
            if (g_szBuf[i] == -1)//�ҵ���Ч����-��ϵ��
            {
                nCount++;//�±�+1
                if (nCount == nChange)//�ҵ��޸�λ��
                {
                    if (strlen(AlterName) == strlen(/*ԭ�ֻ����볤��*/
                        &g_szBuf[  /*��ǰ��ַ*/i+  2+/*ƫ�Ƶ�ַ*/strlen(&g_szBuf[i])]))
                        //����޸ĵ��ֻ��ź�ԭ���ֻ��ų���һ�£���ԭ���޸�
                        //��ͷ��ԭ��һ�������Բ��øı�
                    {
                        strcpy(&g_szBuf[i + 2 +
                            /*ƫ�Ƶ�ַ*/strlen(&g_szBuf[i])], AlterName);
                        break;
                    }

                    else  if (strlen(AlterName) <  strlen(/*ԭ�ֻ����볤��*/
                        &g_szBuf[  /*��ǰ��ַ*/i + 2 +/*ƫ�Ƶ�ַ*/strlen(&g_szBuf[i])]))
                        //����޸ĵ��ֻ��ų���С��ԭ���ֻ��ų��ȣ���ԭ���޸�
                        //��ͷ��ԭ��һ�������Բ��øı�
                    {
                        memset(&g_szBuf[i + 2+strlen(&g_szBuf[i])],
                            0, strlen(&g_szBuf[i +2 +strlen(&g_szBuf[i])]));
                        //���ԭ���ַ���
                        strcpy(&g_szBuf[i + 2 + strlen(&g_szBuf[i])], AlterName);
                        break;
                    }
                    else  if (strlen(AlterName) > strlen(/*ԭ�ֻ����볤��*/
                        &g_szBuf[  /*��ǰ��ַ*/i + 2 +/*ƫ�Ƶ�ַ*/strlen(&g_szBuf[i])]))
                        //����޸ĵ��ֻ��ų��ȴ���ԭ���ֻ��ŵĳ��ȣ�
                        //������ĩβ�޸�
                        //��ԭ������ϵ�˱�ͷ��Ϊ-3
                    {
                        //���ַ���ĩβ����µ���ϵ��
                        strcpy(&g_szBuf[nFileSize], &g_szBuf[i]);
                        //���ԭ��Ӧ����ϵ�˵绰����
                        strcpy(&g_szBuf[nFileSize + 2 + strlen(&g_szBuf[i])],
                            AlterName);
                        g_szBuf[nFileSize + 1 + strlen(&g_szBuf[i])] = -2;
                        //��ԭ��ͷ��Ϊ-3
                        g_szBuf[i] = -3;
                        g_szBuf[i + 1 + strlen(&g_szBuf[i])] = -3;
                        break;
                    }
                }
            }
        }
    }
    for (i = 0; i < SIZE; i++)
    {
        if ((g_szBuf[i] == -1&& i== 0) || (g_szBuf[i] == -2 && i == 0) || (g_szBuf[i] == -3 && i == 0))
        {
            if (nTally == 1)
            {
                fp = fopen("MyData2.bin", "wb");
                nTally++;
            }
            if (fp == NULL)
            {
                printf("�ļ���ʧ��\r\n");
                exit(1);
            }
            fwrite(&g_szBuf[i], sizeof(char), strlen(&g_szBuf[i]) + 1, fp);
            fclose(fp);
        }

        else if ((g_szBuf[i] == -1 && g_szBuf[i-1] == '\0') ||
            (g_szBuf[i] == -2 && g_szBuf[i - 1] == '\0') || 
            (g_szBuf[i] == -3 && g_szBuf[i - 1] == '\0'))
        {
            if (nTally == 1)
            {
                fp = fopen("MyData2.bin", "wb");
                nTally++;
            }
            else
            {
                fp = fopen("MyData2.bin", "ab+");
            }
            if (fp == NULL)
            {
                printf("�ļ���ʧ��\r\n");
                exit(1);
            }
            fwrite(&g_szBuf[i], sizeof(char), strlen(&g_szBuf[i]) + 1, fp);
            fclose(fp);
        }
    }
    
EXIT_PROC:
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }
    Clean();//���ԭ����
}
void Que()//������ϵ�˹���
{
    Clean();
    Output();
    int nStrlen = 0;
    FILE* fp = NULL;
    char QueIn[32] = { 0 };
    char c;
    int nFileSize = 0;
    int i = 0;
    int nCount = 0;
    int nSele = 0;
    printf("---------------------��ϵ�˲���---------------------\r\n");
    printf("-------------1����������\r\n");
    printf("-------------2���ֻ��Ų���\r\n");
    printf("-------------3ģ������\r\n");
    scanf("%d", &nSele);
    fp = fopen("MyData2.bin", "rb");
    fseek(fp, 0, SEEK_END);
    nFileSize = ftell(fp);
    if (fp == NULL)
    {
        printf("�ļ���ʧ��\r\n");
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < nFileSize; i++)//����Ϣ�Ӷ������ļ����ȡ������
    {
        if (fread(&g_szBuf[i], sizeof(char), 1, fp) != 1)
        {
            goto EXIT_PROC;
        }
    }
    fclose(fp);//�ر�ָ��
    //ָ����������
    if (nSele == 1)
    {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("$���뱻���ҵ�������");
        scanf("%32s", QueIn);
        while ((c = getchar()) != '\n' && c != EOF);
        for (i = 0; i < nFileSize; i++)//���������ҵ���Чֵ
        {
            if (g_szBuf[i] == -1)
            {

                if (strcmp(&g_szBuf[i+1], QueIn) == 0)//�㷨��ȷ
                {
                    nCount++;
                    //������ҵ����������ֻ���
                    printf("���ҳɹ���\r\n");
                    printf("%d~��ϵ�ˣ�%s--�ֻ��ţ�%s", nCount,
                        &g_szBuf[i + 1], &g_szBuf[i + strlen(&g_szBuf[i]) + 2]);
                }
            }
        }
    }
    //ָ���������ҽ���
    else if (nSele == 2)//ָ���������
    {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("���뱻���ҵ��ֻ��ţ�");
        scanf("%11s", QueIn);
        while ((c = getchar()) != '\n' && c != EOF);
        for (i = 0; i < nFileSize; i++)//���������ҵ���Чֵ
        {
            if (g_szBuf[i] == -1)
            {

                if (strcmp(&g_szBuf[i + strlen(&g_szBuf[i]) + 2], QueIn) == 0)//�㷨��ȷ
                {
                    nCount++;
                    //������ҵ����������ֻ���
                    printf("���ҳɹ���\r\n");
                    printf("%d~��ϵ�ˣ�%s---�ֻ��ţ�%s",nCount, 
                    &g_szBuf[i + 1],&g_szBuf[i+strlen(&g_szBuf[i])+2]); 
                }
            }
        }
    }//ָ�����������
   //ģ������
    else if (nSele == 3)
    {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("���뱻���ҵ�ģ�����������ֻ��ţ�");
        scanf("%32s", QueIn);
        while ((c = getchar()) != '\n' && c != EOF);
        for (i = 0; i < nFileSize; i++)//���������ҵ���Чֵ
        {
            if (g_szBuf[i] == -1)
            {

                if ((strstr(&g_szBuf[i+1], QueIn) != NULL)||
                    (strstr(&g_szBuf[i + strlen(&g_szBuf[i]) + 2], QueIn) != NULL))//�㷨��ȷ
                {
                    nCount++;
                    //������ҵ����������ֻ���
                    printf("���ҳɹ���\r\n");
                    printf("%d~��ϵ�ˣ�%s---�ֻ��ţ�%s\r\n", nCount,
                        &g_szBuf[i + 1], &g_szBuf[i + strlen(&g_szBuf[i]) + 2]);
                }
            }
        }
    }
    else
    {
        printf("��������");
    }

EXIT_PROC:
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }
    Clean();
}
void Count()//ͳ����ϵ�˹���
{
    //5.��ͳ��ÿ����ϵ����Ϣ�ĳ��ִ����ͱ�����

    Clean();
    FILE* fp = NULL;
    int nCount = 0;
    int nFileSize = 0;
    char ChCount[32] = { 0 };
    char c;
    int i = 0;
    float fNumerator = 0;
    float fDenominator = 0;
    float fConsult = 0;
    fp = fopen("MyData2.bin", "rb");
    fseek(fp, 0, SEEK_END);
    nFileSize = ftell(fp);
    if (fp == NULL)
    {
        printf("�ļ���ʧ��\r\n");
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < nFileSize; i++)//����Ϣ�Ӷ������ļ����ȡ������
    {
        if (fread(&g_szBuf[i], sizeof(char), 1, fp) != 1)
        {
            goto EXIT_PROC;
        }
    }
    fclose(fp);
    printf("--------------------ͳ����ϵ��--------------------\r\n");
    printf("--------------------�����뱻ͳ����ϵ������:");
    //while ((c = getchar()) != '\n' && c != EOF);
    scanf("%32s", ChCount);
    //while ((c = getchar()) != '\n' && c != EOF);
    for (i = 0; i < nFileSize; i++)
    {
        if (g_szBuf[i] == -1)
        {
            fDenominator++;//��ĸ
            if (strcmp(&g_szBuf[i + 1], ChCount)==0)
            {
                fNumerator++;//����
            }
        }
    }
    fConsult = (fNumerator / fDenominator)*100;
    printf("----$%s$������%.0f��----���ֵı�����:%.2f%%", ChCount, fNumerator, fConsult);
EXIT_PROC:
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }
    Clean();

}
void Resource()//��ϵ����Դ�ֲ�����
{
    Clean();
    FILE* fp = NULL;
    int nCount = 0;
    int nFileSize = 0;
    int i = 0;
    fp = fopen("MyData2.bin", "rb");
    fseek(fp, 0, SEEK_END);
    nFileSize = ftell(fp);
    if (fp == NULL)
    {
        printf("�ļ���ʧ��\r\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < nFileSize; i++)//����Ϣ�Ӷ������ļ����ȡ������
    {
        if (fread(&g_szBuf[i], sizeof(char), 1, fp) != 1)
        {
            goto EXIT_PROC;
        }
    }
    fclose(fp);
    for (i = 0; i < nFileSize; i++)//����Ϣ�Ӷ������ļ����ȡ������
    {
        //g_szBuf[i+strlen(&g_szBuf[i])] =='\0'   g_szBuf[i] == -3 && g_szBuf[i-1]=='\0'
        if (g_szBuf[i] == -3 && i ==0 )
        {
            for (int j = 0; j < strlen(&g_szBuf[i]); j++)
            {
                printf("F");
            }
        }
        else if(g_szBuf[i] == -3 && g_szBuf[i - 1] == '\0')
        {
            for (int j = 0; j < strlen(&g_szBuf[i]); j++)
            {
                printf("F");
            }
        }
        else if((g_szBuf[i] == -1 && i == 0)|| (g_szBuf[i] == -2 && i == 0))
        {
            for (int j = 0; j < strlen(&g_szBuf[i]); j++)
            {
                printf("U");
            }
        }
        else if ((g_szBuf[i] == -1 && g_szBuf[i-1] == '\0') || (g_szBuf[i] == -2 && g_szBuf[i - 1] == '\0'))
        {
            for (int j = 0; j < strlen(&g_szBuf[i]); j++)
            {
                printf("U");
            }
        }
    }
EXIT_PROC:
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }
    Clean();
}
void FragMent()//��ϵ����Ƭ������
{
    Clean();
    FILE* fp = NULL;
    int nCount = 0;
    int nFileSize = 0;
    int i = 0;
    int nTally = 1;
    fp = fopen("MyData2.bin", "rb");
    fseek(fp, 0, SEEK_END);
    nFileSize = ftell(fp);
    if (fp == NULL)
    {
        printf("�ļ���ʧ��\r\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < nFileSize; i++)//����Ϣ�Ӷ������ļ����ȡ������
    {
        if (fread(&g_szBuf[i], sizeof(char), 1, fp) != 1)
        {
            goto EXIT_PROC;
        }
    }
    fclose(fp);

    for (i = 0; i < nFileSize; i++)
    {
        if ((i==0 && g_szBuf[i] == -1) || (i == 0 && g_szBuf[i] == -2))
            //��һ��д�������ж�����
        {
             if (nTally == 1)
             {
                fp = fopen("MyData2.bin", "wb");
                //��wb��ԭ�ļ���ʼд����������Դ�ļ�������
                 nTally++;
             }
            //else
          //  {
            //    fp = fopen("MyData2.bin", "ab+");
            //}
            if (fp == NULL)//�ļ���ʧ���ж�����
            {
                printf("�ļ���ʧ��\r\n");
                //��ʾ�ļ���ʧ��
                exit(1);
                //�˳�����
            }
            fwrite(&g_szBuf[i], sizeof(char), strlen(&g_szBuf[i]) + 1, fp);
            //���ļ�д���һ������
            fclose(fp);
            //�ر��ļ�ָ��
        }
        else if((g_szBuf[i] == -1&&g_szBuf[i-1] == '\0') || ( g_szBuf[i] == -2 && g_szBuf[i - 1] == '\0'))
            //д��ʣ����Ч�����ж�����
        {
            if (nTally == 1)
            {
                fp = fopen("MyData2.bin", "wb");
                //��wb��ԭ�ļ���ʼд����������Դ�ļ�������
                nTally++;
            }
            else
            {
                 fp = fopen("MyData2.bin", "ab+");
                   //׷��д���ļ�
                  if (fp == NULL)
                     //�ļ���ʧ���ж�����
                  {
                      printf("�ļ���ʧ��\r\n");
                        //��ʾ�ļ���ʧ��
                      exit(1);
                        //�˳�����
                  }
                  fwrite(&g_szBuf[i], sizeof(char), strlen(&g_szBuf[i]) + 1, fp);
                   //д��ʣ�µ���Ч����
                  fclose(fp);
                   //�ر��ļ�ָ��
            }
        }
    }


EXIT_PROC:
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }
    Clean();

}
void Output()//�����ϵ�˹���
{
    printf("--------------------ͨѶ¼--------------------\r\n");
    FILE* fp = NULL;
    int nCount = 0;
    int nFileSize = 0;
    int i = 0;
    fp = fopen("MyData2.bin", "rb");
    fseek(fp, 0, SEEK_END);
    nFileSize = ftell(fp);
    if (fp == NULL)
    {
        printf("�ļ���ʧ��\r\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < nFileSize; i++)//����Ϣ�Ӷ������ļ����ȡ������
    {
        if (fread(&g_szBuf[i], sizeof(char), 1, fp) != 1)
        {
            goto EXIT_PROC;
        }
    }
    fclose(fp);
    for (i = 0; i < nFileSize; i++)//���������ҵ���Чֵ
    {
        if (g_szBuf[i] == -1)
        {
            nCount++;
            printf("%d:%s:%s\r\n", 
                nCount, &g_szBuf[i + 1], &g_szBuf[i + 2 + strlen(&g_szBuf[i])]);
        }
    }
EXIT_PROC:
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }
}
void Show()//����ѡ��������
{
    int i = 0;//�����û��Ĺ���ѡ��
    //system("color 4e");//�����滻����ɫ
    //int j = 1;
    while (1)
    {
        system("cls");//�����һ������
        printf("*****************��ϵ����ɾ�Ĳ�*****************\r\n");
        printf("------------------1�������ַ���------------------\r\n");
        printf("------------------2��ɾ���ַ���------------------\r\n");
        printf("------------------3���޸��ַ���------------------\r\n");
        printf("------------------4����ѯ�ַ���------------------\r\n");
        printf("------------------5��ͳ���ַ���------------------\r\n");
        printf("------------------6���洢��Դ�ֲ�----------------\r\n");
        printf("------------------7����Ƭ����--------------------\r\n");
        printf("------------------8����ӡ�ַ���------------------\r\n");
        printf("------------------0���˳�����------------------\r\n");
        printf("------------------��ѡ����ģ�飺");
        scanf_s("%d", &i);//�����û��Ĺ���ѡ��
        switch (i)//��switch-caseʵ���û��Թ��ܵ�ѡ��
        {
        case 0:
            exit(1);
        case 1:
            printf("###################################################\r\n");
            Add();
            printf("###################################################\r\n");
            system("pause");
            break;
        case 2:
            printf("###################################################\r\n");
            Del();
            printf("###################################################\r\n");
            system("pause");
            break;
        case 3:
            printf("###################################################\r\n");
            Alter();
            printf("###################################################\r\n");
            system("pause");
            break;
        case 4:
            printf("###################################################\r\n");
            Que();
            printf("###################################################\r\n");
            system("pause");
            break;
        case 5:
            printf("###################################################\r\n");
            Count();
            printf("\r\n");
            printf("###################################################\r\n");
            system("pause");
            break;
        case 6:
            printf("###############��Դ�ֲ�#########################\r\n");
            Resource();
            printf("\r\n");
            //printf("###################################################\r\n");
            system("pause");
            break;
        case 7:
            FragMent();
            printf("��Ƭ�������......");
            system("pause");
            break;
        case 8:
            printf("###################################################\r\n");
            Output();
            printf("###################################################\r\n");
            system("pause");
            break;
        default:
            printf("###################################################\r\n");
            printf("�����������ٴ����룡\r\n");
            printf("###################################################\r\n");
            system("pause");
            //��ʾ������Ϣ��
            break;
        }
    }
   
}



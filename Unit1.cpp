//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <windows.h>
#include <Winsock2.h>
#include <Iphlpapi.h>
#include <cstring.h>
#include <string.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button1Click(TObject *Sender)
{

  char *ip=Edit1->Text.c_str();
  //Будем использовать сокеты
    WSADATA WsaData;
    DWORD _ip=inet_addr(ip);
    if (WSAStartup(0x0202, &WsaData)==NULL)
        printf("WSA Starup OK!\n");

   Edit2->Text = "";

//Создаём UDP-сокет и отсылаем по нему любые данные 
    SOCKET udp_s;
    SOCKADDR_IN udp_sin; 
    udp_s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 
    if(udp_s!=SOCKET_ERROR) 
    { 
        udp_sin.sin_family = AF_INET; 
        udp_sin.sin_port = htons(5232); //Шлём на любой порт. 
        udp_sin.sin_addr.s_addr = _ip; 
        if(sendto(udp_s, "TEST", 5, NULL, (SOCKADDR*)&udp_sin, sizeof(udp_sin))>0) 
        { //Пакет отослан. Вытаскиваем MAC-адрес из системы
            MIB_IPNETTABLE * pIpNetTable = (MIB_IPNETTABLE *) new char[0xFFFF];
            ULONG cbIpNetTable = 0xFFFF; 
            if (NO_ERROR == GetIpNetTable (pIpNetTable, &cbIpNetTable, TRUE))
            {
                for (DWORD i = 0; i < pIpNetTable->dwNumEntries; i++)
                { 
                    if(pIpNetTable->table[i].dwAddr==_ip&&pIpNetTable->table[i].dwType!=2)
                    {
                        Edit2->Text="";
                        Edit2->Text=Edit2->Text + IntToHex(int(pIpNetTable->table[i].bPhysAddr[0]),2)+":";
                        Edit2->Text=Edit2->Text + IntToHex(int(pIpNetTable->table[i].bPhysAddr[1]),2)+":";
                        Edit2->Text=Edit2->Text + IntToHex(int(pIpNetTable->table[i].bPhysAddr[2]),2)+":";
                        Edit2->Text=Edit2->Text + IntToHex(int(pIpNetTable->table[i].bPhysAddr[3]),2)+":";
                        Edit2->Text=Edit2->Text + IntToHex(int(pIpNetTable->table[i].bPhysAddr[4]),2)+":";
                        Edit2->Text=Edit2->Text + IntToHex(int(pIpNetTable->table[i].bPhysAddr[5]),2);
                        Edit2->CopyToClipboard();
                                    delete[] pIpNetTable;
                                    closesocket(udp_s); 
                         WSACleanup();
                         break;
                    }
              Edit2->Text="MAC-address not found";
             }

             delete[] pIpNetTable;
            }
            else Edit2->Text="ERROR Open IPMAC table";
        } 
        else Edit2->Text="Send data ERROR!";
 
        closesocket(udp_s); 
    } 
    else Edit2->Text="ERROR open socket";
 
    WSACleanup();         //Освобождаем ресурсы
}
//---------------------------------------------------------------------------


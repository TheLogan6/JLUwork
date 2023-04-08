#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<stdbool.h>
#include"warehouse.h"
#include"customer.h" 
#include"manager.h" 
#include"sellbill.h"

void LoginInterface();    //��¼����
void ManagerInterface(); // ���̹������ 
void NewClientInterface();

void InitInterface();  

void ErrorHappens();
void RefreshPage();

void ClientLogin();
void ManagerLogin();
void PasswordOutput();

void ManagerChooseMode();
void ClientChooseMode(client* cur_cus);


int inputcheck(char numstring[]);  // �ж����������Ƿ�Ϸ� 

void ManagerInterface_Read();    //ֻ��ģʽ 
void ManagerInterface_Write();    // �޸�ģʽ 

void SalePromotion();            // �������� 


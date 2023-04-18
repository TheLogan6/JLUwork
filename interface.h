#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<stdbool.h>

#include"warehouse.h"
#include"client.h" 
#include"customer.h" 
#include"manager.h" 
#include"sellbill.h"
#include"shiningpoints.h"
#include"supplier.h" 

void LoginInterface(int position);    //��¼����
void ManagerInterface(); // ���̹������ 
void NewClientInterface();

void InitInterface();  

void ErrorHappens();
void RefreshPage();

void ClientLogin();
void ManagerLogin();
void PasswordOutput();

void ManagerChooseMode();
void ManInferface(int i);
void ClientChooseMode(client* cur_cus);


int inputcheck(char numstring[]);  // �ж����������Ƿ�Ϸ� 

//void ManagerInterface_Read();    //ֻ��ģʽ 
//void ManagerInterface_Write();    // �޸�ģʽ 

void Inventory_Mode();
void Clinet_Mode();
void Bill_Mode(); 
void restock_mode();   

void SalePromotion(client* cur_cus);            // �������� 
void choosegift(double buy_money);



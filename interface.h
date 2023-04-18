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

void LoginInterface(int position);    //登录界面
void ManagerInterface(); // 店铺管理界面 
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


int inputcheck(char numstring[]);  // 判断整数输入是否合法 

//void ManagerInterface_Read();    //只读模式 
//void ManagerInterface_Write();    // 修改模式 

void Inventory_Mode();
void Clinet_Mode();
void Bill_Mode(); 
void restock_mode();   

void SalePromotion(client* cur_cus);            // 促销界面 
void choosegift(double buy_money);



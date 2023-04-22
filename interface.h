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
#include"supplier.h" 

void LoginInterface(int position);     //登录界面
void ManagerInterface();              // 店铺管理界面 
void NewClientInterface();

void InitInterface();  
void ClientLogin();
void ManagerLogin();
void PasswordOutput();

void ManagerChooseMode();
void ManInferface(int i);
void ClientChooseMode(client* cur_cus);
int inputcheck(char numstring[]);  // 判断整数输入是否合法 

void Inventory_Mode();
void Clinet_Mode();
void Bill_Mode(); 
void restock_mode();   

void SalePromotion(client* cur_cus);            // 促销界面 
void choosegift(double buy_money);
void ShoppintcartInterface(client* cur_cus);    //购物车界面 


void ErrorHappens();
void RefreshPage();



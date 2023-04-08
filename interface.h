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

void LoginInterface();    //登录界面
void ManagerInterface(); // 店铺管理界面 
void NewClientInterface();

void InitInterface();  

void ErrorHappens();
void RefreshPage();

void ClientLogin();
void ManagerLogin();
void PasswordOutput();

void ManagerChooseMode();
void ClientChooseMode(client* cur_cus);


int inputcheck(char numstring[]);  // 判断整数输入是否合法 

void ManagerInterface_Read();    //只读模式 
void ManagerInterface_Write();    // 修改模式 

void SalePromotion();            // 促销界面 


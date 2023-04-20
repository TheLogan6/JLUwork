#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>

#include"interface.h"
#include"warehouse.h"
#include"client.h" 
#include"customer.h" 
#include"sellbill.h"
#include"shiningpoints.h"
#include"supplier.h"
 

void ManagerInput();
void Restock();

//void wornout(ProductSource* tar, int amount);

	
/*-------------------------------管理员订单售后处理-----------------*/

void aftersercive_check();        // 售后订单处理 
void agree();
void reject();     // 拒绝退换货 

void costAndprofit();
void writeprofit();
void readprofit(); 

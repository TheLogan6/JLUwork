#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>
#include"interface.h"
#include"warehouse.h"
#include"sellbill.h"

void ManagerInput();
void Restock();
void wornout(); // 随机产生

	
/*-------------------------------管理员订单售后处理-----------------*/

void aftersercive_check();        // 售后订单处理 
void agree();
void reject();     // 拒绝退换货 

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

//extern char* BillType[6] = {"待确认", "已确认", "已退货", "已换货"};
 

typedef struct Bill_Aftersales{
	struct Bill_Aftersales* pre;
	struct sell_bill*  rawbill;
	int 	type;
	int 	ifexpiration; 
	struct Bill_Aftersales* next;
}Bill_Aftersales;

void ShoppintcartInterface(client* cur_cus); // 购物车界面 

void Deleteitems();					//删除订单 
void Changequantity();

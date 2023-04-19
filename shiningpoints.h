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
#include"manager.h" 
#include"sellbill.h"
#include"supplier.h" 

//extern char* BillType[6] = {"待确认", "已确认", "已退货", "已换货"};
extern char* code[12][10];
//extern Inventory* Inv_head;
struct shopping_cart{
    int id;
    int cus_id;
    int cnt;
    int x,y,z;
    char goods_name[30];
    double single_cost,total_cost;
    struct shopping_cart*next;
};
typedef struct shopping_cart shopping_cart;

void showShoppingCart(client*cus);
void addShoppingCart(shopping_cart**p,int cnt,int cus_id,double money,int x,int y,int z);
void readShoppingCart(client**L);
void writeShoppingCart(client**L);
void delShoppingCart(client*L,int id);

typedef struct Bill_Aftersales{
	struct Bill_Aftersales* pre;
	struct sell_bill*  rawbill;
	int 	type;
	int 	ifexpiration; 
	struct Bill_Aftersales* next;
}Bill_Aftersales;

//void ShoppintcartInterface(client* cur_cus); // 购物车界面 
void ChangeNumber(client*cur_cus, int tarid);
void Deleteitems();					//删除订单 
void Changequantity();

#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>

#include"warehouse.h"
#include"customer.h" 
#include"manager.h" 
#include"sellbill.h"
#include"interface.h"


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

void ChangeNumber(client*cur_cus, int tarid);
void Deleteitems();					//É¾³ý¶©µ¥ 
void ClientInput();


void PurchaseInterface(client* cur_cus);
void PurchaseProduct(client* cur_cus, int ChooseBrand, struct sell_bill* newbill);

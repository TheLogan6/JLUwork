#pragma once
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

typedef struct supply{
	int transport_cost;
	char suppliername[50];
	struct supply *next;
}supplier,*supplierlist;
typedef struct productin{//商家进货时的商品结构体
    char commodity_name[100];//商品品牌
    int commodity_id;//商品编号,用于区分不同商品或同一商品的不同规格或口味、
    int  commodity_packagenum;//每箱商品有多少瓶
    double commodity_price;//商品单价
    int sum_price;//商品总价
    int commodity_number;//商品进货数量（箱数）
    int commodity_volume;//一瓶商品有多少毫升
    char date[50];//进货日期
    supplier* provider;
    struct productin *next;
}productin,*productlistin;





void createsupplylist();
void printsupplylist();
void generate_randomstring(char str[], int n);
int inputcheck();
void initproductinlist();
supplier* choosesupplier();
void createproductinlist();
void printfile();
void addproductinlist();
void printproductinlist();
productin* searchproductinlist(char name[100],int id);
void deleteproductinlist();
void searchproductin();
void correctproductinlist();
void damage();
void productin_interface();

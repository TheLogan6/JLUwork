#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <sys/types.h>
#include<limits.h>
#include <float.h>

#define isFiniteNumber(d)d<=DBL_MAX&&d>=-DBL_MAX

typedef struct supply{
	int transport_cost;
	char suppliername[50];
	struct supply *next;
}supplier,*supplierlist;
typedef struct productin{//商家进货时的商品结构体
    char commodity_name[100];//商品品牌
    int commodity_id;//商品编号,用于区分不同商品或同一商品的不同规格或口味、
    int  commodity_packagenum;//每箱商品有多少瓶
    double commodity_price;//每箱价格
    double sum_price;//商品总价
    int commodity_number;//商品进货数量（箱数）
    int commodity_volume;//一瓶商品有多少毫升
    char date[50];//进货日期
    supplier* provider;
    struct productin *next;
}productin,*productlistin;

productlistin L1;//进货单
supplierlist L2;

int isdate(char* date_string);
void createsupplylist();
void printsupplylist();
void generate_randomstring(char str[], int n);
void initproductinlist();
supplier* choosesupplier();
void createproductinlist();
void printproductinlist();
void printfile();
void addproductinlist();
productin* searchproductinlist(char name[100],int id);
void deleteproductinlist();
void searchproductin();
void correctproductinlist();
void damage();
void productin_interface();
int inputNum();

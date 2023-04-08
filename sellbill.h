
#pragma once

#include<stdio.h>
#include<time.h>
#include<string.h>
#include <stdbool.h>
#include<stdlib.h>

#include"customer.h"
#include"interface.h"
#include"warehouse.h" 

//宏
#define Number_Of_Brand 7
//结构体?


struct sell_bill{//卖出
    struct sell_bill* pre;
    //订单标识
    int order;//订单序号
    //时间信息(6)
    int year;                   //年
    int month;                  //月
    int day;                    //日
    int hour;                   //几时
    int minute;                 //几分
    int second;                 //几秒
    //产品标识(3)
    char brand[100];            //哪个品牌
    int number_of_brand;        //品牌编号
    int ProductNumber;			//商品编号
    int SpecificationNumber;    //规格编号
    //产品售出规格、单价、总数、总价(3)
    int packagingsize;    		//包装大小
    double Unit_Price;           //销售单价
    int volume;                 //产品容量
    int number_of_packagingzise;//这个包装的买了多少箱
    int total_number;           //卖出的总数
    double total_price;         //总价
    //卖给谁的(3)
    double discount_for_client; //对于客户来说优惠是多少
    struct sell_bill* next;
    struct customer* buyer;    //顾客的链表结点
    struct Inventory* product;
};
//全局变量?
extern char* code[12][5];
extern struct lognode *log_head;
extern struct customer* L;
extern struct sell_bill* bill_pre;
//其他函数调用?
extern bool chekBalance(struct customer** user,int number);struct Inventory* Inv_head;
extern void writeLog(struct lognode*L);
extern void addLogNode(struct lognode **l,client**L,int cus_id,int op,double money);
//我的函数调用?
struct sell_bill* find_pointer_of_given_bill(int order, struct sell_bill* head);
struct customer* Find_pointer_of_client(int id);
struct sell_bill* Initiate_Bill();						// 读取 
struct sell_bill* Sell_select_brand(int number_of_brand);    //选品牌 
void Sell_select_ProductNumber(int number, struct sell_bill* newbill);      // 
struct sell_bill* Sell_select_Number_of_goods(struct sell_bill* newbill,struct customer* user);
struct  sell_bill* Sell_confirm(struct sell_bill* newbill,struct customer* user);
void Print_Bills_Of_Given_Brand(void);           //
void Print_Bills_Of_Given_Id(void);
void Print_Bills_Of_Given_Name(void);
void Print_Bills_Of_Given_Client(void);
void Search_For_The_Bills_Of_Given_Data(void);
void Delete_Bill(void);                                  //  删除订单 
void Check_Bills(void);

void sell_save(struct sell_bill* newbill);              // 保存 


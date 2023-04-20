#pragma once

#include<stdio.h>
#include<time.h>
#include<string.h>
#include <stdbool.h>
#include<stdlib.h>

#include"customer.h"

#include"warehouse.h" 

//宏
#define Number_Of_Brand 10
#define Return_Reason_num 8
#define Exchange_Reason_num 6
//结构体?


struct sell_bill//卖出
{
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
    int id;
    double discount_for_client; //对于客户来说优惠是多少
    //状态
    int status;//取消是0，正常是1，申请换货是2，申请退货是3，已换货是4，已退货是5
    int reason_num;//原因所对应的编号
    int change_num;//退换货涉及的箱数
    struct sell_bill* next;
    struct sell_bill* related;
    struct customer* buyer;    //顾客的链表结点
    struct Inventory* product;
};
//全局变量?
//全局变量?
extern struct sell_bill* bill_with_problem;
extern char Exchange_reason[Exchange_Reason_num][50];
extern char Return_reason[Return_Reason_num][50];
extern char* code[12][10];
extern struct lognode *log_head;
extern struct customer* L;
extern struct sell_bill* bill_pre;
//其他函数调用?
extern bool chekBalance(struct customer** user,int number);struct Inventory* Inv_head;
extern void writeLog(struct lognode*L);
extern void addLogNode(struct lognode **l,client**L,int cus_id,int op,double money);
extern struct sell_bill* bill_with_problem;
//我的函数调用?

//正常订单

struct sell_bill* find_pointer_of_given_bill(int order, struct sell_bill* head);
struct customer* Find_pointer_of_client(int id);
struct sell_bill* Initiate_Bill();						// 读取
struct sell_bill* Sell_select_brand(int number_of_brand);    //选品牌
void Sell_select_ProductNumber(int number, struct sell_bill* newbill);      //
void Sell_select_Number_of_goods(struct sell_bill* newbill,struct customer* user);
int Sell_confirm(struct sell_bill* newbill,struct customer* user);
void Print_Bills_Of_Given_Brand(void);           //
int Scanf_ID(void);
int Print_Bills_Of_Given_Id(int ID_of_client);
void Search_For_The_Bills_Of_Given_Data(void);
int Delete_Bill(void);                                  //  删除订单
void Check_Bills(void);
void sell_save(struct sell_bill* newbill);              // 保存
//不正常订单

struct sell_bill* Initiate_Bill_with_problem(void);
void Exchange(struct customer* user);
void Return(struct customer* user);
void Check_Bills_with_problem(void);
void Decide_bill(void);

void writeproblembill();
void writebill();

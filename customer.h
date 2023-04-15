#pragma once

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
//#include "bill.h"
#include <sys/types.h>
#include<limits.h>
#include <float.h>
#define isFiniteNumber(d)d<=DBL_MAX&&d>=-DBL_MAX
#define enter puts("")
#define MAXN 10010
#define cout printf
#define cin scanf


struct customer{
    int id;
    int level;
    char name[20];
    float point;
    char password[10];
    double balance;
    char phoneNumber[12];
    struct customer*ne,*pre;
    struct shopping_cart* cart;
};
typedef struct customer client;

struct lognode{
    int date;
    int id;
    client *cus;
    double money;
    char event[30];
    float point;
    struct lognode*next;
};
typedef struct lognode LogNode;

extern int cus_cnt;
extern int log_cnt;
extern LogNode *log_head;
extern client *cus_head;

void changeInfo(client**L,int id);//修改用户信息
client* findClient(client**L,int id);//寻找用户
void addClient(client **L,client*p);//添加用户
void writeClientInfo(client* L);// ����ͻ���Ϣ 
void delClient(client **L,int id);//删除用户
void readClient(client** L);//从文件中读取用户信息
void printCustomer(client*L);//打印所有用户信息
bool checkPassword(client*L,int id,char *s);//检验用户密码正确性

bool recharge(client**L,LogNode **log_head,int id,double money);
//支付与检验金额正确性
bool checkBalance(client**L,double money);
//排序用户链表
void cusSort(client**L,int op);
void InitLog(LogNode**l,client**cus);
void addLogNode(LogNode **l,client**L,int cus_id,int op,double money);  // ��¼�˵��ڵ� 
void printLog(LogNode*L);
void writeLog(LogNode*L);
int checkNum();
double checkDouble();

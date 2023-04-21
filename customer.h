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

void changeInfo(client**L,int id);
client* findClient(client**L,int id);
void addClient(client **L,client*p);
void writeClientInfo(client* L);// 保存客户信息 
void delClient(client **L,int id);
void readClient(client** L);
void printCustomer(client*L);
bool checkPassword(client*L,int id,char *s);
void update(client**L,double money);
bool recharge(client**L,LogNode **log_head,int id,double money);
bool checkBalance(client**L,double money);
void cusSort(client**L,int op);
void InitLog(LogNode**l,client**cus);
void addLogNode(LogNode **l,client**L,int cus_id,int op,double money);  // 记录账单节点 
void printLog(LogNode*L);
void writeLog(LogNode*L);
void showCusInfo(client*cus,LogNode*logh); 
int checkNum();
double checkDouble();

int getchoice(int *position,int row,int *choice );

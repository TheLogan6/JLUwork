
#pragma once

#include<stdio.h>
#include<time.h>
#include<string.h>
#include <stdbool.h>
#include<stdlib.h>

#include"customer.h"
#include"interface.h"
#include"warehouse.h" 

//��
#define Number_Of_Brand 7
//�ṹ��?


struct sell_bill{//����
    struct sell_bill* pre;
    //������ʶ
    int order;//�������
    //ʱ����Ϣ(6)
    int year;                   //��
    int month;                  //��
    int day;                    //��
    int hour;                   //��ʱ
    int minute;                 //����
    int second;                 //����
    //��Ʒ��ʶ(3)
    char brand[100];            //�ĸ�Ʒ��
    int number_of_brand;        //Ʒ�Ʊ��
    int ProductNumber;			//��Ʒ���
    int SpecificationNumber;    //�����
    //��Ʒ�۳���񡢵��ۡ��������ܼ�(3)
    int packagingsize;    		//��װ��С
    double Unit_Price;           //���۵���
    int volume;                 //��Ʒ����
    int number_of_packagingzise;//�����װ�����˶�����
    int total_number;           //����������
    double total_price;         //�ܼ�
    //����˭��(3)
    double discount_for_client; //���ڿͻ���˵�Ż��Ƕ���
    struct sell_bill* next;
    struct customer* buyer;    //�˿͵�������
    struct Inventory* product;
};
//ȫ�ֱ���?
extern char* code[12][5];
extern struct lognode *log_head;
extern struct customer* L;
extern struct sell_bill* bill_pre;
//������������?
extern bool chekBalance(struct customer** user,int number);struct Inventory* Inv_head;
extern void writeLog(struct lognode*L);
extern void addLogNode(struct lognode **l,client**L,int cus_id,int op,double money);
//�ҵĺ�������?
struct sell_bill* find_pointer_of_given_bill(int order, struct sell_bill* head);
struct customer* Find_pointer_of_client(int id);
struct sell_bill* Initiate_Bill();						// ��ȡ 
struct sell_bill* Sell_select_brand(int number_of_brand);    //ѡƷ�� 
void Sell_select_ProductNumber(int number, struct sell_bill* newbill);      // 
struct sell_bill* Sell_select_Number_of_goods(struct sell_bill* newbill,struct customer* user);
struct  sell_bill* Sell_confirm(struct sell_bill* newbill,struct customer* user);
void Print_Bills_Of_Given_Brand(void);           //
void Print_Bills_Of_Given_Id(void);
void Print_Bills_Of_Given_Name(void);
void Print_Bills_Of_Given_Client(void);
void Search_For_The_Bills_Of_Given_Data(void);
void Delete_Bill(void);                                  //  ɾ������ 
void Check_Bills(void);

void sell_save(struct sell_bill* newbill);              // ���� 


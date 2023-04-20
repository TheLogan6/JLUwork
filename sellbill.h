#pragma once

#include<stdio.h>
#include<time.h>
#include<string.h>
#include <stdbool.h>
#include<stdlib.h>

#include"customer.h"

#include"warehouse.h" 

//��
#define Number_Of_Brand 10
#define Return_Reason_num 8
#define Exchange_Reason_num 6
//�ṹ��?


struct sell_bill//����
{
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
    int id;
    double discount_for_client; //���ڿͻ���˵�Ż��Ƕ���
    //״̬
    int status;//ȡ����0��������1�����뻻����2�������˻���3���ѻ�����4�����˻���5
    int reason_num;//ԭ������Ӧ�ı��
    int change_num;//�˻����漰������
    struct sell_bill* next;
    struct sell_bill* related;
    struct customer* buyer;    //�˿͵�������
    struct Inventory* product;
};
//ȫ�ֱ���?
//ȫ�ֱ���?
extern struct sell_bill* bill_with_problem;
extern char Exchange_reason[Exchange_Reason_num][50];
extern char Return_reason[Return_Reason_num][50];
extern char* code[12][10];
extern struct lognode *log_head;
extern struct customer* L;
extern struct sell_bill* bill_pre;
//������������?
extern bool chekBalance(struct customer** user,int number);struct Inventory* Inv_head;
extern void writeLog(struct lognode*L);
extern void addLogNode(struct lognode **l,client**L,int cus_id,int op,double money);
extern struct sell_bill* bill_with_problem;
//�ҵĺ�������?

//��������

struct sell_bill* find_pointer_of_given_bill(int order, struct sell_bill* head);
struct customer* Find_pointer_of_client(int id);
struct sell_bill* Initiate_Bill();						// ��ȡ
struct sell_bill* Sell_select_brand(int number_of_brand);    //ѡƷ��
void Sell_select_ProductNumber(int number, struct sell_bill* newbill);      //
void Sell_select_Number_of_goods(struct sell_bill* newbill,struct customer* user);
int Sell_confirm(struct sell_bill* newbill,struct customer* user);
void Print_Bills_Of_Given_Brand(void);           //
int Scanf_ID(void);
int Print_Bills_Of_Given_Id(int ID_of_client);
void Search_For_The_Bills_Of_Given_Data(void);
int Delete_Bill(void);                                  //  ɾ������
void Check_Bills(void);
void sell_save(struct sell_bill* newbill);              // ����
//����������

struct sell_bill* Initiate_Bill_with_problem(void);
void Exchange(struct customer* user);
void Return(struct customer* user);
void Check_Bills_with_problem(void);
void Decide_bill(void);

void writeproblembill();
void writebill();

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
typedef struct productin{//�̼ҽ���ʱ����Ʒ�ṹ��
    char commodity_name[100];//��ƷƷ��
    int commodity_id;//��Ʒ���,�������ֲ�ͬ��Ʒ��ͬһ��Ʒ�Ĳ�ͬ�����ζ��
    int  commodity_packagenum;//ÿ����Ʒ�ж���ƿ
    double commodity_price;//��Ʒ����
    int sum_price;//��Ʒ�ܼ�
    int commodity_number;//��Ʒ����������������
    int commodity_volume;//һƿ��Ʒ�ж��ٺ���
    char date[50];//��������
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

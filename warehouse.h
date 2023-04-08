#pragma once
#define pau system("pause")
#include"interface.h"
#include<stdio.h>
#include<stdlib.h> 
#include<time.h>

typedef struct Inventory{                                  // ���ṹ��
	struct  Inventory* pre;             
	char	DrinksBrand[20];                              // ��ˮƷ��      
	int     BrandNumber;								//��ˮƷ�Ʊ��  
	int  	ProductNumber;									//��Ʒ��� 
	int     SpecificationNumber;								//����� 
	int     volume;                                       // ��ˮ������С 
	int 	Reserve;										//��Ʒ��� 
	int     packagingsize;    								//��װ��С 
	int     quality_year, quality_month, quality_day;            //�������� 
	float   Price;                                        // ���ۼ۸�  
	
	struct Inventory* next;                        
}Inventory;

typedef struct ProductSource{							//��Դ�ṹ�� 
	struct  ProductSource*  pre;         
	char    DrinksBrand_sou[20];
	int     BrandNumber_sou;                        
	int     ProductNumber_sou;		
	int     SpecificationNumber_sou;								//����� 				
	int     volume_sou;                                       
	int     packagingsize_sou;    	
	float   Price_sou;             
	int     quality_year_sou, quality_month_sou, quality_day_sou;     // ������                          
	struct  ProductSource* next;
}ProductSource;

typedef struct SpecialInv{
	struct SpecialInv* pre;
	Inventory* Pro;
	double SpecialPrice;
	struct SpecialInv* next;
}SpecialInv; 

void encode_product();
/*---------------------------------������---------------------------------*/ 

Inventory* InitInventory();        //(��ʼ��)���ֿ�  �޸Ĳֿ����� 
void PrintInventory(Inventory* Inv_head);

void ChangeInventory();               //�޸Ĳֿ���Ʒ��Ϣ
Inventory* FindInventory(int Brand, int Specification);  // ������Ʒ 
void UpdateInventory();					//�����޸���Ϣ 
void AddNewinventory(Inventory* newInv);      // �����²�Ʒ��Ϣ 

void InventorySortMode(); 								//���ѡ�� 
void SortByNumber(Inventory* Inv_head);                  // ��������� 
void SortByReserve(Inventory* Inv_head);              // ����������� 
void SortByPrice(Inventory* Inv_head);                // ���۸����� 

int countSpecification(int Brand); 

/* --------------------------------- �ؼ���Ʒ����----------------------------------*/
SpecialInv* InitSpecialInv(); 
void PrintSpecialInv();

/* --------------------------------- ��Դ����----------------------------------*/ 

ProductSource* ReadSource();
void PrintSource(ProductSource* Sou_head);
int countSpecification_sou(int Brand); 
ProductSource* FindSource(int Brand, int Specification);

#pragma once
#define pau system("pause")
#include"interface.h"
#include<stdio.h>
#include<stdlib.h> 
#include<time.h>

typedef struct Inventory{                                  // 库存结构体
	struct  Inventory* pre;             
	char	DrinksBrand[100];                              // 酒水品牌      
	int     BrandNumber;								//酒水品牌编号  
	int  	ProductNumber;									//商品编号 
	int     SpecificationNumber;								//规格编号 
	int     volume;                                       // 酒水容量大小 
	int 	Reserve;										//商品库存 
	int     packagingsize;    								//包装大小 
	int     quality_year, quality_month, quality_day;            //保质日期 
	float   Price;                                        // 销售价格  
	
	int 	nearexpiry;                                     //是否临期               
	struct  Inventory* next;                        
}Inventory;

typedef struct ProductSource{							//货源结构体 
	struct  ProductSource*  pre;         
	char    DrinksBrand_sou[20];
	int     BrandNumber_sou;                        
	int     ProductNumber_sou;		
	int     SpecificationNumber_sou;								//规格编号 				
	int     volume_sou;                                       
	int     packagingsize_sou;    	
	float   Price_sou;             
	int     quality_year_sou, quality_month_sou, quality_day_sou;     // 保质期                          
	struct  ProductSource* next;
}ProductSource;

//typedef struct SpecialInv{
//	struct SpecialInv* pre;
//	Inventory* Pro;                     //直接指向库存 
////	double SpecialPrice;                
//	struct SpecialInv* next;
//}SpecialInv; 

typedef struct Gift{
	struct Gift* pre;
	int 	reorder;                                 // 重编号 
	int 	brand, product;         // 确立唯一一个商品 
	int     gif_volume; 
	int 	bottle;									//用瓶来管理 
	int     gif_year, gif_month, gif_day;
	float   value;                                // 粗略赠品价值 
	struct Gift* next;
}Gift;

void encode_product();
/*-----------------------------------库存操作---------------------------------*/ 

Inventory* InitInventory();               //(初始化)读仓库  修改仓库内容 
void PrintInventory(Inventory* Inv_head);

void ChangeInventory();                       //修改仓库商品信息
Inventory* FindInventory(int Brand, int Specification);  // 查找商品 
void UpdateInventory();				           	//保存修改信息 
void AddNewinventory(Inventory* newInv);      // 增加新产品信息 

void InventorySortMode(); 								//库存选择 
void SortByNumber(Inventory* Inv_head);                  // 按编号排序 
void SortByReserve(Inventory* Inv_head);              // 按库存量排序 
void SortByPrice(Inventory* Inv_head);                // 按价格排序 
int countSpecification(int Brand); 

/* --------------------------------- 特价商品操作----------------------------------*/
//SpecialInv* InitSpecialInv(); 

void PrintSpecialInv();
void JudgeNearexpiry();

/* --------------------------------- 货源操作----------------------------------*/ 

ProductSource* ReadSource();
void PrintSource(ProductSource* Sou_head);
int countSpecification_sou(int Brand); 
ProductSource* FindSource(int Brand, int Specification);

/*-------------------------------- 赠品操作---------------------------*/
void addintogift(); 

Gift* InitGift(); 
void PrintGift();
void UpdateGift();	    //赠品写刷新 

void wornout(ProductSource* tar, int amount); // 随机产生

/*-------------------------------管理员订单售后处理-----------------*/
void agree();      // 同意退换货
void reject();     // 拒绝退换货 

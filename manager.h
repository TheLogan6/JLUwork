#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>

#include"interface.h"
#include"warehouse.h"
#include"client.h" 
#include"customer.h" 
#include"sellbill.h"
#include"shiningpoints.h"
#include"supplier.h"
 

void ManagerInput();
void Restock();

//void wornout(ProductSource* tar, int amount);

	
/*-------------------------------����Ա�����ۺ���-----------------*/

void aftersercive_check();        // �ۺ󶩵����� 
void agree();
void reject();     // �ܾ��˻��� 

void costAndprofit();
void writeprofit();
void readprofit(); 

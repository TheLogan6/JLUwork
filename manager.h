#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>
#include"interface.h"
#include"warehouse.h"
#include"sellbill.h"

void ManagerInput();
void Restock();
void wornout(); // �������

	
/*-------------------------------����Ա�����ۺ���-----------------*/

void aftersercive_check();        // �ۺ󶩵����� 
void agree();
void reject();     // �ܾ��˻��� 

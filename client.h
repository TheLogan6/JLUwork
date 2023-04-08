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
#include"customer.h" 

void ClientInput();
void PurchaseInterface(client* cur_cus);

void PurchaseProduct(client* cur_cus, int ChooseBrand, struct sell_bill* newbill);

#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>

#include"warehouse.h"
#include"customer.h" 
#include"manager.h" 
#include"sellbill.h"
#include"shiningpoints.h"
#include"supplier.h" 
#include"interface.h"

void ClientInput();
void PurchaseInterface(client* cur_cus);

void PurchaseProduct(client* cur_cus, int ChooseBrand, struct sell_bill* newbill);

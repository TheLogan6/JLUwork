#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>
#include"interface.h"
#include"warehouse.h" 
#include"client.h"
#include"manager.h"
#include"customer.h"
#include"sellbill.h"
#include"shiningpoints.h" 

//全局变量区
char* code[12][5];
char* BillType[6];
Inventory* Inv_head;
SpecialInv* SpeInv_head;
ProductSource* Sou_head;
client* L;//没有哨位节点 
LogNode* log_head;
int cus_cnt;
int log_cnt;
client *cus_head;
struct sell_bill* bill_pre;

int total_brand;    // 产品的品牌总数 
const int passwordans = 123456;
double total_money = 50000.00;    //  


//end 全局变量 

int main(int argc, char *argv[]) {
	encode_product();
	Inv_head = InitInventory();
	readClient(&L);
	InitLog(&log_head,&L);
	Sou_head = ReadSource();

	bill_pre = Initiate_Bill(); 
	total_brand = 7; 

	SpeInv_head = InitSpecialInv();
//	PrintSpecialInv();
//	pau;
	while(1)                //用作返回上一级 
	{
        system("cls"); 
		LoginInterface();
        char ChooseLogin_s[10];
        system("taskkill /im process.exe>nul 2>nul");
        scanf("%s", ChooseLogin_s);
        int ChooseLogin = inputcheck(ChooseLogin_s);
        switch(ChooseLogin){
            case(1) : {
                ClientInput();
                break;
            }
            case(2) : {
                ManagerInput();
                break;
            }
            case(3) : {
                addClient(&L,NULL); 
                writeClientInfo(L);
                pau;
                break;
            }
            case(4):{
            	return 0;
				break;
			}
            default:{
//            	ErrorHappens(); 
            	RefreshPage();
				break;
			}
            	
        }
	}
	return 0;
}


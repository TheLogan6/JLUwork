#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>
#include<conio.h>
#include"interface.h"
#include"warehouse.h" 
#include"client.h"
#include"manager.h"
#include"customer.h"
#include"sellbill.h"
#include"shiningpoints.h" 
#include"supplier.h" 

//全局变量区
char Exchange_reason[Exchange_Reason_num][50]={"不喜欢","商品与描述不符","产品过期","商品少件","商品破损","发错货物"};
char Return_reason[Return_Reason_num][50]={"不想要了","不喜欢","商品与描述不符","产品过期","质量问题","商品少件","商品破损","发错货物"};
char* code[12][5];
char* BillType[6];
Inventory* Inv_head;                // 库存商品 
//SpecialInv* SpeInv_head;             // 特价商品 
ProductSource* Sou_head;            // 货源结构体 
client* L;                         //客户节点 没有哨位节点 
LogNode* log_head;                 //  
int cus_cnt;  
int log_cnt;
//client *cus_head;
struct sell_bill* bill_pre;            //有哨位节点 
struct sell_bill* bill_with_problem;  // 有哨位节点 

int total_brand;    // 产品的品牌总数 
char passwordans[20] = "123456";
double total_money = 50000.00;    //  


//end 全局变量 

int main(int argc, char *argv[]) {
	encode_product();
	Inv_head = InitInventory();
	readClient(&L);
	InitLog(&log_head,&L);
	Sou_head = ReadSource();
	bill_pre = Initiate_Bill(); 
	//initproductinlist();
	//createproductinlist();
	total_brand = 7; 
	readShoppingCart(&L);	
	JudgeNearexpiry();

	bill_with_problem=Initiate_Bill_with_problem();
	while(1)                //用作返回上一级 
	{
        system("cls"); 
	
        char ChooseLogin_s[10];
//       system("taskkill /im process.exe>nul 2>nul");
//        scanf("%s", ChooseLogin_s);
//        int ChooseLogin = inputcheck(ChooseLogin_s);
	int ChooseLogin;
    int position=0;int row=4;
	while(1){
		system("cls");
		LoginInterface(position);
		char ch=getch();
		if(ch=='w'){
			position=(position-1+row)%row;
		}
		if(ch=='s')position=(position+1)%row;
		if(ch=='\r'){
			ChooseLogin=position+1;
			break;
		};
	}
        switch(ChooseLogin){
            case(1) : {
                ClientInput();
                break;
            }
            case(2) : {
                ManagerInput();
                break;
            }
            case(3) : { //新用户添加 
                addClient(&L,NULL); 
                writeClientInfo(L);
                pau;
                break;
            }
            case(4):{ // 退出程序 
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


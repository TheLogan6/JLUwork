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

//ȫ�ֱ�����
char Exchange_reason[Exchange_Reason_num][50]={"��ϲ��","��Ʒ����������","��Ʒ����","��Ʒ�ټ�","��Ʒ����","�������"};
char Return_reason[Return_Reason_num][50]={"����Ҫ��","��ϲ��","��Ʒ����������","��Ʒ����","��������","��Ʒ�ټ�","��Ʒ����","�������"};
char* code[12][5];
char* BillType[6];
Inventory* Inv_head;                // �����Ʒ 
//SpecialInv* SpeInv_head;             // �ؼ���Ʒ 
ProductSource* Sou_head;            // ��Դ�ṹ�� 
client* L;                         //�ͻ��ڵ� û����λ�ڵ� 
LogNode* log_head;                 //  
int cus_cnt;  
int log_cnt;
//client *cus_head;
struct sell_bill* bill_pre;            //����λ�ڵ� 
struct sell_bill* bill_with_problem;  // ����λ�ڵ� 

int total_brand;    // ��Ʒ��Ʒ������ 
char passwordans[20] = "123456";
double total_money = 50000.00;    //  


//end ȫ�ֱ��� 

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
	while(1)                //����������һ�� 
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
            case(3) : { //���û���� 
                addClient(&L,NULL); 
                writeClientInfo(L);
                pau;
                break;
            }
            case(4):{ // �˳����� 
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


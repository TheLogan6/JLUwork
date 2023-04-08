#include"interface.h"

extern Inventory* Inv_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][5]; 
extern SpecialInv* SpeInv_head;
extern int total_brand;
void LoginInterface(){
	system("cls");
    system("color B4"); // B天蓝色   4：红色字 
    printf("\n\n\n\n");
    printf("\t\t\t\t\t-------------登录界面----------------\n");
    printf("\t\t\t\t\t          (1).客户登录               \n");
    printf("\t\t\t\t\t          (2).管理员登录             \n");
    printf("\t\t\t\t\t          (3).新客户注册             \n");
    printf("\t\t\t\t\t          (4).退出系统               \n");
    printf("\t\t\t\t\t-------------------------------------\n");
    printf("\t\t\t\t请选择你要进行的服务：（1-4）:");
}

void ClientLogin(){
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t-----------用户登录界面----------------\n");
	printf("\t\t\t\t\t    (在账号输入处输入0可以返回上一个界面)\n");
    printf("\t\t\t\t\t 请输入您的账号：");
}

void ManagerLogin(){
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t-----------管理员登录界面----------------\n");
	printf("\t\t\t\t\t     (输入0可以返回上一个界面)\n");
    printf("\t\t\t\t\t 请输入管理者密钥：");
} 

void PasswordOutput(){
	printf("\t\t\t\t\t 请输入您的密码：");
} 

 

void NewClientInterface(){
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t-----------新用户注册界面----------------\n");
    printf("\t\t\t\t\t   您的账号是：");
}
 
/*-------------------------------管理者界面---------------------*/ 
void ManagerChooseMode(){
	while(1)
	{
		system("cls");
		Sleep(300);
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------店铺管理界面----------------\n");
		printf("\t\t\t\t\t     (输入0可以返回上一个界面)\n");
		printf("\t\t\t\t\t       1. 信息查询模式(只读)\n");
		printf("\t\t\t\t\t       2. 信息修改模式\n"); 
		printf("\t\t\t\t\t       3. 进货模式\n");
		printf("\t\t\t\t       请输入你要选择的服务：");
		int Mana_mode;
		char Mana_mode_s[5];
		scanf("%s", Mana_mode_s);
		Mana_mode = inputcheck(Mana_mode_s);
		if(Mana_mode == -1){
			RefreshPage();
			continue;
		}
		if(Mana_mode == 0)
			break;
		switch(Mana_mode){ // 信息查询模式 
			case(1):{
				ManagerInterface_Read();
				break;
			}
			case(2):{
				ManagerInterface_Write();
				break;
			}
			case(3):{
				Restock();
				break;
			}
		
		}
	}
	
}

void ManagerInterface_Read(){	
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------店铺管理界面(查询模式)----------------\n");
		printf("\t\t\t\t\t   (输入0可以返回上一个界面)\n");
		printf("\t\t\t\t\t (1). 查看仓库货品清单\n");
		printf("\t\t\t\t\t (2). 查看客户信息\n"); 
		printf("\t\t\t\t\t (3). 查看销售订单\n");
		printf("\t\t\t\t\t (4). 查看进货订单\n");
		printf("\t\t\t\t\t (5).  订单查询\n");
		printf("\t\t\t\t\t (10). 查看机器建议？\n");
		printf("\t\t\t\t 请输入你想要进行的服务：(1-6)");
		
		int ManagerOp;
//		ManagerInterface();
		char ManagerOp_s[5];
		scanf("%s", ManagerOp_s);
		ManagerOp = inputcheck(ManagerOp_s);
		if(ManagerOp == -1 || ManagerOp > 10){
			RefreshPage();
			continue;
		}		
		switch(ManagerOp){
			case(0): return;
			case(1):{//查看仓库货品清单
				system("cls");
				InventorySortMode();
				break;
			}
			case(2):{//查看客户信息
				printCustomer(L);
				pau; 
				break;
			} 
			case(3):{ //查看销售订单
				Check_Bills();
				pau;
				break;
			}
			case(4):{// 查看进货订单 
				
				pau;
				break;
			}
			case(5):{//修改客户信息 
				Search_For_The_Bills_Of_Given_Data();
				pau;
				break;
			}
			case(6):{// 用户充值
				
				
			}
			case(9):{
				
			} 
			default:{
				ErrorHappens();
				break;
			}
		}
	}
} 

void ManagerInterface_Write(){	
	while(1)
	{
		system("cls");
		Sleep(300);
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------店铺管理界面(修改模式)----------------\n");
		printf("\t\t\t\t\t   (输入0可以返回上一个界面)\n");
		printf("\t\t\t\t\t (1). 修改仓库商品信息\n");
		printf("\t\t\t\t\t (2). 修改客户信息\n");
		printf("\t\t\t\t\t (3). 客户充值\n");
		printf("\t\t\t\t\t (4). 删除销售订单\n");
		printf("\t\t\t\t\t (5). 修改进货订单\n");
		printf("\t\t\t\t\t (10). 查看机器建议？\n");
		printf("\t\t\t\t 请输入你想要进行的服务：(1-6)");
		int ManagerOp;
		char ManagerOp_s[5];
		scanf("%s", ManagerOp_s);
		ManagerOp = inputcheck(ManagerOp_s);
		if(ManagerOp == -1 || ManagerOp > 10){
			RefreshPage();
			continue;
		}		
		switch(ManagerOp){
			case(0): return;
			case(1):{//改变仓库商品信息 
				ChangeInventory(); 
				break;
			} 
			case(2):{//修改客户信息 
				system("cls");
				char tempid_s[5];
				int tempid;
				printf("请输入您的id:");
				scanf("%s", tempid_s);
				tempid = inputcheck(tempid_s);
				if(tempid == -1){
					RefreshPage();
					continue;
				}	
				changeInfo(&L, tempid);
				writeClientInfo(L);
				pau;
				break;
			}
			case(3):{// 用户充值
				int tempid;
				double tempmoney;
				printf("请输入用户id：");
				while(1)
				{
					char tempid_s[5];
					printf("请输入您的id:");
					scanf("%s", tempid_s);
					tempid = inputcheck(tempid_s);
					if(tempid == -1){
						RefreshPage();
						continue;
					}		
					client* p=findClient(&L, tempid); 
					if(!p) continue;
					printf("请输充值金额：");
					scanf("%lf", &tempmoney);
					if(!recharge(&p, NULL, tempid, tempmoney)) ErrorHappens();
					else break;
					writeClientInfo(L);
					pau;
					break;
				}
				
			}
			case(4):{//删除订单 
				system("cls");
				Delete_Bill();

				pau;
				break;
			}
			case(5):{

				pau;
				break;
			} 
			default:{
				ErrorHappens();
				break;
			}
		}
	}	
		
		
}


/*-------------------------------客户界面---------------------*/ 
void ClientChooseMode(client* cur_cus){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t-------------客户界面----------------\n");
		printf("\t\t\t\t\t     (输入0可以返回上一个界面)\n");
		printf("\t\t\t\t\t       1.   批发\n");
		printf("\t\t\t\t\t       2. 查询历史订单\n"); 
		printf("\t\t\t\t\t       3.  售后服务\n"); 
		printf("\t\t\t\t\t       4.  购物车\n"); 
		printf("\t\t\t\t\t       5. 临期商品大促销\n"); 
		printf("\t\t\t\t       请输入你要选择的服务：");
		int Cli_mode;
		char Cli_mode_s[5];
		scanf("%s", Cli_mode_s);
		Cli_mode = inputcheck(Cli_mode_s);
		if(Cli_mode == -1){
			RefreshPage();
			continue;
		}
		if(Cli_mode == 0)
			break;
		switch(Cli_mode){
			case(1):{
				PurchaseInterface(cur_cus);
				break;
			}
			case(2):{
				//查询历史订单 
				break;
			}
			case(3):{
				// 售后服务 
				break;
			}
			case(4):{ // 购物车界面 
				
				break;
			}
			case(5):{ // 临期商品 
				SalePromotion();
				break;
			}
		
		}
		
	}
	
}
/* ------------------------------------------- 促销界面-------------------------------------------*/
void SalePromotion(){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t-------------促销界面----------------\n");
		printf("\t\t\t\t\t     (输入0可以返回上一个界面)\n");
		PrintSpecialInv(); 
		printf("\t\t\t\t       请输入你要选择的服务：");
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		scanf("%s", ChooseBrand_s);
		ChooseBrand = inputcheck(ChooseBrand_s);
		if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		if(ChooseBrand == 0) return ;
		printf("\n\t\t\t\t请选择你要批发的产品编号：");
		scanf("%s", ChooseProduct_s);
		ChooseProduct = inputcheck(ChooseProduct_s);
		if(ChooseProduct == -1){
			RefreshPage();
			continue;
		}
		else if(ChooseProduct == 0) return;
		SpecialInv* p = SpeInv_head->next;
		while(p)
		{
			if(p->Pro->BrandNumber == ChooseBrand && p->Pro->SpecificationNumber == ChooseProduct){
				break;
			}
			p = p->next;
		}
		if(p){
			RefreshPage();
			continue;
		}
		int  buy_amount;
		char buy_amount_s[5]; 
		printf("\n\t\t\t\t请选择你要批发的数量(单次不得超过100箱)：");
		scanf("%s", buy_amount_s);
		buy_amount = inputcheck(buy_amount_s);
		if(buy_amount == -1 || buy_amount > 100){
			RefreshPage();
			continue;
		}
		else if(buy_amount == 0) return;
		ProductSource* tar_sou = FindSource(ChooseBrand, ChooseProduct);
		if(tar_sou == NULL){
			RefreshPage();
			continue;
		}
		double buy_money;
		buy_money = buy_amount * tar_sou->Price_sou;
		printf("\t\t您已成功购买%s品牌的%s%d箱,",tar_sou->DrinksBrand_sou, code[tar_sou->BrandNumber_sou][tar_sou->ProductNumber_sou], buy_amount);
		printf(" 每箱%d瓶, 每瓶%d毫升！\n", tar_sou->packagingsize_sou, tar_sou->volume_sou);
		printf("\t\t\t 共计%.2f元!\n", buy_money);
		
		system("pause");
	}
	
	
} 



/*------------------------------------------其他功能----------------------------------------------*/
 
void ErrorHappens(){
	printf("\n\t\t\t\t 您的输入有误, 请重新输入："); 
}


void RefreshPage(){
	printf("\n\t\t\t\t 您的输入不符合规范，按任意键可刷新界面！\n");
	system("pause");
} 

int inputcheck(char numstring[]){
	int n = strlen(numstring);
	if(n > 20) return -1;
	int ans = 0;
	for(int i = 0; i < n; i++)
	{
		if(numstring[i] > '9' || numstring[i] < '0') return -1;
		else ans = ans*10 + (int)(numstring[i] - '0');
	}
	return ans;
} 

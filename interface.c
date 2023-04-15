#include"interface.h"

extern Inventory* Inv_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][5]; 
//extern SpecialInv* SpeInv_head;
extern int total_brand;
void LoginInterface(){
	system("cls");
    system("color B4"); // B天蓝色   4：红色字 
    printf("\n\n\n\n"); 
    printf("\t\t\t\t\t          欢迎使用酒水管理系统！\n");
    Sleep(300);
    printf("\t\t\t\t\t--------------登录界面----------------\n");
    Sleep(100);
    printf("\t\t\t\t\t|          (1). 客户登录             |\n");
    Sleep(100);
    printf("\t\t\t\t\t|          (2).管理员登录            |\n");
    Sleep(100);
    printf("\t\t\t\t\t|          (3).新客户注册            |\n");
    Sleep(100);
    printf("\t\t\t\t\t|          (4).退出系统              |\n");
    Sleep(100);
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
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------店铺管理界面----------------\n");
		printf("\t\t\t\t\t     (输入0可以返回上一个界面)\n");
		printf("\t\t\t\t\t       1. 信息查询模式(只读)\n");
		printf("\t\t\t\t\t       2. 信息修改模式\n"); 
		printf("\t\t\t\t\t       3. 进货模式\n");
		printf("\t\t\t\t\t       4. 用户订单处理\n");
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
				ManagerInterface_Read();       // 只读模式 
				break;
			}
			case(2):{
				ManagerInterface_Write();       // 修改模式 
				break;
			}
			case(3):{
				Restock();                    // 进货流程 
				break;
			}
			case(4):{
				aftersercive_check();                // 用户订单处理 
				pau;
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
				//printproductinlist();
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
		printf("\t\t\t\t\t (6). 删除进货订单\n");
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
					if(!recharge(&p, &log_head, tempid, tempmoney)) ErrorHappens();
					else{
						 printf("\t\t\t\t您已充值成功，本次充值金额：%lf",tempmoney);
						 writeClientInfo(L);
						 pau;
						 break;
				}
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
			case(6):{
				system("cls");
				//deleteproductinlist();
				break;
			} 
			default:{
				ErrorHappens();
				break;
			}
		}
	}	
		
		
}


/*------------------------------------------客户界面------------------------------------*/ 
void ClientChooseMode(client* cur_cus){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t-------------客户界面----------------\n");
		printf("\t\t\t\t\t     (输入0可以返回上一个界面)\n");
		printf("\t\t\t\t\t       1.   批发\n");
		printf("\t\t\t\t\t       2. 查询历史订单\n"); 
		printf("\t\t\t\t\t       3.  商品换货\n"); 
		printf("\t\t\t\t\t       4.  商品退货\n"); 
		printf("\t\t\t\t\t       5.  购物车\n"); 
		printf("\t\t\t\t\t       6. 临期商品大促销\n"); 

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
				Print_Bills_Of_Given_Id(cur_cus->id);
				pau;
				break;
			}
			case(3):{
				Exchange(cur_cus);
				break;
			}
			case(4):{  // 商品退货 
				Return(cur_cus);
				break;
			}
			case(5):{  // 购物车界面
				ShoppintcartInterface(cur_cus);
				break;
			}
			case(6):{ // 临期商品促销 
				SalePromotion(cur_cus);
				break;
			}
			
		
		}
		
	}
	
}
/* ------------------------------------------- 促销界面-------------------------------------------*/
void SalePromotion(client* cur_cus){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t-----------------促销界面----------------\n");
		printf("\t\t\t\t\t    (在品牌编号出输入0可直接返回上一个界面)\n");
		PrintSpecialInv(); 
		printf("\t\t\t\t       请输入你要选择的品牌编号：");
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		scanf("%s", ChooseBrand_s);
		ChooseBrand = inputcheck(ChooseBrand_s);
//		PrintInventory(Inv_head->next);
//		pau;
		Inventory* q = Inv_head->next;
		while(q)
		{
			if(q->BrandNumber == ChooseBrand && q->nearexpiry == 1) break;
			q = q->next;
		}
		if(ChooseBrand == 0) return ;
		if(ChooseBrand == -1){
			RefreshPage();
			continue;
		}
		else if(q == NULL){
			printf("\t\t未找到该促销商品，您的输入有误，请在页面刷新后重新输入！"); 
			pau;
			continue;
		}	
		printf("\n\t\t\t\t请选择正在促销中的产品编号：");
		scanf("%s", ChooseProduct_s);
		ChooseProduct = inputcheck(ChooseProduct_s);
		if(ChooseProduct == -1){
			RefreshPage();
			continue;
		}
		Inventory* tar = Inv_head->next;
		while(tar)
		{
			if(tar->BrandNumber == ChooseBrand && tar->SpecificationNumber == ChooseProduct && tar->nearexpiry == 1)
				break;
			tar = tar->next;
		}
		if(tar == NULL)
		{
			printf("\t\t未找到该促销商品，您的输入有误，请在页面刷新后重新输入！"); 
			pau;
			continue;
		}
		int  buy_amount;
		char buy_amount_s[5]; 
		printf("\n\t\t\t\t请选择你要批发的数量(单次不得超过100箱)：");
		scanf("%s", buy_amount_s);
		buy_amount = inputcheck(buy_amount_s);
		if(buy_amount == -1  || buy_amount == 0 ){
			RefreshPage();
			continue;
		}
		if( buy_amount > 100 || tar->Reserve < buy_amount)
		{
			printf("\t\t您输入的商品数量不符合规范，请按任意键刷新后重新输入！\n"); 
			pau;
			continue;
		}
		double buy_money;
		buy_money = buy_amount * tar->Price;
		printf("-------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t              支付选择          \n"); 
		printf("\t\t\t\t\t 1. 现金支付\n");
		printf("\t\t\t\t\t 2. 余额支付\n");
		printf("\t\t\t\t\t 3. 加入购物车\n");
		printf("\t\t\t\t\t 4. 取消本次购买\n"); 
		printf("\t\t\t\t\t请选择您支付方式: ");
		int paychoice;
		char paychoice_s[5];
		scanf("%s", paychoice_s);
		paychoice = inputcheck(paychoice_s);
		if(paychoice == -1){
			RefreshPage();
			continue;
		}
		switch(paychoice){
			case(1):{
				struct sell_bill *newbill = (struct sell_bill *) malloc(sizeof(struct sell_bill));
				newbill->next = NULL;
    			newbill->pre = NULL;
    			Inventory* tar = Inv_head->next;
				while(tar)
				{
					if(tar->BrandNumber == ChooseBrand && tar->SpecificationNumber == ChooseProduct && tar->nearexpiry == 1)
						break;
					tar = tar->next;
				}
				strcpy(newbill->brand,tar->DrinksBrand);
				newbill->number_of_brand = tar->BrandNumber;
				newbill->ProductNumber = tar->ProductNumber;
				newbill->SpecificationNumber = tar->SpecificationNumber;
				newbill->packagingsize = tar->packagingsize;
				newbill->Unit_Price = tar->Price;
				newbill->volume = tar->volume;
				newbill->number_of_packagingzise = tar->packagingsize;
				newbill->total_number = buy_amount;
				newbill->total_price = buy_money;
				if (cur_cus->level == 1) {
			        newbill->discount_for_client = 0.98;
			    }
			    else if (cur_cus->level == 2) {
			        newbill->discount_for_client = 0.95;
			    }
			    else if (cur_cus->level == 3) {
			        newbill->discount_for_client = 0.90;
			    }
			    newbill->buyer = cur_cus;
			    newbill->status = 1;
				printf("\n\t\t\t\t现金支付成功！\n");
				printf("\t\t\t您已成功购买%s品牌的%s%d箱,",code[tar->BrandNumber][0], code[tar->BrandNumber][tar->ProductNumber], buy_amount);
				printf("每箱%d瓶, 每瓶%d毫升！\n", tar->packagingsize, tar->volume);
				printf("\t\t\t\t 共计%.2f元!\n", buy_money);
				sell_save(newbill);
				break;
			}
			case(2):{
				printf("\n\t\t\t余额支付成功！\n");
				printf("\t\t您已成功购买%s品牌的%s%d箱,",code[tar->BrandNumber][0], code[tar->BrandNumber][tar->ProductNumber], buy_amount);
				printf(" 每箱%d瓶, 每瓶%d毫升！\n", tar->packagingsize, tar->volume);
				printf("\t\t\t 共计%.2f元!\n", buy_money);
				system("pause");
				break;
			}
			case(3):{// 加入购物车 
				addShoppingCart(&cur_cus->cart,buy_amount,cur_cus->id,tar->Price,tar->BrandNumber, tar->ProductNumber, tar->SpecificationNumber); 
				writeShoppingCart(&L);
				printf("\n\t\t\t已成功加入购物车!"); 
				break;
			} 
			case(4):{
				printf("\n\t\t\t 您已成功取消本次购买！");
				printf("\n\t\t   按任意键可刷新本次界面!");
				pau;
				continue;
				break;
			}
			default:{
				RefreshPage();
				pau;
				break;
			}
		}
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



/*-------------------------------购物车界面-----------------------------------*/
void ShoppintcartInterface(client* cur_cus){          // 当前客户信息 
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------购物车界面----------------\n");
		printf("\t\t\t\t\t    (输入0可以返回客户界面)\n");	
		showShoppingCart(cur_cus);
		printf("\n\t\t\t\t   1. 删除订单\n");
		printf("\t\t\t\t   2. 修改购买数量\n");
		printf("\t\t\t\t   3. 支付结算");
		printf("\n\t\t\t\t 请选择您要对你的购物车进行的服务：");
		char ShoppingcartOp_s[5];
		int ShoppingcartOp;
		scanf("%s", ShoppingcartOp_s);
		ShoppingcartOp = inputcheck(ShoppingcartOp_s);
		if(ShoppingcartOp == -1){
			RefreshPage();
			continue;
		} 
		if(ShoppingcartOp == 0) return;
		switch(ShoppingcartOp){
			case(1):{
				int  delete_id;
				char delete_id_s2[10];
				printf("\t\t\t\t请输入你想要删除的订单号："); 
				scanf("%s", delete_id_s2);
				delete_id = inputcheck(delete_id_s2);
				if(delete_id == -1) {
					RefreshPage();
					continue;
				}
				delShoppingCart(cur_cus, delete_id);
				printf("\t\t\t您已成功删除购物车内容！");
				writeShoppingCart(&L);
				pau;
				break;
			}
			case(2):{
				int  change_id;
				char change_id_s[10];
				printf("\t\t\t\t请输入你想要修改的订单号："); 
				scanf("%s", change_id_s);
				change_id = inputcheck(change_id_s);
				int l = 0;
				shopping_cart *p = cur_cus->cart;
				while(p)
				{
					l++;
					p = p->next;
				}
				if(change_id > l || change_id == -1){
					RefreshPage();
					continue; 
				}
				//ChangeNumber(cur_cus, change_id);
				break;
			} 
			case(3):{
				
				break;
			} 
		}
	}
} 

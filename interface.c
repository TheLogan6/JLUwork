#include"interface.h"

extern Inventory* Inv_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][5]; 
//extern SpecialInv* SpeInv_head;
extern int total_brand;
void LoginInterface(){
	system("cls");
    system("color B4"); // B����ɫ   4����ɫ�� 
    printf("\n\n\n\n"); 
    printf("\t\t\t\t\t          ��ӭʹ�þ�ˮ����ϵͳ��\n");
    Sleep(300);
    printf("\t\t\t\t\t--------------��¼����----------------\n");
    Sleep(100);
    printf("\t\t\t\t\t|          (1). �ͻ���¼             |\n");
    Sleep(100);
    printf("\t\t\t\t\t|          (2).����Ա��¼            |\n");
    Sleep(100);
    printf("\t\t\t\t\t|          (3).�¿ͻ�ע��            |\n");
    Sleep(100);
    printf("\t\t\t\t\t|          (4).�˳�ϵͳ              |\n");
    Sleep(100);
    printf("\t\t\t\t\t-------------------------------------\n");
    printf("\t\t\t\t��ѡ����Ҫ���еķ��񣺣�1-4��:");
}

void ClientLogin(){
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t-----------�û���¼����----------------\n");
	printf("\t\t\t\t\t    (���˺����봦����0���Է�����һ������)\n");
    printf("\t\t\t\t\t �����������˺ţ�");
}

void ManagerLogin(){
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t-----------����Ա��¼����----------------\n");
	printf("\t\t\t\t\t     (����0���Է�����һ������)\n");
    printf("\t\t\t\t\t �������������Կ��");
} 

void PasswordOutput(){
	printf("\t\t\t\t\t �������������룺");
} 

 

void NewClientInterface(){
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t-----------���û�ע�����----------------\n");
    printf("\t\t\t\t\t   �����˺��ǣ�");
}
 
/*-------------------------------�����߽���---------------------*/ 
void ManagerChooseMode(){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------���̹������----------------\n");
		printf("\t\t\t\t\t     (����0���Է�����һ������)\n");
		printf("\t\t\t\t\t       1. ��Ϣ��ѯģʽ(ֻ��)\n");
		printf("\t\t\t\t\t       2. ��Ϣ�޸�ģʽ\n"); 
		printf("\t\t\t\t\t       3. ����ģʽ\n");
		printf("\t\t\t\t\t       4. �û���������\n");
		printf("\t\t\t\t       ��������Ҫѡ��ķ���");
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
		switch(Mana_mode){ // ��Ϣ��ѯģʽ 
			case(1):{
				ManagerInterface_Read();       // ֻ��ģʽ 
				break;
			}
			case(2):{
				ManagerInterface_Write();       // �޸�ģʽ 
				break;
			}
			case(3):{
				Restock();                    // �������� 
				break;
			}
			case(4):{
				aftersercive_check();                // �û��������� 
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
		printf("\t\t\t\t\t------------���̹������(��ѯģʽ)----------------\n");
		printf("\t\t\t\t\t   (����0���Է�����һ������)\n");
		printf("\t\t\t\t\t (1). �鿴�ֿ��Ʒ�嵥\n");
		printf("\t\t\t\t\t (2). �鿴�ͻ���Ϣ\n"); 
		printf("\t\t\t\t\t (3). �鿴���۶���\n");
		printf("\t\t\t\t\t (4). �鿴��������\n");
		printf("\t\t\t\t\t (5).  ������ѯ\n");
		printf("\t\t\t\t\t (10). �鿴�������飿\n");
		printf("\t\t\t\t ����������Ҫ���еķ���(1-6)");
		
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
			case(1):{//�鿴�ֿ��Ʒ�嵥
				system("cls");
				InventorySortMode();
				break;
			}
			case(2):{//�鿴�ͻ���Ϣ
				printCustomer(L);
				pau; 
				break;
			} 
			case(3):{ //�鿴���۶���
				Check_Bills();
				pau;
				break;
			}
			case(4):{// �鿴�������� 
				//printproductinlist();
				pau;
				break;
			}
			case(5):{//�޸Ŀͻ���Ϣ 
				Search_For_The_Bills_Of_Given_Data();
				pau;
				break;
			}
			case(6):{// �û���ֵ
				
				
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
		printf("\t\t\t\t\t------------���̹������(�޸�ģʽ)----------------\n");
		printf("\t\t\t\t\t   (����0���Է�����һ������)\n");
		printf("\t\t\t\t\t (1). �޸Ĳֿ���Ʒ��Ϣ\n");
		printf("\t\t\t\t\t (2). �޸Ŀͻ���Ϣ\n");
		printf("\t\t\t\t\t (3). �ͻ���ֵ\n");
		printf("\t\t\t\t\t (4). ɾ�����۶���\n");
		printf("\t\t\t\t\t (5). �޸Ľ�������\n");
		printf("\t\t\t\t\t (6). ɾ����������\n");
		printf("\t\t\t\t\t (10). �鿴�������飿\n");
		printf("\t\t\t\t ����������Ҫ���еķ���(1-6)");
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
			case(1):{//�ı�ֿ���Ʒ��Ϣ 
				ChangeInventory(); 
				break;
			} 
			case(2):{//�޸Ŀͻ���Ϣ 
				system("cls");
				char tempid_s[5];
				int tempid;
				printf("����������id:");
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
			case(3):{// �û���ֵ
				int tempid;
				double tempmoney;
				while(1)
				{
					char tempid_s[5];
					printf("����������id:");
					scanf("%s", tempid_s);
					tempid = inputcheck(tempid_s);
					if(tempid == -1){
						RefreshPage();
						continue;
					}		
					client* p=findClient(&L, tempid); 
					if(!p) continue;
					printf("�����ֵ��");
					scanf("%lf", &tempmoney);
					if(!recharge(&p, &log_head, tempid, tempmoney)) ErrorHappens();
					else{
						 printf("\t\t\t\t���ѳ�ֵ�ɹ������γ�ֵ��%lf",tempmoney);
						 writeClientInfo(L);
						 pau;
						 break;
				}
					pau;
					break;
				}
				
			}
			case(4):{//ɾ������ 
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


/*------------------------------------------�ͻ�����------------------------------------*/ 
void ClientChooseMode(client* cur_cus){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t-------------�ͻ�����----------------\n");
		printf("\t\t\t\t\t     (����0���Է�����һ������)\n");
		printf("\t\t\t\t\t       1.   ����\n");
		printf("\t\t\t\t\t       2. ��ѯ��ʷ����\n"); 
		printf("\t\t\t\t\t       3.  ��Ʒ����\n"); 
		printf("\t\t\t\t\t       4.  ��Ʒ�˻�\n"); 
		printf("\t\t\t\t\t       5.  ���ﳵ\n"); 
		printf("\t\t\t\t\t       6. ������Ʒ�����\n"); 

		printf("\t\t\t\t       ��������Ҫѡ��ķ���");
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
				//��ѯ��ʷ���� 
				Print_Bills_Of_Given_Id(cur_cus->id);
				pau;
				break;
			}
			case(3):{
				Exchange(cur_cus);
				break;
			}
			case(4):{  // ��Ʒ�˻� 
				Return(cur_cus);
				break;
			}
			case(5):{  // ���ﳵ����
				ShoppintcartInterface(cur_cus);
				break;
			}
			case(6):{ // ������Ʒ���� 
				SalePromotion(cur_cus);
				break;
			}
			
		
		}
		
	}
	
}
/* ------------------------------------------- ��������-------------------------------------------*/
void SalePromotion(client* cur_cus){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t-----------------��������----------------\n");
		printf("\t\t\t\t\t    (��Ʒ�Ʊ�ų�����0��ֱ�ӷ�����һ������)\n");
		PrintSpecialInv(); 
		printf("\t\t\t\t       ��������Ҫѡ���Ʒ�Ʊ�ţ�");
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
			printf("\t\tδ�ҵ��ô�����Ʒ������������������ҳ��ˢ�º��������룡"); 
			pau;
			continue;
		}	
		printf("\n\t\t\t\t��ѡ�����ڴ����еĲ�Ʒ��ţ�");
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
			printf("\t\tδ�ҵ��ô�����Ʒ������������������ҳ��ˢ�º��������룡"); 
			pau;
			continue;
		}
		int  buy_amount;
		char buy_amount_s[5]; 
		printf("\n\t\t\t\t��ѡ����Ҫ����������(���β��ó���100��)��");
		scanf("%s", buy_amount_s);
		buy_amount = inputcheck(buy_amount_s);
		if(buy_amount == -1  || buy_amount == 0 ){
			RefreshPage();
			continue;
		}
		if( buy_amount > 100 || tar->Reserve < buy_amount)
		{
			printf("\t\t���������Ʒ���������Ϲ淶���밴�����ˢ�º��������룡\n"); 
			pau;
			continue;
		}
		double buy_money;
		buy_money = buy_amount * tar->Price;
		printf("-------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t              ֧��ѡ��          \n"); 
		printf("\t\t\t\t\t 1. �ֽ�֧��\n");
		printf("\t\t\t\t\t 2. ���֧��\n");
		printf("\t\t\t\t\t 3. ���빺�ﳵ\n");
		printf("\t\t\t\t\t 4. ȡ�����ι���\n"); 
		printf("\t\t\t\t\t��ѡ����֧����ʽ: ");
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
				printf("\n\t\t\t\t�ֽ�֧���ɹ���\n");
				printf("\t\t\t���ѳɹ�����%sƷ�Ƶ�%s%d��,",code[tar->BrandNumber][0], code[tar->BrandNumber][tar->ProductNumber], buy_amount);
				printf("ÿ��%dƿ, ÿƿ%d������\n", tar->packagingsize, tar->volume);
				printf("\t\t\t\t ����%.2fԪ!\n", buy_money);
				sell_save(newbill);
				break;
			}
			case(2):{
				printf("\n\t\t\t���֧���ɹ���\n");
				printf("\t\t���ѳɹ�����%sƷ�Ƶ�%s%d��,",code[tar->BrandNumber][0], code[tar->BrandNumber][tar->ProductNumber], buy_amount);
				printf(" ÿ��%dƿ, ÿƿ%d������\n", tar->packagingsize, tar->volume);
				printf("\t\t\t ����%.2fԪ!\n", buy_money);
				system("pause");
				break;
			}
			case(3):{// ���빺�ﳵ 
				addShoppingCart(&cur_cus->cart,buy_amount,cur_cus->id,tar->Price,tar->BrandNumber, tar->ProductNumber, tar->SpecificationNumber); 
				writeShoppingCart(&L);
				printf("\n\t\t\t�ѳɹ����빺�ﳵ!"); 
				break;
			} 
			case(4):{
				printf("\n\t\t\t ���ѳɹ�ȡ�����ι���");
				printf("\n\t\t   ���������ˢ�±��ν���!");
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



/*------------------------------------------��������----------------------------------------------*/
 
void ErrorHappens(){
	printf("\n\t\t\t\t ������������, ���������룺"); 
}


void RefreshPage(){
	printf("\n\t\t\t\t �������벻���Ϲ淶�����������ˢ�½��棡\n");
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



/*-------------------------------���ﳵ����-----------------------------------*/
void ShoppintcartInterface(client* cur_cus){          // ��ǰ�ͻ���Ϣ 
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------���ﳵ����----------------\n");
		printf("\t\t\t\t\t    (����0���Է��ؿͻ�����)\n");	
		showShoppingCart(cur_cus);
		printf("\n\t\t\t\t   1. ɾ������\n");
		printf("\t\t\t\t   2. �޸Ĺ�������\n");
		printf("\t\t\t\t   3. ֧������");
		printf("\n\t\t\t\t ��ѡ����Ҫ����Ĺ��ﳵ���еķ���");
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
				printf("\t\t\t\t����������Ҫɾ���Ķ����ţ�"); 
				scanf("%s", delete_id_s2);
				delete_id = inputcheck(delete_id_s2);
				if(delete_id == -1) {
					RefreshPage();
					continue;
				}
				delShoppingCart(cur_cus, delete_id);
				printf("\t\t\t���ѳɹ�ɾ�����ﳵ���ݣ�");
				writeShoppingCart(&L);
				pau;
				break;
			}
			case(2):{
				int  change_id;
				char change_id_s[10];
				printf("\t\t\t\t����������Ҫ�޸ĵĶ����ţ�"); 
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

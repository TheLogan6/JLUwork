#include"interface.h"

extern Inventory* Inv_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][5]; 
extern SpecialInv* SpeInv_head;
extern int total_brand;
void LoginInterface(){
	system("cls");
    system("color B4"); // B����ɫ   4����ɫ�� 
    printf("\n\n\n\n");
    printf("\t\t\t\t\t-------------��¼����----------------\n");
    printf("\t\t\t\t\t          (1).�ͻ���¼               \n");
    printf("\t\t\t\t\t          (2).����Ա��¼             \n");
    printf("\t\t\t\t\t          (3).�¿ͻ�ע��             \n");
    printf("\t\t\t\t\t          (4).�˳�ϵͳ               \n");
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
		Sleep(300);
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------���̹������----------------\n");
		printf("\t\t\t\t\t     (����0���Է�����һ������)\n");
		printf("\t\t\t\t\t       1. ��Ϣ��ѯģʽ(ֻ��)\n");
		printf("\t\t\t\t\t       2. ��Ϣ�޸�ģʽ\n"); 
		printf("\t\t\t\t\t       3. ����ģʽ\n");
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
				printf("�������û�id��");
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
					if(!recharge(&p, NULL, tempid, tempmoney)) ErrorHappens();
					else break;
					writeClientInfo(L);
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
			default:{
				ErrorHappens();
				break;
			}
		}
	}	
		
		
}


/*-------------------------------�ͻ�����---------------------*/ 
void ClientChooseMode(client* cur_cus){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t-------------�ͻ�����----------------\n");
		printf("\t\t\t\t\t     (����0���Է�����һ������)\n");
		printf("\t\t\t\t\t       1.   ����\n");
		printf("\t\t\t\t\t       2. ��ѯ��ʷ����\n"); 
		printf("\t\t\t\t\t       3.  �ۺ����\n"); 
		printf("\t\t\t\t\t       4.  ���ﳵ\n"); 
		printf("\t\t\t\t\t       5. ������Ʒ�����\n"); 
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
				break;
			}
			case(3):{
				// �ۺ���� 
				break;
			}
			case(4):{ // ���ﳵ���� 
				
				break;
			}
			case(5):{ // ������Ʒ 
				SalePromotion();
				break;
			}
		
		}
		
	}
	
}
/* ------------------------------------------- ��������-------------------------------------------*/
void SalePromotion(){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t-------------��������----------------\n");
		printf("\t\t\t\t\t     (����0���Է�����һ������)\n");
		PrintSpecialInv(); 
		printf("\t\t\t\t       ��������Ҫѡ��ķ���");
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		scanf("%s", ChooseBrand_s);
		ChooseBrand = inputcheck(ChooseBrand_s);
		if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		if(ChooseBrand == 0) return ;
		printf("\n\t\t\t\t��ѡ����Ҫ�����Ĳ�Ʒ��ţ�");
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
		printf("\n\t\t\t\t��ѡ����Ҫ����������(���β��ó���100��)��");
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
		printf("\t\t���ѳɹ�����%sƷ�Ƶ�%s%d��,",tar_sou->DrinksBrand_sou, code[tar_sou->BrandNumber_sou][tar_sou->ProductNumber_sou], buy_amount);
		printf(" ÿ��%dƿ, ÿƿ%d������\n", tar_sou->packagingsize_sou, tar_sou->volume_sou);
		printf("\t\t\t ����%.2fԪ!\n", buy_money);
		
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

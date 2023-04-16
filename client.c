#include"client.h"

extern Inventory* Inv_head;
extern int total_brand;
extern client* L;
extern char* code[12][5];

void PurchaseInterface(client* cur_cus){
	int position=0,row=8,ChooseBrand=0;
	while(1)
	{
		system("cls");
		printf("\n\n\n\n\n"); 
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t               ��Ʒ��������              \n");
//    	printf("\t\t\t\t\t         (����0���Է�����һ������)       \n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
		for(int i = 1; i <= 7; i++)
		{
		if(position==i-1)printf("\t\t\t\t\t|            --->   %-14s        |\n",code[i][0]);
		else printf("\t\t\t\t\t|                   %-14s        |\n",  code[i][0]);
		}
		if(position==7)printf("\t\t\t\t\t|            --->   %-14s        |\n","�˳�"); 
		else  printf("\t\t\t\t\t|                   %-14s        |\n","�˳�"); 
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\n\t\t\t\t\t��ѡ������Ҫѡ����Ʒ�ƣ�");
//		int ChooseBrand;
//		char ChooseBrand_s[5];
//		scanf("%s", ChooseBrand_s);
//		ChooseBrand = inputcheck(ChooseBrand_s);
//		if(ChooseBrand == -1 || ChooseBrand > total_brand){
//			RefreshPage();
//			continue;
//		}
		int op=getchoice(&position,row,&ChooseBrand);
		if(op<0)break;
			
	} 
	if(ChooseBrand == 8) return ;
	else{
		struct sell_bill* newbill = Sell_select_brand(ChooseBrand);
		PurchaseProduct(cur_cus, ChooseBrand, newbill);
	}
}

void PurchaseProduct(client* cur_cus, int ChooseBrand, struct sell_bill* newbill){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n\n"); 
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t               ��Ʒ��������              \n");
    	printf("\t\t\t\t\t         (����0���Է�����һ������)       \n");
    	printf("\t\t\t\t\t --------------------------------------- \n");

		
		printf("\t\t\t\t\t      ��ǰѡ���Ʒ����: %s       ",code[ChooseBrand][0]);
		printf("\n\n\n");
		printf("\t\t ��Ʒ����  |  ��Ʒ���  |  ��ˮ����(/ƿ) | �ֿ��� | ��װ��С(/��) |  �ۼ�(/��) \n"); 
		Inventory* p = Inv_head->next;
		while(p)
		{
			if(p->BrandNumber == ChooseBrand)
			{
				printf("\t\t  %-14s", code[p->BrandNumber][p->ProductNumber]);
				printf(" %-12d %-14d%-14d%-13d", p->SpecificationNumber, p->volume, p->Reserve, p->packagingsize);
				printf("%-10.2f\n", p->Price);
			} 
			p = p->next;
		}
		int ChooseProduct;
		printf("\t\t------------------------------------------------------------------------------------- \n");
		printf("\t\t\t\t\t ��ѡ����Ҫ�����Ĳ�Ʒ��ţ�");
		char ChooseProduct_s[5];
		scanf("%s", ChooseProduct_s);
		ChooseProduct = inputcheck(ChooseProduct_s);
		if(ChooseProduct == -1 || ChooseProduct > 7){
			RefreshPage();
			continue;
		}
		if(ChooseProduct == 0) return; 
		else{
			Sell_select_ProductNumber(ChooseProduct, newbill);
			Sell_select_Number_of_goods(newbill,cur_cus);
			int i = Sell_confirm(newbill, cur_cus);
			if(i!=3) {
				sell_save(newbill);
				if(i!=4) UpdateInventory();
			}
//			printf("\n\t\t\t\t���ѳɹ�ѡ��  ,����Ϊ  ,��װΪ  "); 
		}
				
//		Sleep(2000); 
//		system("pause"); 
	}
}

void ClientInput(){
    int ClientId;
	char ClientPassword[12];    
    while(1)
    {
        ClientLogin();
		while((scanf("%d", &ClientId)) == 0)
		{
        	char garbage[20];
            gets(garbage);
			ErrorHappens();
		}
        if(ClientId == 0) return;
        PasswordOutput();
        
        
		char ClientPassword[20];
		char temp;
		int i = 0;
		while(1)
		{
			temp = _getch();
			if(temp == '\r' || temp == '\n') break;
			else if (temp == '\b') {             // �˸������ 
				if(i!=0){
					printf("\b \b");
					i--;
				}
			}
			else{
				printf("*");
				ClientPassword[i++] = temp;
			}
		}
		ClientPassword[i] = '\0';
//		if(i == 1 && ClientPassword[i-1] == '0') return;
//		else if(strcmp(ClientPasswordPassword, passwordans) == 0)
//        	ManagerChooseMode();
//		else {
//			printf("������������������ڽ���ˢ�º��������룡");
//			continue; 
//		}
        
        if(!checkPassword(L, ClientId, ClientPassword)){
        	printf("\n\t\t\t\t ��������˺Ż���������, �밴�����ˢ�º��������룡\n");
			system("pause"); 
		}
		else{
			client* cur_cus=findClient(&L,ClientId);
			ClientChooseMode(cur_cus); 
		}  
    }
}

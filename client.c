#include"client.h"

extern Inventory* Inv_head;
extern int total_brand;
extern client* L;
extern char* code[12][5];

void PurchaseInterface(client* cur_cus){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------��Ʒ��������----------------\n");
		printf("\t\t\t\t\t   (����0���Է�����һ������)\n");
		for(int i = 1; i <= 7; i++)
		{
			printf("\t\t\t\t\t%d : %s\n", i , code[i][0]);
		}
		printf("\n\t\t\t\t\t��ѡ������Ҫѡ����Ʒ�ƣ�");
		int ChooseBrand;
		char ChooseBrand_s[5];
		scanf("%s", ChooseBrand_s);
		ChooseBrand = inputcheck(ChooseBrand_s);
		if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		if(ChooseBrand == 0) return ;
		else{
			struct sell_bill* newbill = Sell_select_brand(ChooseBrand);
			PurchaseProduct(cur_cus, ChooseBrand, newbill);
		}	
	} 
}

void PurchaseProduct(client* cur_cus, int ChooseBrand, struct sell_bill* newbill){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------��Ʒ��������2----------------\n");
		printf("\t\t\t\t\t   (����0���Է�����һ������)\n");
		printf("\t\t\t****** ��ǰѡ���Ʒ����: %s ******  \n\n",code[ChooseBrand][0]);
		printf("\n\t\t��Ʒ����    ��Ʒ���     ��ˮ����(/ƿ)  �ֿ��� ��װ��С(/��) �ۼ�(/��)\n"); 
		Inventory* p = Inv_head->next;
		while(p)
		{
			if(p->BrandNumber == ChooseBrand)
			{
				printf("\t\t%-12s", code[p->BrandNumber][p->ProductNumber]);
				printf("%-11d%-13d%-12d%-12d", p->SpecificationNumber, p->volume, p->Reserve, p->packagingsize);
				printf("%-10.2f\n", p->Price);
			} 
			p = p->next;
		}
		int ChooseProduct;
		printf("\n\t\t\t\t��ѡ����Ҫ�����Ĳ�Ʒ��ţ�");
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
			Sell_confirm(newbill, cur_cus);
			sell_save(newbill);
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
        char ch;
		int l=0;
        getchar();
        while((ch=getchar())!='\n')
        {
        	ClientPassword[l++] = ch;
		}
		ClientPassword[l] = '\0';
        //searchclient
        if(!checkPassword(L, ClientId, ClientPassword)){
        	printf("\t\t\t\t ��������˺Ż���������, �밴�����ˢ�º��������룡\n");
			system("pause"); 
		}
		else{
			client* cur_cus=findClient(&L,ClientId);
			ClientChooseMode(cur_cus); 
		}  
    }
}

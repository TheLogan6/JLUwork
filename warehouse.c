#include"warehouse.h"

extern char* code[12][10];
extern Inventory* Inv_head;
extern ProductSource* Sou_head;
extern int total_brand;
extern Gift* Gift_head;

void encode_product(){
	code[1][0] = "ũ��ɽȪ";code[1][1] = "����ˮ", code[1][2] = "��Ȫˮ" ;code[1][3] = "���ζ���";code[1][3] = "Ԫ��ɭ��";
	code[2][0] = "��Դ"; code[2][1] = "ƻ��֭"; code[2][2] = "����֭"; code[2][3] = "����֭";
	code[3][0] = "�ൺơ��" ; code[3][1] = "�ൺ����"; code[3][2] = "�ൺС��ƿ" ;
	code[4][0] = "���"; code[4][1] = "ˮ�����"; code[4][2] = "�������" ;
	code[5][0] = "����Һ"; code[5][1] = "������"; code[5][2] = "������"; code[5][3] = "�ƽ��";
	code[6][0] = "��ʦ��" ;code[6][1] = "�����"; code[6][2] = "���̲�"; code[6][3] = "����ѩ��";
	code[7][0] = "�޹���"; code[7][1] = "Ӫ������"; code[7][2] = "AD����"; 
	code[8][0]="ϲ��"        ;  code[8][1] = "ϲСƿ����ˮ";
	code[9][0]="�ɿڿ���"    ; code[9][1] = "����";code[9][1] = "ѩ��";
	code[10][0]="��Ҥ�α�"   ;    code[10][1] = "��Ҥ��ζ";
}

Inventory* InitInventory(){
	Inventory* Inv_head = (Inventory*)malloc(sizeof(Inventory));  // ��λ�ڵ� 
	Inv_head->pre = NULL;
	Inv_head->next = NULL;
	Inventory* Inv_tail = Inv_head;                    // βָ�� 
	FILE* Storehouse_fp;
	Storehouse_fp = fopen("warehouse.txt","r+");
	if(Storehouse_fp == NULL){
		printf("Storehousefile cannot open, error happens!");
		exit(-1);
	}
	char garbage[100];
	while((fscanf(Storehouse_fp, "%s", garbage))!=EOF)
	{
//		char garbage[50];
//		fgets(garbage, sizeof(Inventory), Storehouse_fp);
		Inventory* p = (Inventory*)malloc(sizeof(Inventory));
//		fscanf(Storehouse_fp, "%s", p->DrinksBrand);
		strcpy(p->DrinksBrand, garbage);
		fscanf(Storehouse_fp, "%d%d%d%d%d%d", &p->BrandNumber, &p->ProductNumber, &p->SpecificationNumber, &p->volume, &p->Reserve, &p->packagingsize);
		fscanf(Storehouse_fp, "%f", &p->Price);
		fscanf(Storehouse_fp, "%d%d%d%d\n", &p->quality_year, &p->quality_month, &p->quality_day, &p->nearexpiry);	
		p->pre = Inv_tail;
		p->next = NULL;
		Inv_tail->next = p;
		Inv_tail = p;
	} 
	fclose(Storehouse_fp);
	return Inv_head;
} 

void PrintInventory(Inventory* Inv_head){
	Inventory* p = Inv_head->next;
	if(p == NULL) {
		printf("\t\t\t\t\t            �����κ���Ʒ��\n");
		pau;
		return;
	}
	printf("\t  ��ˮƷ��  | Ʒ�Ʊ�� |   ��Ʒ����   | ��Ʒ��� | ������С | ��װ��С | ������� |     �۸�     |       ������\n");
	while(p)
	{
		printf("\t  %-15s%-9d", code[p->BrandNumber][0], p->BrandNumber);
		printf(" %-16s", code[p->BrandNumber][p->ProductNumber]);
		printf("%-10d%-10d %-11d", p->SpecificationNumber, p->volume, p->packagingsize, p->Reserve);
		if(p->Reserve == 0) printf("(������)   ");
		else printf(" %-11d", p->Reserve);
		printf("%-12.2f  ", p->Price);
		printf(" %d��%d��%d��\n", p->quality_year, p->quality_month, p->quality_day);
		p = p->next;
	}
}


Inventory* FindInventory(int Brand, int Specification){
	Inventory* p = Inv_head->next;
	while(p)
	{
		if(p->BrandNumber == Brand && p->SpecificationNumber == Specification)
			return p;
		else p = p->next;
	}
	return NULL;
}

void AddNewinventory(Inventory* newInv){
	return;
}

void UpdateInventory(){
    FILE* warehouse_fp = fopen("warehouse.txt", "w");
    if (warehouse_fp == NULL)
    {
        printf("warehouseFile cannot open, error happens!");
        exit(-1);
    }
    //fprintf(newstorehouse_fp, "��ˮƷ��   |  Ʒ�Ʊ�� |   ��Ʒ���   |�����| ������С | ��װ��С | ������� |  �������\n");
    Inventory* p = Inv_head->next;

    while (p != NULL)
    {
        fprintf(warehouse_fp, "%-20s", p->DrinksBrand);
		fprintf(warehouse_fp, "%-9d%-9d", p->BrandNumber, p->ProductNumber);
		fprintf(warehouse_fp, "%-9d%-9d%-9d%-9d", p->SpecificationNumber, p->volume, p->Reserve, p->packagingsize); 
		fprintf(warehouse_fp, "%-15.2f", p->Price);
		fprintf(warehouse_fp, "%-9d%-9d%-9d%-5d\n", p->quality_year, p->quality_month, p->quality_day, p->nearexpiry);
		p = p->next;
    }
    fclose(warehouse_fp);
    return;
}


void ChangeInventory(){
	while(1)
	{
		system("cls");
		
		printf("\n\n\n\n"); 
		
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t            �޸���Ʒ��Ϣ����             \n");
    	printf("\t\t\t\t\t         (����0�ɷ�����һ������)         \n"); 
    	printf("\t\t\t\t\t --------------------------------------- \n");
		PrintInventory(Inv_head);
		if(Inv_head->next == NULL){
			return;
		}
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t  ��ѡ����Ҫ���ĵ�Ʒ�Ʊ�ţ�");
		ChooseBrand = checkNum();
		if(ChooseBrand == 0) return;
		else if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		printf("\t\t\t\t  ��ѡ����Ҫ���ĵĲ�Ʒ��ţ�");
		ChooseProduct = checkNum();
		int maxnum1 = countSpecification(ChooseBrand);
		if(ChooseProduct == -1 || ChooseProduct > maxnum1){
			RefreshPage();
			continue;
		}
		Inventory* tar = FindInventory(ChooseBrand, ChooseProduct);
		if(tar == NULL)
		{
			printf("\t\t\t\t  �Ҳ�������Ʒ��������������\n");
			printf("\t\t\t\t  �밴�����ˢ�º��������룡");
			system("pause");
			continue;
		}
		else
		{
			while(1)
			{
				system("cls");
				printf("\n\n\n\n"); 
		    	printf("\t\t\t\t\t --------------------------------------- \n");
		    	printf("\t\t\t\t\t            �޸���Ʒ��Ϣ����             \n");
		    	printf("\t\t\t\t\t         (����0�ɷ�����һ������)         \n"); 
		    	printf("\t\t\t\t\t --------------------------------------- \n");
				printf("\t  ��ˮƷ��  | Ʒ�Ʊ�� |   ��Ʒ����   | ��Ʒ��� | ������С | ��װ��С | ������� |   �۸�   |          ������\n");
				printf("\t%-17s%-9d ", tar->DrinksBrand, tar->BrandNumber);
				printf("%-16s", code[tar->BrandNumber][tar->ProductNumber]);
				printf("%-10d%-10d%-11d", tar->SpecificationNumber, tar->volume, tar->packagingsize);
				if(tar->Reserve == 0) printf("(������)    ");
				else printf("%-11d", tar->Reserve);
				printf("%-12.2f   ", tar->Price);
				printf("%d��%d��%d��\n", tar->quality_year, tar->quality_month, tar->quality_day);
				printf("\t\t\t\t\t --------------------------------------- \n");
			    printf("\t\t\t\t\t                                        \n");
			    printf("\t\t\t\t\t         (1).   �޸Ŀ������            \n");
			    printf("\t\t\t\t\t         (2).   �޸������۸�            \n");
			    printf("\t\t\t\t\t         (3).    �¼ܸ���Ʒ             \n");
			    printf("\t\t\t\t\t         (0).  ������һ������           \n");
				printf("\t\t\t\t\t                                        \n");
				printf("\t\t\t\t\t --------------------------------------- \n");

				printf("\t\t\t\t\t ��ѡ����Ҫ���еĲ�����");
				int ChangeInfo;
				char ChangeInfo_s[5];
				ChangeInfo = checkNum();
				if(ChangeInfo == -1 || ChangeInfo > 3) {
					RefreshPage();
					continue;
				}
				if(ChangeInfo == 0) break;
				switch(ChangeInfo){
					case(1):{   ////�޸Ŀ������ 
						printf("\t\t\t\t  �������µĿ������(���ó�����������)��");
						int NewReserve;
						char NewReserve_s[6];
						NewReserve = checkNum();
						if(NewReserve == -1 || NewReserve > 1000) {
							RefreshPage();
							continue;
						}
						tar->Reserve = NewReserve;
						UpdateInventory();
						printf("\t\t\t\t  ���ѳɹ��޸Ŀ���������������ˢ�£�");
						system("pause");
						break;
					}
					case(2):{ // �޸ļ۸� 
						printf("\t\t\t\t  �������µ������۸�(ֻ������λС���Ҳ���С��1Ԫ)��");
						float NewPrice;
						if((scanf("%f", &NewPrice))==0 || NewPrice < 1)
						{
							char garbage[20];
							gets(garbage);
							RefreshPage();
							continue;
						}
						tar->Price = NewPrice;
						UpdateInventory(); 
						printf("\t\t\t\t  ���ѳɹ��޸ļ۸񣬰������ˢ�£�");
						system("pause");
						break;
					}
					case(3):{ // ɾ����Ʒ 
						printf("\t\t\t\t\t --------------------------------------- \n");
						printf("\t\t\t\t\t             1. Yes\n");
						printf("\t\t\t\t\t             2. No\n  ");
						printf("\t\t\t\t\t        ��ȷ��Ҫ�¼ܸ���Ʒ��");
						int checkdelete;
						char checkdelete_s[6];
						checkdelete = checkNum();
						if(checkdelete == -1 || checkdelete == 0) {
							RefreshPage();
							continue;
						}
						if(checkdelete == 1) {
//							Inventory* fro = tar->pre;
//							fro->next = fro->next->next;
//							if(fro->next != NULL)  // ɾ�����һ��Ԫ�� 
//								fro->next->pre = fro;
//							// �������
//							Inventory* temp = Inv_head->next;
//							while(temp)
//							{
//								if(temp->BrandNumber == ChooseBrand && temp->SpecificationNumber > ChooseProduct)
//									temp->SpecificationNumber -- ;
//								temp = temp->next;
//							}// �������
							tar->Reserve = 0;
							UpdateInventory(); 
							printf("\t\t\t\t  ���ѳɹ��޸����ݣ����������������һ�����棡");
							pau;continue;
						}
						else if(checkdelete == 2){
							printf("\t\t\t\t  ��δɾ�������ݣ����������ˢ�¸ý��棡");
							pau;continue;
						}
						break;
					}
					default:RefreshPage(); continue;	
				}
					
			}
		}
	}
} 



void reduceinventory(Inventory* tar, int num){
	if(tar->Reserve >= num) tar->Reserve-=num;
}

int countSpecification(int Brand){
	Inventory* p = Inv_head->next;
	int res = 0;
	while(p)
	{
		if(p->BrandNumber == Brand) res++;
		p = p->next;
	}
	return res;
}

void queryinventory(){
	while(1)
	{
		system("cls");
		int sortmode;
		char sortmode_s[5];
		printf("\n\n\n\n"); 
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t               ��ѯ��Ʒ��Ϣ              \n");
		printf("\t\t\t\t\t           (����0�ɷ�����һ������)       \n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t ��������Ҫ��ѯ����ƷƷ������: ");
		
		char queryinventory[100]={'\0'};int l=0;char ch;
	flag:
		l=0;
    	while((ch=getchar())!='\n') queryinventory[l++]=ch;
    	queryinventory[l]='\0';
	    if(queryinventory[0]=='\0') goto flag;
	    if(l==1&&queryinventory[0]=='0') return ;

		int j = 0;
		for(int i = 1; i <= 10; i++)
		{
			if(strcmp(code[i][0], queryinventory) == 0) j = i;
		}
		if(j == 0){
			printf("\t\t\t\t\t �����������������밴�����ˢ�º����ԣ�");
			pau;
			continue;
		}
		
		int flag = 0;
		Inventory* p = Inv_head->next;
		while(p)
		{
			if(p->BrandNumber == j)
			{
				flag++;
				if(flag == 1) printf("\t  ��ˮƷ��  | Ʒ�Ʊ�� |   ��Ʒ����   | ��Ʒ��� | ������С | ��װ��С | ������� |     �۸�     |       ������\n");
				printf("\t  %-15s%-9d", code[p->BrandNumber][0], p->BrandNumber);
				printf(" %-16s", code[p->BrandNumber][p->ProductNumber]);
				printf("%-10d%-10d %-11d", p->SpecificationNumber, p->volume, p->packagingsize, p->Reserve);
				if(p->Reserve == 0) printf("(������)   ");
				else printf(" %-11d", p->Reserve);
				printf("%-12.2f  ", p->Price);
				printf(" %d��%d��%d��\n", p->quality_year, p->quality_month, p->quality_day);
			}
			p = p->next;
		}
		if(flag == 0){
			printf("\t\t\t\t\t        �����û�и���Ʒ��\n");
			printf("\t\t\t\t\t      �������ˢ�º�����²�ѯ��\n");
			pau; 
			continue;
		}
		else{
			printf("\t\t\t\t\t --------------------------------------- \n");
			printf("\t\t\t\t\t      �������ˢ�º�����²�ѯ��\n");
			pau;
		}
	}
	
}


/*---------------------------------�������ָ���--------------------------------------------*/ 

void InventorySortMode(){
	while(1)
	{
		system("cls");
		int sortmode;
		char sortmode_s[5];
		printf("\n\n\n\n"); 
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t               �鿴��Ʒ��Ϣ              \n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t|                                       |\n");
		printf("\t\t\t\t\t|         (1). ����Ʒ���(Ĭ��)         |\n");
		printf("\t\t\t\t\t|         (2). �����������С           |\n");
		printf("\t\t\t\t\t|         (3).   ���۸�ߵ�             |\n");
		printf("\t\t\t\t\t|         (0).  ������һ������          |\n");
		printf("\t\t\t\t\t|                                       |\n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t ��ѡ������Ҫ����ķ�ʽ��");
		
		sortmode = checkNum();
		if(sortmode == -1){
			RefreshPage();
			continue;
		}
		if(sortmode == 0) break;
		switch(sortmode){
			case(1):{
				printf("\t\t\t\t\t --------------------------------------- \n");
				SortByNumber(Inv_head);
				PrintInventory(Inv_head);
				printf("\t\t\t\t  �������ˢ�½�������ѡ������ʽ\n");
				pau;
				break;
			}
			case(2):{
				printf("\t\t\t\t\t --------------------------------------- \n");
				SortByReserve(Inv_head);
				PrintInventory(Inv_head);
				SortByNumber(Inv_head);
				printf("\t\t\t\t  �������ˢ�½�������ѡ������ʽ\n");
				pau;
				break;
			}
			case(3):{
				printf("\t\t\t\t\t --------------------------------------- \n");
				SortByPrice(Inv_head);
				PrintInventory(Inv_head);
				SortByNumber(Inv_head);
				printf("\t\t\t\t  �������ˢ�½�������ѡ������ʽ\n");
				pau;
				break;
			}
			default: RefreshPage();continue;
		}
	} 
}

//--------------------------------------------------�������ʽ
void SortByNumber(Inventory* Inv_head){
	Inventory* p = Inv_head;  // ������p��ĺ���  , ��С���� 
	if(p->next == NULL) return;
	while(p)
	{
		Inventory* q = p->next;
		Inventory* tar = q;
		while(q)
		{
			if(q->BrandNumber < tar->BrandNumber) tar = q;
			else if(q->BrandNumber == tar->BrandNumber && q->SpecificationNumber < tar->SpecificationNumber) tar = q;
			q = q->next;
		}
		if(p->next == tar)
			p = p->next;
		else if(tar->next == NULL)
		{
			tar->pre->next = NULL;
			
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			
			p = p->next;
		}
		else
		{
			
			tar->pre->next = tar->next;
			tar->next->pre = tar->pre; // ɾ��
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			p = p->next;
		}	
	}
}
void SortByReserve(Inventory* Inv_head){
	Inventory* p = Inv_head;  // ������p��ĺ���  , ��С���� 
	if(p->next == NULL) return;
	while(p)
	{
		Inventory* q = p->next;
		Inventory* tar = q;
		while(q)
		{
			if(q->Reserve < tar->Reserve) tar = q;
			q = q->next;
		}
		if(p->next == tar)
			p = p->next;
		else if(tar->next == NULL)
		{
			tar->pre->next = NULL;
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			p = p->next;
		}
		else
		{
			
			tar->pre->next = tar->next;
			tar->next->pre = tar->pre; // ɾ��
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			p = p->next;
		}	
	}
} 

void SortByPrice(Inventory* Inv_head){
	Inventory* p = Inv_head;
	if(p->next == NULL) return;
	while(p)
	{
		Inventory* q = p->next;
		Inventory* tar = q;
		while(q)
		{
			if(q->Price < tar->Price) tar = q;
			q = q->next;
		}
		if(p->next == tar)
			p = p->next;
		else if(tar->next == NULL)
		{
			tar->pre->next = NULL;
			
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			
			p = p->next;
		}
		else
		{
			tar->pre->next = tar->next;
			tar->next->pre = tar->pre; // ɾ�� 
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			
			p = p->next;
		}	
	}
} 


/*---------------------------   ��Դ�ָ���----------------------------*/ 

ProductSource* ReadSource(){
	ProductSource* Sou_head = (ProductSource*)malloc(sizeof(ProductSource));  // ��λ�ڵ� 
	Sou_head->pre = NULL;
	Sou_head->next = NULL;
	ProductSource* Sou_tail = Sou_head;                    // βָ�� 
	FILE* source_fp;
	source_fp = fopen("��Դ.txt","r+");
	if(source_fp == NULL){
		printf("sourcefile cannot open, error happens!");
		exit(-1);
	}
	char garbage[20];
	while((fscanf(source_fp, "%s", garbage))!=EOF)
	{
		ProductSource* p = (ProductSource*)malloc(sizeof(ProductSource));
		strcpy(p->DrinksBrand_sou, garbage);
//		fgets(p->DrinksBrand, 20, fp);
		fscanf(source_fp, "%d%d%d%d%d", &p->BrandNumber_sou, &p->ProductNumber_sou, &p->SpecificationNumber_sou, &p->volume_sou, &p->packagingsize_sou);
		fscanf(source_fp, "%f", &p->Price_sou);	
		fscanf(source_fp, "%d%d%d\n", &p->quality_year_sou, &p->quality_month_sou, &p->quality_day_sou);
		p->pre = Sou_tail;
		p->next = NULL;
		Sou_tail->next = p;
		Sou_tail = p;
	} 
	return Sou_head;
} 

void PrintSource(ProductSource* Sou_head){
	ProductSource* p = Sou_head->next;
	
	printf("\t  ��ˮƷ��  | Ʒ�Ʊ�� |   ��Ʒ����   | ��Ʒ��� | ������С | ��װ��С |    �۸�    |            ������\n");
	while(p)
	{
		printf("\t  %-15s%-9d", code[p->BrandNumber_sou][0], p->BrandNumber_sou);
		printf(" %-16s", code[p->BrandNumber_sou][p->ProductNumber_sou]);
		printf("%-10d%-10d %-11d ", p->SpecificationNumber_sou, p->volume_sou, p->packagingsize_sou);
		printf("%-12.2f   ", p->Price_sou);
		printf(" %d��%d��%d��\n", p->quality_year_sou, p->quality_month_sou, p->quality_day_sou);
		p = p->next;
	}
}

int countSpecification_sou(int Brand){
	ProductSource* p = Sou_head->next;
	int res = 0;
	while(p)
	{
		if(p->BrandNumber_sou == Brand) res++;
		p = p->next;
	}
	return res;
}
ProductSource* FindSource(int Brand, int Specification){
	ProductSource* p = Sou_head->next;
	while(p)
	{
		if(p->BrandNumber_sou == Brand && p->SpecificationNumber_sou == Specification)
			return p;
		p = p->next;
	}
	return NULL;
}



void addinwarehouse(ProductSource* tar, int amount){
	Inventory* p = Inv_head->next;
	Inventory* temp = p;
	while(p)
	{
		if(p->BrandNumber == tar->BrandNumber_sou && p->ProductNumber==tar->ProductNumber_sou && p->volume==tar->volume_sou&& p->packagingsize==tar->packagingsize_sou &&p->quality_year==tar->quality_year_sou &&p->quality_month&&tar->quality_month_sou&&p->quality_day==tar->quality_day_sou)
		{
			break;
		}	
		else p = p->next;
		if(p) temp = p;
	}
	if(p == NULL)
	{
		Inventory* newinv = (Inventory*)malloc(sizeof(Inventory));
		strcpy(newinv->DrinksBrand,tar->DrinksBrand_sou);
		newinv->BrandNumber = tar->BrandNumber_sou;
		newinv->nearexpiry = 0;
		newinv->packagingsize = tar->packagingsize_sou;
		newinv->Price = tar->Price_sou * 1.5;
		newinv->ProductNumber = tar->ProductNumber_sou;
		newinv->quality_day = tar->quality_day_sou;
		newinv->quality_month = tar->quality_month_sou;
		newinv->quality_year = tar->quality_year_sou;
		newinv->Reserve = amount;
		newinv->SpecificationNumber = countSpecification(tar->BrandNumber_sou)+1;
		newinv->volume = tar->volume_sou; 
		newinv->pre = temp;
		temp->next = newinv;
		newinv->next = NULL;
	}
	else{
		p->Reserve += amount;
	}
}

/*--------------------------------------------------������Ʒ����--------------------------*/ 
int timegap(int x1, int y1, int z1, int x2, int y2, int z2){ // 1�Ǳ������� 
//	printf("%d %d %d %d %d %d",x1,y1,z1,x2,y2,z2);
	return (x1-x2)*365 + (y1-y2)* 30 + (z1-z2);
}

void JudgeNearexpiry(){
	Inventory* q = Inv_head->next;
	time_t timep;
	struct tm *p;
    time(&timep);
    p = localtime(&timep); //ȡ�õ��ؾ���ʱ��
	while(q)
	{
		if(q->nearexpiry == 1) {
			q = q->next;
			continue;
		}
		else if(timegap(q->quality_year,q->quality_month,q->quality_day,1900+p->tm_year, 1+p->tm_mon, p->tm_mday) < 60 )
		{
			q->Price *= 0.5;
			q->nearexpiry = 1;
		}
		q = q->next;
	}
	UpdateInventory();
	return;
}

void PrintSpecialInv(){
	Inventory* p = Inv_head->next;

	printf("\t  ��ˮƷ��  | Ʒ�Ʊ�� |   ��Ʒ����   | ��Ʒ��� | ������С | ��װ��С | ������� |   �����۸�   |       ������\n");
	while(p)
	{
		if(p->nearexpiry == 1)
		{
			
			printf("\t  %-15s%-9d", code[p->BrandNumber][0], p->BrandNumber);
			printf(" %-16s", code[p->BrandNumber][p->ProductNumber]);
			printf("%-10d%-10d %-11d ", p->SpecificationNumber, p->volume, p->packagingsize);
			if(p->Reserve == 0) printf("  (������)  ");
			else printf("%-11d",p->Reserve); 
			printf("%-12.2f  ", p->Price);
			printf(" %d��%d��%d��\n", p->quality_year, p->quality_month, p->quality_day);
			p = p->next;
		}
		p = p->next;	
	}	
}



/*------------------------------------ ��Ʒ����-----------------------------------*/
Gift* InitGift(){
	Gift* Gift_head = (Gift*)malloc(sizeof(Gift));  // ��λ�ڵ� 
	Gift_head->pre = NULL;
	Gift_head->next = NULL;
	Gift* Gift_tail = Gift_head;                    // βָ�� 
	FILE* Gift_fp;
	Gift_fp = fopen("gift.txt","r+");
	if(Gift_fp == NULL){
		printf("Giftfile cannot open, error happens!");
		exit(-1);
	}
	int reorder,brand,product,gif_volume,bottle,value;
	while(fscanf(Gift_fp, "%d%d%d%d", &reorder, &brand, &product, &gif_volume)!=EOF)
	{
		Gift* p = (Gift*)malloc(sizeof(Gift));
		p->reorder = reorder;
		p->brand = brand;
		p->product = product;
		p->gif_volume = gif_volume;
		fscanf(Gift_fp, "%d", &p->bottle);
		fscanf(Gift_fp, "%f", &p->value);
		fscanf(Gift_fp, "%d%d%d\n", &p->gif_year, &p->gif_month, &p->gif_day);
		p->pre = Gift_tail;
		p->next = NULL;
		Gift_tail->next = p;
		Gift_tail = p;
	} 
	
	return Gift_head; 
} 
void PrintGift(){
	Gift* p = Gift_head->next;
	if(p == NULL){
		printf("\t\t\t\t\t       �ֿ���û����Ʒ��\n");
		return;
	} 
	printf("\t  ��Ʒ��� | ��ˮƷ��  | Ʒ�Ʊ�� |   ��Ʒ����   | ������С | �������(ƿ) |  ��Ʒ��ֵ  |       ������\n");
	while(p)
	{
		printf("\t     %-8d%-15s%-9d", p->reorder, code[p->brand][0], p->brand);
		printf(" %-15s", code[p->brand][p->product]);
		printf("%-12d",p->gif_volume); 
		printf("%-14d",p->bottle); 
		printf("%-12.2f  ", p->value);
		printf("%d��%d��%d��\n", p->gif_year, p->gif_month, p->gif_day);
		p = p->next;
	}
}

void UpdateGift(){
	FILE* Gift_fp;
	Gift_fp = fopen("gift.txt","w+");
    if (Gift_fp == NULL)
    {
        printf("giftFile cannot open, error happens!");
        exit(-1);
	}
    Gift* p = Gift_head->next;
    while (p != NULL)
    {
        fprintf(Gift_fp, "%-5d%-5d%-5d%-5d", p->reorder, p->brand, p->product, p->gif_volume);
		fprintf(Gift_fp, "%-5d", p->bottle);
		fprintf(Gift_fp, "%-10.2f", p->value);
		fprintf(Gift_fp, "%-5d%-5d%-5d\n", p->gif_year, p->gif_month, p->gif_day);
		p = p->next;
    }
    fclose(Gift_fp);
    return;
}


void Giftsort(Gift* Gift_head){
	Gift* p = Gift_head;
	if(p->next == NULL) return;
	while(p)
	{
		Gift* q = p->next;
		Gift* tar = q;
		while(q)
		{
			if(q->gif_year < tar->gif_year) tar = q;
			else if(q->gif_month < tar->gif_month) tar = q;
			else if(q->gif_day < tar->gif_day) tar = q;
			q = q->next;
		}
		if(p->next == tar)
			p = p->next;
		else if(tar->next == NULL)
		{
			tar->pre->next = NULL;
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			p = p->next;
		}
		else
		{
			
			tar->pre->next = tar->next;
			tar->next->pre = tar->pre; // ɾ��
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			p = p->next;
		}
	}
	//������� 
	Gift* q = Gift_head->next;
	int i = 1;
	while(q)
	{
		q->reorder = i++;
		q = q->next;
	}
	UpdateGift();
	return; 
}

void deltegift(){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n"); 
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t                 ��Ʒɾ��                \n");
		printf("\t\t\t\t\t         (����0���Է�����һ������)       \n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		if(Gift_head->next == NULL)
		{
			PrintGift();
			pau;
			return;
		}
		PrintGift();
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t ����������Ҫɾ������Ʒ���:");
		int giftid;
		giftid = checkNum(); 
		if(giftid == -1){
			RefreshPage();continue;
		}
		if(giftid == 0) return;
		Gift* q = Gift_head->next;
		while(q)
		{
			if(q->reorder = giftid) break;
			q = q->next;
		}
		if(q == NULL){
			printf("\t\t\t\t\t ������������δ�ҵ��ñ����Ʒ�����������룡");
			pau;
		}
		else{
			Gift* temp = q;
			q = q->pre;
			q->next = q->next->next;
			free(temp);
			printf("\t\t\t\t\t    ���ѳɹ�ɾ������Ʒ��");
			pau;
		}
		//������� 
		q = Gift_head->next;
		int i = 1;
		while(q)
		{
			q->reorder = i++;
			q = q->next;
		}
		UpdateGift();
	}
	
}


void reducegift(Gift* tar, int num){              // ������Ʒ 
	if(tar->bottle > num) tar->bottle-=num;
	else if(tar->bottle == num)            // ɾ������Ʒ 
	{
		if(tar->next == NULL)
		{
			Gift* temp = tar->pre;
			temp->next = temp->next->next;
		}
		else {
			Gift* temp = tar->pre;
			temp->next = temp->next->next;
			temp->next->pre = temp;
		}
	}
	Giftsort(Gift_head);//������� 
}



void wornout(ProductSource* tar, int amount){ // ��Ʒ�Ĳ����� 
	int odds = rand()%10;
	if(odds == 1) 
	{
		int n = (int) (amount/10);   //n�� 
		int loss = rand()%2+1;      // �����ʧ1��2ƿ 
		int num_gift = n * (tar->packagingsize_sou - loss);
		//ֱ������Ʒ�в��� 
		Gift* p = Gift_head->next;
		Gift* temp = Gift_head;
		int i = 0;
		while(p)
		{
			i++;
			if(p->brand==tar->BrandNumber_sou&&p->product==tar->ProductNumber_sou&& p->gif_volume == tar->volume_sou  &&p->gif_year==tar->quality_year_sou&&p->gif_month==tar->quality_month_sou&&p->gif_day==tar->quality_day_sou)
			{
				p->bottle += num_gift;
				break;
			}
			p = p->next;
			if(p) temp = p;
		}
		if(p==NULL) 
		{
			Gift* newgift = (Gift*)malloc(sizeof(Gift));
			temp->next = newgift;
			newgift->next = NULL;
			newgift->pre = temp;
			newgift->reorder = ++i;
			newgift->brand = tar->BrandNumber_sou;
			newgift->product = tar->ProductNumber_sou;
			newgift->bottle = num_gift;
			newgift->gif_year=tar->quality_year_sou;
			newgift->gif_month=tar->quality_month_sou;
			newgift->gif_day=tar->quality_day_sou;
			newgift->value = (tar->Price_sou)/(tar->packagingsize_sou);
			newgift->gif_volume = tar->volume_sou;
		}
		UpdateGift();
		PrintGift();
		pau;
		printf("\t\t\t ���ź�������;����%d������������,����ʧ%dƿ��ˮ��\n", n,loss);
		printf("\t\t\t  ����%dƿ��ˮ���޷�����, �ѳɹ�������Ʒ�У�\n", num_gift);
		
		//��������//
		addinwarehouse(tar , amount - n); 
		printf("\t\t\t  ʣ��%d���ˮ����, �ѳɹ�������棡\n", amount-n);
		UpdateInventory();
	}
	else
	{
		
		printf("\t\t\t ����;�������ⷢ��, �����԰�ȫ�ʹ�ֿ⣡\n");
		addinwarehouse(tar, amount);
		UpdateInventory();
	}
	return; 
}






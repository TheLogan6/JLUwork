#include"warehouse.h"

extern char* code[12][5];
extern Inventory* Inv_head;
extern ProductSource* Sou_head;
extern int total_brand;
extern SpecialInv* SpeInv_head;

void encode_product(){
	code[1][0] = "ũ��ɽȪ";code[1][1] = "����ˮ", code[1][2] = "��Ȫˮ" ;code[1][3] = "���ζ���";
	code[2][0] = "��Դ"; code[2][1] = "ƻ��֭"; code[2][2] = "����֭"; code[2][3] = "����֭";
	code[3][0] = "�ൺơ��" ; code[3][1] = "�ൺ����"; code[3][2] = "�ൺС��ƿ" ;
	code[4][0] = "���"; code[4][1] = "ˮ�����"; code[4][2] = "�������" ;
	code[5][0] = "����Һ"; code[5][1] = "������"; code[5][2] = "������"; code[5][3] = "�ƽ��";
	code[6][0] = "��ʦ��" ;code[6][1] = "�����"; code[6][2] = "���̲�"; code[6][3] = "����ѩ��";
	code[7][0] = "�޹���"; code[7][1] = "Ӫ������"; 
}

Inventory* InitInventory(){
	Inventory* Inv_head = (Inventory*)malloc(sizeof(Inventory));  // ��λ�ڵ� 
	Inv_head->pre = NULL;
	Inv_head->next = NULL;
	Inventory* Inv_tail = Inv_head;                    // βָ�� 
	FILE* Storehouse_fp;
	Storehouse_fp = fopen("�ֿ�.txt","r+");
	if(Storehouse_fp == NULL){
		printf("Storehousefile cannot open, error happens!");
		exit(-1);
	}

	while(!feof(Storehouse_fp))
	{
//		char garbage[50];
//		fgets(garbage, sizeof(Inventory), Storehouse_fp);
		Inventory* p = (Inventory*)malloc(sizeof(Inventory));
		fscanf(Storehouse_fp, "%s", p->DrinksBrand);
//		fgets(p->DrinksBrand, 20, fp);
		fscanf(Storehouse_fp, "%d%d%d%d%d%d", &p->BrandNumber, &p->ProductNumber, &p->SpecificationNumber, &p->volume, &p->Reserve, &p->packagingsize);
		fscanf(Storehouse_fp, "%f\n", &p->Price);
		fscanf(Storehouse_fp, "%d%d%d\n", &p->quality_year, &p->quality_month, &p->quality_day);	
		p->pre = Inv_tail;
		p->next = NULL;
		Inv_tail->next = p;
		Inv_tail = p;
	} 
	return Inv_head;
} 

void PrintInventory(Inventory* Inv_head){
	Inventory* p = Inv_head->next;
//	printf("  ��ˮƷ��   |  Ʒ�Ʊ�� |   ��Ʒ��   |��Ʒ���| ������С | ��װ��С | ������� |  �������\n");
//	while(p)
//	{
//		printf("%-20s", p->DrinksBrand);
//		printf("%-9d%", p->BrandNumber);
//		printf("%-15s", code[p->BrandNumber][p->ProductNumber]);
//		printf("%-7d%-11d%-11d%-9d", p->SpecificationNumber, p->volume, p->packagingsize, p->Reserve); 
//		printf("%-10.2f\n", p->Price);
//		p = p->next;
//	}
	printf("  ��ˮƷ��  | Ʒ�Ʊ�� |   ��Ʒ����   | ��Ʒ��� | ������С | ��װ��С | ������� |   �۸�   |          ������\n");
	while(p)
	{
		printf("%-18s%-9d", p->DrinksBrand, p->BrandNumber);
		printf("%-16s", code[p->BrandNumber][p->ProductNumber]);
		printf("%-10d%-10d%-11d%-11d", p->SpecificationNumber, p->volume, p->packagingsize, p->Reserve);
		if(p->Reserve == 0) printf("(������)");
		printf("%-12.2f   ", p->Price);
		printf("%d��%d��%d��\n", p->quality_year, p->quality_month, p->quality_day);
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
    FILE* newstorehouse_fp = fopen("�²ֿ�.txt", "w");
    if (newstorehouse_fp == NULL)
    {
        printf("NewstorehouseFile cannot open, error happens!");
        exit(-1);
    }
    //fprintf(newstorehouse_fp, "��ˮƷ��   |  Ʒ�Ʊ�� |   ��Ʒ���   |�����| ������С | ��װ��С | ������� |  �������\n");
    Inventory* p = Inv_head->next;
    while (p != NULL)
    {
        fprintf(newstorehouse_fp, "%-20s", p->DrinksBrand);
		fprintf(newstorehouse_fp, "%-9d%-9d", p->BrandNumber, p->ProductNumber);
		fprintf(newstorehouse_fp, "%-9d%-9d%-9d%-9d", p->SpecificationNumber, p->volume, p->packagingsize, p->Reserve); 
		fprintf(newstorehouse_fp, "%-15.2f\n", p->Price);
		p = p->next;
    }
    fclose(newstorehouse_fp);
    return;
}


void ChangeInventory(){
	while(1)
	{
		system("cls");
		printf("\t\t----------------------------�޸���Ʒ��Ϣ����-----------------------------\n");
		printf("\t\t                       (����0���Է�����һ������)\n") ;
		PrintInventory(Inv_head);
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		printf("\t\t\t��ѡ����Ҫ���ĵ�Ʒ�Ʊ�ţ�");
		scanf("%s", ChooseBrand_s);
		ChooseBrand = inputcheck(ChooseBrand_s);
		if(ChooseBrand == 0) return;
		else if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		printf("\t\t\t��ѡ����Ҫ���ĵĲ�Ʒ��ţ�");
		scanf("%s", ChooseProduct_s);
		ChooseProduct = inputcheck(ChooseProduct_s);
		int maxnum1 = countSpecification(ChooseBrand);
		if(ChooseProduct == -1 || ChooseProduct > maxnum1){
			RefreshPage();
			continue;
		}
		Inventory* tar = FindInventory(ChooseBrand, ChooseProduct);
		if(!tar)
		{
			printf("�Ҳ�������Ʒ��������������\n");
			printf("�밴�����ˢ�º��������룡");
			system("pause");
			continue;
		}
		else
		{
			while(1)
			{
				system("cls");
				printf("\n\n\n\n");
				printf("\t\t-----------------------�޸���Ʒ��Ϣ����-----------------------\n");
				printf("\t\t                  (����0���Է�����һ������)\n") ;	
				printf("  ��ˮƷ��  | Ʒ�Ʊ�� |   ��Ʒ����   | ��Ʒ��� | ������С | ��װ��С | ������� |   �۸�   |          ������\n");
				printf("%-18s%-9d", tar->DrinksBrand, tar->BrandNumber);
				printf("%-16s", code[tar->BrandNumber][tar->ProductNumber]);
				printf("%-10d%-10d%-11d%-11d", tar->SpecificationNumber, tar->volume, tar->packagingsize, tar->Reserve);
				if(tar->Reserve == 0) printf("(������)");
				printf("%-12.2f   ", tar->Price);
				printf("%d��%d��%d��\n", tar->quality_year, tar->quality_month, tar->quality_day);

				printf("\t\t\t\t\t  1. �޸Ŀ������\n");
				printf("\t\t\t\t\t  2. �޸������۸�\n");
				printf("\t\t\t\t\t  3. �޸ı�����(��)\n");
				printf("\t\t\t\t\t  3. ɾ������Ʒ\n");
				printf("\t\t\t\t\t ��ѡ����Ҫ���еĲ�����");
				int ChangeInfo;
				char ChangeInfo_s[5];
				scanf("%s", ChangeInfo_s);
				ChangeInfo = inputcheck(ChangeInfo_s);
				if(ChangeInfo == -1 || ChangeInfo > 3) {
					RefreshPage();
					continue;
				}
				if(ChangeInfo == 0) break;
				switch(ChangeInfo){
					case(1):{   ////�޸Ŀ������ 
						printf("\t\t\t\t\t�������µĿ������(���ó�����������)��");
						int NewReserve;
						char NewReserve_s[6];
						scanf("%s", NewReserve_s);
						NewReserve = inputcheck(NewReserve_s);
						if(NewReserve == -1 || NewReserve > 1000) {
							RefreshPage();
							continue;
						}
						tar->Reserve = NewReserve;
						UpdateInventory();
						printf("\t\t\t\t���ѳɹ��޸Ŀ���������������ˢ�£�");
						system("pause");
						break;
					}
					case(2):{ // �޸ļ۸� 
						printf("\t\t\t\t�������µ������۸�(ֻ������λС���Ҳ���С��1Ԫ)��");
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
						printf("\t\t\t\t���ѳɹ��޸ļ۸񣬰������ˢ�£�");
						system("pause");
						break;
					}
//					case(3):{  // �޸���Ʒ������ 
//						printf("\t\t\t�������µ���Ʒ������:");
//						printf("\t\t\t  �꣺\n");
//						int year, month, day;
//						char year_s[5], month_s[5], day_s[5];
//						scanf("%s", year_s);
//						printf("\t\t\t  �£�");
//						scanf("%s", month_s);
//						printf("\t\t\t  �գ�");
//						scanf("%s", day_s);
//						year = inputcheck(year_s);
//						month = inputcheck(month_s);
//						year = inputcheck(year_s);
//					}
					case(3):{ // ɾ����Ʒ 
						printf("\t\t\t\t\t ��ȷ��Ҫɾ������Ʒ��\n");
						printf("\t\t\t\t\t    1.Yes\n");
						printf("\t\t\t\t\t    2.No\n\t\t\t\t\t     ");
						int checkdelete;
						char checkdelete_s[6];
						scanf("%s", checkdelete_s);
						checkdelete = inputcheck(checkdelete_s);
						if(checkdelete == -1 || checkdelete == 0) {
							RefreshPage();
							continue;
						}
						if(checkdelete == 1) {
							Inventory* fro = tar->pre;
							fro->next = fro->next->next;
							if(fro->next != NULL)  // ɾ�����һ��Ԫ�� 
								fro->next->pre = fro;
							// �������
							Inventory* temp = Inv_head->next;
							while(temp)
							{
								if(temp->BrandNumber == ChooseBrand && temp->SpecificationNumber > ChooseProduct)
									temp->SpecificationNumber -- ;
								temp = temp->next;
							}// �������
							
							UpdateInventory(); 
							printf("\t\t\t���ѳɹ��޸����ݣ����������������һ�����棡");
							pau;return;
						}
						else if(checkdelete == 2){
							printf("\t\t\t��δɾ�������ݣ����������ˢ�¸ý��棡");
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



/*---------------------------------�������ָ���--------------------------------------------*/ 

void InventorySortMode(){
	while(1)
	{
		system("cls");
		int sortmode;
		char sortmode_s[5];
		printf("\t\t\t\t--------------�����Ϣ��ѯ����------------------\n");
		printf("\t\t\t\t    (����0���Է�����һ������)\n") ;	
		printf("\t\t\t\t     1. ����Ʒ���(Ĭ��)\n"); 
		printf("\t\t\t\t     2. �����������С\n"); 
		printf("\t\t\t\t     3.  ���۸�ߵ�\n"); 
		printf("\t\t\t\t    ��ѡ������Ҫ����ķ�ʽ��");
		scanf("%s", sortmode_s);
		
		sortmode = inputcheck(sortmode_s);
		if(sortmode == -1){
			RefreshPage();
			continue;
		}
		if(sortmode == 0) break;
		switch(sortmode){
			case(1):{
				SortByNumber(Inv_head);
				PrintInventory(Inv_head);
				printf("\t\t  �������ˢ�½�������ѡ������ʽ\n");
				pau;
				break;
			}
			case(2):{
				SortByReserve(Inv_head);
				PrintInventory(Inv_head);
				SortByNumber(Inv_head);
				printf("\t\t  �������ˢ�½�������ѡ������ʽ\n");
				pau;
				break;
			}
			case(3):{
				SortByPrice(Inv_head);
				PrintInventory(Inv_head);
				SortByNumber(Inv_head);
				printf("\t\t  �������ˢ�½�������ѡ������ʽ\n");
				pau;
				break;
			}
			default: RefreshPage();continue;
		}
	} 
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
	while(!feof(source_fp))
	{
		ProductSource* p = (ProductSource*)malloc(sizeof(ProductSource));
		fscanf(source_fp, "%s", p->DrinksBrand_sou);
//		fgets(p->DrinksBrand, 20, fp);
		fscanf(source_fp, "%d%d%d%d%d", &p->BrandNumber_sou, &p->ProductNumber_sou, &p->SpecificationNumber_sou, &p->volume_sou, &p->packagingsize_sou);
		fscanf(source_fp, "%f\n", &p->Price_sou);	
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
	printf("  ��ˮƷ��  | Ʒ�Ʊ�� |   ��Ʒ����   | ��Ʒ��� | ������С | ��װ��С |  �۸�  |          ������\n");
	while(p)
	{
		printf("%-18s%-9d", p->DrinksBrand_sou, p->BrandNumber_sou);
		printf("%-16s", code[p->BrandNumber_sou][p->ProductNumber_sou]);
		printf("%-10d%-9d%-11d", p->SpecificationNumber_sou, p->volume_sou, p->packagingsize_sou);
		printf("%-12.2f   ", p->Price_sou);
		printf("%d��%d��%d��\n", p->quality_year_sou, p->quality_month_sou, p->quality_day_sou);
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
		if(p->BrandNumber_sou == Brand && p->SpecificationNumber_sou)
			return p;
	}
	return NULL;
}

int timegap(int x1, int y1, int z1, int x2, int y2, int z2){ // 1�Ǳ������� 
//	printf("%d %d %d %d %d %d",x1,y1,z1,x2,y2,z2);
	return (x1-x2)*365 + (y1-y2)* 30 + (z1-z2);
}



SpecialInv* InitSpecialInv(){
	SpecialInv* head = (SpecialInv*)malloc(sizeof(SpecialInv));
	head->next = NULL;
	SpecialInv* tail = head;
	time_t timep;
	struct tm *p;
    time(&timep);
    p = localtime(&timep); //ȡ�õ��ؾ���ʱ��
//    printf("%d %d %d ", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday);
	Inventory* q = Inv_head->next;
	while(q)
	{
		if(timegap(q->quality_year,q->quality_month,q->quality_day,1900+p->tm_year, 1+p->tm_mon, p->tm_mday) < 60 ){
			SpecialInv* node = (SpecialInv*)malloc(sizeof(SpecialInv));
			node->Pro = q;
			node->next = NULL;
			node->pre = tail;
			node->SpecialPrice = q->Price * 0.6;
			tail->next = node;
			tail = node;
		}
		q = q->next;
	}
	return head;
} 

void PrintSpecialInv(){
	SpecialInv* p = SpeInv_head->next;
	printf("  ��ˮƷ��  | Ʒ�Ʊ�� |   ��Ʒ����   | ��Ʒ��� | ������С | ��װ��С |  �����۸�  |          ������\n");
	while(p)
	{
		printf("%-18s%-9d", p->Pro->DrinksBrand, p->Pro->BrandNumber);
		printf("%-16s", code[p->Pro->BrandNumber][p->Pro->ProductNumber]);
		printf("%-10d%-9d%-11d", p->Pro->SpecificationNumber, p->Pro->volume, p->Pro->packagingsize);
		printf("%-12.2f   ", p->Pro->Price);
		printf("%d��%d��%d��\n", p->Pro->quality_year, p->Pro->quality_month, p->Pro->quality_day);
		p = p->next;	
	}	
}

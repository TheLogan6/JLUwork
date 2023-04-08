#include"warehouse.h"

extern char* code[12][5];
extern Inventory* Inv_head;
extern ProductSource* Sou_head;
extern int total_brand;
extern SpecialInv* SpeInv_head;

void encode_product(){
	code[1][0] = "农夫山泉";code[1][1] = "纯净水", code[1][2] = "矿泉水" ;code[1][3] = "红茶味茶π";
	code[2][0] = "汇源"; code[2][1] = "苹果汁"; code[2][2] = "葡萄汁"; code[2][3] = "葡萄汁";
	code[3][0] = "青岛啤酒" ; code[3][1] = "青岛纯生"; code[3][2] = "青岛小棕瓶" ;
	code[4][0] = "舍得"; code[4][1] = "水晶舍得"; code[4][2] = "至尊舍得" ;
	code[5][0] = "五粮液"; code[5][1] = "剑兰春"; code[5][2] = "五粮春"; code[5][3] = "黄金酒";
	code[6][0] = "康师傅" ;code[6][1] = "冰红茶"; code[6][2] = "冰绿茶"; code[6][3] = "冰糖雪梨";
	code[7][0] = "娃哈哈"; code[7][1] = "营养快线"; 
}

Inventory* InitInventory(){
	Inventory* Inv_head = (Inventory*)malloc(sizeof(Inventory));  // 哨位节点 
	Inv_head->pre = NULL;
	Inv_head->next = NULL;
	Inventory* Inv_tail = Inv_head;                    // 尾指针 
	FILE* Storehouse_fp;
	Storehouse_fp = fopen("仓库.txt","r+");
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
//	printf("  酒水品牌   |  品牌编号 |   商品名   |商品编号| 容量大小 | 包装大小 | 库存容量 |  批量标价\n");
//	while(p)
//	{
//		printf("%-20s", p->DrinksBrand);
//		printf("%-9d%", p->BrandNumber);
//		printf("%-15s", code[p->BrandNumber][p->ProductNumber]);
//		printf("%-7d%-11d%-11d%-9d", p->SpecificationNumber, p->volume, p->packagingsize, p->Reserve); 
//		printf("%-10.2f\n", p->Price);
//		p = p->next;
//	}
	printf("  酒水品牌  | 品牌编号 |   商品名称   | 商品编号 | 容量大小 | 包装大小 | 库存容量 |   价格   |          保质期\n");
	while(p)
	{
		printf("%-18s%-9d", p->DrinksBrand, p->BrandNumber);
		printf("%-16s", code[p->BrandNumber][p->ProductNumber]);
		printf("%-10d%-10d%-11d%-11d", p->SpecificationNumber, p->volume, p->packagingsize, p->Reserve);
		if(p->Reserve == 0) printf("(已售罄)");
		printf("%-12.2f   ", p->Price);
		printf("%d年%d月%d日\n", p->quality_year, p->quality_month, p->quality_day);
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
    FILE* newstorehouse_fp = fopen("新仓库.txt", "w");
    if (newstorehouse_fp == NULL)
    {
        printf("NewstorehouseFile cannot open, error happens!");
        exit(-1);
    }
    //fprintf(newstorehouse_fp, "酒水品牌   |  品牌编号 |   商品编号   |规格编号| 容量大小 | 包装大小 | 库存容量 |  批量标价\n");
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
		printf("\t\t----------------------------修改商品信息界面-----------------------------\n");
		printf("\t\t                       (输入0可以返回上一个界面)\n") ;
		PrintInventory(Inv_head);
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		printf("\t\t\t请选择你要更改的品牌编号：");
		scanf("%s", ChooseBrand_s);
		ChooseBrand = inputcheck(ChooseBrand_s);
		if(ChooseBrand == 0) return;
		else if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		printf("\t\t\t请选择你要更改的产品编号：");
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
			printf("找不到该商品，您的输入有误！\n");
			printf("请按任意键刷新后重新输入！");
			system("pause");
			continue;
		}
		else
		{
			while(1)
			{
				system("cls");
				printf("\n\n\n\n");
				printf("\t\t-----------------------修改商品信息界面-----------------------\n");
				printf("\t\t                  (输入0可以返回上一个界面)\n") ;	
				printf("  酒水品牌  | 品牌编号 |   商品名称   | 商品编号 | 容量大小 | 包装大小 | 库存容量 |   价格   |          保质期\n");
				printf("%-18s%-9d", tar->DrinksBrand, tar->BrandNumber);
				printf("%-16s", code[tar->BrandNumber][tar->ProductNumber]);
				printf("%-10d%-10d%-11d%-11d", tar->SpecificationNumber, tar->volume, tar->packagingsize, tar->Reserve);
				if(tar->Reserve == 0) printf("(已售罄)");
				printf("%-12.2f   ", tar->Price);
				printf("%d年%d月%d日\n", tar->quality_year, tar->quality_month, tar->quality_day);

				printf("\t\t\t\t\t  1. 修改库存容量\n");
				printf("\t\t\t\t\t  2. 修改批发价格\n");
				printf("\t\t\t\t\t  3. 修改保质期(无)\n");
				printf("\t\t\t\t\t  3. 删除该商品\n");
				printf("\t\t\t\t\t 请选择你要进行的操作：");
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
					case(1):{   ////修改库存容量 
						printf("\t\t\t\t\t请输入新的库存容量(不得超过库存最大量)：");
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
						printf("\t\t\t\t您已成功修改库存容量，按任意键刷新！");
						system("pause");
						break;
					}
					case(2):{ // 修改价格 
						printf("\t\t\t\t请输入新的批发价格(只保留两位小数且不得小于1元)：");
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
						printf("\t\t\t\t您已成功修改价格，按任意键刷新！");
						system("pause");
						break;
					}
//					case(3):{  // 修改商品保质期 
//						printf("\t\t\t请输入新的商品保质期:");
//						printf("\t\t\t  年：\n");
//						int year, month, day;
//						char year_s[5], month_s[5], day_s[5];
//						scanf("%s", year_s);
//						printf("\t\t\t  月：");
//						scanf("%s", month_s);
//						printf("\t\t\t  日：");
//						scanf("%s", day_s);
//						year = inputcheck(year_s);
//						month = inputcheck(month_s);
//						year = inputcheck(year_s);
//					}
					case(3):{ // 删除商品 
						printf("\t\t\t\t\t 你确认要删除该商品吗？\n");
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
							if(fro->next != NULL)  // 删除最后一个元素 
								fro->next->pre = fro;
							// 编号重排
							Inventory* temp = Inv_head->next;
							while(temp)
							{
								if(temp->BrandNumber == ChooseBrand && temp->SpecificationNumber > ChooseProduct)
									temp->SpecificationNumber -- ;
								temp = temp->next;
							}// 编号重排
							
							UpdateInventory(); 
							printf("\t\t\t您已成功修改数据，按任意键返回至上一个界面！");
							pau;return;
						}
						else if(checkdelete == 2){
							printf("\t\t\t您未删除该数据，按任意键可刷新该界面！");
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



/*---------------------------------库存排序分割线--------------------------------------------*/ 

void InventorySortMode(){
	while(1)
	{
		system("cls");
		int sortmode;
		char sortmode_s[5];
		printf("\t\t\t\t--------------库存信息查询界面------------------\n");
		printf("\t\t\t\t    (输入0可以返回上一个界面)\n") ;	
		printf("\t\t\t\t     1. 按产品编号(默认)\n"); 
		printf("\t\t\t\t     2. 按库存容量大小\n"); 
		printf("\t\t\t\t     3.  按价格高低\n"); 
		printf("\t\t\t\t    请选择您想要排序的方式：");
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
				printf("\t\t  按任意键刷新界面重新选择排序方式\n");
				pau;
				break;
			}
			case(2):{
				SortByReserve(Inv_head);
				PrintInventory(Inv_head);
				SortByNumber(Inv_head);
				printf("\t\t  按任意键刷新界面重新选择排序方式\n");
				pau;
				break;
			}
			case(3):{
				SortByPrice(Inv_head);
				PrintInventory(Inv_head);
				SortByNumber(Inv_head);
				printf("\t\t  按任意键刷新界面重新选择排序方式\n");
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
//--------------------------------------------------库存排序方式
void SortByNumber(Inventory* Inv_head){
	Inventory* p = Inv_head;  // 插入在p点的后面  , 从小到大 
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
			tar->next->pre = tar->pre; // 删除
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			p = p->next;
		}	
	}
}
void SortByReserve(Inventory* Inv_head){
	Inventory* p = Inv_head;  // 插入在p点的后面  , 从小到大 
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
			tar->next->pre = tar->pre; // 删除
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
			tar->next->pre = tar->pre; // 删除
			 
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			
			p = p->next;
		}	
	}
} 


/*---------------------------   货源分割线----------------------------*/ 

ProductSource* ReadSource(){
	ProductSource* Sou_head = (ProductSource*)malloc(sizeof(ProductSource));  // 哨位节点 
	Sou_head->pre = NULL;
	Sou_head->next = NULL;
	ProductSource* Sou_tail = Sou_head;                    // 尾指针 
	FILE* source_fp;
	source_fp = fopen("货源.txt","r+");
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
	printf("  酒水品牌  | 品牌编号 |   商品名称   | 商品编号 | 容量大小 | 包装大小 |  价格  |          保质期\n");
	while(p)
	{
		printf("%-18s%-9d", p->DrinksBrand_sou, p->BrandNumber_sou);
		printf("%-16s", code[p->BrandNumber_sou][p->ProductNumber_sou]);
		printf("%-10d%-9d%-11d", p->SpecificationNumber_sou, p->volume_sou, p->packagingsize_sou);
		printf("%-12.2f   ", p->Price_sou);
		printf("%d年%d月%d日\n", p->quality_year_sou, p->quality_month_sou, p->quality_day_sou);
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

int timegap(int x1, int y1, int z1, int x2, int y2, int z2){ // 1是保质期限 
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
    p = localtime(&timep); //取得当地具体时间
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
	printf("  酒水品牌  | 品牌编号 |   商品名称   | 商品编号 | 容量大小 | 包装大小 |  促销价格  |          保质期\n");
	while(p)
	{
		printf("%-18s%-9d", p->Pro->DrinksBrand, p->Pro->BrandNumber);
		printf("%-16s", code[p->Pro->BrandNumber][p->Pro->ProductNumber]);
		printf("%-10d%-9d%-11d", p->Pro->SpecificationNumber, p->Pro->volume, p->Pro->packagingsize);
		printf("%-12.2f   ", p->Pro->Price);
		printf("%d年%d月%d日\n", p->Pro->quality_year, p->Pro->quality_month, p->Pro->quality_day);
		p = p->next;	
	}	
}

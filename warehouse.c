#include"warehouse.h"

extern char* code[12][10];
extern Inventory* Inv_head;
extern ProductSource* Sou_head;
extern int total_brand;
extern Gift* Gift_head;

void encode_product(){
	code[1][0] = "农夫山泉";code[1][1] = "纯净水", code[1][2] = "矿泉水" ;code[1][3] = "红茶味茶π";code[1][3] = "元气森林";
	code[2][0] = "汇源"; code[2][1] = "苹果汁"; code[2][2] = "葡萄汁"; code[2][3] = "葡萄汁";
	code[3][0] = "青岛啤酒" ; code[3][1] = "青岛纯生"; code[3][2] = "青岛小棕瓶" ;
	code[4][0] = "舍得"; code[4][1] = "水晶舍得"; code[4][2] = "至尊舍得" ;
	code[5][0] = "五粮液"; code[5][1] = "剑兰春"; code[5][2] = "五粮春"; code[5][3] = "黄金酒";
	code[6][0] = "康师傅" ;code[6][1] = "冰红茶"; code[6][2] = "冰绿茶"; code[6][3] = "冰糖雪梨";
	code[7][0] = "娃哈哈"; code[7][1] = "营养快线"; code[7][2] = "AD钙奶"; 
	code[8][0]="喜茶"        ;  code[8][1] = "喜小瓶气泡水";
	code[9][0]="可口可乐"    ; code[9][1] = "可乐";code[9][1] = "雪碧";
	code[10][0]="大窑嘉宾"   ;    code[10][1] = "大窑橙味";
}

Inventory* InitInventory(){
	Inventory* Inv_head = (Inventory*)malloc(sizeof(Inventory));  // 哨位节点 
	Inv_head->pre = NULL;
	Inv_head->next = NULL;
	Inventory* Inv_tail = Inv_head;                    // 尾指针 
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
		printf("\t\t\t\t\t            暂无任何商品！\n");
		pau;
		return;
	}
	printf("\t  酒水品牌  | 品牌编号 |   商品名称   | 商品编号 | 容量大小 | 包装大小 | 库存容量 |     价格     |       保质期\n");
	while(p)
	{
		printf("\t  %-15s%-9d", code[p->BrandNumber][0], p->BrandNumber);
		printf(" %-16s", code[p->BrandNumber][p->ProductNumber]);
		printf("%-10d%-10d %-11d", p->SpecificationNumber, p->volume, p->packagingsize, p->Reserve);
		if(p->Reserve == 0) printf("(已售罄)   ");
		else printf(" %-11d", p->Reserve);
		printf("%-12.2f  ", p->Price);
		printf(" %d年%d月%d日\n", p->quality_year, p->quality_month, p->quality_day);
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
    //fprintf(newstorehouse_fp, "酒水品牌   |  品牌编号 |   商品编号   |规格编号| 容量大小 | 包装大小 | 库存容量 |  批量标价\n");
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
    	printf("\t\t\t\t\t            修改商品信息界面             \n");
    	printf("\t\t\t\t\t         (输入0可返回上一个界面)         \n"); 
    	printf("\t\t\t\t\t --------------------------------------- \n");
		PrintInventory(Inv_head);
		if(Inv_head->next == NULL){
			return;
		}
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t  请选择你要更改的品牌编号：");
		ChooseBrand = checkNum();
		if(ChooseBrand == 0) return;
		else if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		printf("\t\t\t\t  请选择你要更改的产品编号：");
		ChooseProduct = checkNum();
		int maxnum1 = countSpecification(ChooseBrand);
		if(ChooseProduct == -1 || ChooseProduct > maxnum1){
			RefreshPage();
			continue;
		}
		Inventory* tar = FindInventory(ChooseBrand, ChooseProduct);
		if(tar == NULL)
		{
			printf("\t\t\t\t  找不到该商品，您的输入有误！\n");
			printf("\t\t\t\t  请按任意键刷新后重新输入！");
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
		    	printf("\t\t\t\t\t            修改商品信息界面             \n");
		    	printf("\t\t\t\t\t         (输入0可返回上一个界面)         \n"); 
		    	printf("\t\t\t\t\t --------------------------------------- \n");
				printf("\t  酒水品牌  | 品牌编号 |   商品名称   | 商品编号 | 容量大小 | 包装大小 | 库存容量 |   价格   |          保质期\n");
				printf("\t%-17s%-9d ", tar->DrinksBrand, tar->BrandNumber);
				printf("%-16s", code[tar->BrandNumber][tar->ProductNumber]);
				printf("%-10d%-10d%-11d", tar->SpecificationNumber, tar->volume, tar->packagingsize);
				if(tar->Reserve == 0) printf("(已售罄)    ");
				else printf("%-11d", tar->Reserve);
				printf("%-12.2f   ", tar->Price);
				printf("%d年%d月%d日\n", tar->quality_year, tar->quality_month, tar->quality_day);
				printf("\t\t\t\t\t --------------------------------------- \n");
			    printf("\t\t\t\t\t                                        \n");
			    printf("\t\t\t\t\t         (1).   修改库存容量            \n");
			    printf("\t\t\t\t\t         (2).   修改批发价格            \n");
			    printf("\t\t\t\t\t         (3).    下架该商品             \n");
			    printf("\t\t\t\t\t         (0).  返回上一个界面           \n");
				printf("\t\t\t\t\t                                        \n");
				printf("\t\t\t\t\t --------------------------------------- \n");

				printf("\t\t\t\t\t 请选择你要进行的操作：");
				int ChangeInfo;
				char ChangeInfo_s[5];
				ChangeInfo = checkNum();
				if(ChangeInfo == -1 || ChangeInfo > 3) {
					RefreshPage();
					continue;
				}
				if(ChangeInfo == 0) break;
				switch(ChangeInfo){
					case(1):{   ////修改库存容量 
						printf("\t\t\t\t  请输入新的库存容量(不得超过库存最大量)：");
						int NewReserve;
						char NewReserve_s[6];
						NewReserve = checkNum();
						if(NewReserve == -1 || NewReserve > 1000) {
							RefreshPage();
							continue;
						}
						tar->Reserve = NewReserve;
						UpdateInventory();
						printf("\t\t\t\t  您已成功修改库存容量，按任意键刷新！");
						system("pause");
						break;
					}
					case(2):{ // 修改价格 
						printf("\t\t\t\t  请输入新的批发价格(只保留两位小数且不得小于1元)：");
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
						printf("\t\t\t\t  您已成功修改价格，按任意键刷新！");
						system("pause");
						break;
					}
					case(3):{ // 删除商品 
						printf("\t\t\t\t\t --------------------------------------- \n");
						printf("\t\t\t\t\t             1. Yes\n");
						printf("\t\t\t\t\t             2. No\n  ");
						printf("\t\t\t\t\t        你确认要下架该商品吗？");
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
//							if(fro->next != NULL)  // 删除最后一个元素 
//								fro->next->pre = fro;
//							// 编号重排
//							Inventory* temp = Inv_head->next;
//							while(temp)
//							{
//								if(temp->BrandNumber == ChooseBrand && temp->SpecificationNumber > ChooseProduct)
//									temp->SpecificationNumber -- ;
//								temp = temp->next;
//							}// 编号重排
							tar->Reserve = 0;
							UpdateInventory(); 
							printf("\t\t\t\t  您已成功修改数据，按任意键返回至上一个界面！");
							pau;continue;
						}
						else if(checkdelete == 2){
							printf("\t\t\t\t  您未删除该数据，按任意键可刷新该界面！");
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
		printf("\t\t\t\t\t               查询商品信息              \n");
		printf("\t\t\t\t\t           (输入0可返回上一个界面)       \n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t 请输入你要查询的商品品牌名称: ");
		
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
			printf("\t\t\t\t\t 请检测您的输入有误，请按任意键刷新后重试！");
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
				if(flag == 1) printf("\t  酒水品牌  | 品牌编号 |   商品名称   | 商品编号 | 容量大小 | 包装大小 | 库存容量 |     价格     |       保质期\n");
				printf("\t  %-15s%-9d", code[p->BrandNumber][0], p->BrandNumber);
				printf(" %-16s", code[p->BrandNumber][p->ProductNumber]);
				printf("%-10d%-10d %-11d", p->SpecificationNumber, p->volume, p->packagingsize, p->Reserve);
				if(p->Reserve == 0) printf("(已售罄)   ");
				else printf(" %-11d", p->Reserve);
				printf("%-12.2f  ", p->Price);
				printf(" %d年%d月%d日\n", p->quality_year, p->quality_month, p->quality_day);
			}
			p = p->next;
		}
		if(flag == 0){
			printf("\t\t\t\t\t        库存中没有该商品！\n");
			printf("\t\t\t\t\t      按任意键刷新后可重新查询！\n");
			pau; 
			continue;
		}
		else{
			printf("\t\t\t\t\t --------------------------------------- \n");
			printf("\t\t\t\t\t      按任意键刷新后可重新查询！\n");
			pau;
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
		printf("\n\n\n\n"); 
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t               查看商品信息              \n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t|                                       |\n");
		printf("\t\t\t\t\t|         (1). 按产品编号(默认)         |\n");
		printf("\t\t\t\t\t|         (2). 按库存容量大小           |\n");
		printf("\t\t\t\t\t|         (3).   按价格高低             |\n");
		printf("\t\t\t\t\t|         (0).  返回上一个界面          |\n");
		printf("\t\t\t\t\t|                                       |\n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t 请选择您想要排序的方式：");
		
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
				printf("\t\t\t\t  按任意键刷新界面重新选择排序方式\n");
				pau;
				break;
			}
			case(2):{
				printf("\t\t\t\t\t --------------------------------------- \n");
				SortByReserve(Inv_head);
				PrintInventory(Inv_head);
				SortByNumber(Inv_head);
				printf("\t\t\t\t  按任意键刷新界面重新选择排序方式\n");
				pau;
				break;
			}
			case(3):{
				printf("\t\t\t\t\t --------------------------------------- \n");
				SortByPrice(Inv_head);
				PrintInventory(Inv_head);
				SortByNumber(Inv_head);
				printf("\t\t\t\t  按任意键刷新界面重新选择排序方式\n");
				pau;
				break;
			}
			default: RefreshPage();continue;
		}
	} 
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
	
	printf("\t  酒水品牌  | 品牌编号 |   商品名称   | 商品编号 | 容量大小 | 包装大小 |    价格    |            保质期\n");
	while(p)
	{
		printf("\t  %-15s%-9d", code[p->BrandNumber_sou][0], p->BrandNumber_sou);
		printf(" %-16s", code[p->BrandNumber_sou][p->ProductNumber_sou]);
		printf("%-10d%-10d %-11d ", p->SpecificationNumber_sou, p->volume_sou, p->packagingsize_sou);
		printf("%-12.2f   ", p->Price_sou);
		printf(" %d年%d月%d日\n", p->quality_year_sou, p->quality_month_sou, p->quality_day_sou);
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

/*--------------------------------------------------临期商品操作--------------------------*/ 
int timegap(int x1, int y1, int z1, int x2, int y2, int z2){ // 1是保质期限 
//	printf("%d %d %d %d %d %d",x1,y1,z1,x2,y2,z2);
	return (x1-x2)*365 + (y1-y2)* 30 + (z1-z2);
}

void JudgeNearexpiry(){
	Inventory* q = Inv_head->next;
	time_t timep;
	struct tm *p;
    time(&timep);
    p = localtime(&timep); //取得当地具体时间
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

	printf("\t  酒水品牌  | 品牌编号 |   商品名称   | 商品编号 | 容量大小 | 包装大小 | 库存容量 |   促销价格   |       保质期\n");
	while(p)
	{
		if(p->nearexpiry == 1)
		{
			
			printf("\t  %-15s%-9d", code[p->BrandNumber][0], p->BrandNumber);
			printf(" %-16s", code[p->BrandNumber][p->ProductNumber]);
			printf("%-10d%-10d %-11d ", p->SpecificationNumber, p->volume, p->packagingsize);
			if(p->Reserve == 0) printf("  (已售罄)  ");
			else printf("%-11d",p->Reserve); 
			printf("%-12.2f  ", p->Price);
			printf(" %d年%d月%d日\n", p->quality_year, p->quality_month, p->quality_day);
			p = p->next;
		}
		p = p->next;	
	}	
}



/*------------------------------------ 赠品操作-----------------------------------*/
Gift* InitGift(){
	Gift* Gift_head = (Gift*)malloc(sizeof(Gift));  // 哨位节点 
	Gift_head->pre = NULL;
	Gift_head->next = NULL;
	Gift* Gift_tail = Gift_head;                    // 尾指针 
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
		printf("\t\t\t\t\t       仓库中没有赠品！\n");
		return;
	} 
	printf("\t  赠品编号 | 酒水品牌  | 品牌编号 |   商品名称   | 容量大小 | 库存容量(瓶) |  商品价值  |       保质期\n");
	while(p)
	{
		printf("\t     %-8d%-15s%-9d", p->reorder, code[p->brand][0], p->brand);
		printf(" %-15s", code[p->brand][p->product]);
		printf("%-12d",p->gif_volume); 
		printf("%-14d",p->bottle); 
		printf("%-12.2f  ", p->value);
		printf("%d年%d月%d日\n", p->gif_year, p->gif_month, p->gif_day);
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
			tar->next->pre = tar->pre; // 删除
			tar->next = p->next;
			tar->pre = p;
			p->next->pre = tar;
			p->next = tar;
			p = p->next;
		}
	}
	//编号重排 
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
		printf("\t\t\t\t\t                 赠品删除                \n");
		printf("\t\t\t\t\t         (输入0可以返回上一个界面)       \n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		if(Gift_head->next == NULL)
		{
			PrintGift();
			pau;
			return;
		}
		PrintGift();
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t 请输入你想要删除的赠品编号:");
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
			printf("\t\t\t\t\t 您的输入有误，未找到该编号赠品，请重新输入！");
			pau;
		}
		else{
			Gift* temp = q;
			q = q->pre;
			q->next = q->next->next;
			free(temp);
			printf("\t\t\t\t\t    您已成功删除该赠品！");
			pau;
		}
		//编号重排 
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


void reducegift(Gift* tar, int num){              // 减少赠品 
	if(tar->bottle > num) tar->bottle-=num;
	else if(tar->bottle == num)            // 删除该赠品 
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
	Giftsort(Gift_head);//编号重排 
}



void wornout(ProductSource* tar, int amount){ // 赠品的产生与 
	int odds = rand()%10;
	if(odds == 1) 
	{
		int n = (int) (amount/10);   //n箱 
		int loss = rand()%2+1;      // 随机损失1—2瓶 
		int num_gift = n * (tar->packagingsize_sou - loss);
		//直接在赠品中查找 
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
		printf("\t\t\t 很遗憾在运输途中有%d箱货物产生意外,共损失%d瓶酒水！\n", n,loss);
		printf("\t\t\t  其余%d瓶酒水因无法售卖, 已成功加入赠品中！\n", num_gift);
		
		//加入库存中//
		addinwarehouse(tar , amount - n); 
		printf("\t\t\t  剩余%d箱酒水正常, 已成功添加入库存！\n", amount-n);
		UpdateInventory();
	}
	else
	{
		
		printf("\t\t\t 运输途中无意外发生, 货物以安全送达仓库！\n");
		addinwarehouse(tar, amount);
		UpdateInventory();
	}
	return; 
}






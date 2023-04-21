#include"supplier.h"
#include"customer.h"

extern supplierlist L2;
extern char *stringsm[];
extern productlistin L1;//进货单
extern int max_;

void createsupplylist(){
	system("cls");
	int i = 1;
	L2 = (supplier*)malloc(sizeof(supplier));
	L2->next = NULL;
	supplier* pro = L2;
	int k = abs(1 + rand() % 3);
	//p = L2->next;
	int supplynum = 3;
	//printf("\t\t\t\t         请分别输入3个供应商的运输费\n");
	while(supplynum--){
		printf("\t\t\t\t\t   请输入第%d个供应商的运输费",i);
		i++;
		//int m = 2000 + abs (rand() % 1000);
		int m;
		m = checkNum();
		supplier* p = (supplier*)malloc(sizeof(supplier));//每次分配一个新的空间
		p->transport_cost = m;
		//char str[50];
		strcpy(p->suppliername,stringsm[(++k) % 3]);
		//strcpy(p->suppliername,str);
		//scanf("%d",&p->transport_cost);
		p->next = NULL;
		pro->next = p;
		pro = p;
	}
	pro->next = NULL;
}
void printsupplylist(){
	if(L2->next == NULL){
		printf("链表为空！\n");
	}
	supplier *p = L2->next;
	while(p != NULL){
		printf("%-20s   %-10d\n",p->suppliername,p->transport_cost);
		p = p->next;
	}
}


void generate_randomstring(char str[], int n)//在指定字符串中生成随机字符串
{
    const char *strings[] = {"农夫山泉", "汇源", "青岛啤酒", "舍得", "五粮液","康师傅","娃哈哈","喜茶","可口可乐","大窑嘉宾"}; // 给定的字符串列表
    const int len = sizeof(strings) / sizeof(strings[0]); // 字符串列表中字符串的个数

    srand(time(NULL)); // 设置随机种子

    int index = rand() % len; // 从字符串列表中随机选择一个字符串
    int str_len = strlen(strings[index]); // 获取所选字符串的长度

    strcpy(str, strings[index]); // 将所选字符串复制到存储随机字符串的字符数组中

    if (n > str_len) {
        str[str_len] = '\0'; // 在存储随机字符串的字符数组的末尾添加字符串结束标志
    }

    return;
}


void initproductinlist()//初始化商家链表
{
	L1 = (productin*)malloc(sizeof(productin));
	L1->next = NULL;
}

supplier* choosesupplier(){//找到费用最小的供应商
	if(L2->next == NULL)
	{
		printf("\t\t\t\t\t         供应商信息\n");
	}
	supplier *p = L2->next;
	supplier *flag;
	int su = max_;
	while(p != NULL){
		if(su > p->transport_cost){
			su = p->transport_cost;
			flag = p;
		}
		p = p->next;
	}
	
	return flag;
}
supplier* choosesupplier2(){
	supplier *p = L2->next;
	supplier *flag;
	int su = max_;
	while(p != NULL){
		if(su > p->transport_cost){
			su = p->transport_cost;
			flag = p;
		}
		p = p->next;
	}
	
	return flag;
}

void createproductinlist() {
	productin *p = L1;
    FILE* f;
    if((f = fopen("C:\\Users\\lenovo\\Desktop\\inn.txt","r"))==NULL){
        printf("文件打开有误\n");
        return;
    }
    createsupplylist();
    //printf("\t\t\t正在生成商品信息,输入end表示结束\n");
    while(true)
    {
    	productin *pro = (productin*)malloc(sizeof(productin)); //创建 一个新的结构体指针,开空间
    	//printf("请输入商品名称：\n");
    	fscanf(f,"%s", pro->commodity_name);
    	
		if (strcmp(pro->commodity_name, "end") == 0){
    		//printf("\t\t\t\t程序退出，欢迎下次光临\n");
    		fclose(f);
            free(pro);
            break;
        }
        
    	//printf("请输入商品编号: \n");
        fscanf(f,"%d",&pro->commodity_id);
        
        //每箱瓶数
        fscanf(f,"%d",&pro->commodity_packagenum);

       // printf("请输入商品价格: \n");
        fscanf(f,"%lf", &pro->commodity_price);

        //printf("请输入商品数量: \n");
        fscanf(f,"%d", &pro->commodity_number);
        
        //总价
        fscanf(f,"%lf",&pro->sum_price);
        
        //读入商品容量
        fscanf(f,"%d",&pro->commodity_volume);

        //printf("请输入商品进货日期: \n");
        fscanf(f,"%s", pro->date);
		
		pro->provider = choosesupplier();
		
		pro->sum_price += pro->provider->transport_cost;
        pro->next = NULL;
        p->next = pro;
        p = pro;

	}
	//printf("商品信息生成完毕\n");
}

void printproductinlist(){//打印进货信息
	if(L1->next == NULL){
		printf("\t\t\t\t\t 未录入任何进货信息，无法输出，请录入商品信息后输出\n");
	}
	printf("\t\t\t\t\t ---------------------------------------------------------\n");
	printf("\t\t\t\t\t                         商品打印                          \n");
	printf("\t\t\t\t\t --------------------------------------------------------- \n");
	printf("\t 酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期      进货商\n");
	productin *p = L1->next;
	while(p != NULL){
		supplier* g = p->provider;
//		p->sum_price += g->transport_cost;
//		printf("%d\n",g->transport_cost);
		printf("\t %-20s %-10d %-10d %-13d %.2lf  %11d\t     %-5.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
		p = p->next;
	}
}

void printfile()
{
	productin *p = L1->next;
	
	FILE* f;
    if((f = fopen("C:\\Users\\lenovo\\Desktop\\inn.txt","w"))==NULL){
        printf("文件打开有误\n");
        return;
    }
    
    while(p != NULL){
    	fprintf(f,"%-20s ",p->commodity_name);
    	fprintf(f,"%-6d ",p->commodity_id);
    	fprintf(f,"%-4d ",p->commodity_packagenum);
    	fprintf(f,"%2.2lf    ",p->commodity_price);
    	fprintf(f,"%-6d ",p->commodity_number);
    	fprintf(f,"%-7.2lf  ",p->sum_price);
    	fprintf(f,"%-5d ",p->commodity_volume);
		fprintf(f,"%s\n",p->date);
		p = p->next;
	}
	fprintf(f,"%s\n","end");
	printf("订单信息已经全部写入文件！\n");
	fclose(f);
}
//每箱价格用每箱瓶数*单价，总价用箱数乘以每箱价格
void addproductinlist(){
	int ko = 0;
	printf("\t\t\t\t\t\t\t\t   ------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t                          订单添加                       \n");
	printf("\t\t\t\t\t\t\t\t   ------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t   |            （1）: 商家手动输入添加商品相关信息     |\n");
	printf("\t\t\t\t\t\t\t\t   |            （0）: 退出添加模块                     |\n");
	printf("\t\t\t\t\t\t\t\t   ---------------------------------------------------\n");
	//char str[10];
	//gets(str);
    int selectnum;
	
    //int selectnum;
    //scanf("%d",&selectnum);
    while(true){
    	printf("\t\t\t\t\t\t\t\t   请输入您需要进行的操作");
    	selectnum = checkNum();
    	switch(selectnum){
	        case(0) : {
	        	if(ko == 0){
	        		printf("\t\t\t\t\t   本次添加未执行有效操作,程序退出\n");
	        		return;
				}
				else{
					printf("\t\t\t\t\t\t\t   这是添加后的订单\n");
					printproductinlist();			
					printfile();
					system("pause");
					return;					
				}
	        }
			case(1) : {
					ko++;
				//printf("\t\t\t\t\t请输入所要添加的商品品牌、编号、包装大小,商品单价，商品总价，进货数量，商品容量，进货日期，供应商 \n");
				printf("\t\t\t\t\t    商品品牌只含有\"农夫山泉\",\"汇源\",\"青岛啤酒\",\"舍得\",\"娃哈哈\",\"五粮液\",\"康师傅\",\"可口可乐\",\"喜茶\",\"大窑嘉宾\"\n");
	
				productin *p = L1;
				while(p->next != NULL){
					p = p->next;
				}//p指向链表最终位置
				//productin *u = (productin*)malloc(sizeof(productin));
//				printf("\t\t\t\t\t请输入所要添加的商品进货日期\n");
//				printf("\t\t\t\t\t请输入所要添加的供应商\n");
				productin *u = (productin*)malloc(sizeof(productin)); //创建 一个新的结构体指针,开空间
				char name[100];//酒水品牌
			    int id;//商品编号,用于区分不同商品或同一商品的不同规格或口味、
			    int  packagenum;//每箱瓶数  
			    double price;//商品价格
			    int sum;//商品总价
			    int number;//商品进货数量（箱数）
			    int volume;//商品容量
			    char str[50];//进货日期
			    printf("\t\t\t\t\t请输入所要添加的商品品牌\n");
			    scanf("%s",name);
				while(strcmp(name, "农夫山泉") != 0 && strcmp(name, "汇源") != 0 && strcmp(name, "青岛啤酒") != 0 && strcmp(name, "舍得") != 0 && strcmp(name, "娃哈哈") != 0&& strcmp(name, "五粮液") != 0 && strcmp(name, "康师傅") != 0 && strcmp(name, "喜茶") != 0 && strcmp(name, "可口可乐") != 0 && strcmp(name, "大窑嘉宾") != 0){
	    			printf("您输入的酒水名称有误，请重新输入!\n");
	    			fflush(stdin);
	    			scanf("%s",name);
				}
				printf("\t\t\t\t\t请输入所要添加的商品编号\n");
				while(scanf("%d", &id) != 1) {
        			printf("请输入合法编号!\n");
        			fflush(stdin); // 清空缓存区，避免无限循环
    			}
    			printf("\t\t\t\t\t请输入所要添加的商品包装大小\n");
    			while(scanf("%d", &packagenum) != 1) {
        			printf("请输入合法包装大小!\n");
        			fflush(stdin); // 清空缓存区，避免无限循环
    			}
				//scanf("%d %d",&id,&packagenum);
				printf("\t\t\t\t\t请输入所要添加的商品单价\n");
				while(scanf("%lf",&price) != 1) {
        			printf("请输入合法单价!\n");
        			fflush(stdin); // 清空缓存区，避免无限循环
    			}
				//scanf("%lf",&price);
				printf("\t\t\t\t\t请输入所要添加的商品进货数量\n");
				while(scanf("%d",&number) != 1) {
        			printf("请输入合法进货数量!\n");
        			fflush(stdin); // 清空缓存区，避免无限循环
    			}
				printf("\t\t\t\t\t请输入所要添加的商品容量\n");
				while(scanf("%d",&volume) != 1) {
        			printf("请输入合法商品容量!\n");
        			fflush(stdin); // 清空缓存区，避免无限循环
    			}
			    printf("\t\t\t\t\t请输入所要添加的商品进货日期\n");
			    int valid_input = 0;
			    while (!valid_input) {
			        scanf("%s", str);
			        valid_input = 1;
			        for (int i = 0; i < strlen(str); i++) {
			            if (!isdigit(str[i]) || strlen(str) != 8) {
			                valid_input = 0;
			                printf("请输入合法的日期格式，例如 20220101！\n");
			                break;
			            }
			        }
			    }
			    
			    strcpy(u->date, str);
			    strcpy(u->commodity_name,name);
			    u->commodity_id = id;
			    u->commodity_packagenum = packagenum;
			    u->commodity_price = price;
			    u->commodity_volume = volume;
			    strcpy(u->date,str);
			    u->commodity_number = number;
			    //createsupplylist();
			    u->provider = choosesupplier();
			    u->sum_price = u->commodity_price * u->commodity_number+ u->provider->transport_cost;
			    u->next = p->next;
			    p->next = u;
			    p = u;
				break;
			}
			default:
				printf("您输入的命令有误，请重新输入0或1!\n");
				fflush(stdin);
		}
	}
}


productin* searchproductinlist(char name[100],int id){//在商家链表中寻找目标结点
	//printf("到了\n");
	productin* qq = L1->next;
	//printf("qq过去了\n");
	//printf("到了\n");
	while(qq != NULL && (strcmp(qq->commodity_name,name) != 0 || qq->commodity_id != id)){
		qq = qq->next;
	}
//	printf("到了\n");
	if(qq == NULL) return NULL;
	
	return qq;
}


void deleteproductinlist(){//从商家链表中删除信息
	int k0 = 0;
	printf("\t\t\t\t\t -----------------------------------------------\n");
	printf("\t\t\t\t\t                   商品删除                    \n");
	printf("\t\t\t\t\t -----------------------------------------------\n");
	if(L1->next == NULL){
		printf("此时不含任何进货信息，无法继续删除\n");	
		return;
	}

    
    while(true){
    	printf("\t\t\t\t\t请输入所要删除的商品名称,输入enddelete表示输入结束!\n");
    	
    	productin *a = (productin*)malloc(sizeof(productin));
    
    	scanf("%s", a->commodity_name);
    	
    	if (strcmp(a->commodity_name, "enddelete") == 0){
    		if(k0 == 0){
    			printf("\t\t\t\t\t  未进行有效删除操作!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t   这是修改后的订单\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
        }
        
        while(strcmp(a->commodity_name, "农夫山泉") != 0 && strcmp(a->commodity_name, "汇源") != 0 && strcmp(a->commodity_name, "青岛啤酒") != 0 && strcmp(a->commodity_name, "舍得") != 0 && strcmp(a->commodity_name, "娃哈哈") != 0&& strcmp(a->commodity_name, "五粮液") != 0 && strcmp(a->commodity_name, "康师傅") != 0 && strcmp(a->commodity_name, "喜茶") != 0 && strcmp(a->commodity_name, "可口可乐") != 0 && strcmp(a->commodity_name, "大窑嘉宾") != 0){
    		printf("您输入的酒水名称有误，请重新输入!\n");
    		fflush(stdin);
    		scanf("%s", a->commodity_name);
    		if (strcmp(a->commodity_name, "enddelete") == 0){
    		if(k0 == 0){
    			printf("\t\t\t\t\t  未进行有效删除操作!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t   这是修改后的订单\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
        }
		}
		printf("\t\t\t\t\t请输入所要删除商品的编号,输入11111结束!\n");
		//while(scanf("%d",&a->commodity_id))
	    scanf("%d",&a->commodity_id);
	    if(a->commodity_id == 11111){
	    	if(k0 == 0){
    			printf("\t\t\t\t\t  未进行有效删除操作!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t   这是修改后的订单\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
		}
	    productin *aim = searchproductinlist(a->commodity_name,a->commodity_id);
	    while(aim == NULL){
	    	printf("\t\t\t\t\t   您输入的编号有误，请重新输入\n");
	    	fflush(stdin);
	    	scanf("%d",&a->commodity_id);
	    	if(a->commodity_id == 11111){
	    		if(k0 == 0){
    				printf("\t\t\t\t\t  未进行有效删除操作!\n");
            		free(a);
            		system("pause");
            		break;
				}
				else{
					printf("\t\t\t\t\t\t\t   这是修改后的订单\n");
					printproductinlist();
				
					printfile();
					system("pause");
					return;
				}
			}
	    	aim = searchproductinlist(a->commodity_name,a->commodity_id);
		}
	
		productin *p = L1;
	
		while(p->next->commodity_name != aim->commodity_name || p->next->commodity_id != aim->commodity_id){//未找到目标结点
		
			p = p->next;
		
		}
	
		p->next = aim->next;
	
		aim->next = NULL;
	
		free(aim);
		k0++;

		if(L1->next == NULL){
			
			printf("\t\t\t\t\t    此时不含任何进货信息，无法继续删除\n");
			
			return;
		}
		else{
			printf("\t\t\t\t\t       该商品信息删除成功！\n");
		}
	}
}
void searchproductin(){//查找商品信息
	//productin *q = L1->next;
	printf("\t\t\t\t\t-----------------------------------------------------\n");
	printf("\t\t\t\t\t                       商品查找                    \n");
	printf("\t\t\t\t\t-----------------------------------------------------\n");
	printf("\t\t\t\t\t|             （1）  酒水品牌及酒水编号             |\n");
	printf("\t\t\t\t\t|             （2）  酒水品牌及每箱瓶数             |\n");
	printf("\t\t\t\t\t|             （3）  酒水品牌及商品单价             |\n");
	printf("\t\t\t\t\t|             （4）  酒水品牌及进货数量             |\n");
	printf("\t\t\t\t\t|             （5）  酒水品牌及商品总价             |\n");
	printf("\t\t\t\t\t|             （6）  商品总价及进货日期             |\n");
	printf("\t\t\t\t\t|             （0）  退出查找模块                   |\n");
	printf("\t\t\t\t\t-----------------------------------------------------\n");
	
	//char ss[10];
	//gets(ss);
	int search_num;
	//scanf("%d",&search_num);
	while(true){
		printf("\t\t\t\t\t           请输入您需要进行的操作         \n");
		search_num = checkNum();
		switch(search_num){
		case(0):{
			
			return;
		}
		case(1):{
			printf("\t\t\t\t\t           请输入酒水品牌\n");
			char str[100];
			scanf("%s",str);
			printf("\t\t\t\t\t           请输入酒水编号\n");
			int numb;
			numb = checkNum();
			productin *p = searchproductinlist(str,numb);
			if(p == NULL){
				printf("\t\t\t\t\t          该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t         该商品信息全部如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(2):{
			printf("\t\t\t\t\t           请输入酒水品牌\n");
			char str[100];
			scanf("%s",str);
			printf("\t\t\t\t\t           请输入每箱瓶数\n");
			int package;
			package = checkNum();
//			scanf("%d",&package);
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_packagenum != package)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t         该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t         该商品全部信息如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(3):{
			printf("\t\t\t\t\t           请输入酒水品牌\n");
			char str[100];
			scanf("%s",str);
			printf("\t\t\t\t\t           请输入每箱价格\n");
			double price;
			scanf("%lf",&price);
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_price != price)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t         该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t         该商品全部信息如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(4):{
			printf("\t\t\t\t\t           请输入酒水品牌\n");
			char str[100];
			scanf("%s",str);
			printf("\t\t\t\t\t           请输入进货数量\n");
			int in;
			in = checkNum();
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_number != in)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t         该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t         该商品全部信息如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(5):{
			printf("\t\t\t\t\t           请输入酒水品牌\n");
			char str[100];
			scanf("%s",str);
			printf("\t\t\t\t\t           请输入商品总价\n");
			double sum;
			scanf("%lf",&sum);
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->sum_price != sum)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t         该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t         该商品全部信息如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(6):{
			printf("\t\t\t\t\t           请输入商品总价\n");
			double sum;
			scanf("%lf",&sum);
			printf("\t\t\t\t\t           请输入进货日期\n");
			char da[50];
			scanf("%s",da);
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->date,da) != 0 || p->sum_price != sum)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t         该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t         该商品全部信息如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		default:{
			printf("\t\t\t\t\t           您输入的查询编号为非法字符，请重新输入0~6中的数字\n");
			break;
		}
		
	}
	}
	
	//printf("\t\t\t\t\t   商品进货信息读入完毕！");
}

void correctproductinlist(){
	int ko = 0;
	if(L1->next == NULL){
		printf("此时不含任何进货信息，无法继续修改\n");	
		return;
	}
	printf("\t\t\t\t\t ---------------------------------------------------------- \n");
	printf("\t\t\t\t\t                         商品修改                          \n");
	printf("\t\t\t\t\t ---------------------------------------------------------\n");
    printf("\t\t\t\t\t|                  (1): 修改商品进货数量                  |\n");//同时要修改总价commodity_number
    printf("\t\t\t\t\t|                  (2): 修改商品进货单价                  |\n");//同时要修改总价commodity_price
    printf("\t\t\t\t\t|                  (3): 修改商品每箱容量                  |\n");//commodity_packagenum
    printf("\t\t\t\t\t|                  (4): 修改商品每瓶容量                  |\n");//commodity_volume
    printf("\t\t\t\t\t|                  (5): 修改商品进货日期                  |\n");//commodity_volume
    printf("\t\t\t\t\t|                  (6): 修改商品供应商                    |\n");
    printf("\t\t\t\t\t|                  (0): 退出修改模块                      |\n");
    printf("\t\t\t\t\t| 三家供应商：firstsupplier,secondsupplier,thirdsupplier  |\n");
    printf("\t\t\t\t\t|---------------------------------------------------------|\n");
    while(true){
    	printf("\t\t\t\t\t         请输入您需要进行的操作");
    	
    	int select;
    	select = checkNum();
	    //scanf("%d",&select);
	    if(select == 0 && ko == 0){//第一次进入函数就要退出
	    	printf("\t\t\t\t\t         本次进货未修改商品订单信息!\n");
	    	system("pause");
	    	return;
		}
		if(select == 0 & ko != 0){
			printf("\t\t\t\t\t         这是修改后的订单\n");
	    	printproductinlist();
			printfile();
			system("pause");
			return;
		}
		while(select != 0 && select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6){
			printf("\t\t\t\t\t         您输入的操作有误,请输入0~6中的数字\n");
			fflush(stdin);
	    	select = checkNum();
		}
		if(L1->next == NULL){
			printf("此时不含任何进货信息，无法继续修改\n");	
			return;
		}	//printf("请输入所要修改商品的名称及编号,输入end表示输入结束!\n");
	    productin *a = (productin*)malloc(sizeof(productin));
	    printf("请输入所要修改商品的名称\n");
	    scanf("%s", a->commodity_name);
	    	
	        
	    while(strcmp(a->commodity_name, "农夫山泉") != 0 && strcmp(a->commodity_name, "汇源") != 0 && strcmp(a->commodity_name, "青岛啤酒") != 0&& strcmp(a->commodity_name, "娃哈哈") != 0&& strcmp(a->commodity_name, "五粮液") != 0 && strcmp(a->commodity_name, "舍得") != 0 && strcmp(a->commodity_name, "可口可乐") != 0 && strcmp(a->commodity_name, "喜茶") != 0 && strcmp(a->commodity_name, "大窑嘉宾") != 0 && strcmp(a->commodity_name, "康师傅") != 0){
	    	printf("您输入的酒水名称有误，请重新输入!\n");
	    	fflush(stdin);
	    	scanf("%s", a->commodity_name);
		}
		printf("请输入所要修改商品的编号!\n");
	    scanf("%d",&a->commodity_id);
	    productin *aim = searchproductinlist(a->commodity_name,a->commodity_id);
	    while(aim == NULL){
	    	printf("\t\t\t\t\t         您输入的编号有误，请重新输入\n");
	    	fflush(stdin);
	    	scanf("%d",&a->commodity_id);
	    	aim = searchproductinlist(a->commodity_name,a->commodity_id);
		}
		
		

	    switch(select){
			case(1):{
				ko++;
				int number;
				printf("\t\t\t\t\t         请输入修改后的进货数量\n");
				while(scanf("%d", &number) != 1) {
        			printf("请输入合法数字!\n");
        			fflush(stdin); // 清空缓存区，避免无限循环
    			}
				aim->commodity_number = number;
				supplier *po = aim->provider;
				aim->sum_price = number * aim->commodity_price + po->transport_cost;

				//printfile();
				break;
			}
			case(2):{
				ko++;
				double price;
				printf("\t\t\t\t\t         请输入修改后的进货单价\n");
				while(scanf("%lf", &price) != 1) {
        			printf("请输入合法数字!\n");
        			fflush(stdin); // 清空缓存区，避免无限循环
    			}
				aim->commodity_price = price;
				supplier *po = aim->provider;
				aim->sum_price = price * aim->commodity_number + po->transport_cost;
//				printf("\t\t\t\t\t    修改成功\n");
//				printf("\t\t\t\t\t     这是修改后的订单\n");
//				printproductinlist();
				//printfile();
				break;
			}
			case(3):{
				ko++;
				printf("\t\t\t\t\t         请输入修改后的每箱容量\n");
				int packagenum;
				while(scanf("%d", &packagenum) != 1) {
        			printf("请输入合法数字!\n");
        			fflush(stdin); // 清空缓存区，避免无限循环
    			}
				aim->commodity_packagenum = packagenum;
//				printf("\t\t\t\t\t    修改成功\n");
//				printf("\t\t\t\t\t     这是修改后的订单\n");
//				printproductinlist();
				//printfile();
				break;
			}
			case(4):{
				ko++;
				printf("\t\t\t\t\t         请输入修改后的每瓶容量\n");
				int volume;
				while(scanf("%d", &volume) != 1) {
        			printf("请输入合法数字!\n");
        			fflush(stdin); // 清空缓存区，避免无限循环
    			}
				aim->commodity_volume = volume;
//				printf("\t\t\t\t\t    修改成功\n");
//				printf("\t\t\t\t\t     这是修改后的订单\n");
//				printproductinlist();
				//printfile();				
				break;
			}
			case (5): {
			    ko++;
			    printf("\t\t\t\t\t         请输入修改后的进货日期\n");
			    char str[50];
			    int valid_input = 0;
			    while (!valid_input) {
			        scanf("%s", str);
			        valid_input = 1;
			        for (int i = 0; i < strlen(str); i++) {
			            if (!isdigit(str[i]) || strlen(str) != 8) {
			                valid_input = 0;
			                printf("请输入合法的日期格式，例如 20220101！\n");
			                break;
			            }
			        }
			    }
			    strcpy(aim->date, str);
//			    printf("\t\t\t\t\t    修改成功\n");
//			    printf("\t\t\t\t\t     这是修改后的订单\n");
//			    printproductinlist();
			    //printfile();				
			    break;
			}

			case(6):{
				ko++;
				printf("\t\t\t\t\t         请输入修改后的供应商\n");
				supplier *p = aim->provider;
				char su[50];
				scanf("%s",su);
				while(strcmp(su,"firstsupplier") != 0 && strcmp(su,"secondsupplier") != 0 && strcmp(su,"thirdsupplier") != 0){
					printf("不含此供货商，请您重新输入!\n");
					scanf("%s",su);
				}
				strcpy(p->suppliername,su);
//				printf("\t\t\t\t\t    修改成功\n");
//				printf("\t\t\t\t\t     这是修改后的订单\n");
//				printproductinlist();
				//printfile();
				break;
			}
			default:{
				printf("您输入的编号有误，请输入0~6中的数字\n");
				break;
			}
		}
		if(L1->next == NULL){
			
			printf("此时不含任何进货信息，无法继续修改\n");
			
			return;
		}
	
	}
}
void damage(){
	int kk = 0;
	//scanf("%d",&selectnum);
	int selectnum;
	int k = rand() % 100;
	if(k >= 90){
		printf("\t\t\t\t\t-----------本次进货无商品破损----------------\n");
		return;
	}
	else{//k<90说明有破损
		//fff:
		printf("\t\t\t\t\t ----------------------------------------------\n");
		printf("\t\t\t\t\t                   商品破损                     \n");
		printf("\t\t\t\t\t ---------------------------------------------- \n");
		printf("\t\t\t\t\t|      (1): 随机生成破损商品                   |\n");
		printf("\t\t\t\t\t|      (2): 商家手动输入破损商品名称及编号     |\n");
		printf("\t\t\t\t\t|      (0): 退出破损模块                       |\n");
		printf("\t\t\t\t\t|----------------------------------------------|\n");
		//char ss[10];//gets(ss);
		//scanf("%d",&selectnum);
		fff:
		while(true){
			printf("请输入您需要进行的操作                     \n");
			selectnum = checkNum();
			switch(selectnum){
			case(0):{
				if(kk == 0){
					printf("\t\t\t\t\t     本次操作未产生实际损耗\n");
					return;
				}
				else{
					printf("\t\t\t\t\t\t\t   这是损耗后的订单\n");
					printproductinlist();
				
					printfile();
					system("pause");
					return;
				}
			}
			
			case(1):{
			
				printf("\t\t\t\t\t     随机生成破损商品名称及编号\n");
				srand((unsigned int)time(NULL));
				int n = 1 + rand() % 3;
				int v = 1 + rand() % 3;
				int sum = 0;
				char str[100];
				generate_randomstring(str,100);
				//printf("%s",str);
				productin *p = NULL;
				p = searchproductinlist(str,n);
				if(p == NULL){
					printf("\t\t\t\t\t     商品随机生成失败，所生成商品编号不在进货单中，请重新操作！\n");
					goto fff;
				
				}
			//printf("777");
				int h = v;
				while(v--){
					srand((unsigned int)time(NULL));
					int w = 1 + rand() % 3;
					sum += w;//v箱商品中共sum瓶发生破损
				}
				p->commodity_number -= h;//共v箱商品出现破损
			//p->commodity_packagenum -= w;//指定某商品某箱子损失了w瓶
				p->sum_price = p->sum_price - p->commodity_price * h;
			//p->sum_price = 0;
				kk++;
				printf("\t\t\t\t\t          %d号%s共有%d箱破损，总瓶数减少%d瓶\n",n,str,h,sum);
				printf("\t\t\t\t\t     该商品现有箱数%d箱,由于破损,总价调整为%.2lf\n",p->commodity_number,p->sum_price);
				break;
			}
			case(2):{
				printf("\t\t\t\t\t     请输入破损商品名称\n");
				char sp[100];
				scanf("%s",sp);
				while(strcmp(sp, "农夫山泉") != 0 && strcmp(sp, "汇源") != 0 && strcmp(sp, "青岛啤酒") != 0&& strcmp(sp, "娃哈哈") != 0&& strcmp(sp, "五粮液") != 0 && strcmp(sp, "舍得") != 0 && strcmp(sp, "可口可乐") != 0 && strcmp(sp, "喜茶") != 0 && strcmp(sp, "大窑嘉宾") != 0 && strcmp(sp, "康师傅") != 0){
	    			printf("您输入的酒水名称有误，请重新输入!\n");
	    			fflush(stdin);
	    			scanf("%s", sp);
				}
				printf("\t\t\t\t\t     请输入破损商品编号\n");
				int damage_num;
				damage_num = checkNum();
				productin *p = NULL;
				p = searchproductinlist(sp,damage_num);
				while(p == NULL){
	    			printf("\t\t\t\t\t         您输入的编号有误，该名称及编号对应的商品不在订单中请重新输入\n");
	    			fflush(stdin);
	    			scanf("%d",&damage_num);
	    			p = searchproductinlist(sp,damage_num);
				}

				printf("\t\t\t\t\t     请输入破损商品箱数\n");
				int damagebox,damagebottle,damagesum = 0;
				damagebox = checkNum();
				int yf = damagebox,i = 1;
				p->commodity_number -= yf;
				while(damagebox--){
					printf("\t\t\t\t\t     请输入第%d箱中破损商品瓶数\n",i);
					i++;
					scanf("%d",&damagebottle);
					damagesum += damagebottle;
				}
				printf("\t\t\t\t\t     原总价%.2lf\n",p->sum_price);
				p->sum_price -= p->commodity_price * yf;
			
				printf("\t\t\t\t\t     %s%d号共%d箱破损，总瓶数减少%d瓶\n",sp,damage_num,yf,damagesum);
				printf("\t\t\t\t\t     该商品现有箱数%d箱,由于破损,总价调整为%.2lf\n",p->commodity_number,p->sum_price);
				kk++;
				break;
			}
			default:{
				printf("请输入0~2的合法字符\n");
				break;
			}
		}
		}
		
	}
}

void productin_interface(){	
	initproductinlist();
	createproductinlist();
	
	while(1){
		system("cls");
		printf("\n\n\n\n\n"); 
    	printf("\t\t\t\t\t -------------------------------------------\n");
		printf("\t\t\t\t\t                进货模块                 \n");
		printf("\t\t\t\t\t -------------------------------------------\n");
		printf("\t\t\t\t\t|       （1）  修改订单信息                |\n");
		printf("\t\t\t\t\t|       （2）  删除部分订单信息            |\n");
		printf("\t\t\t\t\t|       （3）  打印订单信息                |\n");
		printf("\t\t\t\t\t|       （4）  增加订单信息                |\n");
		printf("\t\t\t\t\t|       （5）  将订单信息写到in.txt文件中  |\n");
		printf("\t\t\t\t\t|       （6）  查询某一条订单信息          |\n");
		printf("\t\t\t\t\t|       （7）  查询商品损耗情况            |\n");
		printf("\t\t\t\t\t|       （0）  操作结束                    |\n");
		printf("\t\t\t\t\t|     请输入你想要进行的服务：(0-7)        |\n");
		printf("\t\t\t\t\t|                                          |\n");
		printf("\t\t\t\t\t ------------------------------------------| \n");
		//char ss[10];
		
		//gets(ss);
		
//		while(getchar() != '\n');
		int productin_num = checkNum();
		//scanf("%d",&productin_num);
		switch(productin_num){
			case(0):{	
				return;
			}
			case(1):{
				system("cls");
				correctproductinlist();
				//printf("打印文件");
				
				//system("pause");
				
				//printf("\t\t\t\t\t     这是修改后的订单\n");
				//printproductinlist();
				//system("pause");
				break;
			}
			case(2):{
				system("cls");
				deleteproductinlist();
				
				//system("pause");
				break;
			}
			case(3):{
				system("cls");
				//createsupplylist();
				//choosesupplier();
				printproductinlist();
				
				system("pause");
				break;
			}
			case(4):{
				system("cls");
				addproductinlist();
				system("pause");
				//system("pause");
				break;
			}
			case(5):{
				system("cls");
				printfile();
				printf("\t\t\t\t\t     进货信息已写入文件中\n");
				system("pause");
				break;
			}
			case(6):{
				system("cls");
				searchproductin();
				system("pause");
				break;
			}
			case(7):{
				system("cls");
				damage();
				//system("pause");
				break;
			}
	
			default:
				system("cls");
				printf("您输入的信息有误,请输入0~7中的数字\n");
				system("pause");
				break;
		}
	}		
}	


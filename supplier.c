#include"supplier.h"
#include"customer.h"

extern productlistin L1;//进货单
extern char *stringsm[];
extern int max_; 
extern int rt[3];
int isdate(char* date_string) {
    if (strlen(date_string) != 8) {
        return 0;
    }
    int year = atoi(strncpy((char*)malloc(5), date_string, 4));
    int month = atoi(strncpy((char*)malloc(3), date_string+4, 2));
    int day = atoi(strncpy((char*)malloc(3), date_string+6, 2));
    if (year != 2023) {
        return 0;
    }
    if (month < 1 || month > 12) {
        return 0;
    }
    if (day < 1 || day > 31) {
        return 0;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return 0;
        }
    }
    if (month == 2) {
        if (day > 29) {
            return 0;
        }
        if (day == 29 && !(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
            return 0;
        }
    }
    return 1;
}

int inputNum(){
	char s[100]={'\0'};int l=0;char ch;
	flag22:
		l = 0;
    while((ch=getchar())!='\n')s[l++]=ch;
    s[l]='\0';
    if(s[0]=='\0')goto flag22;
    if(l==1&&s[0]=='0')return 0;
	int ret=0;
	for(int i=0;s[i];i++){
		if(i==0&&s[i]=='0')return -1;
		if(s[i]<='9'&&s[i]>='0')ret=ret*10+s[i]-'0';
		else return -1;
	} 
	return ret;
}

void createsupplylist(){
	int i = 1;
	L2 = (supplier*)malloc(sizeof(supplier));
	L2->next = NULL;
	supplier* pro = L2;
	int k = abs(1 + rand() % 3);
	srand(time(NULL));
	int m = abs (rand() % 3);
	int supplynum = 3;
	while(supplynum--){
		
		//m = inputNum();
		supplier* p = (supplier*)malloc(sizeof(supplier));//每次分配一个新的空间
		p->transport_cost = rt[(++m) % 3];
		//char str[50];
		strcpy(p->suppliername,stringsm[(++k) % 3]);
		//strcpy(p->suppliername,str);
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
	createsupplylist();
	productin *p = L1;
    FILE* f;
    if((f = fopen("inn.txt","r"))==NULL){
        printf("文件打开有误\n");
        return;
    }
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    if(size == 0){
//    	printf("文件为空，无法建立订单信息\n");
//    	system("pause");
    	return;
	}

    fseek(f, 0, SEEK_SET);
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
	
}

void printproductinlist(){//打印进货信息
	if(L1->next == NULL){
		printf("\t\t\t\t\t\t\t\t      未录入任何进货信息，无法输出，请录入商品信息后输出\n");
		return;
	}
	printf("\t\t\t\t\t\t\t\t      ---------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t                               商品打印                          \n");
	printf("\t\t\t\t\t\t\t\t      --------------------------------------------------------- \n");
	printf("\t\t\t\t   酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期      进货商\n");
	productin *p = L1->next;
	while(p != NULL){
		supplier* g = p->provider;
		printf("\t\t\t\t   %-20s %-10d %-10d %-13d %.2lf  %11d\t     %-5.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
		p = p->next;
	}
}

void printfile()
{
	productin *p = L1->next;
	
	FILE* f;
    if((f = fopen("inn.txt","w"))==NULL){
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
    while(true){
    	printf("\t\t\t\t\t\t\t\t   请输入您需要进行的操作");
    	selectnum = inputNum();
    	switch(selectnum){
	        case(0) : {
	        	if(ko == 0){
	        		printf("\t\t\t\t\t\t\t\t   本次添加未执行有效操作,程序退出\n");
	        		return;
				}
				else{
					printf("\t\t\t\t\t\t\t\t   这是添加后的订单\n");
					printproductinlist();			
					printfile();
					system("pause");
					return;					
				}
	        }
			case(1) : {
					ko++;
				//printf("\t\t\t\t\t请输入所要添加的商品品牌、编号、包装大小,商品单价，商品总价，进货数量，商品容量，进货日期，供应商 \n");
				printf("\t\t\t\t\t   商品品牌只含有\"农夫山泉\",\"汇源\",\"青岛啤酒\",\"舍得\",\"娃哈哈\",\"五粮液\",\"康师傅\",\"可口可乐\",\"喜茶\",\"大窑嘉宾\"\n");
				if(L1->next != NULL){
					productin *p = L1;
					while(p->next != NULL){
						p = p->next;
					}//p指向链表最终位置
		
					productin *u = (productin*)malloc(sizeof(productin)); //创建 一个新的结构体指针,开空间
					char name[100];//酒水品牌
				    int id;//商品编号,用于区分不同商品或同一商品的不同规格或口味、
				    int  packagenum;//每箱瓶数  
				    double price;//商品价格
				    double sum;//商品总价
				    int number;//商品进货数量（箱数）
				    int volume;//商品容量
				    char str[50];//进货日期
				    printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品品牌   ");
				    fgets(name, 100, stdin);
	    			name[strcspn(name, "\n")] = '\0';
					while(strcmp(name, "农夫山泉") != 0 && strcmp(name, "汇源") != 0 && strcmp(name, "青岛啤酒") != 0 && strcmp(name, "舍得") != 0 && strcmp(name, "娃哈哈") != 0&& strcmp(name, "五粮液") != 0 && strcmp(name, "康师傅") != 0 && strcmp(name, "喜茶") != 0 && strcmp(name, "可口可乐") != 0 && strcmp(name, "大窑嘉宾") != 0){
		    			printf("\t\t\t\t\t\t\t\t   您输入的酒水名称有误，请重新输入!\n");
		    			printf("\t\t\t\t\t\t\t\t   ");
		    			fflush(stdin);
		    			fgets(name, 100, stdin);
	    				name[strcspn(name, "\n")] = '\0';
					}
					printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品编号   ");
					id = inputNum();
					while(id == -1) {
	        			printf("\t\t\t\t\t\t\t\t   请输入合法编号!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // 清空缓存区，避免无限循环
	        			id = inputNum();
	    			}
	    			printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品包装大小   ");
	    			packagenum = inputNum();
	    			while(packagenum == -1) {
	        			printf("\t\t\t\t\t\t\t\t   请输入合法包装大小!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // 清空缓存区，避免无限循环
	        			packagenum = inputNum();
	    			}
					
					printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品单价(单价是浮点类型，可最多精确到分)   ");
					price = checkDouble();
					while(price < 0) {
	        			printf("\t\t\t\t\t\t\t\t   请输入合法单价!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // 清空缓存区，避免无限循环
	        			price = inputNum();
	    			}
					
					printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品进货数量   ");
					number = inputNum();
					while(number == -1) {
	        			printf("\t\t\t\t\t\t\t\t   请输入合法进货数量!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // 清空缓存区，避免无限循环
	        			number = inputNum();
	    			}
					printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品容量   ");
					volume = inputNum();
					while(volume == -1) {
	        			printf("\t\t\t\t\t\t\t\t   请输入合法商品容量!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // 清空缓存区，避免无限循环
	        			volume = inputNum();
	    			}
				    printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品进货日期   ");
				    fgets(str, 50, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
					str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
					while(!isdate(str)){
						printf("\t\t\t\t\t\t\t\t   请输入合法进货日期!\n");
						printf("\t\t\t\t\t\t\t\t   \n");
						fgets(str, 50, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
						str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
					}
	
				    
				    strcpy(u->date, str);
				    strcpy(u->commodity_name,name);
				    u->commodity_id = id;
				    u->commodity_packagenum = packagenum;
				    u->commodity_price = price;
				    u->commodity_volume = volume;
				    u->commodity_number = number;
				    //createsupplylist();
				    u->provider = choosesupplier();
				    u->sum_price = u->commodity_price * u->commodity_number+ u->provider->transport_cost;
				    u->next = p->next;
				    p->next = u;
				    p = u;
					break;
				}
				else{
					productin *q = L1;
					productin *gg = (productin*)malloc(sizeof(productin));
					char name[100];//酒水品牌
				    int id;//商品编号,用于区分不同商品或同一商品的不同规格或口味、
				    int  packagenum;//每箱瓶数  
				    double price;//商品价格
				    double sum;//商品总价
				    int number;//商品进货数量（箱数）
				    int volume;//商品容量
				    char str[50];//进货日期
				    printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品品牌   ");
				    fgets(name, 100, stdin);
	    			name[strcspn(name, "\n")] = '\0';
					while(strcmp(name, "农夫山泉") != 0 && strcmp(name, "汇源") != 0 && strcmp(name, "青岛啤酒") != 0 && strcmp(name, "舍得") != 0 && strcmp(name, "娃哈哈") != 0&& strcmp(name, "五粮液") != 0 && strcmp(name, "康师傅") != 0 && strcmp(name, "喜茶") != 0 && strcmp(name, "可口可乐") != 0 && strcmp(name, "大窑嘉宾") != 0){
		    			printf("\t\t\t\t\t\t\t\t   您输入的酒水名称有误，请重新输入!\n");
		    			printf("\t\t\t\t\t\t\t\t   ");
		    			fflush(stdin);
		    			fgets(name, 100, stdin);
	    				name[strcspn(name, "\n")] = '\0';
					}
					printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品编号   ");
					id = inputNum();
					while(id == -1) {
	        			printf("\t\t\t\t\t\t\t\t   请输入合法编号!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // 清空缓存区，避免无限循环
	        			id = inputNum();
	    			}
	    			printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品包装大小   ");
	    			packagenum = inputNum();
	    			while(packagenum == -1) {
	        			printf("\t\t\t\t\t\t\t\t   请输入合法包装大小!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // 清空缓存区，避免无限循环
	        			packagenum = inputNum();
	    			}
					
					printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品单价(单价是浮点类型，可最多精确到分)   ");
					price = checkDouble();
					while(price < 0) {
	        			printf("\t\t\t\t\t\t\t\t   请输入合法单价!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // 清空缓存区，避免无限循环
	        			price = inputNum();
	    			}
					
					printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品进货数量   ");
					number = inputNum();
					while(number == -1) {
	        			printf("\t\t\t\t\t\t\t\t   请输入合法进货数量!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // 清空缓存区，避免无限循环
	        			number = inputNum();
	    			}
					printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品容量   ");
					volume = inputNum();
					while(volume == -1) {
	        			printf("\t\t\t\t\t\t\t\t   请输入合法商品容量!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // 清空缓存区，避免无限循环
	        			volume = inputNum();
	    			}
				    printf("\t\t\t\t\t\t\t\t   请输入所要添加的商品进货日期   ");
				    fgets(str, 50, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
					str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
					while(!isdate(str)){
						printf("\t\t\t\t\t\t\t\t   请输入合法进货日期!\n");
						printf("\t\t\t\t\t\t\t\t   ");
						fgets(str, 50, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
						str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
					}
				    strcpy(gg->date, str);
				    strcpy(gg->commodity_name,name);
				    gg->commodity_id = id;
				    gg->commodity_packagenum = packagenum;
				    gg->commodity_price = price;
				    gg->commodity_volume = volume;
				    gg->commodity_number = number;
				    //createsupplylist();
				    gg->provider = choosesupplier();
				    gg->sum_price = gg->commodity_price * gg->commodity_number + gg->provider->transport_cost;
				    gg->next = q->next;
				    q->next = gg;
				    q = gg;
					break;
				}
			}
			default:
				printf("\t\t\t\t\t\t\t\t   您输入的命令有误，请重新输入0或1!\n");
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
	printf("\t\t\t\t\t\t\t\t    -----------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t                      商品删除                    \n");
	printf("\t\t\t\t\t\t\t\t    -----------------------------------------------\n");
	if(L1->next == NULL){
		printf("\t\t\t\t\t\t\t\t    此时不含任何进货信息，无法继续删除,请录入信息后进行删除操作\n");
		system("pause");
		return;
	}

    
    while(true){
    	printf("\t\t\t\t\t\t\t\t   请输入所要删除的商品名称,输入enddelete表示输入结束!\n");
    	printf("\t\t\t\t\t\t\t\t   ");
    	productin *a = (productin*)malloc(sizeof(productin));
    
		fgets(a->commodity_name, 50, stdin);
    	a->commodity_name[strcspn(a->commodity_name, "\n")] = '\0';
    	if (strcmp(a->commodity_name, "enddelete") == 0){
    		if(k0 == 0){
    			printf("\t\t\t\t\t\t\t\t   未进行有效删除操作!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t\t   这是删除后的订单\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
        }
    	while(strcmp(a->commodity_name, "农夫山泉") != 0 && strcmp(a->commodity_name, "汇源") != 0 && strcmp(a->commodity_name, "青岛啤酒") != 0&& strcmp(a->commodity_name, "娃哈哈") != 0&& strcmp(a->commodity_name, "五粮液") != 0 && strcmp(a->commodity_name, "舍得") != 0 && strcmp(a->commodity_name, "可口可乐") != 0 && strcmp(a->commodity_name, "喜茶") != 0 && strcmp(a->commodity_name, "大窑嘉宾") != 0 && strcmp(a->commodity_name, "康师傅") != 0){
	    	printf("\t\t\t\t\t\t\t\t   您输入的商品名称有误，请重新输入\n");
	    	printf("\t\t\t\t\t\t\t\t   ");
	    	fflush(stdin);
	    	fgets(a->commodity_name, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
			a->commodity_name[strcspn(a->commodity_name, "\n")] = '\0'; // 去掉字符串末尾的换行符
			if (strcmp(a->commodity_name, "enddelete") == 0){
    		if(k0 == 0){
    			printf("\t\t\t\t\t\t\t\t   未进行有效删除操作!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t\t   这是删除后的订单\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
        }
		}
    	
        
//        while(strcmp(a->commodity_name, "农夫山泉") != 0 && strcmp(a->commodity_name, "汇源") != 0 && strcmp(a->commodity_name, "青岛啤酒") != 0 && strcmp(a->commodity_name, "舍得") != 0 && strcmp(a->commodity_name, "娃哈哈") != 0&& strcmp(a->commodity_name, "五粮液") != 0 && strcmp(a->commodity_name, "康师傅") != 0 && strcmp(a->commodity_name, "喜茶") != 0 && strcmp(a->commodity_name, "可口可乐") != 0 && strcmp(a->commodity_name, "大窑嘉宾") != 0){
//    		printf("\t\t\t\t\t   您输入的酒水名称有误，请重新输入!\n");
//    		printf("\t\t\t\t\t   ");
//    		fflush(stdin);
//    		fgets(a->commodity_name, 50, stdin);
//    		a->commodity_name[strcspn(a->commodity_name, "\n")] = '\0';
//    		if (strcmp(a->commodity_name, "enddelete") == 0){
//    		if(k0 == 0){
//    			printf("\t\t\t\t\t  未进行有效删除操作!\n");
//            	free(a);
//            	system("pause");
//            	break;
//			}
//			else{
//				printf("\t\t\t\t\t   这是删除后的订单\n");
//				printproductinlist();
//				
//				printfile();
//				system("pause");
//				return;
//			}
//        }
//		}
		printf("\t\t\t\t\t\t\t\t   请输入所要删除商品的编号,输入11111结束!\n");
		printf("\t\t\t\t\t\t\t\t   ");
	    //fgets(a->commodity_id, 50, stdin);
	    a->commodity_id = inputNum();
	    while(a->commodity_id == -1){
	    	printf("\t\t\t\t\t\t\t\t   请输入合法编号!\n");
        	printf("\t\t\t\t\t\t\t\t   ");
        	fflush(stdin); // 清空缓存区，避免无限循环
        	a->commodity_id = inputNum();
		}	    
	    if(a->commodity_id == 11111){
	    	if(k0 == 0){
    			printf("\t\t\t\t\t\t\t\t   未进行有效删除操作!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t\t   这是删除后的订单\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
		}
	    productin *aim = searchproductinlist(a->commodity_name,a->commodity_id);
	    while(aim == NULL){
	    	printf("\t\t\t\t\t\t\t\t   您输入的编号有误，请重新输入\n");
	    	printf("\t\t\t\t\t\t\t\t   ");
	    	fflush(stdin);
	    	a->commodity_id = inputNum();
	    	while(a->commodity_id == -1){
	    		printf("\t\t\t\t\t\t\t\t   请输入合法编号!\n");
        		printf("\t\t\t\t\t\t\t\t   ");
        		fflush(stdin); // 清空缓存区，避免无限循环
        		a->commodity_id = inputNum();
			}
	    	if(a->commodity_id == 11111){
	    		if(k0 == 0){
    				printf("\t\t\t\t\t\t\t\t   未进行有效删除操作!\n");
            		free(a);
            		system("pause");
            		break;
				}
				else{
					printf("\t\t\t\t\t\t\t\t   这是删除后的订单\n");
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
			
			printf("\t\t\t\t\t\t\t\t   此时不含任何进货信息，无法继续删除\n");
			
			return;
		}
		else{
			printf("\t\t\t\t\t\t\t\t   该商品信息删除成功！\n");
		}
	}
}
void searchproductin(){//查找商品信息
	//productin *q = L1->next;
	if(L1->next == NULL){
		printf("\t\t\t\t\t此时不含任何进货信息无法查询\n");
		system("pause");
		return;
	}
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
	
	while(true){
		printf("\t\t\t\t\t           请输入您需要进行的操作  ");
		search_num = inputNum();
		switch(search_num){
		case(0):{
			
			return;
		}
		case(1):{
			printf("\t\t\t\t\t           请输入酒水品牌   ");
			char str[100];
			fgets(str, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
			str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
			while(strcmp(str, "农夫山泉") != 0 && strcmp(str, "汇源") != 0 && strcmp(str, "青岛啤酒") != 0 && strcmp(str, "舍得") != 0 && strcmp(str, "娃哈哈") != 0&& strcmp(str, "五粮液") != 0 && strcmp(str, "康师傅") != 0 && strcmp(str, "喜茶") != 0 && strcmp(str, "可口可乐") != 0 && strcmp(str, "大窑嘉宾") != 0){
				printf("\t\t\t\t\t           请输入所给10种酒水品牌之一\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin); // 清空缓存区，避免无限循环
				fgets(str, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
				str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
			}

			printf("\t\t\t\t\t           请输入酒水编号   ");
			int numb;
			numb = inputNum();
			while(numb == -1) {
        			printf("\t\t\t\t\t           请输入合法酒水编号!\n");
        			printf("\t\t\t\t\t           ");
        			fflush(stdin); // 清空缓存区，避免无限循环
        			numb = inputNum();
    		}
			productin *p = searchproductinlist(str,numb);
			if(p == NULL){
				printf("\t\t\t\t\t           该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t          该商品信息全部如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(2):{
			printf("\t\t\t\t\t           请输入酒水品牌   ");
			char str[100];
			fgets(str, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
			str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
			while(strcmp(str, "农夫山泉") != 0 && strcmp(str, "汇源") != 0 && strcmp(str, "青岛啤酒") != 0 && strcmp(str, "舍得") != 0 && strcmp(str, "娃哈哈") != 0&& strcmp(str, "五粮液") != 0 && strcmp(str, "康师傅") != 0 && strcmp(str, "喜茶") != 0 && strcmp(str, "可口可乐") != 0 && strcmp(str, "大窑嘉宾") != 0){
				printf("\t\t\t\t\t           请输入所给10种酒水品牌之一\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin); // 清空缓存区，避免无限循环
				fgets(str, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
				str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
			}
			printf("\t\t\t\t\t           请输入每箱瓶数   ");
			int package;
			package = inputNum();
			while(package == -1) {
        		printf("\t\t\t\t\t           请输入合法每箱瓶数!\n");
        		printf("\t\t\t\t\t           ");
        		fflush(stdin); // 清空缓存区，避免无限循环
        		package = inputNum();
    		}

			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_packagenum != package)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t          该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t          该商品全部信息如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(3):{
			printf("\t\t\t\t\t           请输入酒水品牌   ");
			char str[100];
			fgets(str, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
			str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
			while(strcmp(str, "农夫山泉") != 0 && strcmp(str, "汇源") != 0 && strcmp(str, "青岛啤酒") != 0 && strcmp(str, "舍得") != 0 && strcmp(str, "娃哈哈") != 0&& strcmp(str, "五粮液") != 0 && strcmp(str, "康师傅") != 0 && strcmp(str, "喜茶") != 0 && strcmp(str, "可口可乐") != 0 && strcmp(str, "大窑嘉宾") != 0){
				printf("\t\t\t\t\t           请输入所给10种酒水品牌之一\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin); // 清空缓存区，避免无限循环
				fgets(str, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
				str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
			}
			printf("\t\t\t\t\t           请输入每箱价格   ");
			double price;

			price = checkDouble();
			while(price < 0) {
        		printf("\t\t\t\t\t           请输入合法每箱价格!\n");
        		printf("\t\t\t\t\t           ");
        		fflush(stdin); // 清空缓存区，避免无限循环
        		price = checkDouble();
    		}
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_price != price)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t          该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t          该商品全部信息如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(4):{
			printf("\t\t\t\t\t           请输入酒水品牌   ");
			char str[100];
			fgets(str, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
			str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
			while(strcmp(str, "农夫山泉") != 0 && strcmp(str, "汇源") != 0 && strcmp(str, "青岛啤酒") != 0 && strcmp(str, "舍得") != 0 && strcmp(str, "娃哈哈") != 0&& strcmp(str, "五粮液") != 0 && strcmp(str, "康师傅") != 0 && strcmp(str, "喜茶") != 0 && strcmp(str, "可口可乐") != 0 && strcmp(str, "大窑嘉宾") != 0){
				printf("\t\t\t\t\t           请输入所给10种酒水品牌之一\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin); // 清空缓存区，避免无限循环
				fgets(str, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
				str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
			}
			printf("\t\t\t\t\t           请输入进货数量   ");
			int in;
			in = inputNum();
			while(in == -1) {
        		printf("\t\t\t\t\t           请输入合法进货数量!\n");
        		printf("\t\t\t\t\t           ");
        		fflush(stdin); // 清空缓存区，避免无限循环
        		in = inputNum();
    		}
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_number != in)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t          该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t          该商品全部信息如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(5):{
			printf("\t\t\t\t\t           请输入酒水品牌   ");
			char str[100];
			fgets(str, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
			str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
			while(strcmp(str, "农夫山泉") != 0 && strcmp(str, "汇源") != 0 && strcmp(str, "青岛啤酒") != 0 && strcmp(str, "舍得") != 0 && strcmp(str, "娃哈哈") != 0&& strcmp(str, "五粮液") != 0 && strcmp(str, "康师傅") != 0 && strcmp(str, "喜茶") != 0 && strcmp(str, "可口可乐") != 0 && strcmp(str, "大窑嘉宾") != 0){
				printf("\t\t\t\t\t           请输入所给10种酒水品牌之一\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin); // 清空缓存区，避免无限循环
				fgets(str, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
				str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
			}
			printf("\t\t\t\t\t           请输入商品总价   ");
			double sum;
			sum = checkDouble();
			while(sum < 0) {
        		printf("\t\t\t\t\t           请输入合法商品总价!\n");
        		printf("\t\t\t\t\t           ");
        		fflush(stdin); // 清空缓存区，避免无限循环
        		sum = checkDouble();
    		}
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->sum_price != sum)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t          该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t          该商品全部信息如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(6):{
			printf("\t\t\t\t\t           请输入商品总价   ");
			double sum;
			sum = checkDouble();
			while(sum < 0) {
        		printf("\t\t\t\t\t           请输入合法商品总价!\n");
        		printf("\t\t\t\t\t           ");
        		fflush(stdin); // 清空缓存区，避免无限循环
        		sum = checkDouble();
    		}
			printf("\t\t\t\t\t           请输入进货日期   ");
			char da[50];
			fgets(da, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
			da[strcspn(da, "\n")] = '\0'; // 去掉字符串末尾的换行符
			while(!isdate(da)){
				printf("\t\t\t\t\t           请输入合法进货日期\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin);
				fgets(da, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
				da[strcspn(da, "\n")] = '\0'; // 去掉字符串末尾的换行符
			}
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->date,da) != 0 || p->sum_price != sum)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t          该商品不在进货订单中\n");
				break;
			}
			printf("\t\t\t\t\t          该商品全部信息如下\n");
			printf("酒水品牌         商品编号     每箱瓶数    商品毫升数     每箱价格     进货数量      商品总价        进货日期    进货商\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		default:{
			printf("\t\t\t\t\t           您输入的查询编号为非法字符，请重新输入0~6中的数字\n");
			//printf("\t\t\t\t\t           ");
			break;
		}
		
	}
	}
	//printf("\t\t\t\t\t   商品进货信息读入完毕！");
}

void correctproductinlist(){
	int ko = 0;
	if(L1->next == NULL){
		printf("\t\t\t\t\t\t\t\t   此时不含任何进货信息，无法继续修改\n");	
		system("pause");
		return;
	}
	printf("\t\t\t\t\t\t\t\t   ---------------------------------------------------------- \n");
	printf("\t\t\t\t\t\t\t\t                            商品修改                          \n");
	printf("\t\t\t\t\t\t\t\t   ---------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t   |                  (1): 修改商品进货数量                  |\n");//同时要修改总价commodity_number
    printf("\t\t\t\t\t\t\t\t   |                  (2): 修改商品进货单价                  |\n");//同时要修改总价commodity_price
    printf("\t\t\t\t\t\t\t\t   |                  (3): 修改商品每箱容量                  |\n");//commodity_packagenum
    printf("\t\t\t\t\t\t\t\t   |                  (4): 修改商品每瓶容量                  |\n");//commodity_volume
    printf("\t\t\t\t\t\t\t\t   |                  (5): 修改商品进货日期                  |\n");//commodity_volume
    printf("\t\t\t\t\t\t\t\t   |                  (6): 修改商品供应商                    |\n");
    printf("\t\t\t\t\t\t\t\t   |                  (0): 退出修改模块                      |\n");
    printf("\t\t\t\t\t\t\t\t   | 三家供应商：firstsupplier,secondsupplier,thirdsupplier  |\n");
    printf("\t\t\t\t\t\t\t\t   |---------------------------------------------------------|\n");
    if(L1->next == NULL){
    	printf("\t\t\t\t\t\t\t\t   订单为空，不可修改\n");
    	system("pause");
	}
    while(true){
    	printf("\t\t\t\t\t\t\t\t   请输入您需要进行的操作");
    	
    	int select;
    	select = inputNum();

	    if(select == 0 && ko == 0){//第一次进入函数就要退出
	    	printf("\t\t\t\t\t\t\t\t   本次进货未修改商品订单信息!\n");
	    	system("pause");
	    	return;
		}
		if(select == 0 & ko != 0){
			printf("\t\t\t\t\t\t\t\t   这是修改后的订单\n");
	    	printproductinlist();
			printfile();
			system("pause");
			return;
		}
		while(select != 0 && select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6){
			printf("\t\t\t\t\t\t\t\t   您输入的操作有误,请输入0~6中的数字\n");
			printf("\t\t\t\t\t\t\t\t   ");
			fflush(stdin);
	    	select = inputNum();
		}
		if(L1->next == NULL){
			printf("\t\t\t\t\t\t\t\t   此时不含任何进货信息，无法继续修改\n");	
			return;
		}	//printf("请输入所要修改商品的名称及编号,输入end表示输入结束!\n");
	    productin *a = (productin*)malloc(sizeof(productin));
	    printf("\t\t\t\t\t\t\t\t   请输入所要修改商品的名称   ");
	    fgets(a->commodity_name, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
		a->commodity_name[strcspn(a->commodity_name, "\n")] = '\0'; // 去掉字符串末尾的换行符

	    	
	        
	    while(strcmp(a->commodity_name, "农夫山泉") != 0 && strcmp(a->commodity_name, "汇源") != 0 && strcmp(a->commodity_name, "青岛啤酒") != 0&& strcmp(a->commodity_name, "娃哈哈") != 0&& strcmp(a->commodity_name, "五粮液") != 0 && strcmp(a->commodity_name, "舍得") != 0 && strcmp(a->commodity_name, "可口可乐") != 0 && strcmp(a->commodity_name, "喜茶") != 0 && strcmp(a->commodity_name, "大窑嘉宾") != 0 && strcmp(a->commodity_name, "康师傅") != 0){
	    	printf("\t\t\t\t\t\t\t\t   您输入的酒水名称有误，请重新输入\n");
	    	printf("\t\t\t\t\t\t\t\t   ");
	    	fflush(stdin);
	    	fgets(a->commodity_name, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
			a->commodity_name[strcspn(a->commodity_name, "\n")] = '\0'; // 去掉字符串末尾的换行符
		}
		printf("\t\t\t\t\t\t\t\t   请输入所要修改商品的编号   ");
	    a->commodity_id = inputNum();
	    while(a->commodity_id == -1){
	    	printf("\t\t\t\t\t\t\t\t   请输入合法编号!\n");
        	printf("\t\t\t\t\t\t\t\t   ");
        	fflush(stdin); // 清空缓存区，避免无限循环
        	a->commodity_id = inputNum();
		}	
		
	    productin *aim = searchproductinlist(a->commodity_name,a->commodity_id);
	    while(aim == NULL){
	    	printf("\t\t\t\t\t\t\t\t   订单中不含此商品信息，请重新输入编号\n");
	    	printf("\t\t\t\t\t\t\t\t   ");
	    	fflush(stdin);
	    	a->commodity_id = inputNum();
	    	aim = searchproductinlist(a->commodity_name,a->commodity_id);
		}
		
		

	    switch(select){
			case(1):{
				ko++;
				int number;
				printf("\t\t\t\t\t\t\t\t   请输入修改后的进货数量   ");
				//printf("\t\t\t\t\t         ");
				number = inputNum();
				while(number == -1) {
        			printf("\t\t\t\t\t\t\t\t   请输入合法数字!\n");
        			printf("\t\t\t\t\t\t\t\t   ");
        			fflush(stdin); // 清空缓存区，避免无限循环
        			number = inputNum();
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
				printf("\t\t\t\t\t\t\t\t   请输入修改后的进货单价   ");
				price = checkDouble();
				while(price < 0) {
        			printf("\t\t\t\t\t\t\t\t   请输入合法数字!\n");
        			printf("\t\t\t\t\t\t\t\t   ");
        			fflush(stdin); // 清空缓存区，避免无限循环
        			price = checkDouble();
    			}
				aim->commodity_price = price;
				supplier *po = aim->provider;
				aim->sum_price = price * aim->commodity_number + po->transport_cost;

				break;
			}
			case(3):{
				ko++;
				printf("\t\t\t\t\t\t\t\t   请输入修改后的每箱容量   ");
				//printf("\t\t\t\t\t         ");
				int packagenum;
				packagenum = inputNum();
				while(packagenum == -1) {
        			printf("\t\t\t\t\t\t\t\t   请输入合法数字!\n");
        			printf("\t\t\t\t\t\t\t\t   ");
        			fflush(stdin); // 清空缓存区，避免无限循环
        			packagenum = inputNum();
    			}
				aim->commodity_packagenum = packagenum;

				break;
			}
			case(4):{
				ko++;
				printf("\t\t\t\t\t\t\t\t   请输入修改后的每瓶容量   ");
				int volume;
				volume = inputNum();
				while(volume == -1) {
        			printf("\t\t\t\t\t\t\t\t   请输入合法数字!\n");
        			printf("\t\t\t\t\t\t\t\t   ");
        			fflush(stdin); // 清空缓存区，避免无限循环
        			volume = inputNum();
    			}
				aim->commodity_volume = volume;
				
				break;
			}
			case (5): {
			    ko++;
			    printf("\t\t\t\t\t\t\t\t   请输入修改后的进货日期   ");
			    //printf("\t\t\t\t\t         ");
			    char str[50];
			    fgets(str, 50, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
				str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
				while(!isdate(str)){
					printf("\t\t\t\t\t\t\t\t   请输入合法进货日期!\n");
					printf("\t\t\t\t\t\t\t\t   ");
					fgets(str, 50, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
					str[strcspn(str, "\n")] = '\0'; // 去掉字符串末尾的换行符
				}
			    strcpy(aim->date, str);		
			    break;
			}

			case(6):{
				ko++;
				printf("\t\t\t\t\t\t\t\t   请输入修改后的供应商   ");
				//printf("\t\t\t\t\t         ");
				supplier *p = aim->provider;
				char su[50];
				fgets(su, 50, stdin);
    			su[strcspn(su, "\n")] = '\0';
				while(strcmp(su,"firstsupplier") != 0 && strcmp(su,"secondsupplier") != 0 && strcmp(su,"thirdsupplier") != 0){
					printf("\t\t\t\t\t\t\t\t   不含此供货商，请您重新输入!\n");
					printf("\t\t\t\t\t\t\t\t   ");
					fgets(su, 50, stdin);
    				su[strcspn(su, "\n")] = '\0';
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
	if(L1->next == NULL){
		printf("\t\t\t\t\t\t\t\t\t     此时不含任何进货信息，无法查询破损");
		system("pause");
		return;
	}
	int kk = 0;
	//("%d",&selectnum);
	int selectnum;
	int k = rand() % 100;
	if(k >= 90){
		printf("\t\t\t\t\t\t\t\t   -----------本次进货无商品破损----------------\n");
		return;
	}
	else{//k<90说明有破损
		//fff:
		printf("\t\t\t\t\t\t\t\t\t     ----------------------------------------------\n");
		printf("\t\t\t\t\t\t\t\t\t                        商品破损                     \n");
		printf("\t\t\t\t\t\t\t\t\t     ------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t\t\t     |      (1): 随机生成破损商品                   |\n");
		printf("\t\t\t\t\t\t\t\t\t     |      (2): 商家手动输入破损商品名称及编号     |\n");
		printf("\t\t\t\t\t\t\t\t\t     |      (0): 退出破损模块                       |\n");
		printf("\t\t\t\t\t\t\t\t\t     |----------------------------------------------|\n");
		//char ss[10];//gets(ss);
		//("%d",&selectnum);
		fff:
		while(true){
			printf("\t\t\t\t\t\t\t\t\t     请输入您需要进行的操作   ");
			selectnum = inputNum();
			switch(selectnum){
			case(0):{
				if(kk == 0){
					printf("\t\t\t\t\t\t\t\t\t     本次操作未产生实际损耗\n");
					return;
				}
				else{
					printf("\t\t\t\t\t\t\t\t\t     损耗后的订单如下\n");
					printproductinlist();
				
					printfile();
					system("pause");
					return;
				}
			}
			
			case(1):{
			
				printf("\t\t\t\t\t\t\t\t\t     随机生成破损商品名称及编号\n");
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
					printf("\t\t\t\t\t\t\t\t\t     商品随机生成失败，所生成商品编号不在进货单中，请重新操作！\n");
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
				p->sum_price = p->sum_price - p->commodity_price * h;
				kk++;
				printf("\t\t\t\t\t\t\t\t\t     %d号%s共有%d箱破损，总瓶数减少%d瓶\n",n,str,h,sum);
				printf("\t\t\t\t\t\t\t\t\t     该商品现有箱数%d箱,由于破损,总价调整为%.2lf\n",p->commodity_number,p->sum_price);
				break;
			}
			case(2):{
				printf("\t\t\t\t\t\t\t\t\t     请输入破损商品名称   ");
				char sp[100];
				fgets(sp, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
				sp[strcspn(sp, "\n")] = '\0'; // 去掉字符串末尾的换行符
				while(strcmp(sp, "农夫山泉") != 0 && strcmp(sp, "汇源") != 0 && strcmp(sp, "青岛啤酒") != 0&& strcmp(sp, "娃哈哈") != 0&& strcmp(sp, "五粮液") != 0 && strcmp(sp, "舍得") != 0 && strcmp(sp, "可口可乐") != 0 && strcmp(sp, "喜茶") != 0 && strcmp(sp, "大窑嘉宾") != 0 && strcmp(sp, "康师傅") != 0){
	    			printf("\t\t\t\t\t\t\t\t\t     您输入的酒水名称有误，请重新输入\n");
	    			printf("\t\t\t\t\t\t\t\t\t     ");
	    			fflush(stdin);
	    			fgets(sp, 100, stdin); // 50表示输入的字符数最多为50个，可以根据实际需要调整
					sp[strcspn(sp, "\n")] = '\0'; // 去掉字符串末尾的换行符
				}
				printf("\t\t\t\t\t\t\t\t\t     请输入破损商品编号   ");
				int damage_num;
				damage_num = inputNum();
				while(damage_num == -1){
	    			printf("\t\t\t\t\t\t\t\t\t     请输入合法编号!\n");
        			printf("\t\t\t\t\t\t\t\t\t     ");
        			fflush(stdin); // 清空缓存区，避免无限循环
        			damage_num = inputNum();
				}	
				productin *p = NULL;
				p = searchproductinlist(sp,damage_num);
				while(p == NULL){
	    			printf("\t\t\t\t\t\t\t\t\t     您输入的编号有误，该名称及编号对应的商品不在订单中请重新输入\n");
	    			printf("\t\t\t\t\t\t\t\t\t     ");
	    			fflush(stdin);
	    			damage_num = inputNum();
	    			p = searchproductinlist(sp,damage_num);
				}

				printf("\t\t\t\t\t\t\t\t\t     请输入破损商品箱数   ");
				int damagebox,damagebottle,damagesum = 0;
				damagebox = inputNum();
				while(damagebox == -1 || damagebox > p->commodity_number || damagebox < 0){
	    			printf("\t\t\t\t\t\t\t\t\t     请输入大于0小于总箱数的合法箱数!\n");
        			printf("\t\t\t\t\t\t\t\t\t     ");
        			fflush(stdin); // 清空缓存区，避免无限循环
        			damagebox = inputNum();
				}
				int yf = damagebox,i = 1;
				p->commodity_number -= yf;
				while(damagebox--){
					printf("\t\t\t\t\t\t\t\t\t     请输入第%d箱中破损商品瓶数   ",i);
					i++;
					damagebottle = inputNum();
					while(damagebottle == -1 || damagebottle > p->commodity_packagenum || damagebottle < 0){
	    				printf("\t\t\t\t\t\t\t\t\t     请输入大于0小于总瓶数的合法瓶数!\n");
        				printf("\t\t\t\t\t\t\t\t\t     ");
        				fflush(stdin); // 清空缓存区，避免无限循环
        				damagebottle = inputNum();
					}
					damagesum += damagebottle;
					p->commodity_packagenum -= damagebottle;
				}
				printf("\t\t\t\t\t\t\t\t\t     原总价%.2lf\n",p->sum_price);
				p->sum_price -= p->commodity_price * yf;
			
				printf("\t\t\t\t\t\t\t\t\t     %s%d号共%d箱破损，总瓶数减少%d瓶\n",sp,damage_num,yf,damagesum);
				printf("\t\t\t\t\t\t\t\t\t     该商品现有箱数%d箱,由于破损,总价调整为%.2lf\n",p->commodity_number,p->sum_price);
				kk++;
				break;
			}
			default:{
				printf("\t\t\t\t\t\t\t\t\t     请输入0~2的合法字符\n");
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
    	printf("\t\t\t\t\t--------------------------------------------\n");
		printf("\t\t\t\t\t                进货模块                 \n");
		printf("\t\t\t\t\t--------------------------------------------\n");
		printf("\t\t\t\t\t|       （1）  修改订单信息                |\n");
		printf("\t\t\t\t\t|       （2）  删除部分订单信息            |\n");
		printf("\t\t\t\t\t|       （3）  打印订单信息                |\n");
		printf("\t\t\t\t\t|       （4）  增加订单信息                |\n");
		printf("\t\t\t\t\t|       （5）  将订单信息写到in.txt文件中  |\n");
		printf("\t\t\t\t\t|       （6）  查询某一条订单信息          |\n");
		printf("\t\t\t\t\t|       （7）  查询商品损耗情况            |\n");
		printf("\t\t\t\t\t|       （0）  操作结束                    |\n");
		printf("\t\t\t\t\t--------------------------------------------\n");
		printf("\t\t\t\t\t      请输入你想要进行的服务：(0-7) ");
		
		int productin_num = inputNum();
		//("%d",&productin_num);
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
				//system("pause");
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
				//system("cls");
				printf("\t\t\t\t\t       您输入的信息有误,请输入0~7中的数字\n");
				printf("\t\t\t\t\t       ");
				//system("pause");
				break;
		}
	}		
}


//#include"supplier.h"
//
//extern supplierlist L2;
//const char *stringsm[] = {"firstsupplier", "secondsupplier", "thirdsupplier"};
//
//void createsupplylist(){
//	L2 = (supplier*)malloc(sizeof(supplier));
//	L2->next = NULL;
//	supplier* pro = L2;
//	int k = abs(1 + rand() % 3);
//	//p = L2->next;
//	int supplynum = 3;
//	//printf("\t\t\t\t         ��ֱ�����3����Ӧ�̵������\n");
//	while(supplynum--){
//		int m = 2000 + abs (rand() % 1000);
//		supplier* p = (supplier*)malloc(sizeof(supplier));//ÿ�η���һ���µĿռ�
//		p->transport_cost = m;
//		//char str[50];
//		strcpy(p->suppliername,stringsm[(++k) % 3]);
//		//strcpy(p->suppliername,str);
//		//scanf("%d",&p->transport_cost);
//		p->next = NULL;
//		pro->next = p;
//		pro = p;
//	}
//	pro->next = NULL;
//}
//void printsupplylist(){
//	supplier *p = L2->next;
//	while(p != NULL){
//		printf("%d  %s ",p->transport_cost,p->suppliername);
//		p = p->next;
//	}
//}
//typedef struct productin{//�̼ҽ���ʱ����Ʒ�ṹ��
//    char commodity_name[100];//��ƷƷ��
//    int commodity_id;//��Ʒ���,�������ֲ�ͬ��Ʒ��ͬһ��Ʒ�Ĳ�ͬ�����ζ��
//    int  commodity_packagenum;//ÿ����Ʒ�ж���ƿ
//    double commodity_price;//��Ʒ����
//    int sum_price;//��Ʒ�ܼ�
//    int commodity_number;//��Ʒ����������������
//    int commodity_volume;//һƿ��Ʒ�ж��ٺ���
//    char date[50];//��������
//    supplier* provider;
//    struct productin *next;
//}productin,*productlistin;
//
//productlistin L1;//������
//
//void generate_randomstring(char str[], int n)//��ָ���ַ�������������ַ���
//{
//    const char *strings[] = {"NongFuSpring", "Huiyuan", "BeerQingdao", "Wahaha", "Wuliangye","Kangshifu"}; // �������ַ����б�
//    const int len = sizeof(strings) / sizeof(strings[0]); // �ַ����б����ַ����ĸ���
//
//    srand(time(NULL)); // �����������
//
//    int index = rand() % len; // ���ַ����б������ѡ��һ���ַ���
//    int str_len = strlen(strings[index]); // ��ȡ��ѡ�ַ����ĳ���
//
//    strcpy(str, strings[index]); // ����ѡ�ַ������Ƶ��洢����ַ������ַ�������
//
//    if (n > str_len) {
//        str[str_len] = '\0'; // �ڴ洢����ַ������ַ������ĩβ����ַ���������־
//    }
//
//    return;
//}
//
//void initproductinlist()//��ʼ���̼�����
//{
//	L1 = (productin*)malloc(sizeof(productin));
//	L1->next = NULL;
//}
//
//supplier* choosesupplier(){//�ҵ�������С�Ĺ�Ӧ��
//	if(L2->next == NULL)
//	{
//		printf("\t\t\t\t\t         ��Ӧ����Ϣ\n");
//	}
//	supplier *p = L2->next;
//	supplier *flag;
//	int su = max_;
//	while(p != NULL){
//		if(su > p->transport_cost){
//			su = p->transport_cost;
//			flag = p;
//		}
//		p = p->next;
//	}
//	
//	return flag;
//}
//
//void createproductinlist() {
//	productin *p = L1;
//    FILE* f;
//    if((f = fopen("in.txt","r"))==NULL){
//        printf("�ļ�������\n");
//        return;
//    }
//    //printf("\t\t\t����������Ʒ��Ϣ,����end��ʾ����\n");
//    while(true)
//    {
//    	productin *pro = (productin*)malloc(sizeof(productin)); //���� һ���µĽṹ��ָ��,���ռ�
//    	//printf("��������Ʒ���ƣ�\n");
//    	fscanf(f,"%s", pro->commodity_name);
//    	
//		if (strcmp(pro->commodity_name, "end") == 0){
//    		//printf("\t\t\t\t�����˳�����ӭ�´ι���\n");
//    		fclose(f);
//            free(pro);
//            break;
//        }
//        
//    	//printf("��������Ʒ���: \n");
//        fscanf(f,"%d",&pro->commodity_id);
//        
//        //��װ��С
//        fscanf(f,"%d",&pro->commodity_packagenum);
//
//       // printf("��������Ʒ�۸�: \n");
//        fscanf(f,"%lf", &pro->commodity_price);
//
//        //printf("��������Ʒ����: \n");
//        fscanf(f,"%d", &pro->commodity_number);
//        
//        //�ܼ�
//        fscanf(f,"%d",&pro->sum_price);
//        
//        //������Ʒ����
//        fscanf(f,"%d",&pro->commodity_volume);
//
//        //printf("��������Ʒ��������: \n");
//        fscanf(f,"%s", pro->date);
//		createsupplylist();
//		pro->provider = choosesupplier();
//		
//		pro->sum_price += pro->provider->transport_cost;
//        pro->next = NULL;
//        p->next = pro;
//        p = pro;
//
//	}
//	//printf("��Ʒ��Ϣ�������\n");
//}
//
//void addproductinlist(){
//    printf("\t\t\t\t\t------------��Ʒ���----------------\n");
//    printf("\t\t\t\t\t    ����0�˳����ģ��\n");
//    printf("\t\t\t\t\t    ����1: ������������Ʒ���Ƽ����\n");
//    printf("\t\t\t\t\t    ����2: �̼��ֶ����������Ʒ�����Ϣ\n");
//    int selectnum;
//    scanf("%d",&selectnum);
//    switch(selectnum){
//        case 0: {
//            return;
//        }
//        case 1: {
//        	printf("ϵͳ�Զ�������Ʒ��Ϣ\n");
//            char name[100];
//            int id;
//            int packagenum;
//            double price;
//            int sum;
//            int number;
//            int volume;
//            char date[50];
//            generate_randomstring(name, 100);
//            srand((unsigned int)time(NULL));
//            id = abs(1 + rand() % 3);
//            //printf("666\n");
//            packagenum = abs(rand() % 37);
//            price = abs(1 + rand() % 1000) * 0.1;
//            number = abs(1 + rand() % 100);
//            sum = price * number;
//            volume = abs(600 + rand() % 200);
//            strcpy(date,"20230420");
//            
//            productin *p = L1;
//            while(p->next != NULL){
//                p = p->next;
//            }
//            productin *u = (productin*)malloc(sizeof(productin)); //���� һ���µĽṹ��ָ��,���ռ�
//            //printf("666\n");
//            strcpy(u->commodity_name, name);
//            u->commodity_id = id;
//            u->commodity_packagenum = packagenum;
//            u->commodity_price = price;
//            u->sum_price = sum;
//            u->commodity_volume = volume;
//            strcpy(u->date, date);
//            u->commodity_number = number;
//            createsupplylist();
//		    u->provider = choosesupplier();
//            u->next = p->next;
//            p->next = u;
//            p = u;
//
//            //printf("��Ʒ��Ϣ������!\n");
//            break;
//        }
//		case(2):{
//			printf("��������Ҫ��ӵ���ƷƷ�ơ���š���װ��С,��Ʒ���ۣ���Ʒ�ܼۣ�������������Ʒ�������������ڣ���Ӧ�� ����endadd��ʾ�������!\n");
//			productin *p = L1;
//			while(p->next != NULL){
//				p = p->next;
//			}
//			productin *u = (productin*)malloc(sizeof(productin)); //���� һ���µĽṹ��ָ��,���ռ�
//			char name[100];//��ˮƷ��
//		    int id;//��Ʒ���,�������ֲ�ͬ��Ʒ��ͬһ��Ʒ�Ĳ�ͬ�����ζ��
//		    int  packagenum;//��װ��С  
//		    double price;//��Ʒ�۸�
//		    int sum;//��Ʒ�ܼ�
//		    int number;//��Ʒ����������������
//		    int volume;//��Ʒ����
//		    char date[50];//��������
//		    
//		    while(1){
//		    	scanf("%s",name);
//		    	if(strcmp(name,"endadd") == 0){
//		    		printf("��Ʒ��Ϣ������!\n");
//		    		break;
//				}
//				scanf("%d %d",&id,&packagenum);
//				scanf("%lf",&price);
//				scanf("%d",&number);
//				scanf("%d",&sum);
//				scanf("%d",&volume);
//				//scanf("%lf",&price);
//		    	//scanf("%d %d",&number,&sum);
//		    	scanf("%s",date);
//		    	strcpy(u->commodity_name,name);
//		    	u->commodity_id = id;
//		    	u->commodity_packagenum = packagenum;
//		    	u->commodity_price = price;
//		    	u->sum_price = sum;
//		    	u->commodity_volume = volume;
//		    	strcpy(u->date,date);
//		    	u->commodity_number = number;
//		    	createsupplylist();
//		    	u->provider = choosesupplier();
//		    	u->next = p->next;
//		    	p->next = u;
//		    	p = u;
//			}
//			break;
//		}
//	}
//    
//}
//void printfile(){
//	productin *p = L1->next;
//	
//	FILE* f;
//    if((f = fopen("c.txt","w"))==NULL){
//        printf("�ļ�������\n");
//        return;
//    }
//    
//    while(p != NULL){
//    	fprintf(f,"%s ",p->commodity_name);
//    	fprintf(f,"%d ",p->commodity_id);
//    	fprintf(f,"%d ",p->commodity_packagenum);
//    	fprintf(f,"%lf ",p->commodity_price);
//    	fprintf(f,"%d ",p->commodity_number);
//    	fprintf(f,"%d ",p->sum_price);
//    	fprintf(f,"%d ",p->commodity_volume);
//		fprintf(f,"%s\n",p->date);
//		p = p->next;
//	}
//	fclose(f);
//}
//
//void printproductinlist(){//��ӡ������Ϣ
//	if(L1->next == NULL){
//		printf("δ¼���κν�����Ϣ���޷��������¼����Ʒ��Ϣ�����\n");
//	}
//	printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
//	productin *p = L1->next;
//	while(p != NULL){
//		supplier* g = p->provider;
//		printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
//		p = p->next;
//	}
//}
//
//productin* searchproductinlist(char name[100],int id){//���̼�������Ѱ��Ŀ����
//	//printf("����\n");
//	productin* qq = L1->next;
//	//printf("qq��ȥ��\n");
//	//printf("����\n");
//	while(qq != NULL && (strcmp(qq->commodity_name,name) != 0 || qq->commodity_id != id)){
//		qq = qq->next;
//	}
////	printf("����\n");
//	if(qq == NULL) return NULL;
//	
//	return qq;
//}
//
//
//void deleteproductinlist(){//���̼�������ɾ����Ϣ
//	if(L1->next == NULL){
//		printf("��ʱ�����κν�����Ϣ���޷�����ɾ��\n");	
//		return;
//	}
//	int selectnum;
//	scanf("%d",&selectnum);
//	printf("��������Ҫɾ������Ʒ���Ƽ����,����enddelete��ʾ�������!\n");
//	
////	FILE* f;
////
////    if((f = fopen("C:\\Users\\lenovo\\Desktop\\deleteproductin.txt","r"))==NULL){
////        printf("�ļ�������\n");
////        return;
////    }
//    
//    while(true){
//    	productin *a = (productin*)malloc(sizeof(productin));
//    
//    	scanf("%s", a->commodity_name);
//    	
//    	if (strcmp(a->commodity_name, "enddelete") == 0){
//    		printf("������Ϣɾ�����!\n");
//            free(a);
//            break;
//        }
//	
//    	scanf("%d",&a->commodity_id);
//    
//		productin *aim = searchproductinlist(a->commodity_name,a->commodity_id);
//	
//		if(aim == NULL){
//			return;
//		}
//	
//		productin *p = L1;
//	
//		while(p->next->commodity_name != aim->commodity_name || p->next->commodity_id != aim->commodity_id){//δ�ҵ�Ŀ����
//		
//			p = p->next;
//		
//		}
//	
//		p->next = aim->next;
//	
//		aim->next = NULL;
//	
//		free(aim);
//		
//		if(L1->next == NULL){
//			
//			printf("��ʱ�����κν�����Ϣ���޷�����ɾ��\n");
//			
//			return;
//		}
//	}
//}
//void searchproductin(){//������Ʒ��Ϣ
//	//productin *q = L1->next;
//	printf("\t\t\t\t\t   ����������Ҫͨ���ĸ����Բ�����Ʒ��Ϣ\n");
//	printf("\t\t\t\t\t         (����0��ʾ��������\n");
//	printf("\t\t\t\t\t         1  ��ˮƷ�Ƽ���ˮ���\n");
//	printf("\t\t\t\t\t         2  ��ˮƷ�Ƽ���װ��С\n");
//	printf("\t\t\t\t\t         3  ��ˮƷ�Ƽ���Ʒ����\n");
//	printf("\t\t\t\t\t         4  ��ˮƷ�Ƽ���������\n");
//	printf("\t\t\t\t\t         5  ��ˮƷ�Ƽ���Ʒ�ܼ�\n");
//	printf("\t\t\t\t\t         6  ��Ʒ�ܼۼ���������\n");
//	int search_num;
//	scanf("%d",&search_num);
//	switch(search_num){
//		case(0):{
//			
//			break;
//		}
//		case(1):{
//			printf("\t\t\t\t\t           �������ˮƷ�Ƽ���ˮ���\n");
//			char str[100];
//			scanf("%s",str);
//			int numb;
//			scanf("%d",&numb);
//			productin *p = searchproductinlist(str,numb);
//			if(p == NULL){
//				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
//			}
//			printf("\t\t\t\t\t         ����Ʒ��Ϣȫ������\n");
//			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
//			supplier* g = p->provider;
//			printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
//			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
//			break;
//		}
//		case(2):{
//			printf("\t\t\t\t\t           �������ˮƷ�Ƽ���װ��С\n");
//			char str[100];
//			scanf("%s",str);
//			int package;
//			scanf("%d",&package);
//			productin *p = L1->next;
//			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_packagenum != package)){
//				p = p->next;
//			}
//			if(p == NULL){
//				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
//			}
//			printf("\t\t\t\t\t         ����Ʒȫ����Ϣ����\n");
//			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
//			supplier* g = p->provider;
//			printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
//			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
//			break;
//		}
//		case(3):{
//			printf("\t\t\t\t\t           �������ˮƷ�Ƽ���������\n");
//			char str[100];
//			scanf("%s",str);
//			int price;
//			scanf("%d",&price);
//			productin *p = L1->next;
//			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_price != price)){
//				p = p->next;
//			}
//			if(p == NULL){
//				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
//			}
//			printf("\t\t\t\t\t         ����Ʒȫ����Ϣ����\n");
//			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
//			supplier* g = p->provider;
//			printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
//			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
//			break;
//		}
//		case(4):{
//			printf("\t\t\t\t\t           �������ˮƷ�Ƽ���������\n");
//			char str[100];
//			scanf("%s",str);
//			int in;
//			scanf("%d",&in);
//			productin *p = L1->next;
//			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_number != in)){
//				p = p->next;
//			}
//			if(p == NULL){
//				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
//			}
//			printf("\t\t\t\t\t         ����Ʒȫ����Ϣ����\n");
//			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
//			supplier* g = p->provider;
//			printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
//			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
//			break;
//		}
//		case(5):{
//			printf("\t\t\t\t\t           �������ˮƷ�Ƽ���Ʒ�ܼ�\n");
//			char str[100];
//			scanf("%s",str);
//			int sum;
//			scanf("%d",&sum);
//			productin *p = L1->next;
//			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->sum_price != sum)){
//				p = p->next;
//			}
//			if(p == NULL){
//				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
//			}
//			printf("\t\t\t\t\t         ����Ʒȫ����Ϣ����\n");
//			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
//			supplier* g = p->provider;
//			printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
//			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
//			break;
//		}
//		case(6):{
//			printf("\t\t\t\t\t           ��������Ʒ�ܼۼ���������\n");
//			int sum;
//			scanf("%d",&sum);
//			char da[50];
//			scanf("%d",&da);
//			productin *p = L1->next;
//			while(p != NULL && (strcmp(p->date,da) != 0 || p->sum_price != sum)){
//				p = p->next;
//			}
//			if(p == NULL){
//				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
//			}
//			printf("\t\t\t\t\t         ����Ʒȫ����Ϣ����\n");
//			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
//			supplier* g = p->provider;
//			printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
//			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
//			break;
//		}
//		default:{
//			printf("������Ĳ�ѯ���Ϊ�Ƿ��ַ��������˳�");
//			break;
//		}
//		
//	}
//	//printf("\t\t\t\t\t   ��Ʒ������Ϣ������ϣ�");
//}
//void correctproductinlist(){
//	if(L1->next == NULL){
//		printf("��ʱ�����κν�����Ϣ���޷������޸�\n");	
//		return;
//	}
//	
//	//printf("��������Ҫ�޸���Ʒ�����Ƽ����,����endcorrect��ʾ�������!\n");
//    
//	while(true){
//		printf("��������Ҫ�޸���Ʒ�����Ƽ����,����endcorrect��ʾ�������!\n");
//		
//    	productin *a = (productin*)malloc(sizeof(productin));
//    
//    	scanf("%s", a->commodity_name);
//    	
//    	if (strcmp(a->commodity_name, "endcorrect") == 0){
//    		printf("������Ϣ�޸����!\n");
//    		//fclose(f);
//            free(a);
//            break;
//        }
//	
//    	scanf("%d",&a->commodity_id);
//    
//		productin *aim = searchproductinlist(a->commodity_name,a->commodity_id);
//	
//		if(aim == NULL){
//			printf("����Ʒ���ڽ������У��޷��޸�\n");
//			continue;
//		}
//		
//		//int id;
//		printf("�������޸ĺ����Ʒ�����Ƽ����\n");
//		
//		
//		scanf("%s",aim->commodity_name);
//		
//		scanf("%d",&aim->commodity_id);
//		if(L1->next == NULL){
//			
//			printf("��ʱ�����κν�����Ϣ���޷������޸�\n");
//			
//			return;
//		}
//	}
//	
//}
//
//
//void damage(){
//	srand((unsigned int)time(NULL));
//	//scanf("%d",&selectnum);
//	int selectnum;
//	int k = rand() % 100;
//	if(k >= 90){
//		printf("\t\t\t\t\t-----------���ν�������Ʒ����----------------\n");
//		return;
//	}
//	else{//k<90˵��������
//		printf("\t\t\t\t\t------------��Ʒ����----------------\n");
//		printf("\t\t\t\t\t    ����0�˳�����ģ��\n");
//		printf("\t\t\t\t\t    ����1: �������������Ʒ���Ƽ����\n");
//		printf("\t\t\t\t\t    ����2: �̼��ֶ�����������Ʒ���Ƽ����\n");
//		scanf("%d",&selectnum);//�����Զ������������̼���������
//		if(selectnum != 0 && selectnum != 1 && selectnum != 2){
//			printf("\t\t\t\t\t    ��������������Ϸ��ַ�0��1��2������3�λ��ᣡ\n");
//			scanf("%d",&selectnum);
//		}
//		if(selectnum != 0 && selectnum != 1 && selectnum != 2){
//			printf("\t\t\t\t\t    ��������������Ϸ��ַ�0��1��2������2�λ��ᣡ\n");
//			scanf("%d",&selectnum);
//		}
//		if(selectnum != 0 && selectnum != 1 && selectnum != 2){
//			printf("\t\t\t\t\t    ��������������Ϸ��ַ�0��1��2������1�λ��ᣡ\n");
//			scanf("%d",&selectnum);
//		}
//		if(selectnum != 0 && selectnum != 1 && selectnum != 2){
//			printf("\t\t\t\t\t    �������󣬳����˳���\n");
//			return;
//		}
//	}
//	switch(selectnum){
//		case(0):{
//			
//			return;
//		}
//		case(1):{
//			printf("\t\t\t\t\t     �������������Ʒ���Ƽ����\n");
//			int n = 1 + rand() % 3;
//			
//			int v = 1 + rand() % 3;
//			int sum = 0;
//			char str[100];
//			generate_randomstring(str,100);
//			productin *p = NULL;
//			p = searchproductinlist(str,n);
//			//printf("777");
//			int h = v;
//			while(v--){
//				srand((unsigned int)time(NULL));
//				int w = 1 + rand() % 3;
//				sum += w;//v����Ʒ�й�sumƿ��������
//			}
//			p->commodity_number -= h;//��v����Ʒ��������
//			//p->commodity_packagenum -= w;//ָ��ĳ��Ʒĳ������ʧ��wƿ
//			p->sum_price = p->sum_price - p->commodity_price * sum;
//			printf("\t\t\t\t\t     ������Ʒ������%d��������ƿ������%dƿ\n",h,sum);
//			printf("\t\t\t\t\t     ����Ʒ��������%d��,��������,�ܼ۵���Ϊ%d\n",p->commodity_number,p->sum_price);
//			break;
//		}
//		case(2):{
//			printf("\t\t\t\t\t     ������������Ʒ���Ƽ����\n");
//			char sp[100];
//			scanf("%s",sp);
//			int damage_num;
//			scanf("%d",&damage_num);
//			productin *p = NULL;
//			p = searchproductinlist(sp,damage_num);
//			printf("\t\t\t\t\t     ������������Ʒ����\n");
//			int damagebox,damagebottle,damagesum = 0;
//			scanf("%d",&damagebox);
//			while(damagebox--){
//				printf("\t\t\t\t\t     ������������Ʒƿ��\n");
//				scanf("%d",&damagebottle);
//				damagesum += damagebottle;
//			}
//			p->sum_price = p->sum_price - p->commodity_price * damagesum;
//			
//			printf("\t\t\t\t\t     ������Ʒ������%d��������ƿ������%dƿ\n",damagebox,damagebottle);
//			printf("\t\t\t\t\t     ����Ʒ��������%d��,��������,�ܼ۵���Ϊ%d\n",p->commodity_number,p->sum_price);
//			break;
//		}
//	}
//	
//	
//}
//
//void productin_interface(){	
//	initproductinlist();
//	createproductinlist();
//	while(1){
//		system("cls");
//		printf("\t\t\t\t\t------------����ģ��----------------\n");
//		printf("\t\t\t\t\t     (����0��ʾ��������\n");
//		printf("\t\t\t\t\t     ����1  �޸Ķ�����Ϣ\n");
//		printf("\t\t\t\t\t     ����2  ɾ�����ֶ�����Ϣ\n");
//		printf("\t\t\t\t\t     ����3  ��ӡ������Ϣ\n");
//		printf("\t\t\t\t\t     ����4  ���Ӷ�����Ϣ\n");
//		printf("\t\t\t\t\t     ����5  ��������Ϣд��c.txt�ļ���\n");
//		printf("\t\t\t\t\t     ����6  ��ѯĳһ��������Ϣ\n");
//		printf("\t\t\t\t\t     ����7  ��ѯ�Ƿ�����Ʒ���\n");
//		printf("\t\t\t\t\t ����������Ҫ���еķ���(0-6)\n");
//		printf("\t\t\t\t\t   ��Ʒ������Ϣ������ϣ�");
//		int productin_num;
//		scanf("%d",&productin_num);
//		switch(productin_num){
//			case(0):{
//				
//				return;
//			}
//			case(1):{
//				system("cls");
//				correctproductinlist();
//				system("pause");
//				printf("\t\t\t\t\t     �����޸ĺ�Ķ���\n");
//				printproductinlist();
//				system("pause");
//				break;
//			}
//			case(2):{
//				system("cls");
//				deleteproductinlist();
//				break;
//			}
//			case(3):{
//				system("cls");
//				createsupplylist();
//				choosesupplier();
//				printproductinlist();
//				system("pause");
//				break;
//			}
//			case(4):{
//				system("cls");
//				addproductinlist();
//				system("pause");
//				printf("\t\t\t\t\t     �������Ӻ�Ķ���\n");
//				printproductinlist();
//				system("pause");
//				break;
//			}
//			case(5):{
//				system("cls");
//				printfile();
//				printf("\t\t\t\t\t     ������Ϣ��д���ļ���\n");
//				system("pause");
//				break;
//			}
//			case(6):{
//				system("cls");
//				searchproductin();
//				system("pause");
//				break;
//			}
//			case(7):{
//				system("cls");
//				damage();
//				system("pause");
//				break;
//			}
//			default:
//				printf("������ı������������0~7�е�����\n");
//		}
//	}		
//}	
////
////int main(){
////	initproductinlist();
////	createproductinlist();
////	printproductinlist();
//////addproductinlist();
//////printproductinlist();
////	productin_interface();
//////	printfile();
//////	damage();
//////	searchproductin();
//////	createsupplylist();
////// 	supplier *t = choosesupplier();
//////	printf("%s  %d\n",t->suppliername,t->transport_cost);
//////	printsupplylist();
////	return 0;
////}

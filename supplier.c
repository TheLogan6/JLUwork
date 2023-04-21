#include"supplier.h"
#include"customer.h"

extern supplierlist L2;
extern char *stringsm[];
extern productlistin L1;//������
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
	//printf("\t\t\t\t         ��ֱ�����3����Ӧ�̵������\n");
	while(supplynum--){
		printf("\t\t\t\t\t   �������%d����Ӧ�̵������",i);
		i++;
		//int m = 2000 + abs (rand() % 1000);
		int m;
		m = checkNum();
		supplier* p = (supplier*)malloc(sizeof(supplier));//ÿ�η���һ���µĿռ�
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
		printf("����Ϊ�գ�\n");
	}
	supplier *p = L2->next;
	while(p != NULL){
		printf("%-20s   %-10d\n",p->suppliername,p->transport_cost);
		p = p->next;
	}
}


void generate_randomstring(char str[], int n)//��ָ���ַ�������������ַ���
{
    const char *strings[] = {"ũ��ɽȪ", "��Դ", "�ൺơ��", "���", "����Һ","��ʦ��","�޹���","ϲ��","�ɿڿ���","��Ҥ�α�"}; // �������ַ����б�
    const int len = sizeof(strings) / sizeof(strings[0]); // �ַ����б����ַ����ĸ���

    srand(time(NULL)); // �����������

    int index = rand() % len; // ���ַ����б������ѡ��һ���ַ���
    int str_len = strlen(strings[index]); // ��ȡ��ѡ�ַ����ĳ���

    strcpy(str, strings[index]); // ����ѡ�ַ������Ƶ��洢����ַ������ַ�������

    if (n > str_len) {
        str[str_len] = '\0'; // �ڴ洢����ַ������ַ������ĩβ����ַ���������־
    }

    return;
}


void initproductinlist()//��ʼ���̼�����
{
	L1 = (productin*)malloc(sizeof(productin));
	L1->next = NULL;
}

supplier* choosesupplier(){//�ҵ�������С�Ĺ�Ӧ��
	if(L2->next == NULL)
	{
		printf("\t\t\t\t\t         ��Ӧ����Ϣ\n");
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
        printf("�ļ�������\n");
        return;
    }
    createsupplylist();
    //printf("\t\t\t����������Ʒ��Ϣ,����end��ʾ����\n");
    while(true)
    {
    	productin *pro = (productin*)malloc(sizeof(productin)); //���� һ���µĽṹ��ָ��,���ռ�
    	//printf("��������Ʒ���ƣ�\n");
    	fscanf(f,"%s", pro->commodity_name);
    	
		if (strcmp(pro->commodity_name, "end") == 0){
    		//printf("\t\t\t\t�����˳�����ӭ�´ι���\n");
    		fclose(f);
            free(pro);
            break;
        }
        
    	//printf("��������Ʒ���: \n");
        fscanf(f,"%d",&pro->commodity_id);
        
        //ÿ��ƿ��
        fscanf(f,"%d",&pro->commodity_packagenum);

       // printf("��������Ʒ�۸�: \n");
        fscanf(f,"%lf", &pro->commodity_price);

        //printf("��������Ʒ����: \n");
        fscanf(f,"%d", &pro->commodity_number);
        
        //�ܼ�
        fscanf(f,"%lf",&pro->sum_price);
        
        //������Ʒ����
        fscanf(f,"%d",&pro->commodity_volume);

        //printf("��������Ʒ��������: \n");
        fscanf(f,"%s", pro->date);
		
		pro->provider = choosesupplier();
		
		pro->sum_price += pro->provider->transport_cost;
        pro->next = NULL;
        p->next = pro;
        p = pro;

	}
	//printf("��Ʒ��Ϣ�������\n");
}

void printproductinlist(){//��ӡ������Ϣ
	if(L1->next == NULL){
		printf("\t\t\t\t\t δ¼���κν�����Ϣ���޷��������¼����Ʒ��Ϣ�����\n");
	}
	printf("\t\t\t\t\t ---------------------------------------------------------\n");
	printf("\t\t\t\t\t                         ��Ʒ��ӡ                          \n");
	printf("\t\t\t\t\t --------------------------------------------------------- \n");
	printf("\t ��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������      ������\n");
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
        printf("�ļ�������\n");
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
	printf("������Ϣ�Ѿ�ȫ��д���ļ���\n");
	fclose(f);
}
//ÿ��۸���ÿ��ƿ��*���ۣ��ܼ�����������ÿ��۸�
void addproductinlist(){
	int ko = 0;
	printf("\t\t\t\t\t\t\t\t   ------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t                          �������                       \n");
	printf("\t\t\t\t\t\t\t\t   ------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t   |            ��1��: �̼��ֶ����������Ʒ�����Ϣ     |\n");
	printf("\t\t\t\t\t\t\t\t   |            ��0��: �˳����ģ��                     |\n");
	printf("\t\t\t\t\t\t\t\t   ---------------------------------------------------\n");
	//char str[10];
	//gets(str);
    int selectnum;
	
    //int selectnum;
    //scanf("%d",&selectnum);
    while(true){
    	printf("\t\t\t\t\t\t\t\t   ����������Ҫ���еĲ���");
    	selectnum = checkNum();
    	switch(selectnum){
	        case(0) : {
	        	if(ko == 0){
	        		printf("\t\t\t\t\t   �������δִ����Ч����,�����˳�\n");
	        		return;
				}
				else{
					printf("\t\t\t\t\t\t\t   ������Ӻ�Ķ���\n");
					printproductinlist();			
					printfile();
					system("pause");
					return;					
				}
	        }
			case(1) : {
					ko++;
				//printf("\t\t\t\t\t��������Ҫ��ӵ���ƷƷ�ơ���š���װ��С,��Ʒ���ۣ���Ʒ�ܼۣ�������������Ʒ�������������ڣ���Ӧ�� \n");
				printf("\t\t\t\t\t    ��ƷƷ��ֻ����\"ũ��ɽȪ\",\"��Դ\",\"�ൺơ��\",\"���\",\"�޹���\",\"����Һ\",\"��ʦ��\",\"�ɿڿ���\",\"ϲ��\",\"��Ҥ�α�\"\n");
	
				productin *p = L1;
				while(p->next != NULL){
					p = p->next;
				}//pָ����������λ��
				//productin *u = (productin*)malloc(sizeof(productin));
//				printf("\t\t\t\t\t��������Ҫ��ӵ���Ʒ��������\n");
//				printf("\t\t\t\t\t��������Ҫ��ӵĹ�Ӧ��\n");
				productin *u = (productin*)malloc(sizeof(productin)); //���� һ���µĽṹ��ָ��,���ռ�
				char name[100];//��ˮƷ��
			    int id;//��Ʒ���,�������ֲ�ͬ��Ʒ��ͬһ��Ʒ�Ĳ�ͬ�����ζ��
			    int  packagenum;//ÿ��ƿ��  
			    double price;//��Ʒ�۸�
			    int sum;//��Ʒ�ܼ�
			    int number;//��Ʒ����������������
			    int volume;//��Ʒ����
			    char str[50];//��������
			    printf("\t\t\t\t\t��������Ҫ��ӵ���ƷƷ��\n");
			    scanf("%s",name);
				while(strcmp(name, "ũ��ɽȪ") != 0 && strcmp(name, "��Դ") != 0 && strcmp(name, "�ൺơ��") != 0 && strcmp(name, "���") != 0 && strcmp(name, "�޹���") != 0&& strcmp(name, "����Һ") != 0 && strcmp(name, "��ʦ��") != 0 && strcmp(name, "ϲ��") != 0 && strcmp(name, "�ɿڿ���") != 0 && strcmp(name, "��Ҥ�α�") != 0){
	    			printf("������ľ�ˮ������������������!\n");
	    			fflush(stdin);
	    			scanf("%s",name);
				}
				printf("\t\t\t\t\t��������Ҫ��ӵ���Ʒ���\n");
				while(scanf("%d", &id) != 1) {
        			printf("������Ϸ����!\n");
        			fflush(stdin); // ��ջ���������������ѭ��
    			}
    			printf("\t\t\t\t\t��������Ҫ��ӵ���Ʒ��װ��С\n");
    			while(scanf("%d", &packagenum) != 1) {
        			printf("������Ϸ���װ��С!\n");
        			fflush(stdin); // ��ջ���������������ѭ��
    			}
				//scanf("%d %d",&id,&packagenum);
				printf("\t\t\t\t\t��������Ҫ��ӵ���Ʒ����\n");
				while(scanf("%lf",&price) != 1) {
        			printf("������Ϸ�����!\n");
        			fflush(stdin); // ��ջ���������������ѭ��
    			}
				//scanf("%lf",&price);
				printf("\t\t\t\t\t��������Ҫ��ӵ���Ʒ��������\n");
				while(scanf("%d",&number) != 1) {
        			printf("������Ϸ���������!\n");
        			fflush(stdin); // ��ջ���������������ѭ��
    			}
				printf("\t\t\t\t\t��������Ҫ��ӵ���Ʒ����\n");
				while(scanf("%d",&volume) != 1) {
        			printf("������Ϸ���Ʒ����!\n");
        			fflush(stdin); // ��ջ���������������ѭ��
    			}
			    printf("\t\t\t\t\t��������Ҫ��ӵ���Ʒ��������\n");
			    int valid_input = 0;
			    while (!valid_input) {
			        scanf("%s", str);
			        valid_input = 1;
			        for (int i = 0; i < strlen(str); i++) {
			            if (!isdigit(str[i]) || strlen(str) != 8) {
			                valid_input = 0;
			                printf("������Ϸ������ڸ�ʽ������ 20220101��\n");
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
				printf("�������������������������0��1!\n");
				fflush(stdin);
		}
	}
}


productin* searchproductinlist(char name[100],int id){//���̼�������Ѱ��Ŀ����
	//printf("����\n");
	productin* qq = L1->next;
	//printf("qq��ȥ��\n");
	//printf("����\n");
	while(qq != NULL && (strcmp(qq->commodity_name,name) != 0 || qq->commodity_id != id)){
		qq = qq->next;
	}
//	printf("����\n");
	if(qq == NULL) return NULL;
	
	return qq;
}


void deleteproductinlist(){//���̼�������ɾ����Ϣ
	int k0 = 0;
	printf("\t\t\t\t\t -----------------------------------------------\n");
	printf("\t\t\t\t\t                   ��Ʒɾ��                    \n");
	printf("\t\t\t\t\t -----------------------------------------------\n");
	if(L1->next == NULL){
		printf("��ʱ�����κν�����Ϣ���޷�����ɾ��\n");	
		return;
	}

    
    while(true){
    	printf("\t\t\t\t\t��������Ҫɾ������Ʒ����,����enddelete��ʾ�������!\n");
    	
    	productin *a = (productin*)malloc(sizeof(productin));
    
    	scanf("%s", a->commodity_name);
    	
    	if (strcmp(a->commodity_name, "enddelete") == 0){
    		if(k0 == 0){
    			printf("\t\t\t\t\t  δ������Чɾ������!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t   �����޸ĺ�Ķ���\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
        }
        
        while(strcmp(a->commodity_name, "ũ��ɽȪ") != 0 && strcmp(a->commodity_name, "��Դ") != 0 && strcmp(a->commodity_name, "�ൺơ��") != 0 && strcmp(a->commodity_name, "���") != 0 && strcmp(a->commodity_name, "�޹���") != 0&& strcmp(a->commodity_name, "����Һ") != 0 && strcmp(a->commodity_name, "��ʦ��") != 0 && strcmp(a->commodity_name, "ϲ��") != 0 && strcmp(a->commodity_name, "�ɿڿ���") != 0 && strcmp(a->commodity_name, "��Ҥ�α�") != 0){
    		printf("������ľ�ˮ������������������!\n");
    		fflush(stdin);
    		scanf("%s", a->commodity_name);
    		if (strcmp(a->commodity_name, "enddelete") == 0){
    		if(k0 == 0){
    			printf("\t\t\t\t\t  δ������Чɾ������!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t   �����޸ĺ�Ķ���\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
        }
		}
		printf("\t\t\t\t\t��������Ҫɾ����Ʒ�ı��,����11111����!\n");
		//while(scanf("%d",&a->commodity_id))
	    scanf("%d",&a->commodity_id);
	    if(a->commodity_id == 11111){
	    	if(k0 == 0){
    			printf("\t\t\t\t\t  δ������Чɾ������!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t   �����޸ĺ�Ķ���\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
		}
	    productin *aim = searchproductinlist(a->commodity_name,a->commodity_id);
	    while(aim == NULL){
	    	printf("\t\t\t\t\t   ������ı����������������\n");
	    	fflush(stdin);
	    	scanf("%d",&a->commodity_id);
	    	if(a->commodity_id == 11111){
	    		if(k0 == 0){
    				printf("\t\t\t\t\t  δ������Чɾ������!\n");
            		free(a);
            		system("pause");
            		break;
				}
				else{
					printf("\t\t\t\t\t\t\t   �����޸ĺ�Ķ���\n");
					printproductinlist();
				
					printfile();
					system("pause");
					return;
				}
			}
	    	aim = searchproductinlist(a->commodity_name,a->commodity_id);
		}
	
		productin *p = L1;
	
		while(p->next->commodity_name != aim->commodity_name || p->next->commodity_id != aim->commodity_id){//δ�ҵ�Ŀ����
		
			p = p->next;
		
		}
	
		p->next = aim->next;
	
		aim->next = NULL;
	
		free(aim);
		k0++;

		if(L1->next == NULL){
			
			printf("\t\t\t\t\t    ��ʱ�����κν�����Ϣ���޷�����ɾ��\n");
			
			return;
		}
		else{
			printf("\t\t\t\t\t       ����Ʒ��Ϣɾ���ɹ���\n");
		}
	}
}
void searchproductin(){//������Ʒ��Ϣ
	//productin *q = L1->next;
	printf("\t\t\t\t\t-----------------------------------------------------\n");
	printf("\t\t\t\t\t                       ��Ʒ����                    \n");
	printf("\t\t\t\t\t-----------------------------------------------------\n");
	printf("\t\t\t\t\t|             ��1��  ��ˮƷ�Ƽ���ˮ���             |\n");
	printf("\t\t\t\t\t|             ��2��  ��ˮƷ�Ƽ�ÿ��ƿ��             |\n");
	printf("\t\t\t\t\t|             ��3��  ��ˮƷ�Ƽ���Ʒ����             |\n");
	printf("\t\t\t\t\t|             ��4��  ��ˮƷ�Ƽ���������             |\n");
	printf("\t\t\t\t\t|             ��5��  ��ˮƷ�Ƽ���Ʒ�ܼ�             |\n");
	printf("\t\t\t\t\t|             ��6��  ��Ʒ�ܼۼ���������             |\n");
	printf("\t\t\t\t\t|             ��0��  �˳�����ģ��                   |\n");
	printf("\t\t\t\t\t-----------------------------------------------------\n");
	
	//char ss[10];
	//gets(ss);
	int search_num;
	//scanf("%d",&search_num);
	while(true){
		printf("\t\t\t\t\t           ����������Ҫ���еĲ���         \n");
		search_num = checkNum();
		switch(search_num){
		case(0):{
			
			return;
		}
		case(1):{
			printf("\t\t\t\t\t           �������ˮƷ��\n");
			char str[100];
			scanf("%s",str);
			printf("\t\t\t\t\t           �������ˮ���\n");
			int numb;
			numb = checkNum();
			productin *p = searchproductinlist(str,numb);
			if(p == NULL){
				printf("\t\t\t\t\t          ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t         ����Ʒ��Ϣȫ������\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(2):{
			printf("\t\t\t\t\t           �������ˮƷ��\n");
			char str[100];
			scanf("%s",str);
			printf("\t\t\t\t\t           ������ÿ��ƿ��\n");
			int package;
			package = checkNum();
//			scanf("%d",&package);
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_packagenum != package)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t         ����Ʒȫ����Ϣ����\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(3):{
			printf("\t\t\t\t\t           �������ˮƷ��\n");
			char str[100];
			scanf("%s",str);
			printf("\t\t\t\t\t           ������ÿ��۸�\n");
			double price;
			scanf("%lf",&price);
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_price != price)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t         ����Ʒȫ����Ϣ����\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(4):{
			printf("\t\t\t\t\t           �������ˮƷ��\n");
			char str[100];
			scanf("%s",str);
			printf("\t\t\t\t\t           �������������\n");
			int in;
			in = checkNum();
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_number != in)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t         ����Ʒȫ����Ϣ����\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(5):{
			printf("\t\t\t\t\t           �������ˮƷ��\n");
			char str[100];
			scanf("%s",str);
			printf("\t\t\t\t\t           ��������Ʒ�ܼ�\n");
			double sum;
			scanf("%lf",&sum);
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->sum_price != sum)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t         ����Ʒȫ����Ϣ����\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(6):{
			printf("\t\t\t\t\t           ��������Ʒ�ܼ�\n");
			double sum;
			scanf("%lf",&sum);
			printf("\t\t\t\t\t           �������������\n");
			char da[50];
			scanf("%s",da);
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->date,da) != 0 || p->sum_price != sum)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t         ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t         ����Ʒȫ����Ϣ����\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		default:{
			printf("\t\t\t\t\t           ������Ĳ�ѯ���Ϊ�Ƿ��ַ�������������0~6�е�����\n");
			break;
		}
		
	}
	}
	
	//printf("\t\t\t\t\t   ��Ʒ������Ϣ������ϣ�");
}

void correctproductinlist(){
	int ko = 0;
	if(L1->next == NULL){
		printf("��ʱ�����κν�����Ϣ���޷������޸�\n");	
		return;
	}
	printf("\t\t\t\t\t ---------------------------------------------------------- \n");
	printf("\t\t\t\t\t                         ��Ʒ�޸�                          \n");
	printf("\t\t\t\t\t ---------------------------------------------------------\n");
    printf("\t\t\t\t\t|                  (1): �޸���Ʒ��������                  |\n");//ͬʱҪ�޸��ܼ�commodity_number
    printf("\t\t\t\t\t|                  (2): �޸���Ʒ��������                  |\n");//ͬʱҪ�޸��ܼ�commodity_price
    printf("\t\t\t\t\t|                  (3): �޸���Ʒÿ������                  |\n");//commodity_packagenum
    printf("\t\t\t\t\t|                  (4): �޸���Ʒÿƿ����                  |\n");//commodity_volume
    printf("\t\t\t\t\t|                  (5): �޸���Ʒ��������                  |\n");//commodity_volume
    printf("\t\t\t\t\t|                  (6): �޸���Ʒ��Ӧ��                    |\n");
    printf("\t\t\t\t\t|                  (0): �˳��޸�ģ��                      |\n");
    printf("\t\t\t\t\t| ���ҹ�Ӧ�̣�firstsupplier,secondsupplier,thirdsupplier  |\n");
    printf("\t\t\t\t\t|---------------------------------------------------------|\n");
    while(true){
    	printf("\t\t\t\t\t         ����������Ҫ���еĲ���");
    	
    	int select;
    	select = checkNum();
	    //scanf("%d",&select);
	    if(select == 0 && ko == 0){//��һ�ν��뺯����Ҫ�˳�
	    	printf("\t\t\t\t\t         ���ν���δ�޸���Ʒ������Ϣ!\n");
	    	system("pause");
	    	return;
		}
		if(select == 0 & ko != 0){
			printf("\t\t\t\t\t         �����޸ĺ�Ķ���\n");
	    	printproductinlist();
			printfile();
			system("pause");
			return;
		}
		while(select != 0 && select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6){
			printf("\t\t\t\t\t         ������Ĳ�������,������0~6�е�����\n");
			fflush(stdin);
	    	select = checkNum();
		}
		if(L1->next == NULL){
			printf("��ʱ�����κν�����Ϣ���޷������޸�\n");	
			return;
		}	//printf("��������Ҫ�޸���Ʒ�����Ƽ����,����end��ʾ�������!\n");
	    productin *a = (productin*)malloc(sizeof(productin));
	    printf("��������Ҫ�޸���Ʒ������\n");
	    scanf("%s", a->commodity_name);
	    	
	        
	    while(strcmp(a->commodity_name, "ũ��ɽȪ") != 0 && strcmp(a->commodity_name, "��Դ") != 0 && strcmp(a->commodity_name, "�ൺơ��") != 0&& strcmp(a->commodity_name, "�޹���") != 0&& strcmp(a->commodity_name, "����Һ") != 0 && strcmp(a->commodity_name, "���") != 0 && strcmp(a->commodity_name, "�ɿڿ���") != 0 && strcmp(a->commodity_name, "ϲ��") != 0 && strcmp(a->commodity_name, "��Ҥ�α�") != 0 && strcmp(a->commodity_name, "��ʦ��") != 0){
	    	printf("������ľ�ˮ������������������!\n");
	    	fflush(stdin);
	    	scanf("%s", a->commodity_name);
		}
		printf("��������Ҫ�޸���Ʒ�ı��!\n");
	    scanf("%d",&a->commodity_id);
	    productin *aim = searchproductinlist(a->commodity_name,a->commodity_id);
	    while(aim == NULL){
	    	printf("\t\t\t\t\t         ������ı����������������\n");
	    	fflush(stdin);
	    	scanf("%d",&a->commodity_id);
	    	aim = searchproductinlist(a->commodity_name,a->commodity_id);
		}
		
		

	    switch(select){
			case(1):{
				ko++;
				int number;
				printf("\t\t\t\t\t         �������޸ĺ�Ľ�������\n");
				while(scanf("%d", &number) != 1) {
        			printf("������Ϸ�����!\n");
        			fflush(stdin); // ��ջ���������������ѭ��
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
				printf("\t\t\t\t\t         �������޸ĺ�Ľ�������\n");
				while(scanf("%lf", &price) != 1) {
        			printf("������Ϸ�����!\n");
        			fflush(stdin); // ��ջ���������������ѭ��
    			}
				aim->commodity_price = price;
				supplier *po = aim->provider;
				aim->sum_price = price * aim->commodity_number + po->transport_cost;
//				printf("\t\t\t\t\t    �޸ĳɹ�\n");
//				printf("\t\t\t\t\t     �����޸ĺ�Ķ���\n");
//				printproductinlist();
				//printfile();
				break;
			}
			case(3):{
				ko++;
				printf("\t\t\t\t\t         �������޸ĺ��ÿ������\n");
				int packagenum;
				while(scanf("%d", &packagenum) != 1) {
        			printf("������Ϸ�����!\n");
        			fflush(stdin); // ��ջ���������������ѭ��
    			}
				aim->commodity_packagenum = packagenum;
//				printf("\t\t\t\t\t    �޸ĳɹ�\n");
//				printf("\t\t\t\t\t     �����޸ĺ�Ķ���\n");
//				printproductinlist();
				//printfile();
				break;
			}
			case(4):{
				ko++;
				printf("\t\t\t\t\t         �������޸ĺ��ÿƿ����\n");
				int volume;
				while(scanf("%d", &volume) != 1) {
        			printf("������Ϸ�����!\n");
        			fflush(stdin); // ��ջ���������������ѭ��
    			}
				aim->commodity_volume = volume;
//				printf("\t\t\t\t\t    �޸ĳɹ�\n");
//				printf("\t\t\t\t\t     �����޸ĺ�Ķ���\n");
//				printproductinlist();
				//printfile();				
				break;
			}
			case (5): {
			    ko++;
			    printf("\t\t\t\t\t         �������޸ĺ�Ľ�������\n");
			    char str[50];
			    int valid_input = 0;
			    while (!valid_input) {
			        scanf("%s", str);
			        valid_input = 1;
			        for (int i = 0; i < strlen(str); i++) {
			            if (!isdigit(str[i]) || strlen(str) != 8) {
			                valid_input = 0;
			                printf("������Ϸ������ڸ�ʽ������ 20220101��\n");
			                break;
			            }
			        }
			    }
			    strcpy(aim->date, str);
//			    printf("\t\t\t\t\t    �޸ĳɹ�\n");
//			    printf("\t\t\t\t\t     �����޸ĺ�Ķ���\n");
//			    printproductinlist();
			    //printfile();				
			    break;
			}

			case(6):{
				ko++;
				printf("\t\t\t\t\t         �������޸ĺ�Ĺ�Ӧ��\n");
				supplier *p = aim->provider;
				char su[50];
				scanf("%s",su);
				while(strcmp(su,"firstsupplier") != 0 && strcmp(su,"secondsupplier") != 0 && strcmp(su,"thirdsupplier") != 0){
					printf("�����˹����̣�������������!\n");
					scanf("%s",su);
				}
				strcpy(p->suppliername,su);
//				printf("\t\t\t\t\t    �޸ĳɹ�\n");
//				printf("\t\t\t\t\t     �����޸ĺ�Ķ���\n");
//				printproductinlist();
				//printfile();
				break;
			}
			default:{
				printf("������ı������������0~6�е�����\n");
				break;
			}
		}
		if(L1->next == NULL){
			
			printf("��ʱ�����κν�����Ϣ���޷������޸�\n");
			
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
		printf("\t\t\t\t\t-----------���ν�������Ʒ����----------------\n");
		return;
	}
	else{//k<90˵��������
		//fff:
		printf("\t\t\t\t\t ----------------------------------------------\n");
		printf("\t\t\t\t\t                   ��Ʒ����                     \n");
		printf("\t\t\t\t\t ---------------------------------------------- \n");
		printf("\t\t\t\t\t|      (1): �������������Ʒ                   |\n");
		printf("\t\t\t\t\t|      (2): �̼��ֶ�����������Ʒ���Ƽ����     |\n");
		printf("\t\t\t\t\t|      (0): �˳�����ģ��                       |\n");
		printf("\t\t\t\t\t|----------------------------------------------|\n");
		//char ss[10];//gets(ss);
		//scanf("%d",&selectnum);
		fff:
		while(true){
			printf("����������Ҫ���еĲ���                     \n");
			selectnum = checkNum();
			switch(selectnum){
			case(0):{
				if(kk == 0){
					printf("\t\t\t\t\t     ���β���δ����ʵ�����\n");
					return;
				}
				else{
					printf("\t\t\t\t\t\t\t   ������ĺ�Ķ���\n");
					printproductinlist();
				
					printfile();
					system("pause");
					return;
				}
			}
			
			case(1):{
			
				printf("\t\t\t\t\t     �������������Ʒ���Ƽ����\n");
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
					printf("\t\t\t\t\t     ��Ʒ�������ʧ�ܣ���������Ʒ��Ų��ڽ������У������²�����\n");
					goto fff;
				
				}
			//printf("777");
				int h = v;
				while(v--){
					srand((unsigned int)time(NULL));
					int w = 1 + rand() % 3;
					sum += w;//v����Ʒ�й�sumƿ��������
				}
				p->commodity_number -= h;//��v����Ʒ��������
			//p->commodity_packagenum -= w;//ָ��ĳ��Ʒĳ������ʧ��wƿ
				p->sum_price = p->sum_price - p->commodity_price * h;
			//p->sum_price = 0;
				kk++;
				printf("\t\t\t\t\t          %d��%s����%d��������ƿ������%dƿ\n",n,str,h,sum);
				printf("\t\t\t\t\t     ����Ʒ��������%d��,��������,�ܼ۵���Ϊ%.2lf\n",p->commodity_number,p->sum_price);
				break;
			}
			case(2):{
				printf("\t\t\t\t\t     ������������Ʒ����\n");
				char sp[100];
				scanf("%s",sp);
				while(strcmp(sp, "ũ��ɽȪ") != 0 && strcmp(sp, "��Դ") != 0 && strcmp(sp, "�ൺơ��") != 0&& strcmp(sp, "�޹���") != 0&& strcmp(sp, "����Һ") != 0 && strcmp(sp, "���") != 0 && strcmp(sp, "�ɿڿ���") != 0 && strcmp(sp, "ϲ��") != 0 && strcmp(sp, "��Ҥ�α�") != 0 && strcmp(sp, "��ʦ��") != 0){
	    			printf("������ľ�ˮ������������������!\n");
	    			fflush(stdin);
	    			scanf("%s", sp);
				}
				printf("\t\t\t\t\t     ������������Ʒ���\n");
				int damage_num;
				damage_num = checkNum();
				productin *p = NULL;
				p = searchproductinlist(sp,damage_num);
				while(p == NULL){
	    			printf("\t\t\t\t\t         ������ı�����󣬸����Ƽ���Ŷ�Ӧ����Ʒ���ڶ���������������\n");
	    			fflush(stdin);
	    			scanf("%d",&damage_num);
	    			p = searchproductinlist(sp,damage_num);
				}

				printf("\t\t\t\t\t     ������������Ʒ����\n");
				int damagebox,damagebottle,damagesum = 0;
				damagebox = checkNum();
				int yf = damagebox,i = 1;
				p->commodity_number -= yf;
				while(damagebox--){
					printf("\t\t\t\t\t     �������%d����������Ʒƿ��\n",i);
					i++;
					scanf("%d",&damagebottle);
					damagesum += damagebottle;
				}
				printf("\t\t\t\t\t     ԭ�ܼ�%.2lf\n",p->sum_price);
				p->sum_price -= p->commodity_price * yf;
			
				printf("\t\t\t\t\t     %s%d�Ź�%d��������ƿ������%dƿ\n",sp,damage_num,yf,damagesum);
				printf("\t\t\t\t\t     ����Ʒ��������%d��,��������,�ܼ۵���Ϊ%.2lf\n",p->commodity_number,p->sum_price);
				kk++;
				break;
			}
			default:{
				printf("������0~2�ĺϷ��ַ�\n");
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
		printf("\t\t\t\t\t                ����ģ��                 \n");
		printf("\t\t\t\t\t -------------------------------------------\n");
		printf("\t\t\t\t\t|       ��1��  �޸Ķ�����Ϣ                |\n");
		printf("\t\t\t\t\t|       ��2��  ɾ�����ֶ�����Ϣ            |\n");
		printf("\t\t\t\t\t|       ��3��  ��ӡ������Ϣ                |\n");
		printf("\t\t\t\t\t|       ��4��  ���Ӷ�����Ϣ                |\n");
		printf("\t\t\t\t\t|       ��5��  ��������Ϣд��in.txt�ļ���  |\n");
		printf("\t\t\t\t\t|       ��6��  ��ѯĳһ��������Ϣ          |\n");
		printf("\t\t\t\t\t|       ��7��  ��ѯ��Ʒ������            |\n");
		printf("\t\t\t\t\t|       ��0��  ��������                    |\n");
		printf("\t\t\t\t\t|     ����������Ҫ���еķ���(0-7)        |\n");
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
				//printf("��ӡ�ļ�");
				
				//system("pause");
				
				//printf("\t\t\t\t\t     �����޸ĺ�Ķ���\n");
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
				printf("\t\t\t\t\t     ������Ϣ��д���ļ���\n");
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
				printf("���������Ϣ����,������0~7�е�����\n");
				system("pause");
				break;
		}
	}		
}	


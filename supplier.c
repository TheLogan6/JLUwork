#include"supplier.h"
#include"customer.h"

extern productlistin L1;//������
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
		supplier* p = (supplier*)malloc(sizeof(supplier));//ÿ�η���һ���µĿռ�
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
        printf("�ļ�������\n");
        return;
    }
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    if(size == 0){
//    	printf("�ļ�Ϊ�գ��޷�����������Ϣ\n");
//    	system("pause");
    	return;
	}

    fseek(f, 0, SEEK_SET);
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
	
}

void printproductinlist(){//��ӡ������Ϣ
	if(L1->next == NULL){
		printf("\t\t\t\t\t\t\t\t      δ¼���κν�����Ϣ���޷��������¼����Ʒ��Ϣ�����\n");
		return;
	}
	printf("\t\t\t\t\t\t\t\t      ---------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t                               ��Ʒ��ӡ                          \n");
	printf("\t\t\t\t\t\t\t\t      --------------------------------------------------------- \n");
	printf("\t\t\t\t   ��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������      ������\n");
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
    while(true){
    	printf("\t\t\t\t\t\t\t\t   ����������Ҫ���еĲ���");
    	selectnum = inputNum();
    	switch(selectnum){
	        case(0) : {
	        	if(ko == 0){
	        		printf("\t\t\t\t\t\t\t\t   �������δִ����Ч����,�����˳�\n");
	        		return;
				}
				else{
					printf("\t\t\t\t\t\t\t\t   ������Ӻ�Ķ���\n");
					printproductinlist();			
					printfile();
					system("pause");
					return;					
				}
	        }
			case(1) : {
					ko++;
				//printf("\t\t\t\t\t��������Ҫ��ӵ���ƷƷ�ơ���š���װ��С,��Ʒ���ۣ���Ʒ�ܼۣ�������������Ʒ�������������ڣ���Ӧ�� \n");
				printf("\t\t\t\t\t   ��ƷƷ��ֻ����\"ũ��ɽȪ\",\"��Դ\",\"�ൺơ��\",\"���\",\"�޹���\",\"����Һ\",\"��ʦ��\",\"�ɿڿ���\",\"ϲ��\",\"��Ҥ�α�\"\n");
				if(L1->next != NULL){
					productin *p = L1;
					while(p->next != NULL){
						p = p->next;
					}//pָ����������λ��
		
					productin *u = (productin*)malloc(sizeof(productin)); //���� һ���µĽṹ��ָ��,���ռ�
					char name[100];//��ˮƷ��
				    int id;//��Ʒ���,�������ֲ�ͬ��Ʒ��ͬһ��Ʒ�Ĳ�ͬ�����ζ��
				    int  packagenum;//ÿ��ƿ��  
				    double price;//��Ʒ�۸�
				    double sum;//��Ʒ�ܼ�
				    int number;//��Ʒ����������������
				    int volume;//��Ʒ����
				    char str[50];//��������
				    printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���ƷƷ��   ");
				    fgets(name, 100, stdin);
	    			name[strcspn(name, "\n")] = '\0';
					while(strcmp(name, "ũ��ɽȪ") != 0 && strcmp(name, "��Դ") != 0 && strcmp(name, "�ൺơ��") != 0 && strcmp(name, "���") != 0 && strcmp(name, "�޹���") != 0&& strcmp(name, "����Һ") != 0 && strcmp(name, "��ʦ��") != 0 && strcmp(name, "ϲ��") != 0 && strcmp(name, "�ɿڿ���") != 0 && strcmp(name, "��Ҥ�α�") != 0){
		    			printf("\t\t\t\t\t\t\t\t   ������ľ�ˮ������������������!\n");
		    			printf("\t\t\t\t\t\t\t\t   ");
		    			fflush(stdin);
		    			fgets(name, 100, stdin);
	    				name[strcspn(name, "\n")] = '\0';
					}
					printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ���   ");
					id = inputNum();
					while(id == -1) {
	        			printf("\t\t\t\t\t\t\t\t   ������Ϸ����!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // ��ջ���������������ѭ��
	        			id = inputNum();
	    			}
	    			printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ��װ��С   ");
	    			packagenum = inputNum();
	    			while(packagenum == -1) {
	        			printf("\t\t\t\t\t\t\t\t   ������Ϸ���װ��С!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // ��ջ���������������ѭ��
	        			packagenum = inputNum();
	    			}
					
					printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ����(�����Ǹ������ͣ�����ྫȷ����)   ");
					price = checkDouble();
					while(price < 0) {
	        			printf("\t\t\t\t\t\t\t\t   ������Ϸ�����!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // ��ջ���������������ѭ��
	        			price = inputNum();
	    			}
					
					printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ��������   ");
					number = inputNum();
					while(number == -1) {
	        			printf("\t\t\t\t\t\t\t\t   ������Ϸ���������!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // ��ջ���������������ѭ��
	        			number = inputNum();
	    			}
					printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ����   ");
					volume = inputNum();
					while(volume == -1) {
	        			printf("\t\t\t\t\t\t\t\t   ������Ϸ���Ʒ����!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // ��ջ���������������ѭ��
	        			volume = inputNum();
	    			}
				    printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ��������   ");
				    fgets(str, 50, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
					str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
					while(!isdate(str)){
						printf("\t\t\t\t\t\t\t\t   ������Ϸ���������!\n");
						printf("\t\t\t\t\t\t\t\t   \n");
						fgets(str, 50, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
						str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
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
					char name[100];//��ˮƷ��
				    int id;//��Ʒ���,�������ֲ�ͬ��Ʒ��ͬһ��Ʒ�Ĳ�ͬ�����ζ��
				    int  packagenum;//ÿ��ƿ��  
				    double price;//��Ʒ�۸�
				    double sum;//��Ʒ�ܼ�
				    int number;//��Ʒ����������������
				    int volume;//��Ʒ����
				    char str[50];//��������
				    printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���ƷƷ��   ");
				    fgets(name, 100, stdin);
	    			name[strcspn(name, "\n")] = '\0';
					while(strcmp(name, "ũ��ɽȪ") != 0 && strcmp(name, "��Դ") != 0 && strcmp(name, "�ൺơ��") != 0 && strcmp(name, "���") != 0 && strcmp(name, "�޹���") != 0&& strcmp(name, "����Һ") != 0 && strcmp(name, "��ʦ��") != 0 && strcmp(name, "ϲ��") != 0 && strcmp(name, "�ɿڿ���") != 0 && strcmp(name, "��Ҥ�α�") != 0){
		    			printf("\t\t\t\t\t\t\t\t   ������ľ�ˮ������������������!\n");
		    			printf("\t\t\t\t\t\t\t\t   ");
		    			fflush(stdin);
		    			fgets(name, 100, stdin);
	    				name[strcspn(name, "\n")] = '\0';
					}
					printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ���   ");
					id = inputNum();
					while(id == -1) {
	        			printf("\t\t\t\t\t\t\t\t   ������Ϸ����!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // ��ջ���������������ѭ��
	        			id = inputNum();
	    			}
	    			printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ��װ��С   ");
	    			packagenum = inputNum();
	    			while(packagenum == -1) {
	        			printf("\t\t\t\t\t\t\t\t   ������Ϸ���װ��С!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // ��ջ���������������ѭ��
	        			packagenum = inputNum();
	    			}
					
					printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ����(�����Ǹ������ͣ�����ྫȷ����)   ");
					price = checkDouble();
					while(price < 0) {
	        			printf("\t\t\t\t\t\t\t\t   ������Ϸ�����!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // ��ջ���������������ѭ��
	        			price = inputNum();
	    			}
					
					printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ��������   ");
					number = inputNum();
					while(number == -1) {
	        			printf("\t\t\t\t\t\t\t\t   ������Ϸ���������!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // ��ջ���������������ѭ��
	        			number = inputNum();
	    			}
					printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ����   ");
					volume = inputNum();
					while(volume == -1) {
	        			printf("\t\t\t\t\t\t\t\t   ������Ϸ���Ʒ����!\n");
	        			printf("\t\t\t\t\t\t\t\t   ");
	        			fflush(stdin); // ��ջ���������������ѭ��
	        			volume = inputNum();
	    			}
				    printf("\t\t\t\t\t\t\t\t   ��������Ҫ��ӵ���Ʒ��������   ");
				    fgets(str, 50, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
					str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
					while(!isdate(str)){
						printf("\t\t\t\t\t\t\t\t   ������Ϸ���������!\n");
						printf("\t\t\t\t\t\t\t\t   ");
						fgets(str, 50, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
						str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
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
				printf("\t\t\t\t\t\t\t\t   �������������������������0��1!\n");
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
	printf("\t\t\t\t\t\t\t\t    -----------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t                      ��Ʒɾ��                    \n");
	printf("\t\t\t\t\t\t\t\t    -----------------------------------------------\n");
	if(L1->next == NULL){
		printf("\t\t\t\t\t\t\t\t    ��ʱ�����κν�����Ϣ���޷�����ɾ��,��¼����Ϣ�����ɾ������\n");
		system("pause");
		return;
	}

    
    while(true){
    	printf("\t\t\t\t\t\t\t\t   ��������Ҫɾ������Ʒ����,����enddelete��ʾ�������!\n");
    	printf("\t\t\t\t\t\t\t\t   ");
    	productin *a = (productin*)malloc(sizeof(productin));
    
		fgets(a->commodity_name, 50, stdin);
    	a->commodity_name[strcspn(a->commodity_name, "\n")] = '\0';
    	if (strcmp(a->commodity_name, "enddelete") == 0){
    		if(k0 == 0){
    			printf("\t\t\t\t\t\t\t\t   δ������Чɾ������!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t\t   ����ɾ����Ķ���\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
        }
    	while(strcmp(a->commodity_name, "ũ��ɽȪ") != 0 && strcmp(a->commodity_name, "��Դ") != 0 && strcmp(a->commodity_name, "�ൺơ��") != 0&& strcmp(a->commodity_name, "�޹���") != 0&& strcmp(a->commodity_name, "����Һ") != 0 && strcmp(a->commodity_name, "���") != 0 && strcmp(a->commodity_name, "�ɿڿ���") != 0 && strcmp(a->commodity_name, "ϲ��") != 0 && strcmp(a->commodity_name, "��Ҥ�α�") != 0 && strcmp(a->commodity_name, "��ʦ��") != 0){
	    	printf("\t\t\t\t\t\t\t\t   ���������Ʒ������������������\n");
	    	printf("\t\t\t\t\t\t\t\t   ");
	    	fflush(stdin);
	    	fgets(a->commodity_name, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
			a->commodity_name[strcspn(a->commodity_name, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			if (strcmp(a->commodity_name, "enddelete") == 0){
    		if(k0 == 0){
    			printf("\t\t\t\t\t\t\t\t   δ������Чɾ������!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t\t   ����ɾ����Ķ���\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
        }
		}
    	
        
//        while(strcmp(a->commodity_name, "ũ��ɽȪ") != 0 && strcmp(a->commodity_name, "��Դ") != 0 && strcmp(a->commodity_name, "�ൺơ��") != 0 && strcmp(a->commodity_name, "���") != 0 && strcmp(a->commodity_name, "�޹���") != 0&& strcmp(a->commodity_name, "����Һ") != 0 && strcmp(a->commodity_name, "��ʦ��") != 0 && strcmp(a->commodity_name, "ϲ��") != 0 && strcmp(a->commodity_name, "�ɿڿ���") != 0 && strcmp(a->commodity_name, "��Ҥ�α�") != 0){
//    		printf("\t\t\t\t\t   ������ľ�ˮ������������������!\n");
//    		printf("\t\t\t\t\t   ");
//    		fflush(stdin);
//    		fgets(a->commodity_name, 50, stdin);
//    		a->commodity_name[strcspn(a->commodity_name, "\n")] = '\0';
//    		if (strcmp(a->commodity_name, "enddelete") == 0){
//    		if(k0 == 0){
//    			printf("\t\t\t\t\t  δ������Чɾ������!\n");
//            	free(a);
//            	system("pause");
//            	break;
//			}
//			else{
//				printf("\t\t\t\t\t   ����ɾ����Ķ���\n");
//				printproductinlist();
//				
//				printfile();
//				system("pause");
//				return;
//			}
//        }
//		}
		printf("\t\t\t\t\t\t\t\t   ��������Ҫɾ����Ʒ�ı��,����11111����!\n");
		printf("\t\t\t\t\t\t\t\t   ");
	    //fgets(a->commodity_id, 50, stdin);
	    a->commodity_id = inputNum();
	    while(a->commodity_id == -1){
	    	printf("\t\t\t\t\t\t\t\t   ������Ϸ����!\n");
        	printf("\t\t\t\t\t\t\t\t   ");
        	fflush(stdin); // ��ջ���������������ѭ��
        	a->commodity_id = inputNum();
		}	    
	    if(a->commodity_id == 11111){
	    	if(k0 == 0){
    			printf("\t\t\t\t\t\t\t\t   δ������Чɾ������!\n");
            	free(a);
            	system("pause");
            	break;
			}
			else{
				printf("\t\t\t\t\t\t\t\t   ����ɾ����Ķ���\n");
				printproductinlist();
				
				printfile();
				system("pause");
				return;
			}
		}
	    productin *aim = searchproductinlist(a->commodity_name,a->commodity_id);
	    while(aim == NULL){
	    	printf("\t\t\t\t\t\t\t\t   ������ı����������������\n");
	    	printf("\t\t\t\t\t\t\t\t   ");
	    	fflush(stdin);
	    	a->commodity_id = inputNum();
	    	while(a->commodity_id == -1){
	    		printf("\t\t\t\t\t\t\t\t   ������Ϸ����!\n");
        		printf("\t\t\t\t\t\t\t\t   ");
        		fflush(stdin); // ��ջ���������������ѭ��
        		a->commodity_id = inputNum();
			}
	    	if(a->commodity_id == 11111){
	    		if(k0 == 0){
    				printf("\t\t\t\t\t\t\t\t   δ������Чɾ������!\n");
            		free(a);
            		system("pause");
            		break;
				}
				else{
					printf("\t\t\t\t\t\t\t\t   ����ɾ����Ķ���\n");
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
			
			printf("\t\t\t\t\t\t\t\t   ��ʱ�����κν�����Ϣ���޷�����ɾ��\n");
			
			return;
		}
		else{
			printf("\t\t\t\t\t\t\t\t   ����Ʒ��Ϣɾ���ɹ���\n");
		}
	}
}
void searchproductin(){//������Ʒ��Ϣ
	//productin *q = L1->next;
	if(L1->next == NULL){
		printf("\t\t\t\t\t��ʱ�����κν�����Ϣ�޷���ѯ\n");
		system("pause");
		return;
	}
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
	
	while(true){
		printf("\t\t\t\t\t           ����������Ҫ���еĲ���  ");
		search_num = inputNum();
		switch(search_num){
		case(0):{
			
			return;
		}
		case(1):{
			printf("\t\t\t\t\t           �������ˮƷ��   ");
			char str[100];
			fgets(str, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
			str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			while(strcmp(str, "ũ��ɽȪ") != 0 && strcmp(str, "��Դ") != 0 && strcmp(str, "�ൺơ��") != 0 && strcmp(str, "���") != 0 && strcmp(str, "�޹���") != 0&& strcmp(str, "����Һ") != 0 && strcmp(str, "��ʦ��") != 0 && strcmp(str, "ϲ��") != 0 && strcmp(str, "�ɿڿ���") != 0 && strcmp(str, "��Ҥ�α�") != 0){
				printf("\t\t\t\t\t           ����������10�־�ˮƷ��֮һ\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin); // ��ջ���������������ѭ��
				fgets(str, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
				str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			}

			printf("\t\t\t\t\t           �������ˮ���   ");
			int numb;
			numb = inputNum();
			while(numb == -1) {
        			printf("\t\t\t\t\t           ������Ϸ���ˮ���!\n");
        			printf("\t\t\t\t\t           ");
        			fflush(stdin); // ��ջ���������������ѭ��
        			numb = inputNum();
    		}
			productin *p = searchproductinlist(str,numb);
			if(p == NULL){
				printf("\t\t\t\t\t           ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t          ����Ʒ��Ϣȫ������\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(2):{
			printf("\t\t\t\t\t           �������ˮƷ��   ");
			char str[100];
			fgets(str, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
			str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			while(strcmp(str, "ũ��ɽȪ") != 0 && strcmp(str, "��Դ") != 0 && strcmp(str, "�ൺơ��") != 0 && strcmp(str, "���") != 0 && strcmp(str, "�޹���") != 0&& strcmp(str, "����Һ") != 0 && strcmp(str, "��ʦ��") != 0 && strcmp(str, "ϲ��") != 0 && strcmp(str, "�ɿڿ���") != 0 && strcmp(str, "��Ҥ�α�") != 0){
				printf("\t\t\t\t\t           ����������10�־�ˮƷ��֮һ\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin); // ��ջ���������������ѭ��
				fgets(str, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
				str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			}
			printf("\t\t\t\t\t           ������ÿ��ƿ��   ");
			int package;
			package = inputNum();
			while(package == -1) {
        		printf("\t\t\t\t\t           ������Ϸ�ÿ��ƿ��!\n");
        		printf("\t\t\t\t\t           ");
        		fflush(stdin); // ��ջ���������������ѭ��
        		package = inputNum();
    		}

			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_packagenum != package)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t          ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t          ����Ʒȫ����Ϣ����\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(3):{
			printf("\t\t\t\t\t           �������ˮƷ��   ");
			char str[100];
			fgets(str, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
			str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			while(strcmp(str, "ũ��ɽȪ") != 0 && strcmp(str, "��Դ") != 0 && strcmp(str, "�ൺơ��") != 0 && strcmp(str, "���") != 0 && strcmp(str, "�޹���") != 0&& strcmp(str, "����Һ") != 0 && strcmp(str, "��ʦ��") != 0 && strcmp(str, "ϲ��") != 0 && strcmp(str, "�ɿڿ���") != 0 && strcmp(str, "��Ҥ�α�") != 0){
				printf("\t\t\t\t\t           ����������10�־�ˮƷ��֮һ\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin); // ��ջ���������������ѭ��
				fgets(str, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
				str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			}
			printf("\t\t\t\t\t           ������ÿ��۸�   ");
			double price;

			price = checkDouble();
			while(price < 0) {
        		printf("\t\t\t\t\t           ������Ϸ�ÿ��۸�!\n");
        		printf("\t\t\t\t\t           ");
        		fflush(stdin); // ��ջ���������������ѭ��
        		price = checkDouble();
    		}
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_price != price)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t          ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t          ����Ʒȫ����Ϣ����\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(4):{
			printf("\t\t\t\t\t           �������ˮƷ��   ");
			char str[100];
			fgets(str, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
			str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			while(strcmp(str, "ũ��ɽȪ") != 0 && strcmp(str, "��Դ") != 0 && strcmp(str, "�ൺơ��") != 0 && strcmp(str, "���") != 0 && strcmp(str, "�޹���") != 0&& strcmp(str, "����Һ") != 0 && strcmp(str, "��ʦ��") != 0 && strcmp(str, "ϲ��") != 0 && strcmp(str, "�ɿڿ���") != 0 && strcmp(str, "��Ҥ�α�") != 0){
				printf("\t\t\t\t\t           ����������10�־�ˮƷ��֮һ\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin); // ��ջ���������������ѭ��
				fgets(str, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
				str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			}
			printf("\t\t\t\t\t           �������������   ");
			int in;
			in = inputNum();
			while(in == -1) {
        		printf("\t\t\t\t\t           ������Ϸ���������!\n");
        		printf("\t\t\t\t\t           ");
        		fflush(stdin); // ��ջ���������������ѭ��
        		in = inputNum();
    		}
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->commodity_number != in)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t          ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t          ����Ʒȫ����Ϣ����\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(5):{
			printf("\t\t\t\t\t           �������ˮƷ��   ");
			char str[100];
			fgets(str, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
			str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			while(strcmp(str, "ũ��ɽȪ") != 0 && strcmp(str, "��Դ") != 0 && strcmp(str, "�ൺơ��") != 0 && strcmp(str, "���") != 0 && strcmp(str, "�޹���") != 0&& strcmp(str, "����Һ") != 0 && strcmp(str, "��ʦ��") != 0 && strcmp(str, "ϲ��") != 0 && strcmp(str, "�ɿڿ���") != 0 && strcmp(str, "��Ҥ�α�") != 0){
				printf("\t\t\t\t\t           ����������10�־�ˮƷ��֮һ\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin); // ��ջ���������������ѭ��
				fgets(str, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
				str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			}
			printf("\t\t\t\t\t           ��������Ʒ�ܼ�   ");
			double sum;
			sum = checkDouble();
			while(sum < 0) {
        		printf("\t\t\t\t\t           ������Ϸ���Ʒ�ܼ�!\n");
        		printf("\t\t\t\t\t           ");
        		fflush(stdin); // ��ջ���������������ѭ��
        		sum = checkDouble();
    		}
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->commodity_name,str) != 0 || p->sum_price != sum)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t          ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t          ����Ʒȫ����Ϣ����\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		case(6):{
			printf("\t\t\t\t\t           ��������Ʒ�ܼ�   ");
			double sum;
			sum = checkDouble();
			while(sum < 0) {
        		printf("\t\t\t\t\t           ������Ϸ���Ʒ�ܼ�!\n");
        		printf("\t\t\t\t\t           ");
        		fflush(stdin); // ��ջ���������������ѭ��
        		sum = checkDouble();
    		}
			printf("\t\t\t\t\t           �������������   ");
			char da[50];
			fgets(da, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
			da[strcspn(da, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			while(!isdate(da)){
				printf("\t\t\t\t\t           ������Ϸ���������\n");
				printf("\t\t\t\t\t           ");
				fflush(stdin);
				fgets(da, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
				da[strcspn(da, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
			}
			productin *p = L1->next;
			while(p != NULL && (strcmp(p->date,da) != 0 || p->sum_price != sum)){
				p = p->next;
			}
			if(p == NULL){
				printf("\t\t\t\t\t          ����Ʒ���ڽ���������\n");
				break;
			}
			printf("\t\t\t\t\t          ����Ʒȫ����Ϣ����\n");
			printf("��ˮƷ��         ��Ʒ���     ÿ��ƿ��    ��Ʒ������     ÿ��۸�     ��������      ��Ʒ�ܼ�        ��������    ������\n");
			supplier* g = p->provider;
			printf("%-20s %-10d %-10d %-13d %.2lf  %11d \t    %.2lf  %15s    %-15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date,g->suppliername);
			//printf("%-20s %-10d %-10d %-13d %.2lf  %11d %13d  %15s\n",p->commodity_name,p->commodity_id,p->commodity_packagenum,p->commodity_volume,p->commodity_price,p->commodity_number,p->sum_price,p->date);
			break;
		}
		default:{
			printf("\t\t\t\t\t           ������Ĳ�ѯ���Ϊ�Ƿ��ַ�������������0~6�е�����\n");
			//printf("\t\t\t\t\t           ");
			break;
		}
		
	}
	}
	//printf("\t\t\t\t\t   ��Ʒ������Ϣ������ϣ�");
}

void correctproductinlist(){
	int ko = 0;
	if(L1->next == NULL){
		printf("\t\t\t\t\t\t\t\t   ��ʱ�����κν�����Ϣ���޷������޸�\n");	
		system("pause");
		return;
	}
	printf("\t\t\t\t\t\t\t\t   ---------------------------------------------------------- \n");
	printf("\t\t\t\t\t\t\t\t                            ��Ʒ�޸�                          \n");
	printf("\t\t\t\t\t\t\t\t   ---------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t   |                  (1): �޸���Ʒ��������                  |\n");//ͬʱҪ�޸��ܼ�commodity_number
    printf("\t\t\t\t\t\t\t\t   |                  (2): �޸���Ʒ��������                  |\n");//ͬʱҪ�޸��ܼ�commodity_price
    printf("\t\t\t\t\t\t\t\t   |                  (3): �޸���Ʒÿ������                  |\n");//commodity_packagenum
    printf("\t\t\t\t\t\t\t\t   |                  (4): �޸���Ʒÿƿ����                  |\n");//commodity_volume
    printf("\t\t\t\t\t\t\t\t   |                  (5): �޸���Ʒ��������                  |\n");//commodity_volume
    printf("\t\t\t\t\t\t\t\t   |                  (6): �޸���Ʒ��Ӧ��                    |\n");
    printf("\t\t\t\t\t\t\t\t   |                  (0): �˳��޸�ģ��                      |\n");
    printf("\t\t\t\t\t\t\t\t   | ���ҹ�Ӧ�̣�firstsupplier,secondsupplier,thirdsupplier  |\n");
    printf("\t\t\t\t\t\t\t\t   |---------------------------------------------------------|\n");
    if(L1->next == NULL){
    	printf("\t\t\t\t\t\t\t\t   ����Ϊ�գ������޸�\n");
    	system("pause");
	}
    while(true){
    	printf("\t\t\t\t\t\t\t\t   ����������Ҫ���еĲ���");
    	
    	int select;
    	select = inputNum();

	    if(select == 0 && ko == 0){//��һ�ν��뺯����Ҫ�˳�
	    	printf("\t\t\t\t\t\t\t\t   ���ν���δ�޸���Ʒ������Ϣ!\n");
	    	system("pause");
	    	return;
		}
		if(select == 0 & ko != 0){
			printf("\t\t\t\t\t\t\t\t   �����޸ĺ�Ķ���\n");
	    	printproductinlist();
			printfile();
			system("pause");
			return;
		}
		while(select != 0 && select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6){
			printf("\t\t\t\t\t\t\t\t   ������Ĳ�������,������0~6�е�����\n");
			printf("\t\t\t\t\t\t\t\t   ");
			fflush(stdin);
	    	select = inputNum();
		}
		if(L1->next == NULL){
			printf("\t\t\t\t\t\t\t\t   ��ʱ�����κν�����Ϣ���޷������޸�\n");	
			return;
		}	//printf("��������Ҫ�޸���Ʒ�����Ƽ����,����end��ʾ�������!\n");
	    productin *a = (productin*)malloc(sizeof(productin));
	    printf("\t\t\t\t\t\t\t\t   ��������Ҫ�޸���Ʒ������   ");
	    fgets(a->commodity_name, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
		a->commodity_name[strcspn(a->commodity_name, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�

	    	
	        
	    while(strcmp(a->commodity_name, "ũ��ɽȪ") != 0 && strcmp(a->commodity_name, "��Դ") != 0 && strcmp(a->commodity_name, "�ൺơ��") != 0&& strcmp(a->commodity_name, "�޹���") != 0&& strcmp(a->commodity_name, "����Һ") != 0 && strcmp(a->commodity_name, "���") != 0 && strcmp(a->commodity_name, "�ɿڿ���") != 0 && strcmp(a->commodity_name, "ϲ��") != 0 && strcmp(a->commodity_name, "��Ҥ�α�") != 0 && strcmp(a->commodity_name, "��ʦ��") != 0){
	    	printf("\t\t\t\t\t\t\t\t   ������ľ�ˮ������������������\n");
	    	printf("\t\t\t\t\t\t\t\t   ");
	    	fflush(stdin);
	    	fgets(a->commodity_name, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
			a->commodity_name[strcspn(a->commodity_name, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
		}
		printf("\t\t\t\t\t\t\t\t   ��������Ҫ�޸���Ʒ�ı��   ");
	    a->commodity_id = inputNum();
	    while(a->commodity_id == -1){
	    	printf("\t\t\t\t\t\t\t\t   ������Ϸ����!\n");
        	printf("\t\t\t\t\t\t\t\t   ");
        	fflush(stdin); // ��ջ���������������ѭ��
        	a->commodity_id = inputNum();
		}	
		
	    productin *aim = searchproductinlist(a->commodity_name,a->commodity_id);
	    while(aim == NULL){
	    	printf("\t\t\t\t\t\t\t\t   �����в�������Ʒ��Ϣ��������������\n");
	    	printf("\t\t\t\t\t\t\t\t   ");
	    	fflush(stdin);
	    	a->commodity_id = inputNum();
	    	aim = searchproductinlist(a->commodity_name,a->commodity_id);
		}
		
		

	    switch(select){
			case(1):{
				ko++;
				int number;
				printf("\t\t\t\t\t\t\t\t   �������޸ĺ�Ľ�������   ");
				//printf("\t\t\t\t\t         ");
				number = inputNum();
				while(number == -1) {
        			printf("\t\t\t\t\t\t\t\t   ������Ϸ�����!\n");
        			printf("\t\t\t\t\t\t\t\t   ");
        			fflush(stdin); // ��ջ���������������ѭ��
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
				printf("\t\t\t\t\t\t\t\t   �������޸ĺ�Ľ�������   ");
				price = checkDouble();
				while(price < 0) {
        			printf("\t\t\t\t\t\t\t\t   ������Ϸ�����!\n");
        			printf("\t\t\t\t\t\t\t\t   ");
        			fflush(stdin); // ��ջ���������������ѭ��
        			price = checkDouble();
    			}
				aim->commodity_price = price;
				supplier *po = aim->provider;
				aim->sum_price = price * aim->commodity_number + po->transport_cost;

				break;
			}
			case(3):{
				ko++;
				printf("\t\t\t\t\t\t\t\t   �������޸ĺ��ÿ������   ");
				//printf("\t\t\t\t\t         ");
				int packagenum;
				packagenum = inputNum();
				while(packagenum == -1) {
        			printf("\t\t\t\t\t\t\t\t   ������Ϸ�����!\n");
        			printf("\t\t\t\t\t\t\t\t   ");
        			fflush(stdin); // ��ջ���������������ѭ��
        			packagenum = inputNum();
    			}
				aim->commodity_packagenum = packagenum;

				break;
			}
			case(4):{
				ko++;
				printf("\t\t\t\t\t\t\t\t   �������޸ĺ��ÿƿ����   ");
				int volume;
				volume = inputNum();
				while(volume == -1) {
        			printf("\t\t\t\t\t\t\t\t   ������Ϸ�����!\n");
        			printf("\t\t\t\t\t\t\t\t   ");
        			fflush(stdin); // ��ջ���������������ѭ��
        			volume = inputNum();
    			}
				aim->commodity_volume = volume;
				
				break;
			}
			case (5): {
			    ko++;
			    printf("\t\t\t\t\t\t\t\t   �������޸ĺ�Ľ�������   ");
			    //printf("\t\t\t\t\t         ");
			    char str[50];
			    fgets(str, 50, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
				str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
				while(!isdate(str)){
					printf("\t\t\t\t\t\t\t\t   ������Ϸ���������!\n");
					printf("\t\t\t\t\t\t\t\t   ");
					fgets(str, 50, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
					str[strcspn(str, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
				}
			    strcpy(aim->date, str);		
			    break;
			}

			case(6):{
				ko++;
				printf("\t\t\t\t\t\t\t\t   �������޸ĺ�Ĺ�Ӧ��   ");
				//printf("\t\t\t\t\t         ");
				supplier *p = aim->provider;
				char su[50];
				fgets(su, 50, stdin);
    			su[strcspn(su, "\n")] = '\0';
				while(strcmp(su,"firstsupplier") != 0 && strcmp(su,"secondsupplier") != 0 && strcmp(su,"thirdsupplier") != 0){
					printf("\t\t\t\t\t\t\t\t   �����˹����̣�������������!\n");
					printf("\t\t\t\t\t\t\t\t   ");
					fgets(su, 50, stdin);
    				su[strcspn(su, "\n")] = '\0';
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
	if(L1->next == NULL){
		printf("\t\t\t\t\t\t\t\t\t     ��ʱ�����κν�����Ϣ���޷���ѯ����");
		system("pause");
		return;
	}
	int kk = 0;
	//("%d",&selectnum);
	int selectnum;
	int k = rand() % 100;
	if(k >= 90){
		printf("\t\t\t\t\t\t\t\t   -----------���ν�������Ʒ����----------------\n");
		return;
	}
	else{//k<90˵��������
		//fff:
		printf("\t\t\t\t\t\t\t\t\t     ----------------------------------------------\n");
		printf("\t\t\t\t\t\t\t\t\t                        ��Ʒ����                     \n");
		printf("\t\t\t\t\t\t\t\t\t     ------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t\t\t     |      (1): �������������Ʒ                   |\n");
		printf("\t\t\t\t\t\t\t\t\t     |      (2): �̼��ֶ�����������Ʒ���Ƽ����     |\n");
		printf("\t\t\t\t\t\t\t\t\t     |      (0): �˳�����ģ��                       |\n");
		printf("\t\t\t\t\t\t\t\t\t     |----------------------------------------------|\n");
		//char ss[10];//gets(ss);
		//("%d",&selectnum);
		fff:
		while(true){
			printf("\t\t\t\t\t\t\t\t\t     ����������Ҫ���еĲ���   ");
			selectnum = inputNum();
			switch(selectnum){
			case(0):{
				if(kk == 0){
					printf("\t\t\t\t\t\t\t\t\t     ���β���δ����ʵ�����\n");
					return;
				}
				else{
					printf("\t\t\t\t\t\t\t\t\t     ��ĺ�Ķ�������\n");
					printproductinlist();
				
					printfile();
					system("pause");
					return;
				}
			}
			
			case(1):{
			
				printf("\t\t\t\t\t\t\t\t\t     �������������Ʒ���Ƽ����\n");
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
					printf("\t\t\t\t\t\t\t\t\t     ��Ʒ�������ʧ�ܣ���������Ʒ��Ų��ڽ������У������²�����\n");
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
				p->sum_price = p->sum_price - p->commodity_price * h;
				kk++;
				printf("\t\t\t\t\t\t\t\t\t     %d��%s����%d��������ƿ������%dƿ\n",n,str,h,sum);
				printf("\t\t\t\t\t\t\t\t\t     ����Ʒ��������%d��,��������,�ܼ۵���Ϊ%.2lf\n",p->commodity_number,p->sum_price);
				break;
			}
			case(2):{
				printf("\t\t\t\t\t\t\t\t\t     ������������Ʒ����   ");
				char sp[100];
				fgets(sp, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
				sp[strcspn(sp, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
				while(strcmp(sp, "ũ��ɽȪ") != 0 && strcmp(sp, "��Դ") != 0 && strcmp(sp, "�ൺơ��") != 0&& strcmp(sp, "�޹���") != 0&& strcmp(sp, "����Һ") != 0 && strcmp(sp, "���") != 0 && strcmp(sp, "�ɿڿ���") != 0 && strcmp(sp, "ϲ��") != 0 && strcmp(sp, "��Ҥ�α�") != 0 && strcmp(sp, "��ʦ��") != 0){
	    			printf("\t\t\t\t\t\t\t\t\t     ������ľ�ˮ������������������\n");
	    			printf("\t\t\t\t\t\t\t\t\t     ");
	    			fflush(stdin);
	    			fgets(sp, 100, stdin); // 50��ʾ������ַ������Ϊ50�������Ը���ʵ����Ҫ����
					sp[strcspn(sp, "\n")] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
				}
				printf("\t\t\t\t\t\t\t\t\t     ������������Ʒ���   ");
				int damage_num;
				damage_num = inputNum();
				while(damage_num == -1){
	    			printf("\t\t\t\t\t\t\t\t\t     ������Ϸ����!\n");
        			printf("\t\t\t\t\t\t\t\t\t     ");
        			fflush(stdin); // ��ջ���������������ѭ��
        			damage_num = inputNum();
				}	
				productin *p = NULL;
				p = searchproductinlist(sp,damage_num);
				while(p == NULL){
	    			printf("\t\t\t\t\t\t\t\t\t     ������ı�����󣬸����Ƽ���Ŷ�Ӧ����Ʒ���ڶ���������������\n");
	    			printf("\t\t\t\t\t\t\t\t\t     ");
	    			fflush(stdin);
	    			damage_num = inputNum();
	    			p = searchproductinlist(sp,damage_num);
				}

				printf("\t\t\t\t\t\t\t\t\t     ������������Ʒ����   ");
				int damagebox,damagebottle,damagesum = 0;
				damagebox = inputNum();
				while(damagebox == -1 || damagebox > p->commodity_number || damagebox < 0){
	    			printf("\t\t\t\t\t\t\t\t\t     ���������0С���������ĺϷ�����!\n");
        			printf("\t\t\t\t\t\t\t\t\t     ");
        			fflush(stdin); // ��ջ���������������ѭ��
        			damagebox = inputNum();
				}
				int yf = damagebox,i = 1;
				p->commodity_number -= yf;
				while(damagebox--){
					printf("\t\t\t\t\t\t\t\t\t     �������%d����������Ʒƿ��   ",i);
					i++;
					damagebottle = inputNum();
					while(damagebottle == -1 || damagebottle > p->commodity_packagenum || damagebottle < 0){
	    				printf("\t\t\t\t\t\t\t\t\t     ���������0С����ƿ���ĺϷ�ƿ��!\n");
        				printf("\t\t\t\t\t\t\t\t\t     ");
        				fflush(stdin); // ��ջ���������������ѭ��
        				damagebottle = inputNum();
					}
					damagesum += damagebottle;
					p->commodity_packagenum -= damagebottle;
				}
				printf("\t\t\t\t\t\t\t\t\t     ԭ�ܼ�%.2lf\n",p->sum_price);
				p->sum_price -= p->commodity_price * yf;
			
				printf("\t\t\t\t\t\t\t\t\t     %s%d�Ź�%d��������ƿ������%dƿ\n",sp,damage_num,yf,damagesum);
				printf("\t\t\t\t\t\t\t\t\t     ����Ʒ��������%d��,��������,�ܼ۵���Ϊ%.2lf\n",p->commodity_number,p->sum_price);
				kk++;
				break;
			}
			default:{
				printf("\t\t\t\t\t\t\t\t\t     ������0~2�ĺϷ��ַ�\n");
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
		printf("\t\t\t\t\t                ����ģ��                 \n");
		printf("\t\t\t\t\t--------------------------------------------\n");
		printf("\t\t\t\t\t|       ��1��  �޸Ķ�����Ϣ                |\n");
		printf("\t\t\t\t\t|       ��2��  ɾ�����ֶ�����Ϣ            |\n");
		printf("\t\t\t\t\t|       ��3��  ��ӡ������Ϣ                |\n");
		printf("\t\t\t\t\t|       ��4��  ���Ӷ�����Ϣ                |\n");
		printf("\t\t\t\t\t|       ��5��  ��������Ϣд��in.txt�ļ���  |\n");
		printf("\t\t\t\t\t|       ��6��  ��ѯĳһ��������Ϣ          |\n");
		printf("\t\t\t\t\t|       ��7��  ��ѯ��Ʒ������            |\n");
		printf("\t\t\t\t\t|       ��0��  ��������                    |\n");
		printf("\t\t\t\t\t--------------------------------------------\n");
		printf("\t\t\t\t\t      ����������Ҫ���еķ���(0-7) ");
		
		int productin_num = inputNum();
		//("%d",&productin_num);
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
				//system("pause");
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
				//system("cls");
				printf("\t\t\t\t\t       ���������Ϣ����,������0~7�е�����\n");
				printf("\t\t\t\t\t       ");
				//system("pause");
				break;
		}
	}		
}


#include "customer.h"
extern int count[4];//��ͬ�ȼ���Ӧ��ͬ���ۿ�
extern client *L;
extern LogNode*log_head;
extern int cus_cnt;
extern int log_cnt;
//��ȡ�ļ��еĿͻ���Ϣ
int checkNum(){
	char s[100]={'\0'};int l=0;char ch;
flag:
	l=0;
    while((ch=getchar())!='\n')s[l++]=ch;
    s[l]='\0';
    if(s[0]=='\0') goto flag;
    if(l==1&&s[0]=='0')return 0;
	int ret=0;
	for(int i=0;s[i];i++){
		if(i==0&&s[i]=='0')return -1;
		if(s[i]<='9'&&s[i]>='0')ret=ret*10+s[i]-'0';
		else return -1;
	} 
	return ret;
}
double checkDouble(){
	char s[100]={'\0'};int l=0;char ch;
    while((ch=getchar())!='\n')s[l++]=ch;
    s[l]='\0';
    double ret=0;double res=0;bool flag=0;
    l=0;
    for(int i=0;s[i];i++){
    	 if(s[i]>'9'&&s[i]!='.'||s[i]<'0'&&s[i]!='.')return -1; 
    	 if(s[i]=='.'){
    	 	if(!flag)flag=1;
    	 	else return -1;
    	 	continue;
		 }
    	 if(s[i]<='9'&&s[i]>='0'&&!flag)ret=ret*10+s[i]-'0';
    	 else if(s[i]<='9'&&s[i]>='0'&&flag){
		 res+=(double)(s[i]-'0')/pow(10,++l);
		 if(l>2)return -2;
		 }
	}
	if( !(isFiniteNumber(ret+res)))return -1;
	return ret+res;
}
void readClient(client **L)
{
    cus_cnt=0;
    FILE *fp = fopen("customer.txt", "r");
    if (!fp)
    {
        cout("�ļ���ȡʧ�ܣ�");
        enter, enter;
        fclose(fp);
        return;
    }
    char buffer[1000];
    *L=(client*) malloc(sizeof(client));(*L)->ne=NULL;
    client *q = *L, *p, *tmp = NULL;
    p=(client*) malloc(sizeof(client));
    fgets(buffer,sizeof buffer,fp);
    char ch;
    char name[20],password[20],phoneNumber[12];
    while (fscanf(fp, "%d%s%d%lf%f%s%s", &p->id,name, &p->level,&p->balance, &p->point,password,phoneNumber) != EOF) {
        tmp = (client *) malloc(sizeof(client));
        tmp->id = p->id;
        tmp->level = p->level;
        tmp->point = p->point;
        tmp->balance=p->balance;
        int i = 0;
        for (i = 0; name[i]; i++)tmp->name[i] = name[i];
        tmp->name[i] = '\0';
        for (i = 0; password[i]; i++)tmp->password[i] = password[i];
        tmp->password[i] = '\0';
        for(i=0;phoneNumber[i];i++)tmp->phoneNumber[i]=phoneNumber[i];
        tmp->phoneNumber[i]='\0';
        q->ne = tmp;
        tmp->pre = q;
        q = tmp;
        q->ne = NULL;
        q->cart=NULL;
        cus_cnt++;
    }
    (*L)=(*L)->ne;
    fclose(fp);
}
//���ͻ���Ϣд���ļ�
void writeClientInfo(client *L) {
    FILE *fp = fopen("customer.txt", "w");
    if (!fp) {
        cout("�ļ���ȡʧ�ܣ�");
        enter;
        Sleep(1000);
        fclose(fp);
        exit(0);
    }
    client *p = L;
    fprintf(fp, "�˿ͱ��\t|\t�˿�����\t|\t�˿͵ȼ�\t|\t�˿����\t|\t�˿ͻ���\t|\t�û�����\t|\t��ϵ�绰\n");
    enter;
    while (p) {
        fprintf(fp, "%d\t\t%s\t\t%d\t\t%.2lf\t\t%.2f\t\t%s\t\t%s\n", p->id, p->name, p->level,p->balance, p->point, p->password,p->phoneNumber);
        p = p->ne;
    }
    fclose(fp);
}
//����û�
void addClient(client **L, client *p) {
		system("cls");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t-------------���û�ע�����----------------\n");
		printf("\t\t\t\t\t-------(������������!q���Է�����һ������)--\n");
		printf("\t\t\t\t\t-------------------------------------------\n");
		if (!*L) {

        int id, level=1, point;
        char password[11];
        char phoneNumber[12];
        char s[20];
        cout("\t\t\t\t������˿͵�������");
        while(1){
        	 char ch;
            int l = 0;
            while ((ch = getchar()) != '\n') {
                if (ch == ' ' ) {
                    cout("\t\t\t\t��������Ʋ��ܺ��пո�\n\t\t\t\t�������������ƣ�");
                    while ((getchar()) != '\n');
                    l = 0;
                    continue;
                }
                s[l++] = ch;
            }
            if(l==0)continue;
            else if(l<19){
            	if(l==2&&s[0]=='!'&&s[1]=='q')return;
            	s[l]='\0';
            	break;
			}
            else{
            	printf("\t\t\t\t���Ƴ��ȹ�����\n\t\t\t\t��������������:") ;
			}
		}
//        cout("������û��ȼ�:(�ȼ�1,2,3)\n");
//        while (1) {
//            int con = cin("%d", &level);
//            if (!con || level <= 0 || level > 3 || getchar() != '\n') {
//                cout("��������ַǷ�������������\n");
//                while (getchar() != '\n');
//            } else
//                break;
        cout("\t\t\t\t�������û��绰����:");
        while (1) {
            char ch;
            int l = 0;
            while ((ch = getchar()) != '\n') {
                if (ch == ' ' || ch > '9' || ch < '0') {
                    cout("\t\t\t\t������ֻ��Ų��ܺ��пո������֣�\n\t\t\t\t�����������ֻ��ţ�");
                    while ((getchar()) != '\n');
                    l = 0;
                    continue;
                }
                phoneNumber[l++] = ch;
            }
            if (ch == '\n') {
                if (l == 11) {
                    phoneNumber[l] = '\0';
                    break;
                } else {
                    cout("\t\t\t\t�ֻ����볤�Ȳ�����Ҫ��,���������룺");
                }
            }
        }
        cout("\t\t\t\t�������û�����(���ڵ���6λ��������10λ)��");
         int l = 0;
        while (1) {
            char ch;
           
//            while ((ch = getchar()) != '\n') {
//                if (ch == ' ') {
//                    cout("\t\t\t\t��������벻�ܺ��пո�\n�������������룺");
//                    while ((ch = getchar()) != '\n');
//                    continue;
//                }
//                password[l++] = ch;
//            }
			while(1){
			ch = _getch();
			if(ch == '\r' || ch == '\n') break;
			else if (ch == '\b') {             // �˸������ 
				if(l!=0){
					printf("\b \b");
					l--;
				}
			}
			else{
				printf("*");
				password[l++] = ch;
			}
			password[l] = '\0';
			}
            if (ch == '\r') {
            	for(int i=0;password[i];i++)if(password[i]==' '){
                	 cout("\n\t\t\t\t��������벻�ܺ��пո�\n�������������룺");
                	 break;
				}
                if (l >= 6 && l <= 10) {
                    password[l] = '\0';
                    break;
                } else {
                    cout("\n\t\t\t\t���볤�Ȳ�����Ҫ��,�������������룺");
                }
                
            }
            
		}
            printf("\n\t\t\t\t���ٴ�ȷ�����룺"); 
        while(1){
			char temp[12];int k=0;char ch;
            while(1){
            ch = _getch();
			if(ch == '\r' || ch == '\n') break;
			else if (ch == '\b') {             // �˸������ 
				if(k!=0){
					printf("\b \b");
					k--;
				}
			}
			else{
				printf("*");
				temp[k++] = ch;
			}
			temp[k] = '\0';
			}
			if(ch=='\r')
			{
				if(l!=k||l>10){
					 cout("\n\t\t\t\t�����������֮ǰ�Ĳ�һ�£����������룺");
					 continue; 
				}
				bool flag=true;
				for(int i=0;temp[i];i++){
					if(temp[i]!=password[i]){
						cout("\n\t\t\t\t�����������֮ǰ�Ĳ�һ�£����������룺");
					 	flag=false;
					 	break;
					}
				}
				if(flag)break;
			}	
		}

		*L = (client *) malloc(sizeof(client));
        (*L)->ne = NULL, (*L)->pre = p;
        (*L)->level = level;
        srand((unsigned int) time(NULL));
        int rdx = rand() % 89998 + 10000;
        while (findClient(L, rdx))rdx = rand() % 89998 + 10000;
        (*L)->id = rdx;
        int i = 0;
        for (i = 0; s[i]; i++)(*L)->name[i] = s[i];
        (*L)->name[i] = '\0';
        (*L)->point = 0;
        for (i = 0; password[i]; i++)(*L)->password[i] = password[i];
        (*L)->password[i] = '\0';
        for (i = 0; phoneNumber[i]; i++)(*L)->phoneNumber[i] = phoneNumber[i];
        (*L)->phoneNumber[i] = '\0';
        (*L)->balance=0.0;
        if (p)p->ne = *L;
        cout("\n\t\t\t\t�����û��ɹ�����ǰ�û���id�ǣ�%d\n", (*L)->id);
        cus_cnt++;
        system("pause");
    	}else
        addClient(&(*L)->ne, *L);
}
//Ѱ���û�
client*findClient(client**L,int id){
    client *p=*L;
    while(p){
        if(p->id==id)return p;
        else p=p->ne;
    }
    return NULL;
}
//��ӡ�û���Ϣ
void printCustomer(client*L){
	system("cls");
	printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t                �ͻ���Ϣ                 \n");
    printf("\t\t\t\t\t --------------------------------------- \n");
    if(!L){
        cout("\t\t\t\t\t\t\t�û��б�Ϊ�գ�\n");
        return;
    }
  printf("\t\t\t%-16s%-12s%-10s%-14s%-10s  %-2s\n", "�˿ͱ��", "�˿�����", "�˿͵ȼ�", "�˿����","�˿ͻ���", "��ϵ�绰");

    client *p=L;
    while(p){
        printf("\t\t\t%-16d%-12s%-10d%-14.2lf%-6.2lf\t%-2s\n", p->id, p->name, p->level, p->balance, p->point, p->phoneNumber);
        p=p->ne;
    }
    cout("\t\t\t�ܼ��û�����%d\n",cus_cnt);
}
//����������ȷ��
bool checkPassword(client*L,int id,char *s){
    for(int i=0;s[i];i++)if(s[i]==' ')return false;
    while(L){
        if(L->id==id)break;
        else L=L->ne;
    }
    if(!L){
//        cout("\t\t\t\t\tid�û������ڣ�\n");
        return false;
    }
    int i=0;
    for(i=0;s[i]&&L->password[i];i++)if(s[i]!=L->password[i])return false;
    if(s[i]=='\0'&&L->password[i]=='\0')return true;
    else return false;
}
//ɾ���û�
void delClient(client **L,int id){
    if(!(*L)) {
        cout("\t\t\t\t�޴��û���");
        enter;
        return; }
    client*dummy=malloc(sizeof(client));
    dummy->ne=*L;
    client *p=dummy->ne,*q=dummy;
    while(p&&p->id!=id)q=p,p=p->ne;
    if(!p||p->id!=id){
        cout("\t\t\t\t�޴��û���");enter;
        return;
    }
    q->ne=p->ne;
    if(p->ne)p->ne->pre=q;
    cus_cnt--;
    (*L)=dummy->ne;
    printf("\t\t\t\tɾ���û��ɹ���\n");
}
//�����û����ֺ͵ȼ�
void update(client**L,double money){
    if(!(*L))return ;
    (*L)->point+=money;
    float point=(*L)->point;
    if(point<1000.0) (*L)->level=1;
    else if(point<10000.0&&point>=1000)(*L)->level=2;
    else (*L)->level=3;
}
//�޸��û���Ϣ
void changeInfo(client**L,int id) {
    if (!(*L)) {
        cout("\t\t\t\t\t�����û���Ϣ��\n");
        return;
    }
    client *p = findClient(L, id);
    if (!p) {
        cout("\t\t\t\t���û������ڣ�\n");
        return;
    }
    cout("\t\t\t\t\n\t\t\t\t(1:���� 2:�ֻ��� 3:��� 4������ 0:����)\n");
    cout("\t\t\t\t\t������Ҫ�޸ĵ���Ϣ��");
    int con;
    while (1) {
        con =checkNum();
        if (con==-1|| con <0 || con > 5 ) {
            cout("\n\t\t\t\t\t��������ַǷ������������룺");
        } else
            break;
    }
    switch (con) {
        case 0:{
            return;
        }
        case 1: {
            cout("\t\t\t\t\t������Ҫ�޸ĵ����룺");
            char password[20] = {'\0'};
            while (1) {
                char ch;
                int l = 0;
                while ((ch = getchar()) != '\n') {
                    if (ch == ' ') {
                        cout("\n\t\t\t\t\t��������벻�ܺ��пո�\n�������������룺");
                        continue;
                    }
                    password[l++] = ch;
                }
                password[l] = '\0';
                if (ch == '\n') {
                    if (l >= 6 && l <= 10) {
                        bool flag = 1;
                        if (strlen(password) != strlen(p->password))flag = 0;
                        else
                            for (int i = 0; password[i] && p->password[i]; i++)
                                if (password[i] != p->password[i])
                                    flag = 0;
                        if (!flag) {
                            int i = 0;
                            for (i = 0; password[i]; i++)p->password[i] = password[i];
                            p->password[i] = '\0';
                            cout("\n\t\t\t\t\t�޸�����ɹ���\n");
                            break;
                        } else {
                            cout("\n\t\t\t\t\t���벻�������ڵ�����һ�£����������룺");
                            l = 0;
                            continue;
                        }
                    } else {
                        cout("\n\t\t\t\t\t���볤�Ȳ�����Ҫ��,�������������룺");
                        l = 0;
                    }
                }
            }
        }
            break;
        case 2: {
            cout("\t\t\t\t\t������Ҫ�޸ĵ��ֻ��ţ�");
            char phoneNumber[12] = {'\0'};
            while (1) {
                char ch;
                int l = 0;
                while ((ch = getchar()) != '\n') {
                    if (ch == ' ' || ch > '9' || ch < '0') {
                        cout("\n\t\t\t\t\t������ֻ��Ų��ܺ��пո������֣�\n�����������ֻ��ţ�");
                        while ((getchar()) != '\n');
                        l = 0;
                        continue;
                    }
                    phoneNumber[l++] = ch;
                }
                if (ch == '\n') {
                    if (l == 11) {
                        phoneNumber[l] = '\0';
                        for (int i = 0; i < 12; i++)p->phoneNumber[i] = phoneNumber[i];
                        break;
                    } else {
                        cout("\n\t\t\t\t\t�ֻ����볤�Ȳ�����Ҫ��,���������룺");
                    }
                }
            }
        }
            break;
        case 3: {
            
            cout("\t\t\t\t\t������Ҫ���ĵ���");
            while (1) {
                double balance=checkDouble();
                if (balance==-1) {
                    cout("\t\t\t\t\t����Ĳ������֣����������룺");
//                    while (getchar() != '\n');
                } else if (!(isFiniteNumber(balance))||balance==-2) {
                    cout("\t\t\t\t\t����Ľ���ȷ�����������룺");
//                    while (getchar() != '\n');
                } else {
                    p->balance = balance;
                    cout("\t\t\t\t\t����޸ĳɹ���\n"); 
                    break;
                }
            }
        }
            break;
        case 4: {
            char s[20];
            int i = 0;
            cout("\t\t\t\t\t������˿͵�������");
            while(1){
			
            char ch;
            int l = 0;
            while ((ch = getchar()) != '\n') {
                if (ch == ' ' ) {
                    cout("\t\t\t\t\t��������Ʋ��ܺ��пո�\n\t\t\t\t�������������ƣ�");
                    while ((getchar()) != '\n');
                    l = 0;
                    continue;
                }
                s[l++] = ch;
            }
            if(l==0)continue;
            else if(l<19){
            	if(l==2&&s[0]=='!'&&s[1]=='q')return;
            	s[l]='\0';
            	break;
			}
            else{
            	printf("\t\t\t\t\t���Ƴ��ȹ�����\n\t\t\t\t��������������:") ;
			}
			}
            for (i = 0; s[i]; i++)p->name[i] = s[i];
            p->name[i] = '\0';
            printf("\n\t\t\t\t\t�û���Ϣ�޸ĳɹ���\n");
        	}
            break;
        default:
            break;
    }
}
//֧����������ȷ��
bool checkBalance(client**cus,double money){
    client *p=(*cus);
    if(!p)return false;
    if(p->balance<money)return false;
    if(!(isFiniteNumber(p->balance-money)))return false;
    p->balance-=money;
    if(money>0){
	addLogNode(&log_head,&L,p->id,0,money);
    writeLog(log_head);
	}
    if(money>0) update(&p,money);
    return true;
}
//��ֵ
bool recharge(client**L,LogNode**log,int id,double money){
    client *p=(*L);

    if(money<0)return false;
    if(!p)return false;
    if(!checkBalance(&p,-money))return false;
	addLogNode(log,L,id,1,money);
	writeLog(*log);
	return true;
    //���¶����ڵ�
}
//��ӡ�û�����
//void printCustomerBill(client*L,struct sell_bill* bill,int id){
//    client *p=L;
//    if(!p){
//        cout("�û���ϢΪ�գ�\n");
//        return;
//    }
//    p= findClient(&L,id);
//
//    //
//}
bool cmp(const client*p,client*q){
    return p->level<q->level||p->level==q->level&&p->point<q->point;
}
int getchoice(int *position,int row,int *choice){
		char ch=getch();
		if(ch=='w'||ch=='W'){
			*position=((*position)-1+row)%row;
		}
		if(ch=='s'||ch=='S')*position=((*position)+1)%row;
		if(ch=='\r'){
			*choice=(*position)+1;
			return -1;
		}
		return *choice;
}
void InitLog(LogNode**L,client**cus){
    log_cnt=0;
    FILE *fp = fopen("cuslog.txt", "r");
    if(!fp){
        cout("�ļ���ʧ�ܣ�\n");
        return;
    }
    char buffer[1000];
    *L=(LogNode *) malloc(sizeof(LogNode));(*L)->next=NULL;
    LogNode *q = *L, *p, *tmp = NULL;
    p=(LogNode *) malloc(sizeof(LogNode));
    fgets(buffer,sizeof buffer,fp);
    int cus_id;char event[30];
    while(fscanf(fp,"%d%d%lf%f%s%d",&p->id,&cus_id,&p->money,&p->point,p->event,&p->date)!=EOF){
    	if(findClient(cus,cus_id)==NULL)continue; 
        tmp=(LogNode*) malloc(sizeof(LogNode));
        tmp->id=p->id;
        tmp->date=p->date;
        tmp->money=p->money;
        tmp->point=p->point;
        tmp->cus= findClient(cus,cus_id);
        strcpy(tmp->event,p->event);
        q->next = tmp;
        q = tmp;
        q->next= NULL;
        log_cnt++;
    }
    (*L)=(*L)->next;
    fclose(fp);
}
void addLogNode(LogNode **l,client **L,int cus_id,int op,double money){
    if(!(*l)){
        *l=(LogNode*) malloc(sizeof(LogNode));
        (*l)->next=NULL;
        LogNode *tmp=*l;
        tmp->cus= findClient(L,cus_id);
        tmp->money=money;
        if(op==1){
            char s[30]="��ֵ";
            strcpy(tmp->event,s);
            tmp->point=0;
        }
        else{
            char s[30]="����";
            strcpy(tmp->event,s);
            tmp->point=(float)money;
        }
        time_t timep;
        time(&timep);
        struct tm *tp;
        tp = gmtime(&timep);
        int date=(tp->tm_year+1900)*10000+(1+tp->tm_mon)*100+tp->tm_mday;
        tmp->date=date;
        tmp->id=++log_cnt;
        tmp->next=NULL;
    }
    else addLogNode(&(*l)->next,L,cus_id,op,money);
}
void printLog(LogNode*L){
    if(!L)return;
    cout("����id\t����\t���\t�¼�\t�û�id\n");
    while(L){
        printf("%d\t%d\t%.2lf\t%s\t%d\n",L->id,L->date,L->money,L->event,L->cus->id);
        L=L->next;
    }
}
void writeLog(LogNode*L){
    FILE *fp = fopen("cuslog.txt", "w");
    if (!fp) {
        cout("�ļ���ȡʧ�ܣ�");
        enter;
        Sleep(1000);
        fclose(fp);
        exit(0);
    }
    LogNode *p = L;
    fprintf(fp, "���\t|\t�˿�id\t|\t���\t|\t��û���\t|\t��������\t|\t����ʱ��\n");
    enter;
    while (p) {
        fprintf(fp, "%d\t\t%d\t\t%.2lf\t\t%.2f\t\t%s\t\t%d\n", p->id, p->cus->id, p->money, p->point, p->event,p->date);
        p = p->next;
    }
    fclose(fp);
}
void showCusInfo(client*cus,LogNode*logh){
	system("cls");
	printf("\n\n\n\n\n"); 
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t              �ҵ���Ϣ                   \n");
    printf("\t\t\t\t\t                                         \n");
    printf("\t\t\t\t\t --------------------------------------- \n");
    
    printf("\t\t\t\t\t�û�����%s\n",cus->name);
    printf("\t\t\t\t\t�û�ID:%d\n",cus->id);
    printf("\t\t\t\t\t�ֻ��ţ�%s\n",cus->phoneNumber);
    printf("\t\t\t\t\t�û��ȼ�:%d\n",cus->level);
    printf("\t\t\t\t\t�û����:%.2lf\n",cus->balance);
    
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t              ���䶯��¼               \n");
    printf("\t\t\t\t%-16s%-12s%-10s%-10s\n", "����", "�漰���", "�䶯ԭ��", "��û���");
    int flag=0;
    while(logh){
    	if(logh->cus->id==cus->id){
    		flag=1;
    		printf("\t\t\t\t%-16d%-12.2lf%-10s%-10.2f\n", logh->date, logh->money, logh->event, logh->point);
		}
		logh=logh->next;
	}
	if(!flag)printf("\t\t\t\t�������䶯��¼Ϊ��\n");
	system("pause"); 
}

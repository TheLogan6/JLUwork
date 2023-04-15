#include "customer.h"
extern int count[4];//��ͬ�ȼ���Ӧ��ͬ���ۿ�
extern client *cus_head;
extern LogNode*log_head;
extern int cus_cnt;
extern int log_cnt;
//��ȡ�ļ��еĿͻ���Ϣ
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
	while(1)
	{
		system("cls");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t-------------���û�ע�����----------------\n");
//		printf("\t\t\t\t\t      (������������0���Է�����һ������)\n");
		if (!*L) {
        *L = (client *) malloc(sizeof(client));
        (*L)->ne = NULL, (*L)->pre = p;
        int id, level=1, point;
        char password[10];
        char phoneNumber[12];
        char s[20];
        cout("\t\t\t������˿͵�������");
        cin("%s", s);
        getchar();
//        cout("������û��ȼ�:(�ȼ�1,2,3)\n");
//        while (1) {
//            int con = cin("%d", &level);
//            if (!con || level <= 0 || level > 3 || getchar() != '\n') {
//                cout("��������ַǷ�������������\n");
//                while (getchar() != '\n');
//            } else
//                break;
        cout("�������û��绰���룺\n");
        while (1) {
            char ch;
            int l = 0;
            while ((ch = getchar()) != '\n') {
                if (ch == ' ' || ch > '9' || ch < '0') {
                    cout("������ֻ��Ų��ܺ��пո������֣�\n�����������ֻ��ţ�");
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
                    cout("�ֻ����볤�Ȳ�����Ҫ��,���������룺");
                }
            }
        }
        cout("�������û�����(���ڵ���6λ��������10λ)��");
        while (1) {
            char ch;
            int l = 0;
            while ((ch = getchar()) != '\n') {
                if (ch == ' ') {
                    cout("��������벻�ܺ��пո�\n�������������룺");
                    while ((ch = getchar()) != '\n');
                    continue;
                }
                password[l++] = ch;
            }
            if (ch == '\n') {
                if (l >= 6 && l <= 10) {
                    password[l] = '\0';
                    break;
                } else {
                    cout("���볤�Ȳ�����Ҫ��,�������������룺");
                }
            }
        }

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
        cout("�����û��ɹ�����ǰ�û���id�ǣ�%d\n", (*L)->id);
        cus_cnt++;
    } else
        addClient(&(*L)->ne, *L);
		
		
	} 
    
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
    if(!L){
        cout("�û��б�Ϊ�գ�\n");
        return;
    }
    printf("�˿ͱ��  �˿�����  �˿͵ȼ�  �˿����  �˿ͻ���  ��ϵ�绰\n");
    client *p=L;
    while(p){
        printf("%d\t%s\t%d\t%.2lf\t%.2lf\t%s\n", p->id, p->name, p->level,p->balance,p->point,p->phoneNumber);
        p=p->ne;
    }
    cout("�ܼ��û�����%d\n",cus_cnt);
}
//����������ȷ��
bool checkPassword(client*L,int id,char *s){
    for(int i=0;s[i];i++)if(s[i]==' ')return false;
    while(L){
        if(L->id==id)break;
        else L=L->ne;
    }
    if(!L){
        cout("id�û������ڣ�\n");
        return false;
    }
    int i=0;
    for(i=0;s[i]&&L->password[i];i++)if(s[i]!=L->password[i])return false;
    if(s[i]=='\0'&&L->password[i]=='\0')return true;
    else return false;
}
//ɾ���û�
void delClient(client **L,int id){
    if(!(*L))return;
    client *p=*L,*q=p;
    while(p&&p->id!=id)q=p,p=p->ne;
    if(!p||p->id!=id){
        cout("�޴��û���");enter;
        return;
    }
    q->ne=p->ne;
    if(p->ne)p->ne->pre=q;
    cus_cnt--;
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
        cout("�����û���Ϣ��\n");
        return;
    }
    client *p = findClient(L, id);
    if (!p) {
        cout("���û������ڣ�\n");
        return;
    }
    cout("������Ҫ�޸ĵ���Ϣ��(1:���� 2:�ֻ��� 3:��� 4������ 0:����)\n");
    int op;
    while (1) {
        int con = cin("%d", &op);
        if (!con || op <0 || op > 5 || getchar() != '\n') {
            cout("��������ַǷ�������������\n");
            while (getchar() != '\n');
        } else
            break;
    }
    switch (op) {
        case 0:{
            return;
        }
        case 1: {
            cout("������Ҫ�޸ĵ����룺");
            char password[20] = {'\0'};
            while (1) {
                char ch;
                int l = 0;
                while ((ch = getchar()) != '\n') {
                    if (ch == ' ') {
                        cout("��������벻�ܺ��пո�\n�������������룺");
                        while (getchar() != '\n');
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
                            cout("�޸�����ɹ���\n");
                            break;
                        } else {
                            cout("���벻�������ڵ�����һ�£�\n");
                            while (getchar() != '\n');
                            l = 0;
                            continue;
                        }
                    } else {
                        cout("���볤�Ȳ�����Ҫ��,�������������룺");
                        l = 0;
                    }
                }
            }
        }
            break;
        case 2: {
            cout("������Ҫ�޸ĵ��ֻ��ţ�");
            char phoneNumber[12] = {'\0'};
            while (1) {
                char ch;
                int l = 0;
                while ((ch = getchar()) != '\n') {
                    if (ch == ' ' || ch > '9' || ch < '0') {
                        cout("������ֻ��Ų��ܺ��пո������֣�\n�����������ֻ��ţ�");
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
                        cout("�ֻ����볤�Ȳ�����Ҫ��,���������룺");
                    }
                }
            }
        }
            break;
        case 3: {
            double balance;
            cout("������Ҫ���ĵ���");
            while (1) {
                int con = cin("%lf", &balance);
                if (!con) {
                    cout("����Ĳ������֣����������룺");
                    while (getchar() != '\n');
                } else if (balance < 0 || !(isFiniteNumber(balance))) {
                    cout("����Ľ���ȷ�����������룺");
                    while (getchar() != '\n');
                } else {
                    p->balance = balance;
                    break;
                }
            }
        }
            break;
        case 4: {
            char s[20];
            int i = 0;
            cout("������˿͵�������\n");
            cin("%s", s);
            for (i = 0; s[i]; i++)p->name[i] = s[i];
            p->name[i] = '\0';
        }
            break;
        default:
            break;
    }
}
//֧����������ȷ��
bool checkBalance(client**L,double money){
    client *p=(*L);
    if(!p)return false;
    if(p->balance<money)return false;
    if(!(isFiniteNumber(p->balance-money)))return false;
    p->balance-=money;
    if(money>0)update(&p,money);
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
void cusSort(client**L,int op){
    client *dummy=*L,*p=*L;
    if(!p)return;

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

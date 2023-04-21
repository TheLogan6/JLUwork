#include "customer.h"
extern int count[4];//不同等级对应不同的折扣
extern client *L;
extern LogNode*log_head;
extern int cus_cnt;
extern int log_cnt;
//读取文件中的客户信息
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
        cout("文件读取失败！");
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
//将客户信息写入文件
void writeClientInfo(client *L) {
    FILE *fp = fopen("customer.txt", "w");
    if (!fp) {
        cout("文件读取失败！");
        enter;
        Sleep(1000);
        fclose(fp);
        exit(0);
    }
    client *p = L;
    fprintf(fp, "顾客编号\t|\t顾客姓名\t|\t顾客等级\t|\t顾客余额\t|\t顾客积分\t|\t用户密码\t|\t联系电话\n");
    enter;
    while (p) {
        fprintf(fp, "%d\t\t%s\t\t%d\t\t%.2lf\t\t%.2f\t\t%s\t\t%s\n", p->id, p->name, p->level,p->balance, p->point, p->password,p->phoneNumber);
        p = p->ne;
    }
    fclose(fp);
}
//添加用户
void addClient(client **L, client *p) {
		system("cls");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t-------------新用户注册界面----------------\n");
		printf("\t\t\t\t\t-------(在姓名处输入!q可以返回上一个界面)--\n");
		printf("\t\t\t\t\t-------------------------------------------\n");
		if (!*L) {

        int id, level=1, point;
        char password[11];
        char phoneNumber[12];
        char s[20];
        cout("\t\t\t\t请输入顾客的姓名：");
        while(1){
        	 char ch;
            int l = 0;
            while ((ch = getchar()) != '\n') {
                if (ch == ' ' ) {
                    cout("\t\t\t\t输入的名称不能含有空格！\n\t\t\t\t请重新输入名称：");
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
            	printf("\t\t\t\t名称长度过长！\n\t\t\t\t请重新输入名称:") ;
			}
		}
//        cout("请分配用户等级:(等级1,2,3)\n");
//        while (1) {
//            int con = cin("%d", &level);
//            if (!con || level <= 0 || level > 3 || getchar() != '\n') {
//                cout("输入的数字非法！请重新输入\n");
//                while (getchar() != '\n');
//            } else
//                break;
        cout("\t\t\t\t请输入用户电话号码:");
        while (1) {
            char ch;
            int l = 0;
            while ((ch = getchar()) != '\n') {
                if (ch == ' ' || ch > '9' || ch < '0') {
                    cout("\t\t\t\t输入的手机号不能含有空格或非数字！\n\t\t\t\t请重新输入手机号：");
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
                    cout("\t\t\t\t手机号码长度不符合要求,请重新输入：");
                }
            }
        }
        cout("\t\t\t\t请输入用户密码(大于等于6位，不多于10位)：");
         int l = 0;
        while (1) {
            char ch;
           
//            while ((ch = getchar()) != '\n') {
//                if (ch == ' ') {
//                    cout("\t\t\t\t输入的密码不能含有空格！\n请重新输入密码：");
//                    while ((ch = getchar()) != '\n');
//                    continue;
//                }
//                password[l++] = ch;
//            }
			while(1){
			ch = _getch();
			if(ch == '\r' || ch == '\n') break;
			else if (ch == '\b') {             // 退格符特判 
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
                	 cout("\n\t\t\t\t输入的密码不能含有空格！\n请重新输入密码：");
                	 break;
				}
                if (l >= 6 && l <= 10) {
                    password[l] = '\0';
                    break;
                } else {
                    cout("\n\t\t\t\t密码长度不符合要求,请重新输入密码：");
                }
                
            }
            
		}
            printf("\n\t\t\t\t请再次确认密码："); 
        while(1){
			char temp[12];int k=0;char ch;
            while(1){
            ch = _getch();
			if(ch == '\r' || ch == '\n') break;
			else if (ch == '\b') {             // 退格符特判 
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
					 cout("\n\t\t\t\t输入的密码与之前的不一致！请重新输入：");
					 continue; 
				}
				bool flag=true;
				for(int i=0;temp[i];i++){
					if(temp[i]!=password[i]){
						cout("\n\t\t\t\t输入的密码与之前的不一致！请重新输入：");
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
        cout("\n\t\t\t\t创建用户成功！当前用户的id是：%d\n", (*L)->id);
        cus_cnt++;
        system("pause");
    	}else
        addClient(&(*L)->ne, *L);
}
//寻找用户
client*findClient(client**L,int id){
    client *p=*L;
    while(p){
        if(p->id==id)return p;
        else p=p->ne;
    }
    return NULL;
}
//打印用户信息
void printCustomer(client*L){
	system("cls");
	printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t                客户信息                 \n");
    printf("\t\t\t\t\t --------------------------------------- \n");
    if(!L){
        cout("\t\t\t\t\t\t\t用户列表为空！\n");
        return;
    }
  printf("\t\t\t%-16s%-12s%-10s%-14s%-10s  %-2s\n", "顾客编号", "顾客姓名", "顾客等级", "顾客余额","顾客积分", "联系电话");

    client *p=L;
    while(p){
        printf("\t\t\t%-16d%-12s%-10d%-14.2lf%-6.2lf\t%-2s\n", p->id, p->name, p->level, p->balance, p->point, p->phoneNumber);
        p=p->ne;
    }
    cout("\t\t\t总计用户数：%d\n",cus_cnt);
}
//检验密码正确性
bool checkPassword(client*L,int id,char *s){
    for(int i=0;s[i];i++)if(s[i]==' ')return false;
    while(L){
        if(L->id==id)break;
        else L=L->ne;
    }
    if(!L){
//        cout("\t\t\t\t\tid用户不存在！\n");
        return false;
    }
    int i=0;
    for(i=0;s[i]&&L->password[i];i++)if(s[i]!=L->password[i])return false;
    if(s[i]=='\0'&&L->password[i]=='\0')return true;
    else return false;
}
//删除用户
void delClient(client **L,int id){
    if(!(*L)) {
        cout("\t\t\t\t无此用户！");
        enter;
        return; }
    client*dummy=malloc(sizeof(client));
    dummy->ne=*L;
    client *p=dummy->ne,*q=dummy;
    while(p&&p->id!=id)q=p,p=p->ne;
    if(!p||p->id!=id){
        cout("\t\t\t\t无此用户！");enter;
        return;
    }
    q->ne=p->ne;
    if(p->ne)p->ne->pre=q;
    cus_cnt--;
    (*L)=dummy->ne;
    printf("\t\t\t\t删除用户成功！\n");
}
//更新用户积分和等级
void update(client**L,double money){
    if(!(*L))return ;
    (*L)->point+=money;
    float point=(*L)->point;
    if(point<1000.0) (*L)->level=1;
    else if(point<10000.0&&point>=1000)(*L)->level=2;
    else (*L)->level=3;
}
//修改用户信息
void changeInfo(client**L,int id) {
    if (!(*L)) {
        cout("\t\t\t\t\t暂无用户信息！\n");
        return;
    }
    client *p = findClient(L, id);
    if (!p) {
        cout("\t\t\t\t该用户不存在！\n");
        return;
    }
    cout("\t\t\t\t\n\t\t\t\t(1:密码 2:手机号 3:余额 4：姓名 0:返回)\n");
    cout("\t\t\t\t\t请输入要修改的信息：");
    int con;
    while (1) {
        con =checkNum();
        if (con==-1|| con <0 || con > 5 ) {
            cout("\n\t\t\t\t\t输入的数字非法！请重新输入：");
        } else
            break;
    }
    switch (con) {
        case 0:{
            return;
        }
        case 1: {
            cout("\t\t\t\t\t请输入要修改的密码：");
            char password[20] = {'\0'};
            while (1) {
                char ch;
                int l = 0;
                while ((ch = getchar()) != '\n') {
                    if (ch == ' ') {
                        cout("\n\t\t\t\t\t输入的密码不能含有空格！\n请重新输入密码：");
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
                            cout("\n\t\t\t\t\t修改密码成功！\n");
                            break;
                        } else {
                            cout("\n\t\t\t\t\t密码不能与现在的密码一致！请重新输入：");
                            l = 0;
                            continue;
                        }
                    } else {
                        cout("\n\t\t\t\t\t密码长度不符合要求,请重新输入密码：");
                        l = 0;
                    }
                }
            }
        }
            break;
        case 2: {
            cout("\t\t\t\t\t请输入要修改的手机号：");
            char phoneNumber[12] = {'\0'};
            while (1) {
                char ch;
                int l = 0;
                while ((ch = getchar()) != '\n') {
                    if (ch == ' ' || ch > '9' || ch < '0') {
                        cout("\n\t\t\t\t\t输入的手机号不能含有空格或非数字！\n请重新输入手机号：");
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
                        cout("\n\t\t\t\t\t手机号码长度不符合要求,请重新输入：");
                    }
                }
            }
        }
            break;
        case 3: {
            
            cout("\t\t\t\t\t请输入要更改的余额：");
            while (1) {
                double balance=checkDouble();
                if (balance==-1) {
                    cout("\t\t\t\t\t输入的不是数字！请重新输入：");
//                    while (getchar() != '\n');
                } else if (!(isFiniteNumber(balance))||balance==-2) {
                    cout("\t\t\t\t\t输入的金额不正确！请重新输入：");
//                    while (getchar() != '\n');
                } else {
                    p->balance = balance;
                    cout("\t\t\t\t\t金额修改成功！\n"); 
                    break;
                }
            }
        }
            break;
        case 4: {
            char s[20];
            int i = 0;
            cout("\t\t\t\t\t请输入顾客的姓名：");
            while(1){
			
            char ch;
            int l = 0;
            while ((ch = getchar()) != '\n') {
                if (ch == ' ' ) {
                    cout("\t\t\t\t\t输入的名称不能含有空格！\n\t\t\t\t请重新输入名称：");
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
            	printf("\t\t\t\t\t名称长度过长！\n\t\t\t\t请重新输入名称:") ;
			}
			}
            for (i = 0; s[i]; i++)p->name[i] = s[i];
            p->name[i] = '\0';
            printf("\n\t\t\t\t\t用户信息修改成功！\n");
        	}
            break;
        default:
            break;
    }
}
//支付与检查金额正确性
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
//充值
bool recharge(client**L,LogNode**log,int id,double money){
    client *p=(*L);

    if(money<0)return false;
    if(!p)return false;
    if(!checkBalance(&p,-money))return false;
	addLogNode(log,L,id,1,money);
	writeLog(*log);
	return true;
    //更新订单节点
}
//打印用户订单
//void printCustomerBill(client*L,struct sell_bill* bill,int id){
//    client *p=L;
//    if(!p){
//        cout("用户信息为空！\n");
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
        cout("文件打开失败！\n");
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
            char s[30]="充值";
            strcpy(tmp->event,s);
            tmp->point=0;
        }
        else{
            char s[30]="消费";
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
    cout("订单id\t日期\t金额\t事件\t用户id\n");
    while(L){
        printf("%d\t%d\t%.2lf\t%s\t%d\n",L->id,L->date,L->money,L->event,L->cus->id);
        L=L->next;
    }
}
void writeLog(LogNode*L){
    FILE *fp = fopen("cuslog.txt", "w");
    if (!fp) {
        cout("文件读取失败！");
        enter;
        Sleep(1000);
        fclose(fp);
        exit(0);
    }
    LogNode *p = L;
    fprintf(fp, "编号\t|\t顾客id\t|\t金额\t|\t获得积分\t|\t消费类型\t|\t消费时间\n");
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
    printf("\t\t\t\t\t              我的信息                   \n");
    printf("\t\t\t\t\t                                         \n");
    printf("\t\t\t\t\t --------------------------------------- \n");
    
    printf("\t\t\t\t\t用户名：%s\n",cus->name);
    printf("\t\t\t\t\t用户ID:%d\n",cus->id);
    printf("\t\t\t\t\t手机号：%s\n",cus->phoneNumber);
    printf("\t\t\t\t\t用户等级:%d\n",cus->level);
    printf("\t\t\t\t\t用户余额:%.2lf\n",cus->balance);
    
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t              余额变动记录               \n");
    printf("\t\t\t\t%-16s%-12s%-10s%-10s\n", "日期", "涉及金额", "变动原因", "获得积分");
    int flag=0;
    while(logh){
    	if(logh->cus->id==cus->id){
    		flag=1;
    		printf("\t\t\t\t%-16d%-12.2lf%-10s%-10.2f\n", logh->date, logh->money, logh->event, logh->point);
		}
		logh=logh->next;
	}
	if(!flag)printf("\t\t\t\t您的余额变动记录为空\n");
	system("pause"); 
}

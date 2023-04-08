#include"sellbill.h"

struct customer* Find_pointer_of_client(int id)
{
    struct  customer* pointer_of_client=L;
    while(pointer_of_client!=NULL)
    {
        if(pointer_of_client->id==id)
            return pointer_of_client;
        pointer_of_client=pointer_of_client->ne;
    }
    return NULL;
}
struct sell_bill* Initiate_Bill()
{
    struct sell_bill* head=(struct sell_bill*)malloc(sizeof(struct sell_bill));
    head->next=NULL;
    head->pre=NULL;
    FILE *filep=fopen("bill.txt", "r");
    if(filep == NULL)
    {
        fclose(filep);
        return head;
    }
    struct sell_bill* point=head;
    int nth_bill=0;//第几笔订单
    while(1)
    {
        nth_bill++;
        struct sell_bill* bill=(struct sell_bill*)malloc(sizeof(struct sell_bill));
        if(fscanf(filep, "%d", &bill->order) == EOF)break;
        if(fscanf(filep, "%d%d%d%d%d%d", &bill->year, &bill->month, &bill->day, &bill->hour, &bill->minute, &bill->second) == EOF)break;
        fscanf(filep, "%s", bill->brand);                //品牌
        fscanf(filep, "%d", &bill->number_of_brand);      //品牌编号
        fscanf(filep, "%d", &bill->ProductNumber);       // 商品编号
        fscanf(filep, "%d", &bill->SpecificationNumber); //规格编号
        fscanf(filep, "%d", &bill->packagingsize);       //包装大小
        fscanf(filep, "%lf", &bill->Unit_Price);         //销售单价
        fscanf(filep, "%d", &bill->volume);              //产品容量
        fscanf(filep, "%d", &bill->number_of_packagingzise);//这个包装的买了多少箱
        fscanf(filep, "%d", &bill->total_number);        //卖出的总数
        fscanf(filep, "%lf", &bill->total_price);        //总价
        int id_of_client;
        fscanf(filep, "%d", &id_of_client);               //客户
        bill->buyer= Find_pointer_of_client(id_of_client);
        fscanf(filep, "%lf", &bill->discount_for_client);//优惠
        point->next=bill;
        bill->pre=point;
        bill->next=NULL;
        struct Inventory* pointer_Inventory=Inv_head->next;
        while(pointer_Inventory!=NULL)
        {
        	if(pointer_Inventory->BrandNumber==bill->number_of_brand&&pointer_Inventory->SpecificationNumber==bill->SpecificationNumber) break;
			pointer_Inventory=pointer_Inventory->next;
		}
        if(pointer_Inventory==NULL) 
        {
        	printf("1");
		}
        bill->product=pointer_Inventory;
        point=bill;
    }
    if(head->next==NULL)
    {
        return head;
    }
    fclose(filep);
    return head;
}
struct sell_bill* Sell_select_brand(int number_of_brand)
{
    struct sell_bill *newbill = (struct sell_bill *) malloc(sizeof(struct sell_bill));
    newbill->next = NULL;
    newbill->pre = NULL;
    struct  Inventory* pointer_Inventory=Inv_head->next;
    while(pointer_Inventory!=NULL)
    {
        if(pointer_Inventory->BrandNumber==number_of_brand)
        {
            strcpy(newbill->brand,pointer_Inventory->DrinksBrand);
            newbill->number_of_brand=pointer_Inventory->BrandNumber;
            break;
        }
        pointer_Inventory=pointer_Inventory->next;
    }
    return newbill;
}
void Sell_select_ProductNumber(int number, struct sell_bill* newbill)
{
//    printf("\n请选择您需要批发的商品编号:");
//    struct Inventory* pointer_of_Inv=Inv_head->next;
//    while(pointer_of_Inv->BrandNumber!=newbill->number_of_brand)pointer_of_Inv=pointer_of_Inv->next;
//    int maxnum=-0x3f3f3f3f;
//    while(pointer_of_Inv->BrandNumber==newbill->number_of_brand)
//    {
//        if(pointer_of_Inv->SpecificationNumber>maxnum)maxnum=pointer_of_Inv->SpecificationNumber;
//        pointer_of_Inv=pointer_of_Inv->next;
//    }
//    while(1)
//    {
//        int ret,count=0;
//        char c;
//        do
//        {
//            if(count!=0)printf("对不起，您输入的商品编号不正确，请您重新输入\n");
//            ret=scanf("%d", &newbill->SpecificationNumber);
//            c = getchar();
//            fflush(stdin);
//            count++;
//        }while ((ret!=1)||(c!='\n'));
//        if(newbill->SpecificationNumber<=0||newbill->SpecificationNumber>maxnum)
//        {
//            printf("对不起，您输入的商品编号不正确，请您重新输入\n");
//            continue;
//        }
//        break;
//    }
	newbill->SpecificationNumber=number;
    struct Inventory* pointer_Inventory=Inv_head->next;
    while(pointer_Inventory!=NULL)
    {
    	if(pointer_Inventory->BrandNumber==newbill->number_of_brand&&pointer_Inventory->SpecificationNumber==newbill->SpecificationNumber) break;
    	pointer_Inventory=pointer_Inventory->next;
	}  
    newbill->ProductNumber=pointer_Inventory->ProductNumber;
    newbill->volume = pointer_Inventory->volume;
    newbill->packagingsize = pointer_Inventory->packagingsize;
    newbill->Unit_Price = pointer_Inventory->Price;
}
struct sell_bill* Sell_select_Number_of_goods(struct sell_bill* newbill,struct customer* user)
{
    printf("请问您需要买多少箱%d瓶/箱的产品:", newbill->packagingsize);
    struct Inventory* pointer_Inventory=Inv_head->next;
    while(pointer_Inventory!=NULL)
    {
    	if(pointer_Inventory->BrandNumber==newbill->number_of_brand&&pointer_Inventory->SpecificationNumber==newbill->SpecificationNumber) break;
    	pointer_Inventory=pointer_Inventory->next;
	}  
    newbill->product=pointer_Inventory;
    while(1)
    {
        int ret,count=0;
        char c;
        do
        {
            if(count!=0)printf("对不起，您输入的购买数目不正确，请您重新输入\n");
            ret=scanf("%d", &newbill->number_of_packagingzise);
            c = getchar();
            fflush(stdin);
            count++;
        }while ((ret!=1)||(c!='\n'));
        if(newbill->number_of_packagingzise>pointer_Inventory->Reserve)
        {
            printf("对不起，您输入的购买数目超过商品库存，请您重新输入\n");
            continue;
        }
        if(newbill->number_of_packagingzise<=0)
        {
            printf("对不起，您输入的购买数目不正确，请您重新输入\n");
            continue;
        }
        break;
    }
    newbill->total_number = newbill->packagingsize * newbill->number_of_packagingzise;
    newbill->total_price = newbill->Unit_Price * newbill->number_of_packagingzise;
    newbill->buyer=user;
    printf("您好顾客%s,鉴于您是%d级会员，您仅需要支付该订单的", user->name, user->level);
    //以下是会员优惠
    if (user->level == 1) {
        newbill->discount_for_client = 0.98;
    }
    if (user->level == 2) {
        newbill->discount_for_client = 0.95;
    }
    if (user->level == 3) {
        newbill->discount_for_client = 0.90;
    }
    int discount = 100 * newbill->discount_for_client;
    newbill->total_price *= newbill->discount_for_client;
    printf("%d%%", discount);
    return newbill;
//    user->point+=newbill->total_price;
}
struct  sell_bill* Sell_confirm(struct sell_bill* newbill,struct customer* user)
{
    bool purchased=false;
    while(purchased==false)
    {
        printf("请选择您的支付方式：\n");
        printf("1.现金支付\n");
        printf("2.余额支付\n");
        printf("3.取消购买\n");
        int buychoice;
        while(1)
        {
            int ret,count=0;
            char c;
            do
            {
                if(count!=0)printf("对不起，您输入的支付方式不正确，请您重新输入\n");
                ret=scanf("%d", &buychoice);
                c = getchar();
                fflush(stdin);
                count++;
            }while ((ret!=1)||(c!='\n'));
            if(buychoice<=0||buychoice>3)
            {
                printf("对不起，您输入的支付方式不正确，请您重新输入\n");
                continue;
            }
            break;
        }
        if(buychoice==1)
        {
            printf("\n您已成功购买，谢谢您的惠顾\n");
//            addLogNode(&log_head,&L,user->id,0,newbill->total_price);
//            writeLog(log_head);
            newbill->product->Reserve-=newbill->number_of_packagingzise;
            purchased=true;
            continue;
        }
        if(buychoice==2)
        {
//            if(chekBalance(&user,newbill->total_price)==true)
            if(true)
            {
                printf("\n您已成功购买，谢谢您的惠顾\n");
//                addLogNode(&log_head,&L,user->id,0,newbill->total_price);
//                writeLog(log_head);
                newbill->product->Reserve-=newbill->number_of_packagingzise;
                purchased=true;
                continue;
            }
            else
            {
                printf("对不起，您的余额不足,您可以选择联系管理员进行余额充值\n");
                continue;
            }
        }
        if(buychoice==3)
        {
            printf("期待您的下一次光临\n");
            return NULL;
        }
    }
    return newbill;
}
void sell_save(struct sell_bill* newbill)
{
    FILE *filep = fopen("bill.txt", "a");time_t timep;
    struct tm *timenow;
    time(&timep);
    timenow = gmtime(&timep);
    struct sell_bill *pointer_of_all_bills = bill_pre->next;
    if (pointer_of_all_bills == NULL)//如果这是第一笔订单
    {
        newbill->pre=bill_pre;
        bill_pre->next=newbill;
        newbill->order=1;
    }
    else
    {
        while(pointer_of_all_bills->next!=NULL)
        {
            pointer_of_all_bills=pointer_of_all_bills->next;
        }
        newbill->pre=pointer_of_all_bills;
        pointer_of_all_bills->next=newbill;
        newbill->order=pointer_of_all_bills->order+1;
    }
    newbill->year=1900+timenow->tm_year;
    newbill->month=1+timenow->tm_mon;
    newbill->day=timenow->tm_mday;
    newbill->hour=8+timenow->tm_hour;
    newbill->minute=timenow->tm_min;
    newbill->second=timenow->tm_sec;
    fprintf(filep,"%d ",newbill->order);
    fprintf(filep,"%d ",newbill->year);
    fprintf(filep,"%d ",newbill->month);
    fprintf(filep,"%d ",newbill->day);
    fprintf(filep,"%d ",newbill->hour);
    fprintf(filep,"%d ",newbill->minute);
    fprintf(filep,"%d ",newbill->second);
    fprintf(filep,"%s ",newbill->brand);
    fprintf(filep,"%d ",newbill->number_of_brand);
    fprintf(filep,"%d ",newbill->ProductNumber);
    fprintf(filep,"%d ",newbill->SpecificationNumber);
    fprintf(filep,"%d ",newbill->packagingsize);
    fprintf(filep,"%.2lf ",newbill->Unit_Price);
    fprintf(filep,"%d ",newbill->volume);
    fprintf(filep,"%d ",newbill->number_of_packagingzise);
    fprintf(filep,"%d ",newbill->total_number);
    fprintf(filep,"%.2lf ",newbill->total_price);
    fprintf(filep,"%d ",newbill->buyer->id);
    fprintf(filep,"%.2lf\n",newbill->discount_for_client);
//    fprintf(filep);
    fclose(filep);
}
void Print_Bills_Of_Given_Brand(void) { printf("您打算查询哪个品牌的订单\n");
    for(int i=1;i<=Number_Of_Brand;i++)
    {
        printf("%d.%s\n",i,code[i][0]);
    }
    printf("请输入您要查询的品牌编号：\n");
    int number_of_brand;
    while(1)
    {
        int ret,count=0;
        char c;
        do
        {
            if(count!=0)printf("对不起，您输入的品牌编号不正确，请您重新输入\n");
            ret=scanf("%d", &number_of_brand);
            c = getchar();
            fflush(stdin);
            count++;
        }while ((ret!=1)||(c!='\n'));
        if(number_of_brand<=0||number_of_brand>Number_Of_Brand)
        {
            printf("对不起，您输入的品牌编号不正确，请您重新输入\n");
            continue;
        }
        break;
    }
    struct sell_bill *bill = bill_pre->next;
    int count = 0;
    while (bill != NULL) {
        if (bill->number_of_brand == number_of_brand) {
            count++;
            if (count == 1)
                printf("—————————————————————————————————————————————————————————历史订单——————————————————————————————————————————————————————\n"
           "编号\t|交易时间\t\t|商品品牌\t|商品名称\t|商品容量(ml)\t|包装大小(瓶/箱)\t|销售单价\t|售出数目(箱)\t|总数(瓶)\t|买家\t\t|买家等级\t|优惠\t|总价\t\n");
    		//订单编号
        printf("%d\t", bill->order);
        printf("|");
        //交易时间?
        printf("%d-", bill->year);
        if (bill->month < 10)printf("0%d-", bill->month);
        else printf("%d-", bill->month);
        if (bill->day < 10)printf("0%d ", bill->day);
        else printf("%d ", bill->day);
        if (bill->hour < 10)printf("0%d:", bill->hour);
        else printf("%d:", bill->hour);
        if (bill->minute < 10)printf("0%d:", bill->minute);
        else printf("%d:", bill->minute);
        if (bill->second < 10)printf("0%d", bill->second);
        else printf("%d", bill->second);
        printf("\t|");
        //产品品牌?
        printf("%s", bill->brand);
        for (int i = 1; i <= 2 - (strlen(bill->brand) +1) / 8; i++)printf("\t");
        printf("|");
        //产品名称?
        printf("%s", code[bill->number_of_brand][bill->ProductNumber]);
        for (int i = 1; i <= 3 -(strlen(code[bill->number_of_brand][bill->ProductNumber]) * 2 +2) / 8; i++)printf("\t");
        printf("|");
        //产品容量?
        printf("%d", bill->volume);
        printf("\t\t|");
        //包装大小?
        printf("%d", bill->packagingsize);
        printf("\t\t\t|");
        //销售单价?
        printf("%.2lf", bill->Unit_Price);
        char Unit_Price[20];
        sprintf(Unit_Price, "%.2lf", bill->Unit_Price);
//        int n=strlen(Unit_Price);
        for (int i = 1; i <= 2 - (strlen(Unit_Price) +1) / 8; i++)printf("\t");
        printf("|");
        //出售个数
        printf("%d", bill->number_of_packagingzise);
        char numberofpackagingsize[20];
        sprintf(numberofpackagingsize, "%d",bill->number_of_packagingzise);
        for (int i = 1; i <= 2 - (strlen(numberofpackagingsize) +1) / 8; i++)printf("\t");
        printf("|");
        //总数?
        printf("%d", bill->total_number);
        char total_number[20];
        sprintf(total_number, "%d", bill->total_number);
        for (int i = 1; i <= 2 - (strlen(total_number) +1) / 8; i++)printf("\t");
        printf("|");
        //买家?
        printf("%s", bill->buyer->name);
        for (int i = 1; i <= 2 - (strlen(bill->buyer->name)+1) / 8; i++)printf("\t");
        printf("|");
        //买家等级?
        printf("%d", bill->buyer->level);
        printf("\t\t|");
        //优惠?
        printf("%.2lf", bill->discount_for_client);
        printf("\t|");
        //总价?
        printf("%.2lf\n", bill->total_price);
        }
        bill = bill->next;
    }
}
void Print_Bills_Of_Given_Id(void)
{
     printf("请输入您要查询的用户ID：");
    int ID_of_client;
    while(1)
    {
        int ret,count=0;
        char c;
        do
        {
            if(count!=0)printf("对不起，您输入的用户ID不正确，请您重新输入\n");
            ret=scanf("%d",&ID_of_client);
            c = getchar();
            fflush(stdin);
            count++;
        }while ((ret!=1)||(c!='\n'));
        if(ID_of_client<=0)
        {
            printf("对不起，您输入的用户ID不正确，请您重新输入\n");
            continue;
        }
        if(Find_pointer_of_client(ID_of_client)==NULL)
        {
            printf("对不起，您输入的用户不存在，请您重新输入\n");
            continue;
        }
        break;
    }
    int count=0;
    struct sell_bill* bill=bill_pre->next;
    while(bill!=NULL)
    {
        if(bill->buyer->id==ID_of_client)
        {
            count++;
            if (count == 1)
                printf("—————————————————————————————————————————————————————————历史订单——————————————————————————————————————————————————————\n"
           "编号\t|交易时间\t\t|商品品牌\t|商品名称\t|商品容量(ml)\t|包装大小(瓶/箱)\t|销售单价\t|售出数目(箱)\t|总数(瓶)\t|买家\t\t|买家等级\t|优惠\t|总价\t\n");
    		//订单编号
        printf("%d\t", bill->order);
        printf("|");
        //交易时间?
        printf("%d-", bill->year);
        if (bill->month < 10)printf("0%d-", bill->month);
        else printf("%d-", bill->month);
        if (bill->day < 10)printf("0%d ", bill->day);
        else printf("%d ", bill->day);
        if (bill->hour < 10)printf("0%d:", bill->hour);
        else printf("%d:", bill->hour);
        if (bill->minute < 10)printf("0%d:", bill->minute);
        else printf("%d:", bill->minute);
        if (bill->second < 10)printf("0%d", bill->second);
        else printf("%d", bill->second);
        printf("\t|");
        //产品品牌?
        printf("%s", bill->brand);
        for (int i = 1; i <= 2 - (strlen(bill->brand) +1) / 8; i++)printf("\t");
        printf("|");
        //产品名称?
        printf("%s", code[bill->number_of_brand][bill->ProductNumber]);
        for (int i = 1; i <= 3 -(strlen(code[bill->number_of_brand][bill->ProductNumber]) * 2 +2) / 8; i++)printf("\t");
        printf("|");
        //产品容量?
        printf("%d", bill->volume);
        printf("\t\t|");
        //包装大小?
        printf("%d", bill->packagingsize);
        printf("\t\t\t|");
        //销售单价?
        printf("%.2lf", bill->Unit_Price);
        char Unit_Price[20];
        sprintf(Unit_Price, "%.2lf", bill->Unit_Price);
//        int n=strlen(Unit_Price);
        for (int i = 1; i <= 2 - (strlen(Unit_Price) +1) / 8; i++)printf("\t");
        printf("|");
        //出售个数
        printf("%d", bill->number_of_packagingzise);
        char numberofpackagingsize[20];
        sprintf(numberofpackagingsize, "%d",bill->number_of_packagingzise);
        for (int i = 1; i <= 2 - (strlen(numberofpackagingsize) +1) / 8; i++)printf("\t");
        printf("|");
        //总数?
        printf("%d", bill->total_number);
        char total_number[20];
        sprintf(total_number, "%d", bill->total_number);
        for (int i = 1; i <= 2 - (strlen(total_number) +1) / 8; i++)printf("\t");
        printf("|");
        //买家?
        printf("%s", bill->buyer->name);
        for (int i = 1; i <= 2 - (strlen(bill->buyer->name)+1) / 8; i++)printf("\t");
        printf("|");
        //买家等级?
        printf("%d", bill->buyer->level);
        printf("\t\t|");
        //优惠?
        printf("%.2lf", bill->discount_for_client);
        printf("\t|");
        //总价?
        printf("%.2lf\n", bill->total_price);
        }
        bill = bill->next;
    }
    if(count==0)
    {
        printf("对不起，您想查询的用户没有历史订单\n");
    }
}
void Print_Bills_Of_Given_Name(void)
{
    printf("请输入您要查询的用户名字：");
    char Name_of_client[30];
    while(1)
    {
        int ret,count=0;
        char c;
        do
        {
            if(count!=0)printf("对不起，您输入的用户名字不正确，请您重新输入\n");
            scanf("%s",Name_of_client);
            c=getchar();
            count++;
        }while (c!='\n'||strcmp(Name_of_client,"\n")==0);
        struct customer* pointer_of_client=L;
        while(pointer_of_client!=NULL)
        {
            if(strcmp(pointer_of_client->name,Name_of_client)==0)break;
            pointer_of_client=pointer_of_client->ne;
        }
        if(pointer_of_client==NULL)
        {
            printf("对不起，您想查询的用户不存在,请您重新输入\n");
            continue;
        }
        break;
    }
    struct sell_bill* bill=bill_pre->next;
    int count=0;
    while(bill!=NULL)
    {
        if((strcmp(bill->buyer->name,Name_of_client))==0)
        {
            count++;
            if (count == 1)
                printf("—————————————————————————————————————————————————————————历史订单——————————————————————————————————————————————————————\n"
           "编号\t|交易时间\t\t|商品品牌\t|商品名称\t|商品容量(ml)\t|包装大小(瓶/箱)\t|销售单价\t|售出数目(箱)\t|总数(瓶)\t|买家\t\t|买家等级\t|优惠\t|总价\t\n");
    		//订单编号
        printf("%d\t", bill->order);
        printf("|");
        //交易时间?
        printf("%d-", bill->year);
        if (bill->month < 10)printf("0%d-", bill->month);
        else printf("%d-", bill->month);
        if (bill->day < 10)printf("0%d ", bill->day);
        else printf("%d ", bill->day);
        if (bill->hour < 10)printf("0%d:", bill->hour);
        else printf("%d:", bill->hour);
        if (bill->minute < 10)printf("0%d:", bill->minute);
        else printf("%d:", bill->minute);
        if (bill->second < 10)printf("0%d", bill->second);
        else printf("%d", bill->second);
        printf("\t|");
        //产品品牌?
        printf("%s", bill->brand);
        for (int i = 1; i <= 2 - (strlen(bill->brand) +1) / 8; i++)printf("\t");
        printf("|");
        //产品名称?
        printf("%s", code[bill->number_of_brand][bill->ProductNumber]);
        for (int i = 1; i <= 3 -(strlen(code[bill->number_of_brand][bill->ProductNumber]) * 2 +2) / 8; i++)printf("\t");
        printf("|");
        //产品容量?
        printf("%d", bill->volume);
        printf("\t\t|");
        //包装大小?
        printf("%d", bill->packagingsize);
        printf("\t\t\t|");
        //销售单价?
        printf("%.2lf", bill->Unit_Price);
        char Unit_Price[20];
        sprintf(Unit_Price, "%.2lf", bill->Unit_Price);
//        int n=strlen(Unit_Price);
        for (int i = 1; i <= 2 - (strlen(Unit_Price) +1) / 8; i++)printf("\t");
        printf("|");
        //出售个数
        printf("%d", bill->number_of_packagingzise);
        char numberofpackagingsize[20];
        sprintf(numberofpackagingsize, "%d",bill->number_of_packagingzise);
        for (int i = 1; i <= 2 - (strlen(numberofpackagingsize) +1) / 8; i++)printf("\t");
        printf("|");
        //总数?
        printf("%d", bill->total_number);
        char total_number[20];
        sprintf(total_number, "%d", bill->total_number);
        for (int i = 1; i <= 2 - (strlen(total_number) +1) / 8; i++)printf("\t");
        printf("|");
        //买家?
        printf("%s", bill->buyer->name);
        for (int i = 1; i <= 2 - (strlen(bill->buyer->name)+1) / 8; i++)printf("\t");
        printf("|");
        //买家等级?
        printf("%d", bill->buyer->level);
        printf("\t\t|");
        //优惠?
        printf("%.2lf", bill->discount_for_client);
        printf("\t|");
        //总价?
        printf("%.2lf\n", bill->total_price);
        }
        bill = bill->next;
    }
    if(count==0)
    {
        printf("对不起，您想要查询的用户不存在或您想查询的用户没有历史订单\n");
    }
}
void Print_Bills_Of_Given_Client(void)
{
     printf("您想通过什么方式查询用户订单？\n");
    printf("1.通过用户id来查询用户订单\n");
    printf("2.通过用户名字来查询用户订单\n");
    printf("请输入您需要的查询方式：\n");
    int way;
    while(1)
    {
        int ret,count=0;
        char c;
        do
        {
            if(count!=0)printf("对不起，您输入的购买数目不正确，请您重新输入\n");
            ret=scanf("%d", &way);
            c = getchar();
            fflush(stdin);
            count++;
        }while ((ret!=1)||(c!='\n'));
        if(way<=0||way>2)
        {
            printf("对不起，您输入的方式不正确，请您重新输入\n");
            continue;
        }
        break;
    }
    if(way==1)
        Print_Bills_Of_Given_Id();
    if(way==2)
        Print_Bills_Of_Given_Name();
}
void Search_For_The_Bills_Of_Given_Data(void)
{
    printf("您打算查询什么订单？\n");
    printf("1.有关给定商品品牌的订单\n");
    printf("2.有关特定买家的订单\n");
    printf("请输入你要查询的订单类型编号(1-2):\n");
    int kind_of_bill;
    while(1)
    {
        int ret,count=0;
        char c;
        do
        {
            if(count!=0)printf("对不起，您输入的编号不正确，请您重新输入\n");
            ret=scanf("%d", &kind_of_bill);
            c = getchar();
            fflush(stdin);
            count++;
        }while ((ret!=1)||(c!='\n'));
        if(kind_of_bill<=0||kind_of_bill>2)
        {
            printf("对不起，您输入的编号不正确，请您重新输入\n");
            continue;
        }
        break;
    }
    if(kind_of_bill==1)
        Print_Bills_Of_Given_Brand();
    if(kind_of_bill==2)
        Print_Bills_Of_Given_Client();
}
struct sell_bill* find_pointer_of_given_bill(int order, struct sell_bill* head)
{
    struct sell_bill* point_of_bill = NULL;
    if (head->next != NULL)
    {
        point_of_bill=head->next;
    }
    else return NULL;
    while(point_of_bill!=NULL&&order!=point_of_bill->order)
    {
        point_of_bill=point_of_bill->next;
    }
    return point_of_bill;
}
void Delete_Bill(void)
{
     if(bill_pre->next == NULL)
    {
        printf("很抱歉，没有历史订单\n");
        return;
    }
    Check_Bills();
    printf("请输入你要删掉的订单编号(输入0可返回上一个界面)\n");
    int order_of_bill;
    while(1)
    {
        int ret,count=0;
        char c;
        do
        {
            if(count!=0)printf("对不起，您输入的订单编号不正确，请您重新输入\n");
            ret=scanf("%d",&order_of_bill);
            c = getchar();
            fflush(stdin);
            count++;
        }while ((ret!=1)||(c!='\n'));
        if(order_of_bill<0)
        {
            printf("对不起，您输入的订单编号不正确，请您重新输入\n");
            continue;
        }
        if(order_of_bill==0) return;
        struct sell_bill* pointer_of_bill=bill_pre;
        while(pointer_of_bill!=NULL&&pointer_of_bill->order!=order_of_bill)
            pointer_of_bill=pointer_of_bill->next;
        if(pointer_of_bill==NULL)
        {
            printf("对不起，您想删除的订单不存在，请您重新输入\n");
            continue;
        }
        break;
    }
    struct sell_bill* pointer_of_bill=bill_pre;
    while(pointer_of_bill->next!=NULL)
    {
        if(pointer_of_bill->next->order==order_of_bill)
            break;
        pointer_of_bill=pointer_of_bill->next;
    }
    pointer_of_bill->next->next->pre=pointer_of_bill;
    struct sell_bill* delete=pointer_of_bill->next;
    pointer_of_bill->next=pointer_of_bill->next->next;
    free(delete);
    printf("删除成功\n");
    FILE* filep= fopen("bill.txt","w");
    struct sell_bill* newbill=bill_pre->next;
    int count=0; 
    while(newbill!=NULL)
    {
        fprintf(filep,"%d ",++count);
        fprintf(filep,"%d ",newbill->year);
        fprintf(filep,"%d ",newbill->month);
        fprintf(filep,"%d ",newbill->day);
        fprintf(filep,"%d ",newbill->hour);
        fprintf(filep,"%d ",newbill->minute);
        fprintf(filep,"%d ",newbill->second);
        fprintf(filep,"%s ",newbill->brand);
        fprintf(filep,"%d ",newbill->number_of_brand);
        fprintf(filep,"%d ",newbill->ProductNumber);
        fprintf(filep,"%d ",newbill->SpecificationNumber);
        fprintf(filep,"%d ",newbill->packagingsize);
        fprintf(filep,"%.2lf ",newbill->Unit_Price);
        fprintf(filep,"%d ",newbill->volume);
        fprintf(filep,"%d ",newbill->number_of_packagingzise);
        fprintf(filep,"%d ",newbill->total_number);
        fprintf(filep,"%.2lf ",newbill->total_price);
        fprintf(filep,"%d ",newbill->buyer->id);
        fprintf(filep,"%.2lf\n",newbill->discount_for_client);
        newbill=newbill->next;
    }
    fclose(filep);
    system("cls");
    bill_pre=Initiate_Bill();
    printf("删除成功后的历史订单为：\n");
    Check_Bills();
}
void Check_Bills(void)
{
    if(bill_pre->next == NULL)
    {
        printf("很抱歉，没有历史订单\n");
        return;
    }
    printf("—————————————————————————————————————————————————————————历史订单——————————————————————————————————————————————————————\n"
           "编号\t|交易时间\t\t|商品品牌\t|商品名称\t|商品容量(ml)\t|包装大小(瓶/箱)\t|销售单价\t|售出数目(箱)\t|总数(瓶)\t|买家\t\t|买家等级\t|优惠\t|总价\t\n");
    //
    struct sell_bill* bill=bill_pre->next;
    while(bill!=NULL)
    {
        //订单编号
        printf("%d\t", bill->order);
        printf("|");
        //交易时间?
        printf("%d-", bill->year);
        if (bill->month < 10)printf("0%d-", bill->month);
        else printf("%d-", bill->month);
        if (bill->day < 10)printf("0%d ", bill->day);
        else printf("%d ", bill->day);
        if (bill->hour < 10)printf("0%d:", bill->hour);
        else printf("%d:", bill->hour);
        if (bill->minute < 10)printf("0%d:", bill->minute);
        else printf("%d:", bill->minute);
        if (bill->second < 10)printf("0%d", bill->second);
        else printf("%d", bill->second);
        printf("\t|");
        //产品品牌?
        printf("%s", bill->brand);
        for (int i = 1; i <= 2 - (strlen(bill->brand) +1) / 8; i++)printf("\t");
        printf("|");
        //产品名称?
        printf("%s", code[bill->number_of_brand][bill->ProductNumber]);
        for (int i = 1; i <= 3 -(strlen(code[bill->number_of_brand][bill->ProductNumber]) * 2 +2) / 8; i++)printf("\t");
        printf("|");
        //产品容量?
        printf("%d", bill->volume);
        printf("\t\t|");
        //包装大小?
        printf("%d", bill->packagingsize);
        printf("\t\t\t|");
        //销售单价?
        printf("%.2lf", bill->Unit_Price);
        char Unit_Price[20];
        sprintf(Unit_Price, "%.2lf", bill->Unit_Price);
//        int n=strlen(Unit_Price);
        for (int i = 1; i <= 2 - (strlen(Unit_Price) +1) / 8; i++)printf("\t");
        printf("|");
        //出售个数
        printf("%d", bill->number_of_packagingzise);
        char numberofpackagingsize[20];
        sprintf(numberofpackagingsize, "%d",bill->number_of_packagingzise);
        for (int i = 1; i <= 2 - (strlen(numberofpackagingsize) +1) / 8; i++)printf("\t");
        printf("|");
        //总数?
        printf("%d", bill->total_number);
        char total_number[20];
        sprintf(total_number, "%d", bill->total_number);
        for (int i = 1; i <= 2 - (strlen(total_number) +1) / 8; i++)printf("\t");
        printf("|");
        //买家?
        printf("%s", bill->buyer->name);
        for (int i = 1; i <= 2 - (strlen(bill->buyer->name)+1) / 8; i++)printf("\t");
        printf("|");
        //买家等级?
        printf("%d", bill->buyer->level);
        printf("\t\t|");
        //优惠?
        printf("%.2lf", bill->discount_for_client);
        printf("\t|");
        //总价?
        printf("%.2lf\n", bill->total_price);
        bill=bill->next;
    }
}

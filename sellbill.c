#include"sellbill.h"
#include"customer.h"
extern double total_cost;
extern double total_income;
extern double current_money;
//正常订单
struct customer* Find_pointer_of_client(int id)
{
	//找到给定id所对应的用户 
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
	//初始化订单信息 
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
        if(fscanf(filep, "%d", &bill->status) == EOF)break;
        if(fscanf(filep, "%d", &bill->reason_num) == EOF)break;
        if(fscanf(filep, "%d", &bill->change_num) == EOF)break;
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
//        int id_of_client;
        fscanf(filep, "%d", &bill->id);               //客户
        bill->buyer= Find_pointer_of_client(bill->id);
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
	//按照给定的商品品牌更新订单属性 
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
	//按照给定的商品编号更新订单属性 
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
void Sell_select_Number_of_goods(struct sell_bill* newbill,struct customer* user)
{
	//选择购买商品的数量 
    printf("\t\t\t\t\t请问您需要买多少箱%d瓶/箱的产品:", newbill->packagingsize);
    struct Inventory* pointer_Inventory=Inv_head->next;
    while(pointer_Inventory!=NULL)
    {
        if(pointer_Inventory->BrandNumber==newbill->number_of_brand&&pointer_Inventory->SpecificationNumber==newbill->SpecificationNumber) break;
        pointer_Inventory=pointer_Inventory->next;
    }
    newbill->product=pointer_Inventory;
    while(1)
    {
        newbill->number_of_packagingzise=checkNum();
        if(newbill->number_of_packagingzise==-1)
		{
			printf("\t\t\t\t\t对不起，您输入的购买数目不正确，请您重新输入:");
			continue;
		}
        if(newbill->number_of_packagingzise>pointer_Inventory->Reserve)
        {
            printf("\t\t\t\t\t对不起，您输入的购买数目超过商品库存，请您重新输入:");
            continue;
        }
        if(newbill->number_of_packagingzise<=0)
        {
            printf("\t\t\t\t\t对不起，您输入的购买数目不正确，请您重新输入:");
            continue;
        }
        break;
    }
    newbill->total_number = newbill->packagingsize * newbill->number_of_packagingzise;
    newbill->total_price = newbill->Unit_Price * newbill->number_of_packagingzise;
    newbill->buyer=user;
    printf("\t\t\t\t\t您好顾客%s,鉴于您是%d级会员，您仅需要支付该订单的", user->name, user->level);
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
    printf("%d%%，因此需要支付%.2lf元", discount,newbill->total_price);
//    user->point+=newbill->total_price;
}
int Sell_confirm(struct sell_bill* newbill,struct customer* user)
{
	//确定订单的购买方式 
    bool flag=false;
    while(flag==false)
    {
        //system("");
        printf("\t\t\t\t\t请选择您的支付方式：\n");
        printf("\t\t\t\t\t1.现金支付\n");
        printf("\t\t\t\t\t2.余额支付\n");
        printf("\t\t\t\t\t3.加入购物车\n");
        printf("\t\t\t\t\t4.取消购买\n");
        printf("\t\t\t\t\t请输入您的支付方式所对应的编号：");
        int buychoice;
        while(1)
        {
            buychoice=checkNum();
            if(buychoice<=0||buychoice>4)
            {
                printf("\n\t\t\t\t\t对不起，您输入的编号不正确，请您重新输入:");
                continue;
            }
            break;
        }
        if(buychoice==1)
        {
            printf("\t\t\t\t\t您已成功购买，谢谢您的惠顾");
//            addLogNode(&log_head,&L,user->id,0,newbill->total_price);
//            writeLog(log_head);
			update(&user,newbill->total_price);
			writeClientInfo(L);
            flag=true;
            newbill->status=1;
            newbill->product->Reserve-=newbill->number_of_packagingzise;
            total_income+=newbill->total_price;
            current_money+=newbill->total_price;
            writeprofit();
            continue;
        }
        if(buychoice==2)
        {
//            if(chekBalance(&user,newbill->total_price)==true)
            if(checkBalance(&user,newbill->total_price))
            {
                printf("\t\t\t\t\t您已成功购买，谢谢您的惠顾");
//                addLogNode(&log_head,&L,user->id,0,newbill->total_price);
//                writeLog(log_head);
                writeClientInfo(L);
                flag=true;
                newbill->status=1;
                newbill->product->Reserve-=newbill->number_of_packagingzise;
                total_income+=newbill->total_price;
                current_money+=newbill->total_price;
                writeprofit();
                continue;
            }
            else
            {
                printf("\t\t\t\t\t对不起，您的余额不足,您可以选择联系管理员进行余额充值\n");
                continue;
            }
        }
        if(buychoice==3)  //加入购物车 
        {
			printf("\t\t\t\t\t期待您的下一次光临");
			addShoppingCart(&user->cart,newbill->number_of_packagingzise,user->id,newbill->Unit_Price,newbill->number_of_brand,newbill->ProductNumber,newbill->SpecificationNumber);
			writeShoppingCart(&L);
            newbill->status=6;
            flag=true;
            continue;
        }
        if(buychoice==4)
        {
            printf("\t\t\t\t\t期待您的下一次光临\n");
            newbill->status=0;
            flag=true;
            continue;
        }
        return buychoice;
    }
}
void sell_save(struct sell_bill* newbill)
{
	//保存订单 
	
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
//       	pau;      可删除吗？ 
        newbill->pre=pointer_of_all_bills;
        pointer_of_all_bills->next=newbill;
        newbill->order=pointer_of_all_bills->order+1;
        newbill->next=NULL;
    }
    newbill->year=1900+timenow->tm_year;
    newbill->month=1+timenow->tm_mon;
    newbill->day=timenow->tm_mday;
    newbill->hour=(8+timenow->tm_hour)%24;
    newbill->minute=timenow->tm_min;
    newbill->second=timenow->tm_sec;
    newbill->reason_num=-1;
	newbill->change_num=-1; 
    fprintf(filep,"%d ",newbill->order);
    fprintf(filep,"%d ",newbill->status);
    fprintf(filep,"%d ",newbill->reason_num);
    fprintf(filep,"%d ",newbill->change_num);
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
    bill_pre = Initiate_Bill(); 
}
void Print_Bills_Of_Given_Brand(void) 
{ 
	//查询给定品牌的订单信息 
	printf("\t\t\t\t\t\t\t\t\t\t您打算查询哪个品牌的订单\n");
    for(int i=1;i<=Number_Of_Brand;i++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t%d.%s\n",i,code[i][0]);
    }
    printf("\t\t\t\t\t\t\t\t\t\t请输入您要查询的品牌编号:(输入0取消查询)");
    int number_of_brand;
    while(1)
    {
        number_of_brand=checkNum();
        if(number_of_brand==0)return;
        if(number_of_brand<0||number_of_brand>Number_Of_Brand)
        {
            printf("\t\t\t\t\t\t\t\t\t\t对不起，您输入的品牌编号不正确，请您重新输入:");
            continue;
        }
        break;
    }
    struct sell_bill *bill = bill_pre->next;
    int count = 0;
    while (bill != NULL) {
        if (bill->number_of_brand == number_of_brand) {
        	if(bill->status==6)
        	{
        		bill=bill->next;
        		continue;
			}
            count++;
            if (count == 1)
                printf("\n——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————\n"
                       "编号\t|订单状态\t\t|交易时间\t\t|商品品牌\t|商品名称\t|商品容量(ml)\t|包装大小(瓶/箱)\t|销售单价\t|售出数目(箱)\t|总数(瓶)\t|买家\t\t|买家等级\t|优惠\t|总价(元)\t\n");
            //订单编号
            printf("%d\t", count);
            printf("|");
            //订单状态
            switch(bill->status)
            {
            	case(0):
            {
                printf("订单取消\t\t");
                printf("|");
                break;
            }
                case(1):
                {
                    printf("订单正常\t\t");
                    printf("|");
                    break;
                }
                case(2):
                {
                    printf("申请换货中\t\t");
                    printf("|");
                    break;
                }
                case(3):
                {
                    printf("申请退货中\t\t");
                    printf("|");
                    break;
                }
                case(4):
                {
                    printf("已换货\t\t\t");
                    printf("|");
                    break;
                }
                case(5):
                {
                    printf("已退货\t\t\t");
                    printf("|");
                    break;
                }
            }
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
            if(bill->buyer!=NULL)
            {
            //买家?
            printf("%d", bill->id);
	        char user_id[20];
	        sprintf(user_id, "%d",bill->id);
	        for (int i = 1; i <= 2 - (strlen(user_id)+1) / 8; i++)printf("\t");
	        printf("|");
            //买家等级?
            printf("%d", bill->buyer->level);
            printf("\t\t|");
			}
            else 
            {
            	printf("该买家已被删除\t|");
            	printf("该买家已被删除\t|");
			}
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
		printf("\t\t\t\t\t\t\t\t\t\t对不起，该品牌还没有任何销售订单\n");
		pau; 
        return;
	 } 
    pau;
}
int Scanf_ID(void)
{
	//输入需要查询的用户ID 
    printf("\t\t\t\t\t\t\t\t\t\t请输入您要查询的用户ID：(输入0取消查询)");
    int ID_of_client;
    while(1)
    {
        ID_of_client=checkNum();
        if(ID_of_client==0) return ID_of_client;
        if(ID_of_client<10000||ID_of_client>99999)
        {
            printf("\t\t\t\t\t\t\t\t\t\t对不起，您输入的用户ID不正确，请您重新输入:");
            continue;
        }
        if(Find_pointer_of_client(ID_of_client)==NULL)
        {
            printf("\t\t\t\t\t\t\t\t\t\t对不起，您输入的用户不存在，请您重新输入:");
            continue;
        }
        break;
    }
    return ID_of_client;
}
int Print_Bills_Of_Given_Id(int ID_of_client)
{//根据用户id去查询该用户的所有订单 
	if(ID_of_client==0) return ID_of_client;
    int count=0;
    struct sell_bill* bill=bill_pre->next;
    while(bill!=NULL)
    {
        if(bill->id==ID_of_client)
        {
        	if(bill->status==6)
        	{
        		bill=bill->next;
        		continue;
			}
            count++;
            if (count == 1)
                printf("\n——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————\n"
                       "编号\t|订单状态\t\t|交易时间\t\t|商品品牌\t|商品名称\t|商品容量(ml)\t|包装大小(瓶/箱)\t|销售单价\t|售出数目(箱)\t|总数(瓶)\t|买家\t\t|买家等级\t|优惠\t|总价(元)\t\n");
            //编号
            printf("%d\t", count);
            printf("|");
            //订单状态
            switch(bill->status)
            {
	            	case(0):
	            {
	                printf("订单取消\t\t");
	                printf("|");
	                break;
	            }
                case(1):
                {
                    printf("订单正常\t\t");
                    printf("|");
                    break;
                }
                case(2):
                {
                    printf("申请换货中\t\t");
                    printf("|");
                    break;
                }
                case(3):
                {
                    printf("申请退货中\t\t");
                    printf("|");
                    break;
                }
                case(4):
                {
                    printf("已换货\t\t\t");
                    printf("|");
                    break;
                }
                case(5):
                {
                    printf("已退货\t\t\t");
                    printf("|");
                    break;
                }
            }
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
            if(bill->buyer!=NULL)
	        {
	        //买家?
	        printf("%d", bill->id);
	        char user_id[20];
	        sprintf(user_id, "%d",bill->id);
	        for (int i = 1; i <= 2 - (strlen(user_id)+1) / 8; i++)printf("\t");
	        printf("|");
	        //买家等级?
	        printf("%d", bill->buyer->level);
	        printf("\t\t|");
			}
	        else 
	        {
	        	printf("该买家已被删除\t|");
	        	printf("该买家已被删除\t|");
			}
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
        printf("\t\t\t\t\t\t\t\t\t\t对不起，该用户没有历史订单\n");
        return 0;
    }
    return count;
}
void Search_For_The_Bills_Of_Given_Data(void)
{
	//确定查询订单的类型 
	system("cls");
				printf("\n\n\n\n\n"); 
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t                        查询特定订单的界面                 \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
    printf("\n\t\t\t\t\t\t\t\t\t\t您打算查询什么订单？\n");
    printf("\t\t\t\t\t\t\t\t\t\t1.有关给定商品品牌的订单\n");
    printf("\t\t\t\t\t\t\t\t\t\t2.有关特定买家的订单\n");
    printf("\t\t\t\t\t\t\t\t\t\t请输入你要查询的订单类型编号(1-2):(输入0取消查询)");
    int kind_of_bill;
    while(1)
    {
        kind_of_bill=checkNum();
        if(kind_of_bill==0)return;
        if(kind_of_bill<0||kind_of_bill>2)
        {
            printf("\t\t\t\t\t\t\t\t\t\t对不起，您输入的编号不正确，请您重新输入\n");
            continue;
        }
        break;
    }
    if(kind_of_bill==1)
        Print_Bills_Of_Given_Brand();
    if(kind_of_bill==2)
    {
    	int num=Scanf_ID();
        Print_Bills_Of_Given_Id(num);
        if(num!=0)pau;
	}
}//
struct sell_bill* find_pointer_of_given_bill(int order, struct sell_bill* head)
{
	//按照订单编号寻找到指定订单 
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
int Delete_Bill(void)
{
	//删除订单 
	system("cls");
				printf("\n\n\n\n\n"); 
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t                        删除订单的界面                 \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
    if(bill_pre->next == NULL)
    {
        printf("\n\t\t\t\t\t很抱歉，没有历史订单\n");
        return 1;
    }
    Check_Bills();
    printf("\t\t\t\t\t请输入你要删掉的订单编号(输入0可取消删除订单):");
   	struct sell_bill* pointer_of_bill=bill_pre->next;
    int order_of_bill;
    while(1)
    {
        order_of_bill=checkNum();
        if(order_of_bill<0)
        {
            printf("\t\t\t\t\t对不起，您输入的订单编号不正确，请您重新输入:");
            continue;
        }
        if(order_of_bill==0) return 0;
        while(pointer_of_bill!=NULL)
        {
        	if(pointer_of_bill->order==order_of_bill)break;
        	pointer_of_bill=pointer_of_bill->next;
		}
        if(pointer_of_bill==NULL)
        {
            printf("\t\t\t\t\t对不起，您想删除的订单不存在，请您重新输入:");
            continue;
        }
        break;
    }
//    struct sell_bill* pointer_of_bill=bill_pre;
//    while(pointer_of_bill->next!=NULL)
//    {
//        if(pointer_of_bill->next->order==order_of_bill)
//            break;
//        pointer_of_bill=pointer_of_bill->next;
//    }
//    pointer_of_bill->next->next->pre=pointer_of_bill;
//    struct sell_bill* delete=pointer_of_bill->next;
//    pointer_of_bill->next=pointer_of_bill->next->next;
	pointer_of_bill->pre->next=pointer_of_bill->next;
	pointer_of_bill->next->pre=pointer_of_bill->pre;
	struct sell_bill* pointer=bill_with_problem->next;
	while(pointer!=NULL)
	{
		if(pointer->order==pointer_of_bill->order)
		{
			pointer->pre->next=pointer->next;
			if(pointer->next!=NULL)
			pointer->next->pre=pointer->pre;
			free(pointer);
			break; 
		}
		pointer=pointer->next;
	}
    free(pointer_of_bill);
    printf("\t\t\t\t\t删除成功\n");
    FILE* filep= fopen("bill.txt","w");
    struct sell_bill* newbill=bill_pre->next;
    int count=0;
    while(newbill!=NULL)
    {
        fprintf(filep,"%d ",++count);
	    fprintf(filep,"%d ",newbill->status);
	    fprintf(filep,"%d ",newbill->reason_num);
	    fprintf(filep,"%d ",newbill->change_num);
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
        fprintf(filep,"%d ",newbill->id);
        fprintf(filep,"%.2lf\n",newbill->discount_for_client);
        newbill=newbill->next;
    }
    fclose(filep);
    system("cls");
				printf("\n\n\n\n\n"); 
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t                        删除订单的界面                 \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
    bill_pre=Initiate_Bill();
    printf("\t\t\t\t\t\t\t\t\t\t删除成功后的历史订单为：\n");
    Check_Bills();
    return 1;
}
void Check_Bills(void)
{
	//查看所有订单 
    if(bill_pre->next == NULL)
    {
        printf("\n\t\t\t\t\t很抱歉，没有历史订单\n");
        return;
    }
    printf("\n—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————\n"
           "订单编号|订单状态\t\t|交易时间\t\t|商品品牌\t|商品名称\t|商品容量(ml)\t|包装大小(瓶/箱)\t|销售单价\t|售出数目(箱)\t|总数(瓶)\t|买家\t\t|买家等级\t|优惠\t|总价(元)\t\n");
    //
    struct sell_bill* bill=bill_pre->next;
    while(bill!=NULL)
    {
    	if(bill->status==6)
        	{
        		bill=bill->next;
        		continue;
			}
        //订单编号
        printf("%d\t", bill->order);
        printf("|");
        //订单状态
        switch(bill->status)
        {
        	case(0):
            {
                printf("订单取消\t\t");
                printf("|");
                break;
            }
            case(1):
            {
                printf("订单正常\t\t");
                printf("|");
                break;
            }
            case(2):
            {
                printf("申请换货中\t\t");
                printf("|");
                break;
            }
            case(3):
            {
                printf("申请退货中\t\t");
                printf("|");
                break;
            }
            case(4):
            {
                printf("已换货\t\t\t");
                printf("|");
                break;
            }
            case(5):
            {
                printf("已退货\t\t\t");
                printf("|");
                break;
            }
        }
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
        if(bill->buyer!=NULL)
        {
        //买家?
        printf("%d", bill->id);
        char user_id[20];
        sprintf(user_id, "%d",bill->id);
        for (int i = 1; i <= 2 - (strlen(user_id)+1) / 8; i++)printf("\t");
        printf("|");
        //买家等级?
        printf("%d", bill->buyer->level);
        printf("\t\t|");
		}
        else 
        {
        	printf("该买家已被删除\t|");
        	printf("该买家已被删除\t|");
		}
        //优惠?
        printf("%.2lf", bill->discount_for_client);
        printf("\t|");
        //总价?
        printf("%.2lf\n", bill->total_price);
        bill=bill->next;
    }
}
//不正常订单
struct sell_bill* Initiate_Bill_with_problem(void)
{
	//初始化退换货订单 
    struct sell_bill* head=(struct sell_bill*)malloc(sizeof(struct sell_bill));
    head->next=NULL;
    head->pre=NULL;
    FILE *filep=fopen("billwithproblem.txt", "r");
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
        if(fscanf(filep, "%d", &bill->status) == EOF)break;
        if(fscanf(filep, "%d", &bill->reason_num) == EOF)break;
        if(fscanf(filep, "%d", &bill->change_num) == EOF)break;
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
        fscanf(filep, "%d", &bill->id);               //客户
        bill->buyer= Find_pointer_of_client(bill->id);
        fscanf(filep, "%lf", &bill->discount_for_client);//优惠
        point->next=bill;
        bill->pre=point;
        bill->next=NULL;
        struct sell_bill* pointer=bill_pre->next;
        while(pointer!=NULL)
        {
            if(pointer->order==bill->order)
            {
                bill->related=pointer;
                break;
            }
            pointer=pointer->next;
        }
        point->next=bill;
        bill->pre=point;
        bill->next=NULL;
        struct Inventory* pointer_Inventory=Inv_head->next;
        while(pointer_Inventory!=NULL)
        {
            if(pointer_Inventory->BrandNumber==bill->number_of_brand&&pointer_Inventory->SpecificationNumber==bill->SpecificationNumber) break;
            pointer_Inventory=pointer_Inventory->next;
        }
        bill->product=pointer_Inventory;
        point=bill;
//        printf("+%d",bill->order);
    }
    if(head->next==NULL)
    {
        return head;
    }
    fclose(filep);
    return head;
}
void Exchange(struct customer* user)
{
	//换货模块 
	system("cls");
				printf("\n\n\n\n\n"); 
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t                        申请换货订单界面                 \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
    int top=Print_Bills_Of_Given_Id(user->id);
    if(top==0)
    {
        printf("\t\t\t\t\t\t\t\t\t\t因此无法进行换货操作\n");
        pau;
        return;
    }
    printf("\t\t\t\t\t\t\t\t\t\t请输入您想申请换货的订单所对应的编号:(输入0取消申请) ");
    int order;
    while(1)
    {
        order=checkNum();
        if(order<0||order>top)
        {
            printf("\t\t\t\t\t\t\t\t\t\t对不起，您输入的编号不正确，请您重新输入:");
            continue;
        }
        if(order==0)return;
        int counter=0;
	    struct sell_bill* bill=bill_pre->next;
	    while(bill!=NULL)
	    {
	        if (bill->id == user->id)
	        {
	            counter++;
	        }
	        if(counter==order)break;
	        bill=bill->next;
	    }
	    if(bill->status!=1)
	    {
	    	printf("\t\t\t\t\t\t\t\t\t\t对不起，您想申请换货的订单处于非正常状态，请您重新输入:");
            continue;
		}
        break;
    }
    printf("\t\t\t\t\t\t\t\t\t\t请问您想要换货的原因是什么？\n");
    for(int i=0;i<Exchange_Reason_num;i++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t%d.%s\n",i+1,Exchange_reason[i]);
    }
    printf("\t\t\t\t\t\t\t\t\t\t请输入您的原因所对应的编号:(输入0取消申请)");
    int reason;
    while(1)
    {
        reason=checkNum(); 
        if(reason<0||reason>Exchange_Reason_num)
        {
            printf("\t\t\t\t\t\t\t\t\t\t对不起，您输入的编号不正确，请您重新输入:");
            continue;
        }
        if(reason==0)return;
        break;
    }
    struct sell_bill* newbill=bill_with_problem->next;
    while(newbill!=NULL)newbill=newbill->next;
    int counter=0;
    struct sell_bill* bill=bill_pre->next;
    while(bill!=NULL)
    {
        if (bill->id == user->id)
        {
            counter++;
        }
        if(counter==order)break;
        bill=bill->next;
    }
    printf("\t\t\t\t\t\t\t\t\t\t请输入您要换货的数量(箱):");
    int number;
    while(1)
    {
        number=checkNum();
        if(number<=0||number>bill->number_of_packagingzise)
        {
            printf("\t\t\t\t\t\t\t\t\t\t对不起，您输入的数目不正确，请您重新输入:");
            continue;
        }
        break;
    }
    FILE *filep = fopen("billwithproblem.txt", "a");
    bill->status=2;
    bill->change_num=number;
    bill->reason_num=reason-1;
    fprintf(filep,"%d ",bill->order);
    fprintf(filep,"%d ",bill->status);
    fprintf(filep,"%d ",bill->reason_num);
    fprintf(filep,"%d ",bill->change_num);
    fprintf(filep,"%d ",bill->year);
    fprintf(filep,"%d ",bill->month);
    fprintf(filep,"%d ",bill->day);
    fprintf(filep,"%d ",bill->hour);
    fprintf(filep,"%d ",bill->minute);
    fprintf(filep,"%d ",bill->second);
    fprintf(filep,"%s ",bill->brand);
    fprintf(filep,"%d ",bill->number_of_brand);
    fprintf(filep,"%d ",bill->ProductNumber);
    fprintf(filep,"%d ",bill->SpecificationNumber);
    fprintf(filep,"%d ",bill->packagingsize);
    fprintf(filep,"%.2lf ",bill->Unit_Price);
    fprintf(filep,"%d ",bill->volume);
    fprintf(filep,"%d ",bill->number_of_packagingzise);
    fprintf(filep,"%d ",bill->total_number);
    fprintf(filep,"%.2lf ",bill->total_price);
    fprintf(filep,"%d ",bill->buyer->id);
    fprintf(filep,"%.2lf\n",bill->discount_for_client);
//    fprintf(filep);
    fclose(filep);
    printf("\t\t\t\t\t\t\t\t\t\t已成功申请换货，请等待管理员操作，给您带来不便实在抱歉，欢迎您的下次光临\n");
    FILE* filep1= fopen("bill.txt","w");
    struct sell_bill* newbill1=bill_pre->next;
    while(newbill1!=NULL)
    {
        fprintf(filep1,"%d ",newbill1->order);
	    fprintf(filep1,"%d ",newbill1->status);
	    fprintf(filep1,"%d ",newbill1->reason_num);
	    fprintf(filep1,"%d ",newbill1->change_num);
        fprintf(filep1,"%d ",newbill1->year);
        fprintf(filep1,"%d ",newbill1->month);
        fprintf(filep1,"%d ",newbill1->day);
        fprintf(filep1,"%d ",newbill1->hour);
        fprintf(filep1,"%d ",newbill1->minute);
        fprintf(filep1,"%d ",newbill1->second);
        fprintf(filep1,"%s ",newbill1->brand);
        fprintf(filep1,"%d ",newbill1->number_of_brand);
        fprintf(filep1,"%d ",newbill1->ProductNumber);
        fprintf(filep1,"%d ",newbill1->SpecificationNumber);
        fprintf(filep1,"%d ",newbill1->packagingsize);
        fprintf(filep1,"%.2lf ",newbill1->Unit_Price);
        fprintf(filep1,"%d ",newbill1->volume);
        fprintf(filep1,"%d ",newbill1->number_of_packagingzise);
        fprintf(filep1,"%d ",newbill1->total_number);
        fprintf(filep1,"%.2lf ",newbill1->total_price);
        fprintf(filep1,"%d ",newbill1->id);
        fprintf(filep1,"%.2lf\n",newbill1->discount_for_client);
        newbill1=newbill1->next;
    }
    fclose(filep1);
    bill_pre=Initiate_Bill();
    bill_with_problem=Initiate_Bill_with_problem();
    pau;
}
void Return(struct customer* user)
{
	//退货模块 
	system("cls");
				printf("\n\n\n\n\n"); 
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t                        申请退货订单界面                 \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
    int top=Print_Bills_Of_Given_Id(user->id);
    if(top==0)
    {
        printf("\t\t\t\t\t\t\t\t\t\t因此无法进行退货操作\n");
        pau;
        return;
    }
    printf("\t\t\t\t\t\t\t\t\t\t请输入您想申请退货的订单所对应的编号: (输入0取消申请)");
    int order;
    while(1)
    {
        order=checkNum();
        if(order<0||order>top)
        {
            printf("\t\t\t\t\t\t\t\t\t\t对不起，您输入的编号不正确，请您重新输入:");
            continue;
        }
        if(order==0)return;
        int counter=0;
	    struct sell_bill* bill=bill_pre->next;
	    while(bill!=NULL)
	    {
	        if (bill->id == user->id)
	        {
	            counter++;
	        }
	        if(counter==order)break;
	        bill=bill->next;
	    }
	    if(bill->status!=1)
	    {
	    	printf("\t\t\t\t\t\t\t\t\t\t对不起，您想申请退货的订单处于非正常状态，请您重新输入:");
            continue;
		}
        break;
    }
    printf("\t\t\t\t\t\t\t\t\t\t请问您想要退货的原因是什么？\n");
    for(int i=0;i<Return_Reason_num;i++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t%d.%s\n",i+1,Return_reason[i]);
    }
    printf("\t\t\t\t\t\t\t\t\t\t请输入您的原因所对应的编号:(按0取消申请)");
    int reason;
    while(1)
    {
        reason=checkNum(); 
        if(reason<0||reason>Return_Reason_num)
        {
            printf("\t\t\t\t\t\t\t\t\t\t对不起，您输入的编号不正确，请您重新输入:");
            continue;
        }
        if(reason==0)return;
        break;
    }
    struct sell_bill* newbill=bill_with_problem->next;
    while(newbill!=NULL)newbill=newbill->next;
    int counter=0;
    struct sell_bill* bill=bill_pre->next;
    while(bill!=NULL)
    {
        if (bill->id == user->id)
        {
            counter++;
        }
        if(counter==order)break;
        bill=bill->next;
    }
    FILE *filep = fopen("billwithproblem.txt", "a");
    bill->status=3;
    bill->change_num=bill->number_of_packagingzise;
    bill->reason_num=reason-1;
    fprintf(filep,"%d ",bill->order);
    fprintf(filep,"%d ",bill->status);
    fprintf(filep,"%d ",bill->reason_num);
    fprintf(filep,"%d ",bill->change_num);
    fprintf(filep,"%d ",bill->year);
    fprintf(filep,"%d ",bill->month);
    fprintf(filep,"%d ",bill->day);
    fprintf(filep,"%d ",bill->hour);
    fprintf(filep,"%d ",bill->minute);
    fprintf(filep,"%d ",bill->second);
    fprintf(filep,"%s ",bill->brand);
    fprintf(filep,"%d ",bill->number_of_brand);
    fprintf(filep,"%d ",bill->ProductNumber);
    fprintf(filep,"%d ",bill->SpecificationNumber);
    fprintf(filep,"%d ",bill->packagingsize);
    fprintf(filep,"%.2lf ",bill->Unit_Price);
    fprintf(filep,"%d ",bill->volume);
    fprintf(filep,"%d ",bill->number_of_packagingzise);
    fprintf(filep,"%d ",bill->total_number);
    fprintf(filep,"%.2lf ",bill->total_price);
    fprintf(filep,"%d ",bill->id);
    fprintf(filep,"%.2lf\n",bill->discount_for_client);
//    fprintf(filep);
    fclose(filep);
    printf("\t\t\t\t\t\t\t\t\t\t已成功申请退货，请等待管理员操作，给您带来不便实在抱歉，欢迎您的下次光临\n");
    FILE* filep1= fopen("bill.txt","w");
    struct sell_bill* newbill1=bill_pre->next;
    while(newbill1!=NULL)
    {
        fprintf(filep1,"%d ",newbill1->order);
	    fprintf(filep1,"%d ",newbill1->status);
	    fprintf(filep1,"%d ",newbill1->reason_num);
	    fprintf(filep1,"%d ",newbill1->change_num);
        fprintf(filep1,"%d ",newbill1->year);
        fprintf(filep1,"%d ",newbill1->month);
        fprintf(filep1,"%d ",newbill1->day);
        fprintf(filep1,"%d ",newbill1->hour);
        fprintf(filep1,"%d ",newbill1->minute);
        fprintf(filep1,"%d ",newbill1->second);
        fprintf(filep1,"%s ",newbill1->brand);
        fprintf(filep1,"%d ",newbill1->number_of_brand);
        fprintf(filep1,"%d ",newbill1->ProductNumber);
        fprintf(filep1,"%d ",newbill1->SpecificationNumber);
        fprintf(filep1,"%d ",newbill1->packagingsize);
        fprintf(filep1,"%.2lf ",newbill1->Unit_Price);
        fprintf(filep1,"%d ",newbill1->volume);
        fprintf(filep1,"%d ",newbill1->number_of_packagingzise);
        fprintf(filep1,"%d ",newbill1->total_number);
        fprintf(filep1,"%.2lf ",newbill1->total_price);
        fprintf(filep1,"%d ",newbill1->id);
        fprintf(filep1,"%.2lf\n",newbill1->discount_for_client);
        newbill1=newbill1->next;
    }
    fclose(filep1);
    bill_pre=Initiate_Bill();
    bill_with_problem=Initiate_Bill_with_problem();
    pau;
}
void Check_Bills_with_problem(void)
{
	//退换货查看订单 
    if(bill_with_problem->next == NULL)
    {
        printf("\t\t\t\t\t很抱歉，没有请求退换货的订单\n");
        return;
    }
    printf("———————————————————————————————————————————————————————————————————————————————————————————————————————————————\n"
           "编号\t|申请状态|申请原因\t\t\t|交易时间\t\t|商品品牌\t|商品名称\t|包装大小(瓶/箱)\t|涉及数目(箱)\t|买家\t\t|买家等级\t\n");
    //
    struct sell_bill* bill=bill_with_problem->next;
    int count=0;
    while(bill!=NULL)
    {
    	if(bill->status==4||bill->status==5||bill->status==6)
    	{
    		bill=bill->next;
    		continue;
		}
        count++;
        //订单编号
        printf("%d\t", count);
        printf("|");
        //订单状态
        switch(bill->status)
        {
            case(2):
            {
                printf("申请换货");
                printf("|");
                break;
            }
            case(3):
            {
                printf("申请退货");
                printf("|");
                break;
            }
        }
        //申请原因
        switch(bill->status)
        {
            case(2):
            {	
                printf("%-30s",Exchange_reason[bill->reason_num]);
                printf("|");
                break;
            }
            case(3):
            {
                printf("%-30s",Return_reason[bill->reason_num]);
                printf("|");
                break;
            }
        }
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
        //包装大小?
        printf("%d", bill->packagingsize);
        printf("\t\t\t|");
        //出售个数
        printf("%d", bill->number_of_packagingzise);
        char numberofpackagingsize[20];
        sprintf(numberofpackagingsize, "%d",bill->number_of_packagingzise);
        for (int i = 1; i <= 2 - (strlen(numberofpackagingsize) +1) / 8; i++)printf("\t");
        printf("|");
        if(bill->buyer!=NULL)
        {
        //买家?
        printf("%d", bill->id);
        char user_id[20];
        sprintf(user_id, "%d",bill->id);
        for (int i = 1; i <= 2 - (strlen(user_id)+1) / 8; i++)printf("\t");
        printf("|");
        //买家等级?
        printf("%d", bill->buyer->level);
        printf("\t\t\n");
		}
        else 
        {
        	printf("该买家已被删除\t|");
        	printf("该买家已被删除\t\n");
		}
		bill=bill->next;
    }
}
void writebill(){
	//写订单 
	FILE* filep= fopen("bill.txt","w");
    struct sell_bill* newbill=bill_pre->next;
    int count=0;
    while(newbill!=NULL)
    {
        fprintf(filep,"%d ",++count);
	    fprintf(filep,"%d ",newbill->status);
	    fprintf(filep,"%d ",newbill->reason_num);
	    fprintf(filep,"%d ",newbill->change_num);
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
        fprintf(filep,"%d ",newbill->id);
        fprintf(filep,"%.2lf\n",newbill->discount_for_client);
        newbill=newbill->next;
    }
    fclose(filep);
}

void writeproblembill(){
	//写有问题的订单 
	struct sell_bill* bill=bill_with_problem->next;
		FILE *filep = fopen("billwithproblem.txt", "w");
	while(bill)
	{
		fprintf(filep,"%d ",bill->order);
	    fprintf(filep,"%d ",bill->status);
	    fprintf(filep,"%d ",bill->reason_num);
	    fprintf(filep,"%d ",bill->change_num);
	    fprintf(filep,"%d ",bill->year);
	    fprintf(filep,"%d ",bill->month);
	    fprintf(filep,"%d ",bill->day);
	    fprintf(filep,"%d ",bill->hour);
	    fprintf(filep,"%d ",bill->minute);
	    fprintf(filep,"%d ",bill->second);
	    fprintf(filep,"%s ",bill->brand);
	    fprintf(filep,"%d ",bill->number_of_brand);
	    fprintf(filep,"%d ",bill->ProductNumber);
	    fprintf(filep,"%d ",bill->SpecificationNumber);
	    fprintf(filep,"%d ",bill->packagingsize);
	    fprintf(filep,"%.2lf ",bill->Unit_Price);
	    fprintf(filep,"%d ",bill->volume);
	    fprintf(filep,"%d ",bill->number_of_packagingzise);
	    fprintf(filep,"%d ",bill->total_number);
	    fprintf(filep,"%.2lf ",bill->total_price);
	    fprintf(filep,"%d ",bill->id);
	    fprintf(filep,"%.2lf\n",bill->discount_for_client);
	    bill = bill->next;
	}
    fclose(filep);
}


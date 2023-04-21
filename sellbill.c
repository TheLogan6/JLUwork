#include"sellbill.h"
#include"customer.h"
extern double total_cost;
extern double total_income;
extern double current_money;
//��������
struct customer* Find_pointer_of_client(int id)
{
	//�ҵ�����id����Ӧ���û� 
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
	//��ʼ��������Ϣ 
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
    int nth_bill=0;//�ڼ��ʶ���
    while(1)
    {
        nth_bill++;
        struct sell_bill* bill=(struct sell_bill*)malloc(sizeof(struct sell_bill));
        if(fscanf(filep, "%d", &bill->order) == EOF)break;
        if(fscanf(filep, "%d", &bill->status) == EOF)break;
        if(fscanf(filep, "%d", &bill->reason_num) == EOF)break;
        if(fscanf(filep, "%d", &bill->change_num) == EOF)break;
        if(fscanf(filep, "%d%d%d%d%d%d", &bill->year, &bill->month, &bill->day, &bill->hour, &bill->minute, &bill->second) == EOF)break;
        fscanf(filep, "%s", bill->brand);                //Ʒ��
        fscanf(filep, "%d", &bill->number_of_brand);      //Ʒ�Ʊ��
        fscanf(filep, "%d", &bill->ProductNumber);       // ��Ʒ���
        fscanf(filep, "%d", &bill->SpecificationNumber); //�����
        fscanf(filep, "%d", &bill->packagingsize);       //��װ��С
        fscanf(filep, "%lf", &bill->Unit_Price);         //���۵���
        fscanf(filep, "%d", &bill->volume);              //��Ʒ����
        fscanf(filep, "%d", &bill->number_of_packagingzise);//�����װ�����˶�����
        fscanf(filep, "%d", &bill->total_number);        //����������
        fscanf(filep, "%lf", &bill->total_price);        //�ܼ�
//        int id_of_client;
        fscanf(filep, "%d", &bill->id);               //�ͻ�
        bill->buyer= Find_pointer_of_client(bill->id);
        fscanf(filep, "%lf", &bill->discount_for_client);//�Ż�
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
	//���ո�������ƷƷ�Ƹ��¶������� 
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
	//���ո�������Ʒ��Ÿ��¶������� 
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
	//ѡ������Ʒ������ 
    printf("\t\t\t\t\t��������Ҫ�������%dƿ/��Ĳ�Ʒ:", newbill->packagingsize);
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
			printf("\t\t\t\t\t�Բ���������Ĺ�����Ŀ����ȷ��������������:");
			continue;
		}
        if(newbill->number_of_packagingzise>pointer_Inventory->Reserve)
        {
            printf("\t\t\t\t\t�Բ���������Ĺ�����Ŀ������Ʒ��棬������������:");
            continue;
        }
        if(newbill->number_of_packagingzise<=0)
        {
            printf("\t\t\t\t\t�Բ���������Ĺ�����Ŀ����ȷ��������������:");
            continue;
        }
        break;
    }
    newbill->total_number = newbill->packagingsize * newbill->number_of_packagingzise;
    newbill->total_price = newbill->Unit_Price * newbill->number_of_packagingzise;
    newbill->buyer=user;
    printf("\t\t\t\t\t���ù˿�%s,��������%d����Ա��������Ҫ֧���ö�����", user->name, user->level);
    //�����ǻ�Ա�Ż�
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
    printf("%d%%�������Ҫ֧��%.2lfԪ", discount,newbill->total_price);
//    user->point+=newbill->total_price;
}
int Sell_confirm(struct sell_bill* newbill,struct customer* user)
{
	//ȷ�������Ĺ���ʽ 
    bool flag=false;
    while(flag==false)
    {
        //system("");
        printf("\t\t\t\t\t��ѡ������֧����ʽ��\n");
        printf("\t\t\t\t\t1.�ֽ�֧��\n");
        printf("\t\t\t\t\t2.���֧��\n");
        printf("\t\t\t\t\t3.���빺�ﳵ\n");
        printf("\t\t\t\t\t4.ȡ������\n");
        printf("\t\t\t\t\t����������֧����ʽ����Ӧ�ı�ţ�");
        int buychoice;
        while(1)
        {
            buychoice=checkNum();
            if(buychoice<=0||buychoice>4)
            {
                printf("\n\t\t\t\t\t�Բ���������ı�Ų���ȷ��������������:");
                continue;
            }
            break;
        }
        if(buychoice==1)
        {
            printf("\t\t\t\t\t���ѳɹ�����лл���Ļݹ�");
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
                printf("\t\t\t\t\t���ѳɹ�����лл���Ļݹ�");
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
                printf("\t\t\t\t\t�Բ�����������,������ѡ����ϵ����Ա��������ֵ\n");
                continue;
            }
        }
        if(buychoice==3)  //���빺�ﳵ 
        {
			printf("\t\t\t\t\t�ڴ�������һ�ι���");
			addShoppingCart(&user->cart,newbill->number_of_packagingzise,user->id,newbill->Unit_Price,newbill->number_of_brand,newbill->ProductNumber,newbill->SpecificationNumber);
			writeShoppingCart(&L);
            newbill->status=6;
            flag=true;
            continue;
        }
        if(buychoice==4)
        {
            printf("\t\t\t\t\t�ڴ�������һ�ι���\n");
            newbill->status=0;
            flag=true;
            continue;
        }
        return buychoice;
    }
}
void sell_save(struct sell_bill* newbill)
{
	//���涩�� 
	
    FILE *filep = fopen("bill.txt", "a");time_t timep;
    struct tm *timenow;
    time(&timep);
    timenow = gmtime(&timep);
    struct sell_bill *pointer_of_all_bills = bill_pre->next;
    if (pointer_of_all_bills == NULL)//������ǵ�һ�ʶ���
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
//       	pau;      ��ɾ���� 
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
	//��ѯ����Ʒ�ƵĶ�����Ϣ 
	printf("\t\t\t\t\t\t\t\t\t\t�������ѯ�ĸ�Ʒ�ƵĶ���\n");
    for(int i=1;i<=Number_Of_Brand;i++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t%d.%s\n",i,code[i][0]);
    }
    printf("\t\t\t\t\t\t\t\t\t\t��������Ҫ��ѯ��Ʒ�Ʊ��:(����0ȡ����ѯ)");
    int number_of_brand;
    while(1)
    {
        number_of_brand=checkNum();
        if(number_of_brand==0)return;
        if(number_of_brand<0||number_of_brand>Number_Of_Brand)
        {
            printf("\t\t\t\t\t\t\t\t\t\t�Բ����������Ʒ�Ʊ�Ų���ȷ��������������:");
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
                printf("\n��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n"
                       "���\t|����״̬\t\t|����ʱ��\t\t|��ƷƷ��\t|��Ʒ����\t|��Ʒ����(ml)\t|��װ��С(ƿ/��)\t|���۵���\t|�۳���Ŀ(��)\t|����(ƿ)\t|���\t\t|��ҵȼ�\t|�Ż�\t|�ܼ�(Ԫ)\t\n");
            //�������
            printf("%d\t", count);
            printf("|");
            //����״̬
            switch(bill->status)
            {
            	case(0):
            {
                printf("����ȡ��\t\t");
                printf("|");
                break;
            }
                case(1):
                {
                    printf("��������\t\t");
                    printf("|");
                    break;
                }
                case(2):
                {
                    printf("���뻻����\t\t");
                    printf("|");
                    break;
                }
                case(3):
                {
                    printf("�����˻���\t\t");
                    printf("|");
                    break;
                }
                case(4):
                {
                    printf("�ѻ���\t\t\t");
                    printf("|");
                    break;
                }
                case(5):
                {
                    printf("���˻�\t\t\t");
                    printf("|");
                    break;
                }
            }
            //����ʱ��?
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
            //��ƷƷ��?
            printf("%s", bill->brand);
            for (int i = 1; i <= 2 - (strlen(bill->brand) +1) / 8; i++)printf("\t");
            printf("|");
            //��Ʒ����?
            printf("%s", code[bill->number_of_brand][bill->ProductNumber]);
            for (int i = 1; i <= 3 -(strlen(code[bill->number_of_brand][bill->ProductNumber]) * 2 +2) / 8; i++)printf("\t");
            printf("|");
            //��Ʒ����?
            printf("%d", bill->volume);
            printf("\t\t|");
            //��װ��С?
            printf("%d", bill->packagingsize);
            printf("\t\t\t|");
            //���۵���?
            printf("%.2lf", bill->Unit_Price);
            char Unit_Price[20];
            sprintf(Unit_Price, "%.2lf", bill->Unit_Price);
//        int n=strlen(Unit_Price);
            for (int i = 1; i <= 2 - (strlen(Unit_Price) +1) / 8; i++)printf("\t");
            printf("|");
            //���۸���
            printf("%d", bill->number_of_packagingzise);
            char numberofpackagingsize[20];
            sprintf(numberofpackagingsize, "%d",bill->number_of_packagingzise);
            for (int i = 1; i <= 2 - (strlen(numberofpackagingsize) +1) / 8; i++)printf("\t");
            printf("|");
            //����?
            printf("%d", bill->total_number);
            char total_number[20];
            sprintf(total_number, "%d", bill->total_number);
            for (int i = 1; i <= 2 - (strlen(total_number) +1) / 8; i++)printf("\t");
            printf("|");
            if(bill->buyer!=NULL)
            {
            //���?
            printf("%d", bill->id);
	        char user_id[20];
	        sprintf(user_id, "%d",bill->id);
	        for (int i = 1; i <= 2 - (strlen(user_id)+1) / 8; i++)printf("\t");
	        printf("|");
            //��ҵȼ�?
            printf("%d", bill->buyer->level);
            printf("\t\t|");
			}
            else 
            {
            	printf("������ѱ�ɾ��\t|");
            	printf("������ѱ�ɾ��\t|");
			}
            //�Ż�?
            printf("%.2lf", bill->discount_for_client);
            printf("\t|");
            //�ܼ�?
            printf("%.2lf\n", bill->total_price);
        }
        bill = bill->next;
    }
    if(count==0)
	{
		printf("\t\t\t\t\t\t\t\t\t\t�Բ��𣬸�Ʒ�ƻ�û���κ����۶���\n");
		pau; 
        return;
	 } 
    pau;
}
int Scanf_ID(void)
{
	//������Ҫ��ѯ���û�ID 
    printf("\t\t\t\t\t\t\t\t\t\t��������Ҫ��ѯ���û�ID��(����0ȡ����ѯ)");
    int ID_of_client;
    while(1)
    {
        ID_of_client=checkNum();
        if(ID_of_client==0) return ID_of_client;
        if(ID_of_client<10000||ID_of_client>99999)
        {
            printf("\t\t\t\t\t\t\t\t\t\t�Բ�����������û�ID����ȷ��������������:");
            continue;
        }
        if(Find_pointer_of_client(ID_of_client)==NULL)
        {
            printf("\t\t\t\t\t\t\t\t\t\t�Բ�����������û������ڣ�������������:");
            continue;
        }
        break;
    }
    return ID_of_client;
}
int Print_Bills_Of_Given_Id(int ID_of_client)
{//�����û�idȥ��ѯ���û������ж��� 
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
                printf("\n��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n"
                       "���\t|����״̬\t\t|����ʱ��\t\t|��ƷƷ��\t|��Ʒ����\t|��Ʒ����(ml)\t|��װ��С(ƿ/��)\t|���۵���\t|�۳���Ŀ(��)\t|����(ƿ)\t|���\t\t|��ҵȼ�\t|�Ż�\t|�ܼ�(Ԫ)\t\n");
            //���
            printf("%d\t", count);
            printf("|");
            //����״̬
            switch(bill->status)
            {
	            	case(0):
	            {
	                printf("����ȡ��\t\t");
	                printf("|");
	                break;
	            }
                case(1):
                {
                    printf("��������\t\t");
                    printf("|");
                    break;
                }
                case(2):
                {
                    printf("���뻻����\t\t");
                    printf("|");
                    break;
                }
                case(3):
                {
                    printf("�����˻���\t\t");
                    printf("|");
                    break;
                }
                case(4):
                {
                    printf("�ѻ���\t\t\t");
                    printf("|");
                    break;
                }
                case(5):
                {
                    printf("���˻�\t\t\t");
                    printf("|");
                    break;
                }
            }
            //����ʱ��?
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
            //��ƷƷ��?
            printf("%s", bill->brand);
            for (int i = 1; i <= 2 - (strlen(bill->brand) +1) / 8; i++)printf("\t");
            printf("|");
            //��Ʒ����?
            printf("%s", code[bill->number_of_brand][bill->ProductNumber]);
            for (int i = 1; i <= 3 -(strlen(code[bill->number_of_brand][bill->ProductNumber]) * 2 +2) / 8; i++)printf("\t");
            printf("|");
            //��Ʒ����?
            printf("%d", bill->volume);
            printf("\t\t|");
            //��װ��С?
            printf("%d", bill->packagingsize);
            printf("\t\t\t|");
            //���۵���?
            printf("%.2lf", bill->Unit_Price);
            char Unit_Price[20];
            sprintf(Unit_Price, "%.2lf", bill->Unit_Price);
//        int n=strlen(Unit_Price);
            for (int i = 1; i <= 2 - (strlen(Unit_Price) +1) / 8; i++)printf("\t");
            printf("|");
            //���۸���
            printf("%d", bill->number_of_packagingzise);
            char numberofpackagingsize[20];
            sprintf(numberofpackagingsize, "%d",bill->number_of_packagingzise);
            for (int i = 1; i <= 2 - (strlen(numberofpackagingsize) +1) / 8; i++)printf("\t");
            printf("|");
            //����?
            printf("%d", bill->total_number);
            char total_number[20];
            sprintf(total_number, "%d", bill->total_number);
            for (int i = 1; i <= 2 - (strlen(total_number) +1) / 8; i++)printf("\t");
            printf("|");
            if(bill->buyer!=NULL)
	        {
	        //���?
	        printf("%d", bill->id);
	        char user_id[20];
	        sprintf(user_id, "%d",bill->id);
	        for (int i = 1; i <= 2 - (strlen(user_id)+1) / 8; i++)printf("\t");
	        printf("|");
	        //��ҵȼ�?
	        printf("%d", bill->buyer->level);
	        printf("\t\t|");
			}
	        else 
	        {
	        	printf("������ѱ�ɾ��\t|");
	        	printf("������ѱ�ɾ��\t|");
			}
	            //�Ż�?
	            printf("%.2lf", bill->discount_for_client);
	            printf("\t|");
	            //�ܼ�?
	            printf("%.2lf\n", bill->total_price);
	        }
        bill = bill->next;
    }
    if(count==0)
    {
        printf("\t\t\t\t\t\t\t\t\t\t�Բ��𣬸��û�û����ʷ����\n");
        return 0;
    }
    return count;
}
void Search_For_The_Bills_Of_Given_Data(void)
{
	//ȷ����ѯ���������� 
	system("cls");
				printf("\n\n\n\n\n"); 
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t                        ��ѯ�ض������Ľ���                 \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
    printf("\n\t\t\t\t\t\t\t\t\t\t�������ѯʲô������\n");
    printf("\t\t\t\t\t\t\t\t\t\t1.�йظ�����ƷƷ�ƵĶ���\n");
    printf("\t\t\t\t\t\t\t\t\t\t2.�й��ض���ҵĶ���\n");
    printf("\t\t\t\t\t\t\t\t\t\t��������Ҫ��ѯ�Ķ������ͱ��(1-2):(����0ȡ����ѯ)");
    int kind_of_bill;
    while(1)
    {
        kind_of_bill=checkNum();
        if(kind_of_bill==0)return;
        if(kind_of_bill<0||kind_of_bill>2)
        {
            printf("\t\t\t\t\t\t\t\t\t\t�Բ���������ı�Ų���ȷ��������������\n");
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
	//���ն������Ѱ�ҵ�ָ������ 
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
	//ɾ������ 
	system("cls");
				printf("\n\n\n\n\n"); 
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t                        ɾ�������Ľ���                 \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
    if(bill_pre->next == NULL)
    {
        printf("\n\t\t\t\t\t�ܱ�Ǹ��û����ʷ����\n");
        return 1;
    }
    Check_Bills();
    printf("\t\t\t\t\t��������Ҫɾ���Ķ������(����0��ȡ��ɾ������):");
   	struct sell_bill* pointer_of_bill=bill_pre->next;
    int order_of_bill;
    while(1)
    {
        order_of_bill=checkNum();
        if(order_of_bill<0)
        {
            printf("\t\t\t\t\t�Բ���������Ķ�����Ų���ȷ��������������:");
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
            printf("\t\t\t\t\t�Բ�������ɾ���Ķ��������ڣ�������������:");
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
    printf("\t\t\t\t\tɾ���ɹ�\n");
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
		    	printf("\t\t\t\t\t\t\t\t\t\t                        ɾ�������Ľ���                 \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
    bill_pre=Initiate_Bill();
    printf("\t\t\t\t\t\t\t\t\t\tɾ���ɹ������ʷ����Ϊ��\n");
    Check_Bills();
    return 1;
}
void Check_Bills(void)
{
	//�鿴���ж��� 
    if(bill_pre->next == NULL)
    {
        printf("\n\t\t\t\t\t�ܱ�Ǹ��û����ʷ����\n");
        return;
    }
    printf("\n��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n"
           "�������|����״̬\t\t|����ʱ��\t\t|��ƷƷ��\t|��Ʒ����\t|��Ʒ����(ml)\t|��װ��С(ƿ/��)\t|���۵���\t|�۳���Ŀ(��)\t|����(ƿ)\t|���\t\t|��ҵȼ�\t|�Ż�\t|�ܼ�(Ԫ)\t\n");
    //
    struct sell_bill* bill=bill_pre->next;
    while(bill!=NULL)
    {
    	if(bill->status==6)
        	{
        		bill=bill->next;
        		continue;
			}
        //�������
        printf("%d\t", bill->order);
        printf("|");
        //����״̬
        switch(bill->status)
        {
        	case(0):
            {
                printf("����ȡ��\t\t");
                printf("|");
                break;
            }
            case(1):
            {
                printf("��������\t\t");
                printf("|");
                break;
            }
            case(2):
            {
                printf("���뻻����\t\t");
                printf("|");
                break;
            }
            case(3):
            {
                printf("�����˻���\t\t");
                printf("|");
                break;
            }
            case(4):
            {
                printf("�ѻ���\t\t\t");
                printf("|");
                break;
            }
            case(5):
            {
                printf("���˻�\t\t\t");
                printf("|");
                break;
            }
        }
        //����ʱ��?
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
        //��ƷƷ��?
        printf("%s", bill->brand);
        for (int i = 1; i <= 2 - (strlen(bill->brand) +1) / 8; i++)printf("\t");
        printf("|");
        //��Ʒ����?
        printf("%s", code[bill->number_of_brand][bill->ProductNumber]);
        for (int i = 1; i <= 3 -(strlen(code[bill->number_of_brand][bill->ProductNumber]) * 2 +2) / 8; i++)printf("\t");
        printf("|");
        //��Ʒ����?
        printf("%d", bill->volume);
        printf("\t\t|");
        //��װ��С?
        printf("%d", bill->packagingsize);
        printf("\t\t\t|");
        //���۵���?
        printf("%.2lf", bill->Unit_Price);
        char Unit_Price[20];
        sprintf(Unit_Price, "%.2lf", bill->Unit_Price);
//        int n=strlen(Unit_Price);
        for (int i = 1; i <= 2 - (strlen(Unit_Price) +1) / 8; i++)printf("\t");
        printf("|");
        //���۸���
        printf("%d", bill->number_of_packagingzise);
        char numberofpackagingsize[20];
        sprintf(numberofpackagingsize, "%d",bill->number_of_packagingzise);
        for (int i = 1; i <= 2 - (strlen(numberofpackagingsize) +1) / 8; i++)printf("\t");
        printf("|");
        //����?
        printf("%d", bill->total_number);
        char total_number[20];
        sprintf(total_number, "%d", bill->total_number);
        for (int i = 1; i <= 2 - (strlen(total_number) +1) / 8; i++)printf("\t");
        printf("|");
        if(bill->buyer!=NULL)
        {
        //���?
        printf("%d", bill->id);
        char user_id[20];
        sprintf(user_id, "%d",bill->id);
        for (int i = 1; i <= 2 - (strlen(user_id)+1) / 8; i++)printf("\t");
        printf("|");
        //��ҵȼ�?
        printf("%d", bill->buyer->level);
        printf("\t\t|");
		}
        else 
        {
        	printf("������ѱ�ɾ��\t|");
        	printf("������ѱ�ɾ��\t|");
		}
        //�Ż�?
        printf("%.2lf", bill->discount_for_client);
        printf("\t|");
        //�ܼ�?
        printf("%.2lf\n", bill->total_price);
        bill=bill->next;
    }
}
//����������
struct sell_bill* Initiate_Bill_with_problem(void)
{
	//��ʼ���˻������� 
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
    int nth_bill=0;//�ڼ��ʶ���
    while(1)
    {
        nth_bill++;
        struct sell_bill* bill=(struct sell_bill*)malloc(sizeof(struct sell_bill));
        if(fscanf(filep, "%d", &bill->order) == EOF)break;
        if(fscanf(filep, "%d", &bill->status) == EOF)break;
        if(fscanf(filep, "%d", &bill->reason_num) == EOF)break;
        if(fscanf(filep, "%d", &bill->change_num) == EOF)break;
        if(fscanf(filep, "%d%d%d%d%d%d", &bill->year, &bill->month, &bill->day, &bill->hour, &bill->minute, &bill->second) == EOF)break;
        fscanf(filep, "%s", bill->brand);                //Ʒ��
        fscanf(filep, "%d", &bill->number_of_brand);      //Ʒ�Ʊ��
        fscanf(filep, "%d", &bill->ProductNumber);       // ��Ʒ���
        fscanf(filep, "%d", &bill->SpecificationNumber); //�����
        fscanf(filep, "%d", &bill->packagingsize);       //��װ��С
        fscanf(filep, "%lf", &bill->Unit_Price);         //���۵���
        fscanf(filep, "%d", &bill->volume);              //��Ʒ����
        fscanf(filep, "%d", &bill->number_of_packagingzise);//�����װ�����˶�����
        fscanf(filep, "%d", &bill->total_number);        //����������
        fscanf(filep, "%lf", &bill->total_price);        //�ܼ�
        fscanf(filep, "%d", &bill->id);               //�ͻ�
        bill->buyer= Find_pointer_of_client(bill->id);
        fscanf(filep, "%lf", &bill->discount_for_client);//�Ż�
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
	//����ģ�� 
	system("cls");
				printf("\n\n\n\n\n"); 
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t                        ���뻻����������                 \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
    int top=Print_Bills_Of_Given_Id(user->id);
    if(top==0)
    {
        printf("\t\t\t\t\t\t\t\t\t\t����޷����л�������\n");
        pau;
        return;
    }
    printf("\t\t\t\t\t\t\t\t\t\t�������������뻻���Ķ�������Ӧ�ı��:(����0ȡ������) ");
    int order;
    while(1)
    {
        order=checkNum();
        if(order<0||order>top)
        {
            printf("\t\t\t\t\t\t\t\t\t\t�Բ���������ı�Ų���ȷ��������������:");
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
	    	printf("\t\t\t\t\t\t\t\t\t\t�Բ����������뻻���Ķ������ڷ�����״̬��������������:");
            continue;
		}
        break;
    }
    printf("\t\t\t\t\t\t\t\t\t\t��������Ҫ������ԭ����ʲô��\n");
    for(int i=0;i<Exchange_Reason_num;i++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t%d.%s\n",i+1,Exchange_reason[i]);
    }
    printf("\t\t\t\t\t\t\t\t\t\t����������ԭ������Ӧ�ı��:(����0ȡ������)");
    int reason;
    while(1)
    {
        reason=checkNum(); 
        if(reason<0||reason>Exchange_Reason_num)
        {
            printf("\t\t\t\t\t\t\t\t\t\t�Բ���������ı�Ų���ȷ��������������:");
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
    printf("\t\t\t\t\t\t\t\t\t\t��������Ҫ����������(��):");
    int number;
    while(1)
    {
        number=checkNum();
        if(number<=0||number>bill->number_of_packagingzise)
        {
            printf("\t\t\t\t\t\t\t\t\t\t�Բ������������Ŀ����ȷ��������������:");
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
    printf("\t\t\t\t\t\t\t\t\t\t�ѳɹ����뻻������ȴ�����Ա������������������ʵ�ڱ�Ǹ����ӭ�����´ι���\n");
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
	//�˻�ģ�� 
	system("cls");
				printf("\n\n\n\n\n"); 
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t                        �����˻���������                 \n");
		    	printf("\t\t\t\t\t\t\t\t\t\t ------------------------------------------------------------------ \n");
    int top=Print_Bills_Of_Given_Id(user->id);
    if(top==0)
    {
        printf("\t\t\t\t\t\t\t\t\t\t����޷������˻�����\n");
        pau;
        return;
    }
    printf("\t\t\t\t\t\t\t\t\t\t���������������˻��Ķ�������Ӧ�ı��: (����0ȡ������)");
    int order;
    while(1)
    {
        order=checkNum();
        if(order<0||order>top)
        {
            printf("\t\t\t\t\t\t\t\t\t\t�Բ���������ı�Ų���ȷ��������������:");
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
	    	printf("\t\t\t\t\t\t\t\t\t\t�Բ������������˻��Ķ������ڷ�����״̬��������������:");
            continue;
		}
        break;
    }
    printf("\t\t\t\t\t\t\t\t\t\t��������Ҫ�˻���ԭ����ʲô��\n");
    for(int i=0;i<Return_Reason_num;i++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t%d.%s\n",i+1,Return_reason[i]);
    }
    printf("\t\t\t\t\t\t\t\t\t\t����������ԭ������Ӧ�ı��:(��0ȡ������)");
    int reason;
    while(1)
    {
        reason=checkNum(); 
        if(reason<0||reason>Return_Reason_num)
        {
            printf("\t\t\t\t\t\t\t\t\t\t�Բ���������ı�Ų���ȷ��������������:");
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
    printf("\t\t\t\t\t\t\t\t\t\t�ѳɹ������˻�����ȴ�����Ա������������������ʵ�ڱ�Ǹ����ӭ�����´ι���\n");
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
	//�˻����鿴���� 
    if(bill_with_problem->next == NULL)
    {
        printf("\t\t\t\t\t�ܱ�Ǹ��û�������˻����Ķ���\n");
        return;
    }
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n"
           "���\t|����״̬|����ԭ��\t\t\t|����ʱ��\t\t|��ƷƷ��\t|��Ʒ����\t|��װ��С(ƿ/��)\t|�漰��Ŀ(��)\t|���\t\t|��ҵȼ�\t\n");
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
        //�������
        printf("%d\t", count);
        printf("|");
        //����״̬
        switch(bill->status)
        {
            case(2):
            {
                printf("���뻻��");
                printf("|");
                break;
            }
            case(3):
            {
                printf("�����˻�");
                printf("|");
                break;
            }
        }
        //����ԭ��
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
        //����ʱ��?
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
        //��ƷƷ��?
        printf("%s", bill->brand);
        for (int i = 1; i <= 2 - (strlen(bill->brand) +1) / 8; i++)printf("\t");
        printf("|");
        //��Ʒ����?
        printf("%s", code[bill->number_of_brand][bill->ProductNumber]);
        for (int i = 1; i <= 3 -(strlen(code[bill->number_of_brand][bill->ProductNumber]) * 2 +2) / 8; i++)printf("\t");
        printf("|");
        //��װ��С?
        printf("%d", bill->packagingsize);
        printf("\t\t\t|");
        //���۸���
        printf("%d", bill->number_of_packagingzise);
        char numberofpackagingsize[20];
        sprintf(numberofpackagingsize, "%d",bill->number_of_packagingzise);
        for (int i = 1; i <= 2 - (strlen(numberofpackagingsize) +1) / 8; i++)printf("\t");
        printf("|");
        if(bill->buyer!=NULL)
        {
        //���?
        printf("%d", bill->id);
        char user_id[20];
        sprintf(user_id, "%d",bill->id);
        for (int i = 1; i <= 2 - (strlen(user_id)+1) / 8; i++)printf("\t");
        printf("|");
        //��ҵȼ�?
        printf("%d", bill->buyer->level);
        printf("\t\t\n");
		}
        else 
        {
        	printf("������ѱ�ɾ��\t|");
        	printf("������ѱ�ɾ��\t\n");
		}
		bill=bill->next;
    }
}
void writebill(){
	//д���� 
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
	//д������Ķ��� 
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


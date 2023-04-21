#include"manager.h" 
extern Inventory* Inv_head;
extern Gift* Gift_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][10]; 
extern char passwordans[20]; 
extern int total_brand;
extern struct sell_bill* bill_pre;            //有哨位节点 
extern struct sell_bill* bill_with_problem;  // 有哨位节点 
extern supplierlist L2;
extern productlistin L1;//进货单
extern double total_cost;
extern double total_income;
extern double current_money;
//   开始进货 
void Restock(){
	Sou_head = ReadSource();
	while(1)
	{
		system("cls");
		printf("\n"); 
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t                进货界面                 \n");
    	printf("\t\t\t\t\t     (在品牌处输入0可以返回上一个界面)   \n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
		PrintSource(Sou_head);
		printf("\n\t\t\t\t请选择你需要购买的品牌：");
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		ChooseBrand = checkNum();
		if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		if(ChooseBrand == 0) return ;
		printf("\n\t\t\t\t请选择你要批发的产品编号：");
		ChooseProduct = checkNum();
		int maxproduct = countSpecification_sou(ChooseBrand);
		if(ChooseProduct == -1 || ChooseProduct > maxproduct){
			RefreshPage();
			continue;
		}
		else if(ChooseProduct == 0) return;
		int  buy_amount;
		char buy_amount_s[5]; 
		printf("\n\t\t\t\t请选择你要批发的数量(单次不得超过100箱 不得少于10箱)：");

		buy_amount = checkNum();
		if(buy_amount == -1 || buy_amount > 100 || buy_amount < 10){
			RefreshPage();
			continue;
		}
		else if(buy_amount == 0) return;
		ProductSource* tar_sou = FindSource(ChooseBrand, ChooseProduct); //找到货源目标 
		if(tar_sou == NULL){
			RefreshPage();
			continue;
		}
		double buy_money;
		buy_money = buy_amount * tar_sou->Price_sou;
		
		printf("\t\t\t\t\t --------------------------------------- \n");
		//加入订单
		productin * newbill = (productin*)malloc(sizeof(productin));
		strcpy(newbill->commodity_name, tar_sou->DrinksBrand_sou);
		newbill->commodity_id = tar_sou->SpecificationNumber_sou;
		newbill->commodity_packagenum = tar_sou->packagingsize_sou;
		newbill->commodity_price = tar_sou->Price_sou;
		newbill->commodity_number = buy_amount;
		newbill->commodity_volume = tar_sou->volume_sou;
		newbill->next  = NULL;
		newbill->provider = choosesupplier2();
		newbill->sum_price = buy_money + newbill->provider->transport_cost;
		time_t timep;
		struct tm *p;
	    time(&timep);
	    p = localtime(&timep); //取得当地具体时间
	    char temp[50];
	    temp[0] = (1900+p->tm_year)/1000 - 0 +'0';
	    temp[1] = ((1900+p->tm_year)%1000)/100- 0 +'0';
	    temp[2] = (((1900+p->tm_year)%100)/10)- 0 +'0';
	    temp[3] = (1900+p->tm_year)%10- 0 +'0';
	    temp[4] = (1+p->tm_mon)/10- 0 +'0';
	    temp[5] = (1+p->tm_mon)%10- 0 +'0';
	    temp[6] = (p->tm_mday)/10- 0 +'0';
	    temp[7] = (p->tm_mday)%10- 0 +'0';
	    temp[8] = '\0';
	    strcpy(newbill->date, temp);
		
		productin *tail = L1;
		while(tail->next)
		{
			tail = tail->next;
		}
		tail->next = newbill;
		
		printf("\t\t\t\t您已成功购买%s品牌的%s%d箱,",tar_sou->DrinksBrand_sou, code[tar_sou->BrandNumber_sou][tar_sou->ProductNumber_sou], buy_amount);
		printf(" 每箱%d瓶, 每瓶%d毫升！\n", tar_sou->packagingsize_sou, tar_sou->volume_sou);
		printf("\t\t\t\t\t订单产生运费%d元,共计%.2f元!\n",newbill->provider->transport_cost, buy_money+newbill->provider->transport_cost);
		
		printfile();
		
		wornout(tar_sou, buy_amount);
		newbill->provider->transport_cost = 100;
		total_cost+=buy_money+newbill->provider->transport_cost;
		current_money-=buy_money+newbill->provider->transport_cost;
		writeprofit();
		system("pause");
	}
	return ;
};

void ManagerInput(){
	while(1)
	{
		ManagerLogin();
		char ManagerPassword[20];
		char temp;
		int i = 0;
		while(1)
		{
			temp = _getch();
			if(temp == '\r' || temp == '\n') break;
			else if (temp == '\b') {             // 退格符特判 
				if(i!=0){
					printf("\b \b");
					i--;
				}
			}
			else{
				printf("*");
				ManagerPassword[i++] = temp;
			}
		}
		ManagerPassword[i] = '\0';
		if(i == 1 && ManagerPassword[i-1] == '0') return;
		else if(strcmp(ManagerPassword, passwordans) == 0)
        	ManagerChooseMode();
		else {
			printf("\n\t\t\t\t\t您输入的密码有误，请在界面刷新后重新输入！\n");
			pau;
			continue; 
		}
		
	}
	
}


/*-------------------------------管理员订单售后处理-----------------*/

void aftersercive_check(){        // 售后订单处理 
	while(1)
	{
		system("cls"); 
		printf("\n\n\n\n"); 
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t             售后订单处理界面            \n");
    	printf("\t\t\t\t\t           (输入0可返回上一个界面)       \n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
		
		Check_Bills_with_problem();
		struct sell_bill* tar = bill_with_problem->next;
		if(bill_with_problem->next == NULL){
			pau; 
			return;
		}
	        
		printf("\n\t\t\t\t\t请选择您要处理的订单编号:");
		int billid;

		billid =checkNum();
		if(billid == -1){
			RefreshPage();
			continue;
		}
		if(billid == 0) return;
		 // tar为问题订单 
		int i = 1;
		while(tar)
		{
			if(i == billid) break;
			i++;
			tar = tar->next;
		}
		if(tar == NULL)
		{
			printf("\n找不到您所输入的订单，请按任意键刷新后重试！");
			continue; 
		}
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t             订单处理              \n");
    	printf("\t\t\t\t\t            1.同意退换货\n");
    	printf("\t\t\t\t\t            2.拒绝退换货\n");
    	printf("\t\t\t\t\t         请输入您要进行的操作:");
    	int choice;

		choice = checkNum();
		if(choice == -1 || choice > 2){
			RefreshPage();
			continue;
		}
		else if(choice == 1){
			if(tar->status == 2)
			{
				tar->status = 4;//已确认退换货
				//在问题订单中删除
				struct sell_bill* pointer=bill_pre->next;
		        while(pointer!=NULL)
		        {
		            if(pointer->order==tar->order)
		            {
		                tar->related=pointer;
		                break;
		            }
		            pointer=pointer->next;
		        }
				struct sell_bill* source = tar->related;
				source->status = 4;
				if(tar->next == NULL)
				{
					tar = tar->pre;
					tar->next = NULL;
				}
				else{
					tar = tar->pre;
					tar->next = tar->next->next;
				}
					
				writeproblembill();
				writebill();
				bill_pre=Initiate_Bill();
	    		bill_with_problem=Initiate_Bill_with_problem();
	    		printf("\t\t\t\t\t 您已成功确认换货, 新商品已从仓库发出！");
				
	    		pau;
				continue;
			} 
			else if(tar->status == 3)
			{
				tar->status = 5;//已确认退换货
				
				struct sell_bill* pointer=bill_pre->next;
				total_income-=tar->total_price;
				current_money-=tar->total_price;
				writeprofit();
				client*cus=findClient(&L,tar->id);
				update(&cus,-tar->total_price);
				recharge(&L,&log_head,cus->id,tar->total_price);
		        while(pointer!=NULL)
		        {
		            if(pointer->order==tar->order)
		            {
		                tar->related=pointer;
		                break;
		            }
		            pointer=pointer->next;
		        }
//		        if(tar->related==NULL)
				struct sell_bill* source = tar->related;
				source->status = 5;
				tar->status = 5;
				if(tar->next == NULL)
				{
					tar = tar->pre;
					tar->next = NULL;
				}
				else{
					tar = tar->pre;
					tar->next = tar->next->next;
				}	
				writeproblembill();
				writebill();
				bill_pre=Initiate_Bill();
	    		bill_with_problem=Initiate_Bill_with_problem();
	    		printf("\t\t\t\t\t 您已成功确认退货，钱款已经打入您的余额！\n");
	    		if(tar->reason_num == 0 || tar->reason_num == 1) //"不想要了","不喜欢"
	    		{
	    			Inventory* q = Inv_head->next;
					while(q)
					{
						if(q->BrandNumber == tar->number_of_brand && q->SpecificationNumber ==tar->SpecificationNumber)
							break;
						q = q->next;
					}
					q->Reserve += tar->number_of_packagingzise;
					printf("\t\t\t\t\t 已成功将商品添加回仓库！");
				}
				else printf("\t\t\t\t\t  已将问题商品处理！") ; 
				pau;
			}
			
			
		}
		else if(choice == 2){                  // 已拒绝 
			tar->status = 1;                //已确认退换货
			tar = tar->pre;
			tar->next = tar->next->next;			
			writeproblembill();
			writebill();
			bill_pre=Initiate_Bill();
	    	bill_with_problem=Initiate_Bill_with_problem();
			printf("\t\t\t 您已确认拒绝此次退换货！");
		}
		pau;
	}
}
void costAndprofit(){
	system("cls");
	printf("\n\n\n\n\n"); 
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t              成本与利润                 \n");
    printf("\t\t\t\t\t                                         \n");
    printf("\t\t\t\t\t --------------------------------------- \n");
    
    time_t timep;
    time(&timep);
    struct tm *tp;
    tp = gmtime(&timep);
    printf("\t\t\t\t\t截止至%d年 %d月 %d日，本店收支情况如下:\n",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday);
    
    printf("\t\t\t\t\t本店总收入:%.2lf\n",total_income);
    printf("\t\t\t\t\t本店总成本:%.2lf\n",total_cost);
    printf("\t\t\t\t\t合计总利润:%.2lf\n",total_income-total_cost);
    printf("\t\t\t\t\t当前剩余资金:%.2lf\n",current_money);
    system("pause");
}

void writeprofit(){
	FILE *fp=fopen("profit.txt","w+");
	if(!fp)return;
	fprintf(fp,"%.2lf     %.2lf     %.2lf",total_cost,total_income,current_money);
	fclose(fp);
}

void readprofit(){
	FILE *fp=fopen("profit.txt","r+");
	if(!fp)return;
	
	fscanf(fp,"%lf%lf%lf",&total_cost,&total_income,&current_money);
	fclose(fp);
}




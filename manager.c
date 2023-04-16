#include"manager.h"

extern Inventory* Inv_head;
extern Gift* Gift_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][5]; 
extern char passwordans[20]; 
extern int total_brand;
extern struct sell_bill* bill_pre;            //有哨位节点 
extern struct sell_bill* bill_with_problem;  // 有哨位节点 
//   开始进货 
void Restock(){
	Sou_head = ReadSource();
	while(1)
	{
		system("cls");
		printf("\n");
		printf("\t\t-----------------------------进货界面------------------------------------\n");
		printf("\t\t                     (输入0可以返回上一个界面)\n");
		PrintSource(Sou_head);
		printf("\n\t\t\t\t请选择你需要购买的品牌：");
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		scanf("%s", ChooseBrand_s);
		ChooseBrand = inputcheck(ChooseBrand_s);
		if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		if(ChooseBrand == 0) return ;
		printf("\n\t\t\t\t请选择你要批发的产品编号：");
		scanf("%s", ChooseProduct_s);
		ChooseProduct = inputcheck(ChooseProduct_s);
		int maxproduct = countSpecification_sou(ChooseBrand);
		if(ChooseProduct == -1 || ChooseProduct > maxproduct){
			RefreshPage();
			continue;
		}
		else if(ChooseProduct == 0) return;
		int  buy_amount;
		char buy_amount_s[5]; 
		printf("\n\t\t\t\t请选择你要批发的数量(单次不得超过100箱 不得少于10箱)：");
		scanf("%s", buy_amount_s);
		buy_amount = inputcheck(buy_amount_s);
		if(buy_amount == -1 || buy_amount > 100 || buy_amount < 10){
			RefreshPage();
			continue;
		}
		else if(buy_amount == 0) return;
		ProductSource* tar_sou = FindSource(ChooseBrand, ChooseProduct);
		if(tar_sou == NULL){
			RefreshPage();
			continue;
		}
		double buy_money;
		buy_money = buy_amount * tar_sou->Price_sou;
		printf("\t\t您已成功购买%s品牌的%s%d箱,",tar_sou->DrinksBrand_sou, code[tar_sou->BrandNumber_sou][tar_sou->ProductNumber_sou], buy_amount);
		printf(" 每箱%d瓶, 每瓶%d毫升！\n", tar_sou->packagingsize_sou, tar_sou->volume_sou);
		printf("\t\t\t 共计%.2f元!\n", buy_money);
		// （加入）这里加入成功写入订单的操作 
		wornout(tar_sou, buy_amount);
		system("pause");
	}
	return ;
};

void wornout(ProductSource* tar, int amount){
//	int odds = rand()%10;
//	if(odds == 1) 
//	{
//		int n = (int) (amount/10);  //n箱 
//		int loss = rand()%3;      // 随机损失1—2瓶 或  包装坏了容量没事 
//		int num_gift = n * (tar->packagingsize_sou - loss);
//		//直接在赠品中查找 
//		Gift* p = Gift_head->next;
//		Gift* temp = p;
//		int i = 0;
//		while(p)
//		{
//			i++;
//			if(p->brand==tar->BrandNumber_sou&&p->product==tar->ProductNumber_sou&&p->gif_year==tar->quality_year_sou&&p->gif_month==tar->quality_month_sou&&p->gif_day==tar->quality_day_sou)
//			{
//				p->bottle += num_gift;
//				break;
//			}
//			p = p->next;
//			if(p) temp = p;
//		}
//		if(p==NULL) 
//		{
//			Gift* newgift = (Gift*)malloc(sizeof(Gift));
//			newgift->next = NULL;
//			newgift->pre = temp;
//			newgift->reorder = ++i;
//			newgift->brand = tar->BrandNumber_sou;
//			newgift->product = tar->ProductNumber_sou;
//			newgift->bottle = num_gift;
//			p->gif_year=tar->quality_year_sou;
//			p->gif_month=tar->quality_month_sou;
//			p->gif_day=tar->quality_day_sou;
//			p->value = tar->Price_sou;
//			p->gif_volume = tar->volume_sou;
//		}
//		UpdateGift();
//		printf("\t\t 很遗憾在运输途中有%d箱货物产生意外,共损失%d瓶酒水！\n", n,loss);
//		printf("\t\t\t  剩余%d瓶酒水因无法售卖, 已成功加入赠品中！\n", num_gift);
//	}
//	else
//	{
//		printf("\t\t\t 运输途中无意外发生, 货物以安全送达仓库！\n");
//	}
	return; 
}


void ManagerInput(){
//    int errorflag = 0;
//    while(1)
//    {
//		char* ManagerPassword; 
//		if(errorflag == 1)
//		{
//			printf("\n\t\t\t\t  您的输入有误, 请按任意键刷新后重新输入!\n\t\t\t\t");
//			system("pause");
//		}
//		system("cls");
//    	ManagerLogin();
//    	char temp;
//    	int i = 0;
//		while(1)
//		{
//			temp = _getch();
//			if(temp == '\r' || temp == '\n') break;
//			else if (temp == '\b') {             // 退格符特判 
//				if(i!=0){
//					printf("\b \b");
//					i--;
//				}
//			}
//			else{
//				printf("*");
//				ManagerPassword[i++] = temp;
//			}
//		}
//		ManagerPassword[i] = '\0';
//        if(i > 0 && ManagerPassword[i-1] == '0') return;
//        else if(strcmp(ManagerPassword, passwordans) == 0) {
//        	errorflag = 0;
//        	ManagerChooseMode();
//		}
//		else errorflag = 1;
//    }
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
			printf("您输入的密码有误，请在界面刷新后重新输入！");
			continue; 
		}
		
	}
	
}





/*-------------------------------管理员订单售后处理-----------------*/

void aftersercive_check(){        // 售后订单处理 
	while(1)
	{
		system("cls"); 
		printf("\n\t---------------------售后订单处理界面--------------------\n");
		Check_Bills_with_problem2();
		printf("请选择您要处理的订单编号:");
		int billid;
		char billid_s[5];
		scanf("%s", billid_s);
		billid = inputcheck(billid_s);
		if(billid == -1){
			RefreshPage();
			continue;
		}
		if(billid == 0) return;
		struct sell_bill* tar = bill_with_problem->next; // tar为问题订单 
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
		printf("----------------------------订单处理---------------------------\n");
		printf("\t\t\t您要进行什么操作:\n");
    	printf("\t\t\t 1.同意退换货\n");
    	printf("\t\t\t 2.拒绝退换货\n");
    	printf("\t\t   请输入您要进行的操作:");
    	int choice;
		char choice_s[5];
		scanf("%s", choice_s);
		choice = inputcheck(choice_s);
		if(choice == -1 || choice > 2){
			RefreshPage();
			continue;
		}
		else if(choice == 1){
			if(tar->status == 2)
			{
				printf("\t\t\t 您已确认成功确认换货, 新商品已从仓库发出！");
				tar->status = 4;//已确认退换货
				//在问题订单中删除
				tar = tar->pre;
				tar->next = tar->next->next;			
				writeproblembill();
				writebill();
				bill_pre=Initiate_Bill();
	    		bill_with_problem=Initiate_Bill_with_problem();
				continue;
			} 
			else if(tar->status == 3)
			{
				tar->status = 4;//已确认退换货
				printf("\t\t\t 您已成功确认确认退货，新商品已从仓库发出！");
				tar = tar->pre;
				tar->next = tar->next->next;
				writeproblembill();
				writebill();
				bill_pre=Initiate_Bill();
	    		bill_with_problem=Initiate_Bill_with_problem();
			}
			
			
		}
		else if(choice == 2){
			tar->status = 1;  //已确认退换货
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










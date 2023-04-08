#include"manager.h"

extern Inventory* Inv_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][5]; 
extern int passwordans; 
extern int total_brand;
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
		printf("\n\t\t\t\t请选择你要批发的数量(单词不得超过100箱)：");
		scanf("%s", buy_amount_s);
		buy_amount = inputcheck(buy_amount_s);
		if(buy_amount == -1 || buy_amount > 100){
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
		system("pause");
	}
	return ;
};


void ManagerInput(){
	int ManagerPassword, errorflag = 0;   // 
    while(1)
    {
		if(errorflag == 1)
		{
			printf("\t\t\t\t  您的输入有误, 请按任意键刷新后重新输入!\n\t\t\t\t");
			system("pause");
		}
		system("cls");
    	ManagerLogin();
		while((scanf("%d", &ManagerPassword)) == 0){
        	char garbage[20];
            gets(garbage);
			ErrorHappens();
		} 
        if(ManagerPassword == 0) return;
        else if(ManagerPassword == passwordans) {
        	errorflag = 0;
        	ManagerChooseMode();
		}
		else errorflag = 1;
    }
}





#include"manager.h"

extern Inventory* Inv_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][5]; 
extern int passwordans; 
extern int total_brand;
//   ��ʼ���� 
void Restock(){
	Sou_head = ReadSource();
	while(1)
	{
		system("cls");
		printf("\n");
		printf("\t\t-----------------------------��������------------------------------------\n");
		printf("\t\t                     (����0���Է�����һ������)\n");
		PrintSource(Sou_head);
		printf("\n\t\t\t\t��ѡ������Ҫ�����Ʒ�ƣ�");
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		scanf("%s", ChooseBrand_s);
		ChooseBrand = inputcheck(ChooseBrand_s);
		if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		if(ChooseBrand == 0) return ;
		printf("\n\t\t\t\t��ѡ����Ҫ�����Ĳ�Ʒ��ţ�");
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
		printf("\n\t\t\t\t��ѡ����Ҫ����������(���ʲ��ó���100��)��");
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
		printf("\t\t���ѳɹ�����%sƷ�Ƶ�%s%d��,",tar_sou->DrinksBrand_sou, code[tar_sou->BrandNumber_sou][tar_sou->ProductNumber_sou], buy_amount);
		printf(" ÿ��%dƿ, ÿƿ%d������\n", tar_sou->packagingsize_sou, tar_sou->volume_sou);
		printf("\t\t\t ����%.2fԪ!\n", buy_money);
		
		// �����룩�������ɹ�д�붩���Ĳ��� 
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
			printf("\t\t\t\t  ������������, �밴�����ˢ�º���������!\n\t\t\t\t");
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





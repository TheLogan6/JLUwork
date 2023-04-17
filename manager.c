#include"manager.h"

extern Inventory* Inv_head;
extern Gift* Gift_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][5]; 
extern char passwordans[20]; 
extern int total_brand;
extern struct sell_bill* bill_pre;            //����λ�ڵ� 
extern struct sell_bill* bill_with_problem;  // ����λ�ڵ� 
//   ��ʼ���� 
void Restock(){
	Sou_head = ReadSource();
	while(1)
	{
		system("cls");
		printf("\n"); 
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t                ��������                 \n");
    	printf("\t\t\t\t\t     (��Ʒ�ƴ�����0���Է�����һ������)   \n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
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
		printf("\n\t\t\t\t��ѡ����Ҫ����������(���β��ó���100�� ��������10��)��");
		scanf("%s", buy_amount_s);
		buy_amount = inputcheck(buy_amount_s);
		if(buy_amount == -1 || buy_amount > 100 || buy_amount < 10){
			RefreshPage();
			continue;
		}
		else if(buy_amount == 0) return;
		ProductSource* tar_sou = FindSource(ChooseBrand, ChooseProduct); //�ҵ���ԴĿ�� 
		if(tar_sou == NULL){
			RefreshPage();
			continue;
		}
		double buy_money;
		buy_money = buy_amount * tar_sou->Price_sou;
		
		printf("\t\t���ѳɹ�����%sƷ�Ƶ�%s%d��,",tar_sou->DrinksBrand_sou, code[tar_sou->BrandNumber_sou][tar_sou->ProductNumber_sou], buy_amount);
		printf(" ÿ��%dƿ, ÿƿ%d������\n", tar_sou->packagingsize_sou, tar_sou->volume_sou);
		printf("\t\t\t\t ����%.2fԪ!\n", buy_money);
		// �����룩�������ɹ�д�붩���Ĳ��� 
		printf("\t\t\t\t\t --------------------------------------- \n");
		
		wornout(tar_sou, buy_amount);
		
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
			else if (temp == '\b') {             // �˸������ 
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
			printf("������������������ڽ���ˢ�º��������룡");
			continue; 
		}
		
	}
	
}





/*-------------------------------����Ա�����ۺ���-----------------*/

void aftersercive_check(){        // �ۺ󶩵����� 
	while(1)
	{
		system("cls"); 
		printf("\n\t---------------------�ۺ󶩵��������--------------------\n");
		Check_Bills_with_problem2();
		printf("��ѡ����Ҫ����Ķ������:");
		int billid;
		char billid_s[5];
		scanf("%s", billid_s);
		billid = inputcheck(billid_s);
		if(billid == -1){
			RefreshPage();
			continue;
		}
		if(billid == 0) return;
		struct sell_bill* tar = bill_with_problem->next; // tarΪ���ⶩ�� 
		int i = 1;
		while(tar)
		{
			if(i == billid) break;
			i++;
			tar = tar->next;
		}
		if(tar == NULL)
		{
			printf("\n�Ҳ�����������Ķ������밴�����ˢ�º����ԣ�");
			continue; 
		}
		printf("----------------------------��������---------------------------\n");
		printf("\t\t\t��Ҫ����ʲô����:\n");
    	printf("\t\t\t 1.ͬ���˻���\n");
    	printf("\t\t\t 2.�ܾ��˻���\n");
    	printf("\t\t   ��������Ҫ���еĲ���:");
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
				printf("\t\t\t ����ȷ�ϳɹ�ȷ�ϻ���, ����Ʒ�ѴӲֿⷢ����");
				tar->status = 4;//��ȷ���˻���
				//�����ⶩ����ɾ��
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
				tar->status = 4;//��ȷ���˻���
				printf("\t\t\t ���ѳɹ�ȷ��ȷ���˻�������Ʒ�ѴӲֿⷢ����");
				tar = tar->pre;
				tar->next = tar->next->next;
				writeproblembill();
				writebill();
				bill_pre=Initiate_Bill();
	    		bill_with_problem=Initiate_Bill_with_problem();
			}
			
			
		}
		else if(choice == 2){
			tar->status = 1;  //��ȷ���˻���
			tar = tar->pre;
			tar->next = tar->next->next;			
			writeproblembill();
			writebill();
			bill_pre=Initiate_Bill();
	    	bill_with_problem=Initiate_Bill_with_problem();
			printf("\t\t\t ����ȷ�Ͼܾ��˴��˻�����");
		}
		pau;
	}
	
}










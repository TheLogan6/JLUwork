#include"manager.h"

extern Inventory* Inv_head;
extern Gift* Gift_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][10]; 
extern char passwordans[20]; 
extern int total_brand;
extern struct sell_bill* bill_pre;            //����λ�ڵ� 
extern struct sell_bill* bill_with_problem;  // ����λ�ڵ� 
extern supplierlist L2;
extern productlistin L1;//������
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
		ChooseBrand = checkNum();
		if(ChooseBrand == -1 || ChooseBrand > total_brand){
			RefreshPage();
			continue;
		}
		if(ChooseBrand == 0) return ;
		printf("\n\t\t\t\t��ѡ����Ҫ�����Ĳ�Ʒ��ţ�");
		ChooseProduct = checkNum();
		int maxproduct = countSpecification_sou(ChooseBrand);
		if(ChooseProduct == -1 || ChooseProduct > maxproduct){
			RefreshPage();
			continue;
		}
		else if(ChooseProduct == 0) return;
		int  buy_amount;
		char buy_amount_s[5]; 
		printf("\n\t\t\t\t��ѡ����Ҫ����������(���β��ó���100�� ��������10��)��");

		buy_amount = checkNum();
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
		
		printf("\t\t\t\t\t --------------------------------------- \n");
		//���붩��
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
	    p = localtime(&timep); //ȡ�õ��ؾ���ʱ��
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
		
		printf("\t\t\t\t���ѳɹ�����%sƷ�Ƶ�%s%d��,",tar_sou->DrinksBrand_sou, code[tar_sou->BrandNumber_sou][tar_sou->ProductNumber_sou], buy_amount);
		printf(" ÿ��%dƿ, ÿƿ%d������\n", tar_sou->packagingsize_sou, tar_sou->volume_sou);
		printf("\t\t\t\t\t���������˷�%dԪ,����%.2fԪ!\n",newbill->provider->transport_cost, buy_money+newbill->provider->transport_cost);
		
		printfile();
		
		wornout(tar_sou, buy_amount);
		
		system("pause");
	}
	return ;
};


void getchartime(){
//	time_t timep;
//	struct tm *p;
//    time(&timep);
//    p = localtime(&timep); //ȡ�õ��ؾ���ʱ��
//    char temp[50];
//    temp[0] = (1900+p->tm_year)/1000 - 0 +'0';
//    temp[1] = ((1900+p->tm_year)%1000)/100- 0 +'0';
//    temp[2] = (((1900+p->tm_year)%100)/10)- 0 +'0';
//    temp[3] = (1900+p->tm_year)%10- 0 +'0';
//    temp[4] = (1+p->tm_mon)/10- 0 +'0';
//    temp[5] = (1+p->tm_mon)%10- 0 +'0';
//    temp[6] = (p->tm_mday)/10- 0 +'0';
//    temp[7] = (p->tm_mday)%10- 0 +'0';
//    temp[8] = '\0';
//	while(q)
//	{
//		if(q->nearexpiry == 1) {
//			q = q->next;
//			continue;
//		}
//		else if(timegap(q->quality_year,q->quality_month,q->quality_day,1900+p->tm_year, 1+p->tm_mon, p->tm_mday) < 60 )
//		{
//			q->Price *= 0.5;
//			q->nearexpiry = 1;
//		}
//		q = q->next;
//	}
}



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
		printf("\n\n\n\n"); 
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t             �ۺ󶩵��������            \n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
		
		Check_Bills_with_problem();
		struct sell_bill* tar = bill_with_problem->next;
		if(bill_with_problem->next == NULL)
	        return;
		printf("\t\t\t\t\t��ѡ����Ҫ����Ķ������:");
		int billid;

		billid =checkNum();
		if(billid == -1){
			RefreshPage();
			continue;
		}
		if(billid == 0) return;
		 // tarΪ���ⶩ�� 
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
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t\t             ��������              \n");
    	printf("\t\t\t\t\t            1.ͬ���˻���\n");
    	printf("\t\t\t\t\t            2.�ܾ��˻���\n");
    	printf("\t\t\t\t\t         ��������Ҫ���еĲ���:");
    	int choice;
		char choice_s[5];
		choice = checkNum();
		if(choice == -1 || choice > 2){
			RefreshPage();
			continue;
		}
		else if(choice == 1){
			if(tar->status == 2)
			{
				tar->status = 4;//��ȷ���˻���
				//�����ⶩ����ɾ��
				tar = tar->pre;
				tar->next = tar->next->next;		
				struct sell_bill* source = tar->related;
				tar->status = 4;	
				writeproblembill();
				writebill();
				bill_pre=Initiate_Bill();
	    		bill_with_problem=Initiate_Bill_with_problem();
	    		printf("\t\t\t\t\t ���ѳɹ�ȷ�ϻ���, ����Ʒ�ѴӲֿⷢ����");
	    		pau;
				continue;
			} 
			else if(tar->status == 3)
			{
				tar->status = 4;//��ȷ���˻���
				tar = tar->pre;
				tar->next = tar->next->next;
				struct sell_bill* source = tar->related;
				tar->status = 4;
				writeproblembill();
				writebill();
				bill_pre=Initiate_Bill();
	    		bill_with_problem=Initiate_Bill_with_problem();
	    		printf("\t\t\t\t\t ���ѳɹ�ȷ���˻�������Ʒ�ѴӲֿⷢ����\n");
	    		if(tar->reason_num == 0 || tar->reason_num == 1) //"����Ҫ��","��ϲ��"
	    		{
	    			Inventory* q = Inv_head->next;
					while(q)
					{
						if(q->BrandNumber == tar->number_of_brand && q->SpecificationNumber ==tar->SpecificationNumber)
							break;
						q = q->next;
					}
					q->Reserve += tar->number_of_packagingzise;
					printf("\t\t\t\t\t �ѳɹ�����Ʒ��ӻزֿ⣡");
				}
				else printf("\t\t\t\t\t  �ѽ�������Ʒ����") ; 
				pau;
			}
			
			
		}
		else if(choice == 2){                  // �Ѿܾ� 
			tar->status = 1;                //��ȷ���˻���
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










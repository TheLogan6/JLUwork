#include"interface.h"

extern Inventory* Inv_head;
extern client* L;
extern ProductSource* Sou_head;
extern char* code[12][5]; 
//extern SpecialInv* SpeInv_head;
extern int total_brand;
void LoginInterface(int position){
	system("cls");
    system("color 1F"); // B����ɫ   4����ɫ�� 
    printf("\n\n\n\n\n"); 
    //printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t           ��ӭʹ�þ�ˮ����ϵͳ��          \n");
    //printf("\t\t\t\t\t --------------------------------------- \n");
    system("cls");
    printf("\n\n\n\n\n"); 
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t                ��¼����                 \n");
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t|                                       |\n");
    if(position==0)printf("\033[1;46m\t\t\t\t\t|         -->(1). �ͻ���¼              |\033[0m\n\033[1;44m");
    else printf("\t\t\t\t\t|            (1). �ͻ���¼              |\n");
    if(position==1)printf("\033[1;46m\t\t\t\t\t|         -->(2).����Ա��¼             |\033[0m\n\033[1;44m"); 
    else printf("\t\t\t\t\t|            (2).����Ա��¼             |\n"); 
    if(position==2)printf("\033[1;46m\t\t\t\t\t|         -->(3).�¿ͻ�ע��             |\033[0m\n\033[1;44m");
    else printf("\t\t\t\t\t|            (3).�¿ͻ�ע��             |\n");
    if(position==3)printf("\033[1;46m\t\t\t\t\t|         -->(4). �˳�ϵͳ              |\033[0m\n\033[1;44m");
    else printf("\t\t\t\t\t|            (4). �˳�ϵͳ              |\n");
    printf("\t\t\t\t\t|                                       |\n");
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t��ѡ����Ҫ���еķ���");
}

void ClientLogin(){
	system("cls");
	
	printf("\n\n\n\n\n"); 
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t               �û���¼����              \n");
    printf("\t\t\t\t\t    (���˺����봦����0���Է�����һ������)\n");
    printf("\t\t\t\t\t --------------------------------------- \n");
	printf("\n"); 

    printf("\t\t\t\t\t �����������˺ţ�");
}

void ManagerLogin(){
	system("cls");
	printf("\n\n\n\n\n"); 
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t              ����Ա��¼����             \n");
    printf("\t\t\t\t\t         (����0���Է�����һ������)       \n");
    printf("\t\t\t\t\t --------------------------------------- \n");
	printf("\n"); 
    printf("\t\t\t\t\t �������������Կ��");
} 

void PasswordOutput(){
	printf("\t\t\t\t\t �������������룺");
} 

 

void NewClientInterface(){
	system("cls");
	printf("\n\n\n\n\n"); 
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t              ���û�ע�����             \n");
    printf("\t\t\t\t\t         (����0���Է�����һ������)       \n");
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t    �����˺��ǣ�");
}
 
/*-------------------------------�����߽���---------------------*/ 
void ManInferface(int i){
	system("cls");
		printf("\n\n\n\n\n"); 
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t               ���̹������              \n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t|                                       |\n");
    	if(i == 1) printf("\033[1;46m\t\t\t\t\t|   -->  (1). ��Ϣ��ѯģʽ(ֻ��)        |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|        (1). ��Ϣ��ѯģʽ(ֻ��)        |\n");
    	if(i == 2) printf("\033[1;46m\t\t\t\t\t|   -->  (2).   ��Ϣ�޸�ģʽ            |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|        (2).   ��Ϣ�޸�ģʽ            |\n");
    	if(i == 3) printf("\033[1;46m\t\t\t\t\t|   -->  (3).     ����ģʽ              |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|        (3).     ����ģʽ              |\n");
    	if(i == 4) printf("\033[1;46m\t\t\t\t\t|   -->  (4).   �û���������            |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|        (4).   �û���������            |\n"); 
    	if(i == 0) printf("\033[1;46m\t\t\t\t\t|   -->  (0).  ������һ������           |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|        (0).  ������һ������           |\n");
		printf("\t\t\t\t\t|                                       |\n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t       ��ѡ����Ҫ���еĲ�����");
}

void ManagerChooseMode(){
	int i = 1;
	char temp;
	int Mana_mode;
	while(1)
	{
		ManInferface(i);
		temp = getch();
		if(temp == 'w') i = (i-1+5)%5;
		else if(temp == 's') i = (i+1)%5;
		else if(temp == '\r'){
			Mana_mode = i;break;
		}
		else continue;
	}
		
	if(Mana_mode == 0) return;

	switch(Mana_mode){ // ��Ϣ��ѯģʽ 
		case(1):{
			ManagerInterface_Read();       // ֻ��ģʽ 
			break;
		}
		case(2):{
			ManagerInterface_Write();       // �޸�ģʽ 
			break;
		}
		case(3):{
			Restock();                    // �������� 
			break;
		}
		case(4):{
			aftersercive_check();                // �û��������� 
			pau;
			break;
		}
	
	}
	
	
}

void ManagerInterface_Read(){	
	while(1)
	{
		int i = 1;
		char temp;
		int ManagerOp;

		while(1)
		{
			system("cls");
			printf("\n\n\n\n\n"); 
	    	printf("\t\t\t\t\t --------------------------------------- \n");
	    	printf("\t\t\t\t\t         ���̹������(��ѯģʽ)          \n");
	    	printf("\t\t\t\t\t --------------------------------------- \n");
	    	printf("\t\t\t\t\t|                                       |\n");
	    	if(i==1) printf("\033[1;46m\t\t\t\t\t|   -->  (1). �鿴�ֿ��Ʒ�嵥          |\033[0m\n\033[1;44m");
	    	else printf("\t\t\t\t\t|        (1). �鿴�ֿ��Ʒ�嵥          |\n");
	    	if(i==2) printf("\033[1;46m\t\t\t\t\t|   -->  (2).   �鿴�ͻ���Ϣ            |\033[0m\n\033[1;44m");
	    	else printf("\t\t\t\t\t|        (2).   �鿴�ͻ���Ϣ            |\n");
	    	if(i==3) printf("\033[1;46m\t\t\t\t\t|   -->  (3).   �鿴���۶���            |\033[0m\n\033[1;44m"); 
	    	else printf("\t\t\t\t\t|        (3).   �鿴���۶���            |\n"); 
	    	if(i==4) printf("\033[1;46m\t\t\t\t\t|   -->  (4).   �鿴��������            |\033[0m\n\033[1;44m");
	    	else printf("\t\t\t\t\t|        (4).   �鿴��������            |\n");
	    	if(i==5) printf("\033[1;46m\t\t\t\t\t|   -->  (5).     ������ѯ              |\033[0m\n\033[1;44m");
	    	else printf("\t\t\t\t\t|        (5).     ������ѯ              |\n");
	    	if(i==0) printf("\033[1;46m\t\t\t\t\t|   -->  (0).  ������һ������           |\033[0m\n\033[1;44m");
	    	else printf("\t\t\t\t\t|        (0).  ������һ������           |\n");
			printf("\t\t\t\t\t|                                       |\n");
			printf("\t\t\t\t\t --------------------------------------- \n");
			printf("\t\t\t\t       ��ѡ����Ҫ���еĲ�����");
			
			temp = getch();	
			if(temp == 'w') i = (i-1+6)%6;
			else if(temp == 's') i = (i+1)%6;
			else if(temp == '\r'){
				ManagerOp = i;break;
			}
			else continue;
		}
	
		switch(ManagerOp){
			case(0): return;
			case(1):{//�鿴�ֿ��Ʒ�嵥
				system("cls");
				InventorySortMode();
				break;
			}
			case(2):{//�鿴�ͻ���Ϣ
				printCustomer(L);
				pau; 
				break;
			} 
			case(3):{ //�鿴���۶���
				Check_Bills();
				pau;
				break;
			}
			case(4):{// �鿴�������� 
				//printproductinlist();
				pau;
				break;
			}
			case(5):{//�޸Ŀͻ���Ϣ 
				Search_For_The_Bills_Of_Given_Data();
				pau;
				break;
			}
			case(6):{// �û���ֵ
				
				
			}
			case(9):{
				
			} 
			default:{
				ErrorHappens();
				break;
			}
		}
	}
} 

void ManagerInterface_Write(){	
	while(1)
	{
		int i = 1;
		char temp;
		int ManagerOp;
		while(1)
		{
			system("cls");
			printf("\n\n\n\n\n"); 
	    	printf("\t\t\t\t\t --------------------------------------- \n");
	    	printf("\t\t\t\t\t         ���̹������(�޸�ģʽ)          \n");
	    	printf("\t\t\t\t\t --------------------------------------- \n");
	    	printf("\t\t\t\t\t|                                       |\n");
	    	if(i==1) printf("\033[1;46m\t\t\t\t\t|        (1). �޸Ĳֿ���Ʒ��Ϣ          |\033[0m\n\033[1;44m");
	    	else printf("\t\t\t\t\t|        (1). �޸Ĳֿ���Ʒ��Ϣ          |\n");
	    	if(i==2) printf("\033[1;46m\t\t\t\t\t|        (2).   �޸Ŀͻ���Ϣ            |\033[0m\n\033[1;44m");
	    	else printf("\t\t\t\t\t|        (2).   �޸Ŀͻ���Ϣ            |\n");
	    	if(i==3) printf("\033[1;46m\t\t\t\t\t|        (3).     �ͻ���ֵ              |\033[0m\n\033[1;44m");
	    	else printf("\t\t\t\t\t|        (3).     �ͻ���ֵ              |\n");
	    	if(i==4) printf("\033[1;46m\t\t\t\t\t|        (4).   ɾ�����۶���            |\033[0m\n\033[1;44m");
	    	else printf("\t\t\t\t\t|        (4).   ɾ�����۶���            |\n");
	    	if(i==0) printf("\033[1;46m\t\t\t\t\t|        (0).  ������һ������           |\033[0m\n\033[1;44m");
	    	else printf("\t\t\t\t\t|        (0).  ������һ������           |\n");
			printf("\t\t\t\t\t|                                       |\n");
			printf("\t\t\t\t\t --------------------------------------- \n");
			printf("\t\t\t\t       ��������Ҫѡ��ķ���");	
			
			temp = getch();	
			if(temp == 'w') i = (i-1+5)%5;
			else if(temp == 's') i = (i+1)%5;
			else if(temp == '\r'){
				ManagerOp = i;break;
			}
			else continue;
		}
		
		switch(ManagerOp){
			case(0): return;
			case(1):{//�ı�ֿ���Ʒ��Ϣ 
				ChangeInventory(); 
				break;
			} 
			case(2):{//�޸Ŀͻ���Ϣ 
				system("cls");
				char tempid_s[5];
				int tempid;
				printf("\t\t\t\t\t --------------------------------------- \n");
			    printf("\t\t\t\t\t                �޸��û���Ϣ                 \n");
			    printf("\t\t\t\t\t --------------------------------------- \n");
				printf("\t\t\t\t\t����������id:");
				scanf("%s", tempid_s);
				tempid = inputcheck(tempid_s);
				if(tempid == -1){
					RefreshPage();
					continue;
				}	
				changeInfo(&L, tempid);
				writeClientInfo(L);
				pau;
				break;
			}
			case(3):{// �û���ֵ
				int tempid;
				double tempmoney;
				while(1)
				{
					system("cls");
					printf("\n\n\n\n\n"); 
			    	printf("\t\t\t\t\t --------------------------------------- \n");
			    	printf("\t\t\t\t\t                ��ֵ����                 \n");
			    	printf("\t\t\t\t\t     (���˺Ŵ�����0���Է�����һ������)   \n");
			    	printf("\t\t\t\t\t --------------------------------------- \n");
					char tempid_s[6];
					printf("\t\t\t\t ����������id: ");
					scanf("%s", tempid_s);
					tempid = inputcheck(tempid_s);
					if(tempid == -1){
						RefreshPage();
						continue;
					}	
					if(tempid == 0)	break;
					client* p=findClient(&L, tempid); 
					if(!p) continue;
					printf("\t\t\t\t �����ֵ��");
					while(getchar()!='\n');
					tempmoney=checkDouble();

					if(!recharge(&L, &log_head, tempid, tempmoney)){
						RefreshPage();continue;
					}
					else{printf("\t\t\t\t��ֵ�ɹ������γ�ֵ��%.2lf",tempmoney);
					writeClientInfo(L);
					pau;
					break;
					} 
					pau;
					
				}
				break;
			}
			case(4):{//ɾ������ 
				system("cls");
				Delete_Bill();
				pau;
				break;
			}
//			case(5):{
//
//				pau;
//				break;
//			} 
//			case(6):{
//				system("cls");
//				//deleteproductinlist();
//				break;
//			} 
			default:{
				ErrorHappens();
				break;
			}
		}
	}	
		
		
}


/*------------------------------------------�ͻ�����------------------------------------*/ 
void ClientChooseMode(client* cur_cus){
	int position=0,row=7,Cli_mode; 
	while(1){
	
	while(1)
	{
		
		system("cls");
		printf("\n\n\n\n\n"); 
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t                �ͻ�����                 \n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t|                                       |\n");
    	if(position==0)printf("\033[1;46m\t\t\t\t\t|     -->        ����                   |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|                ����                   |\n");
    	if(position==1)printf("\033[1;46m\t\t\t\t\t|     -->    ��ѯ��ʷ����               |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|            ��ѯ��ʷ����               |\n");
    	if(position==2)printf("\033[1;46m\t\t\t\t\t|     -->      ��Ʒ����                 |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|              ��Ʒ����                 |\n");
    	if(position==3)printf("\033[1;46m\t\t\t\t\t|     -->      ��Ʒ�˻�                 |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|              ��Ʒ�˻�                 |\n");
    	if(position==4)printf("\033[1;46m\t\t\t\t\t|     -->       ���ﳵ                  |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|               ���ﳵ                  |\n");
    	if(position==5)printf("\033[1;46m\t\t\t\t\t|     -->   ������Ʒ�����              |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|           ������Ʒ�����              |\n");
    	if(position==6)printf("\033[1;46m\t\t\t\t\t|     -->   ������һ������              |\033[0m\n\033[1;44m");
    	else printf("\t\t\t\t\t|           ������һ������              |\n");
		printf("\t\t\t\t\t|                                       |\n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t       ��������Ҫѡ��ķ���");
		
//		int Cli_mode;
//		char Cli_mode_s[5];
//		scanf("%s", Cli_mode_s);
//		Cli_mode = inputcheck(Cli_mode_s);
		char ch=getch();
		if(ch=='w'){
			position=(position-1+row)%row;
		}
		if(ch=='s')position=(position+1)%row;
		if(ch=='\r'){
			Cli_mode=position+1;
			break;
		};
}
//		if(Cli_mode == -1){
//			RefreshPage();
//			continue;
//		}
		if(Cli_mode == 7)
			return;
		switch(Cli_mode){
			case(1):{
				PurchaseInterface(cur_cus);
				break;
			}
			case(2):{
				//��ѯ��ʷ���� 
				Print_Bills_Of_Given_Id(cur_cus->id);
				pau;
				break;
			}
			case(3):{
				Exchange(cur_cus);
				break;
			}
			case(4):{  // ��Ʒ�˻� 
				Return(cur_cus);
				break;
			}
			case(5):{  // ���ﳵ����
				ShoppintcartInterface(cur_cus);
				break;
			}
			case(6):{ // ������Ʒ���� 
				SalePromotion(cur_cus);
				break;
			}
			
		
		}
	}
}
	
/* ------------------------------------------- ��������-------------------------------------------*/
void SalePromotion(client* cur_cus){
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t                ��������                 \n");
    	printf("\t\t\t\t\t  (��Ʒ�Ʊ�ų�����0��ֱ�ӷ�����һ������)\n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
		
		PrintSpecialInv(); 
		printf("\t\t\t\t       ��������Ҫѡ���Ʒ�Ʊ�ţ�");
		int ChooseBrand, ChooseProduct;
		char ChooseBrand_s[5], ChooseProduct_s[5];
		scanf("%s", ChooseBrand_s);
		ChooseBrand = inputcheck(ChooseBrand_s);
//		PrintInventory(Inv_head->next);
//		pau;
		Inventory* q = Inv_head->next;
		while(q)
		{
			if(q->BrandNumber == ChooseBrand && q->nearexpiry == 1) break;
			q = q->next;
		}
		if(ChooseBrand == 0) return ;
		if(ChooseBrand == -1){
			RefreshPage();
			continue;
		}
		else if(q == NULL){
			printf("\t\tδ�ҵ��ô�����Ʒ������������������ҳ��ˢ�º��������룡"); 
			pau;
			continue;
		}	
		printf("\n\t\t\t\t��ѡ�����ڴ����еĲ�Ʒ��ţ�");
		scanf("%s", ChooseProduct_s);
		ChooseProduct = inputcheck(ChooseProduct_s);
		if(ChooseProduct == -1){
			RefreshPage();
			continue;
		}
		Inventory* tar = Inv_head->next;
		while(tar)
		{
			if(tar->BrandNumber == ChooseBrand && tar->SpecificationNumber == ChooseProduct && tar->nearexpiry == 1)
				break;
			tar = tar->next;
		}
		if(tar == NULL)
		{
			printf("\t\tδ�ҵ��ô�����Ʒ������������������ҳ��ˢ�º��������룡"); 
			pau;
			continue;
		}
		int  buy_amount;
		char buy_amount_s[5]; 
		printf("\n\t\t\t\t��ѡ����Ҫ����������(���β��ó���100��)��");
		scanf("%s", buy_amount_s);
		buy_amount = inputcheck(buy_amount_s);
		if(buy_amount == -1  || buy_amount == 0 ){
			RefreshPage();
			continue;
		}
		if( buy_amount > 100 || tar->Reserve < buy_amount)
		{
			printf("\t\t���������Ʒ���������Ϲ淶���밴�����ˢ�º��������룡\n"); 
			pau;
			continue;
		}
		double buy_money;
		buy_money = buy_amount * tar->Price;
		printf("-------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t              ֧��ѡ��          \n"); 
		printf("\t\t\t\t\t 1. �ֽ�֧��\n");
		printf("\t\t\t\t\t 2. ���֧��\n");
		printf("\t\t\t\t\t 3. ���빺�ﳵ\n");
		printf("\t\t\t\t\t 4. ȡ�����ι���\n"); 
		printf("\t\t\t\t\t��ѡ����֧����ʽ: ");
		int paychoice;
		char paychoice_s[5];
		scanf("%s", paychoice_s);
		paychoice = inputcheck(paychoice_s);
		if(paychoice == -1){
			RefreshPage();
			continue;
		}
		switch(paychoice){
			case(1):{
				struct sell_bill *newbill = (struct sell_bill *) malloc(sizeof(struct sell_bill));
				newbill->next = NULL;
    			newbill->pre = NULL;
    			Inventory* tar = Inv_head->next;
				while(tar)
				{
					if(tar->BrandNumber == ChooseBrand && tar->SpecificationNumber == ChooseProduct && tar->nearexpiry == 1)
						break;
					tar = tar->next;
				}
				strcpy(newbill->brand,tar->DrinksBrand);
				newbill->number_of_brand = tar->BrandNumber;
				newbill->ProductNumber = tar->ProductNumber;
				newbill->SpecificationNumber = tar->SpecificationNumber;
				newbill->packagingsize = tar->packagingsize;
				newbill->Unit_Price = tar->Price;
				newbill->volume = tar->volume;
				newbill->number_of_packagingzise = tar->packagingsize;
				newbill->total_number = buy_amount;
				newbill->total_price = buy_money;
				if (cur_cus->level == 1) {
			        newbill->discount_for_client = 0.98;
			    }
			    else if (cur_cus->level == 2) {
			        newbill->discount_for_client = 0.95;
			    }
			    else if (cur_cus->level == 3) {
			        newbill->discount_for_client = 0.90;
			    }
			    newbill->buyer = cur_cus;
			    newbill->status = 1;
				printf("\n\t\t\t\t�ֽ�֧���ɹ���\n");
				printf("\t\t\t���ѳɹ�����%sƷ�Ƶ�%s%d��,",code[tar->BrandNumber][0], code[tar->BrandNumber][tar->ProductNumber], buy_amount);
				printf("ÿ��%dƿ, ÿƿ%d������\n", tar->packagingsize, tar->volume);
				printf("\t\t\t\t ����%.2fԪ!\n", buy_money);
				sell_save(newbill);
				break;
			}
			case(2):{
				printf("\n\t\t\t���֧���ɹ���\n");
				printf("\t\t���ѳɹ�����%sƷ�Ƶ�%s%d��,",code[tar->BrandNumber][0], code[tar->BrandNumber][tar->ProductNumber], buy_amount);
				printf(" ÿ��%dƿ, ÿƿ%d������\n", tar->packagingsize, tar->volume);
				printf("\t\t\t ����%.2fԪ!\n", buy_money);
				system("pause");
				break;
			}
			case(3):{// ���빺�ﳵ 
				addShoppingCart(&cur_cus->cart,buy_amount,cur_cus->id,tar->Price,tar->BrandNumber, tar->ProductNumber, tar->SpecificationNumber); 
				writeShoppingCart(&L);
				printf("\n\t\t\t�ѳɹ����빺�ﳵ!"); 
				break;
			} 
			case(4):{
				printf("\n\t\t\t ���ѳɹ�ȡ�����ι���");
				printf("\n\t\t   ���������ˢ�±��ν���!");
				pau;
				continue;
				break;
			}
			default:{
				RefreshPage();
				pau;
				break;
			}
		}
		system("pause");
	}
	
	
} 



/*------------------------------------------��������----------------------------------------------*/
 
void ErrorHappens(){
	printf("\n\t\t\t\t ������������, ���������룺"); 
}


void RefreshPage(){
	printf("\n\t\t\t\t �������벻���Ϲ淶�����������ˢ�½��棡\n");
	system("pause");
} 

int inputcheck(char numstring[]){
	int n = strlen(numstring);
	if(n > 20) return -1;
	int ans = 0;
	if(n > 1 && numstring[0] == '0') return -1;
	for(int i = 0; i < n; i++)
	{
		if(numstring[i] > '9' || numstring[i] < '0') return -1;
		else ans = ans*10 + (int)(numstring[i] - '0');
	}
	return ans;
} 



/*-------------------------------���ﳵ����-----------------------------------*/
void ShoppintcartInterface(client* cur_cus){          // ��ǰ�ͻ���Ϣ 
	int position=0,row=4,ShoppingcartOp;
	first:
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t               ���ﳵ����                \n");
    	printf("\t\t\t\t\t --------------------------------------- \n");
    	
		showShoppingCart(cur_cus);
		printf("\t\t\t\t\t --------------------------------------- \n");
    	printf("\t\t\t\t\t                                        \n");
    	if(position==0)printf("\t\t\t\t\t         --->     ɾ������              \n");
    	else printf("\t\t\t\t\t                  ɾ������              \n");
    	if(position==1)printf("\t\t\t\t\t         --->   �޸Ĺ�������            \n");
    	else printf("\t\t\t\t\t                �޸Ĺ�������            \n");
    	if(position==2)printf("\t\t\t\t\t         --->     ֧������              \n");
    	else printf("\t\t\t\t\t                  ֧������              \n");
    	if(position==3)printf("\t\t\t\t\t         --->  ������һ������           \n");
    	else printf("\t\t\t\t\t               ������һ������           \n");
		printf("\t\t\t\t\t                                        \n");
		printf("\t\t\t\t\t --------------------------------------- \n");
		printf("\t\t\t\t  ��ѡ����Ҫ����Ĺ��ﳵ���еĲ�����");
		
//		char ShoppingcartOp_s[5];
//		int ShoppingcartOp;
//		scanf("%s", ShoppingcartOp_s);
//		ShoppingcartOp = inputcheck(ShoppingcartOp_s);
//		if(ShoppingcartOp == -1){
//			RefreshPage();
//			continue;
//		} 
//		if(ShoppingcartOp == 0) return;
		int op=getchoice(&position,row,&ShoppingcartOp);
		if(op<0)break;
	}	
	if(ShoppingcartOp==4)return;
	switch(ShoppingcartOp){
			case(1):{
				int  delete_id;
				char delete_id_s2[10];
				printf("\t\t\t\t  ����������Ҫɾ���Ķ����ţ�"); 
				scanf("%s", delete_id_s2);
				delete_id = inputcheck(delete_id_s2);
				if(delete_id == -1) {
					RefreshPage();
					goto first;
				}
				delShoppingCart(cur_cus, delete_id);
				printf("\t\t\t\t  ���ѳɹ�ɾ�����ﳵ���ݣ�");
				writeShoppingCart(&L);
				pau;
				break;
			}
			case(2):{
				int  change_id;
				char change_id_s[10];
				printf("\t\t\t\t  ����������Ҫ�޸ĵĶ����ţ�"); 
				scanf("%s", change_id_s);
				change_id = inputcheck(change_id_s);
				int l = 0;
				shopping_cart *p = cur_cus->cart;
				while(p)
				{
					l++;
					p = p->next;
				}
				if(change_id > l || change_id == -1){
					RefreshPage();
					goto first;
				}
				//ChangeNumber(cur_cus, change_id);
				break;
			} 
			case(3):{
				
				break;
			} 
		}
	}


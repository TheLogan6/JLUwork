#include"shiningpoints.h"

void ShoppintcartInterface(client* cur_cus){          // ��ǰ�ͻ���Ϣ 
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------���ﳵ����----------------\n");
		printf("\t\t\t\t\t    (����0���Է��ع������)\n");
		printf("\t������� | Ʒ������ | ��Ʒ���� | ��ˮ���� | ��װ��С | ���� | �������� | ���");
		//��ӡ���еĶ��� 
		printf("\t ��ѡ����Ҫ����Ĺ��ﳵ���еķ���");
		printf("\t 1. ɾ������\n");
		printf("\t 2. �޸Ĺ�������\n");
		printf("\t 3. ֧������");
		char ShoppingcartOp_s[5];
		int ShoppingcartOp;
		scanf("%s", ShoppingcartOp_s);
		ShoppingcartOp = inputcheck(ShoppingcartOp_s);
		if(ShoppingcartOp == -1){
			RefreshPage();
			continue;
		} 
		if(ShoppingcartOp == 0) return;
		switch(ShoppingcartOp){
			case(1):{
				Deleteitems();
				break;
			}
			case(2):{
				Changequantity();
				break;
			} 
		}
	}
}
		
void ShoppintcartServe(){
}	
void Deleteitems(){
}	
void Changequantity(){
	
}
		

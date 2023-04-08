#include"shiningpoints.h"

void ShoppintcartInterface(client* cur_cus){          // 当前客户信息 
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t------------购物车界面----------------\n");
		printf("\t\t\t\t\t    (输入0可以返回购物界面)\n");
		printf("\t订单编号 | 品牌名称 | 商品名称 | 酒水容量 | 包装大小 | 单价 | 购买数量 | 金额");
		//打印所有的订单 
		printf("\t 请选择您要对你的购物车进行的服务：");
		printf("\t 1. 删除订单\n");
		printf("\t 2. 修改购买数量\n");
		printf("\t 3. 支付结算");
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
		

#include"shiningpoints.h"

void showShoppingCart(client*cus){
    if(!cus)return ;
    shopping_cart*p=cus->cart; 
    if(!p){
    	printf("\t\t\t\t\t\t��Ŷ,���ﳵ��û���κζ�����\n");
    	return;
	}
    int cnt=0;
    double total_price=0;
    printf("\t������� |    Ʒ������    |   ��Ʒ����   | ��ˮ���� |  ��װ��С  |  ��������  |   ����   |  �ܽ��\n");
    while(p) 
	{
        p->id=++cnt;
        Inventory* q = Inv_head->next;
        while(q)
        {
        	if(q->BrandNumber == p->x&& q->SpecificationNumber == p->z) break;
        	q = q->next;
		}
		if(q == NULL || q->Reserve==0) printf("����ѡ�����Ʒ��������");
        else{

			printf("\t  %-9d%-20s%-15s", p->id, q->DrinksBrand, code[p->x][p->y]);
			printf("%-12d%-12d%-12d%-9.2lf%-10.2lf\n", q->volume, q->packagingsize, p->cnt,p->single_cost,p->total_cost);
			total_price += p->total_cost;
		}
        p=p->next;
    }
    printf("\t\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t      ��ǰ���ﳵ�ܽ��Ϊ%.2fԪ��\n",total_price);
}
void addShoppingCart(shopping_cart**p,int cnt,int cus_id,double money,int x,int y,int z){
    if((*p)&&(*p)->x==x&&(*p)->y==y&&(*p)->z==z){
            (*p)->cnt+=cnt;
            return;
    }
    else if(!(*p)){
        shopping_cart *tmp=(shopping_cart*)malloc(sizeof(shopping_cart));
        tmp->single_cost=money;
        tmp->cnt=cnt;
        tmp->cus_id=cus_id;
        tmp->total_cost=(double)money*cnt;
        tmp->x=x,tmp->y=y,tmp->z=z;
        strcpy(tmp->goods_name,"tempname");
        tmp->next=NULL;
        *p=tmp;
    }
    else addShoppingCart(&(*p)->next,cnt,cus_id,money,x,y,z);
}
void readShoppingCart(client**L){
    FILE *fp=fopen("shoppingcart.txt", "r");
    if(!fp){
        printf("�ļ���ʧ�ܣ�\n");
        exit(0);
    }
    char buffer[1000];
    fgets(buffer,sizeof buffer,fp);
    char ch;
    int id,cus_id;double money;int cnt,x,y,z;
    while (fscanf(fp, "%d%d%d%lf%d%d%d",&id,&cus_id,&cnt,&money,&x,&y,&z)!=EOF){
        client *p= findClient(L,cus_id);
        addShoppingCart(&(p->cart),cnt,cus_id,money,x,y,z);
    }
    fclose(fp);
}


void writeShoppingCart(client**L){
    client *p=*L;
    FILE *fp= fopen("shoppingcart.txt", "w");
    fprintf(fp,"id\t�ͻ�id\t��Ʒ����\t��Ʒ����\t���x\t���y\t���z\n");
    if(!p)return ;
    while(p){
        shopping_cart *tmp=p->cart;
        while(tmp){
            fprintf(fp,"%d\t%d\t%d\t%lf\t%d\t%d\t%d\n",tmp->id,tmp->cus_id,tmp->cnt,tmp->single_cost,tmp->x,tmp->y,tmp->z);
            tmp=tmp->next;
        }
        p=p->ne;
    }
    fclose(fp);
}

void delShoppingCart(client*L,int id){
    shopping_cart *p=L->cart;
    shopping_cart *dummy= malloc(sizeof(shopping_cart));
    dummy->next=p;
    p=dummy;
    while(p&&p->next){
        if(p->next->id==id)break;
        p=p->next;
    }
    if(p->next!=NULL)p->next=p->next->next;
    L->cart=dummy->next;
}

void ChangeNumber(client*cur_cus, int tarid){
	shopping_cart *p = cur_cus->cart;
	while(p)
	{
		if(p->id == tarid) break;
		p = p->next;
	}
	if(p==NULL) printf("\t\t\t\t δ�ҵ��ö���,��ˢ�º��������룡");
	printf("\t\t\t\t ����������Ҫ�޸ĵ�����(���β��ó���300��)��");
	int  change_num;
	char change_num_s[10];

	change_num = checkNum();
	if(change_num == -1 || change_num == 0){
		RefreshPage();
		return;
	} 
	else {
		p->cnt = change_num;
		p->total_cost = change_num * p->single_cost;
	}
	
}


 

		
		

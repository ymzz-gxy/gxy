#include<stdio.h>
#include<conio.h>

typedef struct Node
{
	char c;
	int Ltag;
	int Rtag;
	struct Node *Parent;
	struct Node *Lchild;
	struct Node *Rchild;
}BiTNode;
typedef struct
{
	int sum;
	BiTNode *bitnode[30];
}BitList;
//�ݹ鴴����
char Creat(BiTNode *node,char c);
//����������
int Antecedentclue(BiTNode *node,BitList *list);
//����������
int Middleorderclue(BiTNode *node,BitList *list);
//����������
int Postorderclue(BiTNode *node,BitList *list);
//����ݹ����������
int AntecedentPushTree(BiTNode *node);
//�����������������
int PushTreeclue(BiTNode *node);
//����ݹ����������
int PostorderPushTree(BiTNode *node);
//��α���������
int LeverPushTree(BiTNode *node);
//�ǵݹ����������
int PushTree(BiTNode *node);
//�������������
int MirrorPushTree(BiTNode *node);
//����֦��
int CompareTree(BiTNode *root,BiTNode *node);

int main()
{
	char c;
	int select;
	BitList *list;
	BiTNode *node,*p,*compare;
	node = (BiTNode* )malloc(sizeof(BiTNode));
	list = (BitList* )malloc(sizeof(BitList));
	list->sum = 0;
	c = 'a';

	p = node;
	Creat(p,c);

	printf("������������:");
	p = node;
	AntecedentPushTree(p);
	printf("\n");

	printf("������������:");
	p = node;
	PostorderPushTree(p);
	printf("\n");

	printf("�ǵݹ����������:");
	p = node;
    PushTree(p);
	printf("\n");

	printf("������������:");
	p = node;
	LeverPushTree(p);
	printf("\n");

	printf("ѡ��1.���� 2.���� 3.���� 4.���� 5.������\n���룺");
	scanf("%d",&select);
	switch(select)
	{
	case 1:{
				p = node;
				//����������
				Antecedentclue(p,list);
				printf("�����������������:");
				p = node;
				PushTreeclue(p);
				printf("\n");
				break;
		   }
	case 2:{
				p = node;
				//����������
				printf("�����������������:");
				Middleorderclue(p,list);
				printf("\n");
				break;
		   }
	case 3:{
				p = node;
				//����������
				printf("�����������������:");
				Postorderclue(p,list);
				printf("\n");
				break;
		   }
	case 4:{
				printf("�������������:");
				p = node;
				MirrorPushTree(p);
				printf("\n");
				break;
		   }
	case 5:{
				compare = (BiTNode* )malloc(sizeof(BiTNode));
				p = compare;
				printf("������c��");
				scanf(" %c",&c);
				Creat(p,c);
				select = CompareTree(node,compare);
				if(select == 1)
					printf("Yes\n");
				else printf("No\n");
				break;
		   }
	}

	return 1;
}
//����֦��
int CompareTree(BiTNode *root,BiTNode *node)
{
	int select;
	BiTNode *rp,*np;
	BitList *list;
	list = (BitList *)malloc(sizeof(BitList));

	list->sum = 0;
	rp = root;
	Antecedentclue(rp,list);

	list->sum = 0;
	np = node;
	Antecedentclue(np,list);

	while(rp != NULL)
	{
		//printf("%c %c\n",rp->c,np->c);
		select = 0;
		if(np->c == rp->c)
			select = 1;
		else np = node;

		if(np->Rchild == NULL && np->c == rp->c)
			break;
		if(rp->Lchild != NULL && rp->Ltag == 0){
			rp = rp->Lchild;
			if(select == 1)
				np = np->Lchild;
		}
		else {
			if(rp->Rchild != NULL){
				rp = rp->Rchild;
				if(select == 1)
					np = np->Rchild;
			}
			else break;
		}
	}

	if(rp->c == np->c)
		return 1;
	else return 0;

}
//������������������
int Postorderclue(BiTNode *node,BitList *list)
{
	BitList *inthread;
	BiTNode *p,*q;
	inthread = (BitList *)malloc(sizeof(BitList));
	inthread->sum = 0;

	p = node;
	q = NULL;
	list->sum = 0;
	while(p != NULL || list->sum > 0)
	{
		while(p != NULL){
			list->bitnode[list->sum++] = p;
			p = p->Lchild;
		}
		if(list->sum > 0){
			p = list->bitnode[list->sum-1];
			if((p->Rchild == NULL) || (p->Rchild == q))
			{
				p = list->bitnode[--list->sum];
				inthread->bitnode[inthread->sum++] = p;
				q = p;p = NULL;
			}
			else p = p->Rchild;
		}
	}
	q = NULL;p = NULL;
	while(inthread->sum > 0)
	{
		q = p;
		p = inthread->bitnode[--inthread->sum];
		if(p->Rchild == NULL && q != NULL){
			p->Rchild = q;
		}
		if(p->Lchild == NULL && inthread->sum > 0){
			p->Lchild = inthread->bitnode[inthread->sum-1];
		}
	}
	while(p != NULL ){
		printf("%c ",p->c);
		if(p == node)
			break;
		if(p->Rtag == 1)
			p = p->Rchild;
		else{
			q = p->Parent;
			if(q != p->Rchild && q->Rtag == 0){
				p = q->Rchild;
				while(p->Ltag == 0 || p->Rtag == 0){
					if(p->Ltag == 0){
						p = p->Lchild;
						continue;
					}
					if(p->Rtag == 0){
						p = p->Rchild;
						continue;
					}
				}
			}
		}
	}
	return 1;
}
//������������������
int Middleorderclue(BiTNode *node,BitList *list)
{
	BitList *inthread;
	BiTNode *p,*q;
	inthread = (BitList *)malloc(sizeof(BitList));
	inthread->sum = 0;

	p = node;
	list->sum = 0;
	while(p != NULL || list->sum > 0)
	{
		if(p != NULL){
			list->bitnode[list->sum++] = p;
			p = p->Lchild;
		}
		else{
			p = list->bitnode[--list->sum];
			inthread->bitnode[inthread->sum++] = p;
			p = p->Rchild;
		}
	}
	q = NULL;p = NULL;
	while(inthread->sum > 0)
	{
		q = p;
		p = inthread->bitnode[--inthread->sum];
		if(p->Rchild == NULL && q != NULL){
			p->Rchild = q;
		}
		if(p->Lchild == NULL && inthread->sum > 0){
			p->Lchild = inthread->bitnode[inthread->sum-1];
		}
	}
	while(p != NULL){
		printf("%c ",p->c);
		if(p->Rtag == 1)
			p = p->Rchild;
		else{
			for(q = p->Rchild;q->Ltag == 0;q = q->Lchild);
			p = q;
		}
	}
	return 1;
}
//�ǵݹ����������
int PushTree(BiTNode *node)
{
	BiTNode *list[20];
	int i = 0,j = 0;
	list[20] = (BiTNode *)malloc(sizeof(BiTNode)*20);

	while(node != NULL || i != j){
		while(node != NULL){
			list[i++] = node;
			node = node->Lchild;
		}
		if(i != j){
			node = list[j++];
			printf("%c ",node->c);
			node = node->Rchild;
		}
	}
	return 1;
}
//�������������
int MirrorPushTree(BiTNode *node)
{
	BiTNode *list[20],*swap;
	int i = 1,j = 0,text;
	list[20] = (BiTNode *)malloc(sizeof(BiTNode)*20);
	list[0] = node;
	while( i != j){
		node = list[j++];
		printf("%c ",node->c);
		swap = node->Lchild;
		node->Lchild = node->Rchild;
		node->Rchild = swap;
		text = node->Ltag;
		node->Ltag = node->Rtag;
		node->Rtag = text;
		if( node->Lchild != NULL ){
			list[i] = node->Lchild;
			i += 1;
		}
		if( node->Rchild != NULL ){
			list[i] = node->Rchild;
			i += 1;
		}
	}
	return 1;
}
//������������
int LeverPushTree(BiTNode *node)
{
	BiTNode *list[20];
	int i = 1,j = 0;
	list[20] = (BiTNode *)malloc(sizeof(BiTNode)*20);
	list[0] = node;
	while( i != j){
		node = list[j++];
		printf("%c ",node->c);
		if( node->Lchild != NULL ){
			list[i] = node->Lchild;
			i += 1;
		}
		if( node->Rchild != NULL ){
			list[i] = node->Rchild;
			i += 1;
		}
	}
	return 1;
}
//��������ݹ������
int PostorderPushTree(BiTNode *node)
{
	if(node->Lchild != NULL){
		PostorderPushTree(node->Lchild);
	}
	if(node->Rchild != NULL){
		PostorderPushTree(node->Rchild);
	}
	printf("%c ",node->c);
	return 1;
}
//�������������
int PushTreeclue(BiTNode *node){
	
	while(node != NULL)
	{
		printf("%c ",node->c);
		if(node->Lchild != NULL && node->Ltag == 0){
			node = node->Lchild;
		}
		else {
			if(node->Rchild != NULL){
				node = node->Rchild;
			}
			else return 1;
		}
	}
	return 1;
}
//���������
int AntecedentPushTree(BiTNode *node){
	printf("%c ",node->c);
	if(node->Lchild != NULL){
		AntecedentPushTree(node->Lchild);
	}
	if(node->Rchild != NULL){
		AntecedentPushTree(node->Rchild);
	}
	return 1;
}
//������������
int Antecedentclue(BiTNode *node,BitList *list){
	BiTNode *q;
	while(node || list->sum > -1){
		list->bitnode[list->sum] = node;
		if( node->Ltag == 0){
			node = node->Lchild;
			list->sum++;
			continue;
		}
		else{
			if(node->Lchild != NULL && list->sum != 0 && node->Ltag == 1){
				node->Lchild = list->bitnode[list->sum-1];
			}
		}
		if(node->Rtag == 0){
			node = node->Rchild;
			list->sum++;
			continue;
		}
		else{
			if(node->Rtag == 1 && node->Ltag == 0){
				node->Rchild = node->Lchild;
			}
		}
		if(node->Rtag == 1 && node->Ltag == 1){
			while(list->sum != -1){
				list->sum--;
				if(list->sum == -1){
					node->Rchild = NULL;
					return 1;
				}
				q = list->bitnode[list->sum];
				if(q->Rtag == 0 && q->Rchild != node){
					list->sum--;
					q = q->Rchild;
					node->Rchild = q;
					node = q;
					break;
				}
			}
		}
		if(list->sum <= -1 && q->Rtag == 1 && q->Ltag == 1){
			node->Rchild = NULL;
			return 1;
		}
	}
	return 1;
}
//����������
char Creat(BiTNode *node,char c){
	int found;

	node->c = c;
	printf("�� (1) �� (0) �������ӣ�");
	scanf("%d",&found);
	if(found == 0){
		node->Ltag = 1;
		node->Lchild = NULL;
	}
	else {
		node->Ltag = 0;
		c += 1;
		node->Lchild = (BiTNode* )malloc(sizeof(BiTNode));
		node->Lchild->Parent = node;
		c = Creat(node->Lchild,c);
	}
	printf("�� (1) �� (0) �����Һ��ӣ�");
	scanf("%d",&found);
	if(found == 0){
		node->Rtag = 1;
		node->Rchild = NULL;
	}
	else {
		node->Rtag = 0;
		c += 1;
		node->Rchild = (BiTNode* )malloc(sizeof(BiTNode));
		node->Rchild->Parent = node;
		c = Creat(node->Rchild,c);
	}
	return c;
}
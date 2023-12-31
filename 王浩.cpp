#include<stdio.h>
#include<string.h>
struct whao {
	int parent[2];  //记录由谁推导出
	char right[500];
	char left[500];
};
struct whao st[100];   //开辟100个结构体的空间
int id=1;             //记录结点的号
void move(int sta,int k) {

	int n=1,m=1;
	int w=sta+1,b,c=0,a; // c用于检查括号是否匹配
	while(st[id+n].right[0]!=NULL||st[id+n].left[0]!=NULL) {
		n++;
		m++;  //找到一个空白的结点
	}
	// 处理非的左移
	if(k==1) {
		for(a=0; st[id].right[a]!=NULL; a++)
			st[id+n].right[a]=st[id].right[a];//右部的内容完全复制
		if(a!=0) {
			st[id+n].right[a]=',';    //添加逗号
			a++;
		}
		if(st[id].left[w]=='(') {
			for(b=1; st[id].left[w+b]!=NULL; b++) {

				if(st[id].left[w+b]==')')
					break;  //碰到右括号，该括号内的内复制完成

				st[id+n].right[a+b-1]=st[id].left[w+b];
			}
		} else {
			for(b=0; st[id].left[w+b]!=NULL; b++) {
				if(st[id].left[w+b]==',')
					break;
				st[id+n].right[a+b]=st[id].left[w+b];
			}
		}
		for(a=0; a<w-1; a++)
			st[id+n].left[a]=st[id].left[a];  //非之前的左部复制过来
		if(a!=0) {
			st[id+n].left[a]=',';
			a++;//添加逗号
		}
		for(; st[id].left[w+b]!=','; b++);
		b++;
		for(; st[id].left[w+b]!=NULL; b++,a++)
			st[id+n].left[a]=st[id].left[w+b];
		st[id].parent[0]=id+n; // 记录父结点
		id++;
	}
	//左移
	if(k==2) {
		for(a=0; st[id].left[a]!=NULL; a++)
			st[id+m].left[a]=st[id].left[a];
		if(a!=0) {
			st[id+m].left[a]=',';
			a++;
		}
		if(st[id].right[w]=='(') {
			for(b=1; st[id].right[w+b]!=NULL; b++) {
				if(st[id].right[w+b]==')')
					break;
				st[id+m].left[a+b-1]=st[id].right[w+b];
			}
		} else {
			for(b=0; st[id].right[w+b]!=NULL; b++) {
				if(st[id].right[w+b]==',')
					break;
				st[id+m].left[a+b]=st[id].right[w+b];
			}
		}
		for(a=0; a<w-1; a++)
			st[id+m].right[a]=st[id].right[a];
		if(a!=0) {
			st[id+m].right[a]=',';
			a++;
		}
		for(; st[id].right[w+b]!=','; b++);
		b++;
		for(; st[id].right[w+b]!=NULL; b++,a++)
			st[id+m].right[a]=st[id].right[w+b];
		st[id].parent[0]=id+m;
		id++;
	}
}
void moveRight(int start) {
	int nu=1;
	while(st[id+nu].right[0]!=NULL||st[id+nu].left[0]!=NULL)
		nu++;
	int begin,end,middle=start;
	int a=0,b=0,c=0,w=0,f;
	for(b=middle; b>0; b--) {
		if(st[id].right[b]==','&&a==0)
			break;  //找到蕴含的前半部分
	}
	begin=b;
	for(b=middle; st[id].right[b]!=NULL; b++) {
		if(st[id].right[b]==',')
			break;//找到蕴含的后半部分
	}
	end=b;
	if(begin!=0)
		c++;
	for(b=0; b<begin+c; b++)
		st[id+nu].right[b]=st[id].right[b];//蕴含前的部分原样复制
	st[id+1].right[b]='!';  //添加非
	for(b++; b-1<middle; b++)
		st[id+nu].right[b]=st[id].right[b-1];//蕴含后的部分移动过去
	st[id+1].right[b]=',';//添加逗号
	if(st[id].right[b+1]=='(') {
		for(b=b+2; b<end-1; b++)
			st[id+nu].right[b-1]=st[id].right[b];
	} else {
		for(b=b+1; b<end; b++)
			st[id+nu].right[b]=st[id].right[b];
	}
	for(; st[id].right[end]!=NULL; b++,end++)
		st[id+nu].right[b]=st[id].right[end];
	st[id].parent[0]=id+nu;
	for(f=0; st[id].left[f]!=NULL; f++)
		st[id+nu].left[f]=st[id].left[f];
	id++;
}
void moveLeft(int start) {
	int nu=1;
	while(st[id+nu].right[0]!=NULL||st[id+nu].left[0]!=NULL)
		nu++;
	int begin,end,middle=start;
	int a=0,b=0,c=0,w=0,f;
	for(b=middle; b>0; b--) {
		if(st[id].left[b]==',')
			break;
	}
	begin=b;
	for(b=middle; st[id].left[b]!=NULL; b++) {
		if(st[id].left[b]==',')
			break;
	}
	end=b;
	if(begin!=0)
		c++;
	for(b=0; b<begin+c; b++) {
		st[id+nu].left[b]=st[id].left[b];
		st[id+nu+1].left[b]=st[id].left[b];
	}
	int b1=b;
	st[id+nu].left[b]='!';
	for(b++; b-1<middle; b++)
		st[id+nu].left[b]=st[id].left[b-1];
	int b2=b;
	if(st[id].left[b+1]=='(') {
		for(b=b+2; b<end-1; b++,b1++)
			st[id+nu+1].left[b1]=st[id].left[b];
	} else {
		for(b=b+1; b<end; b++,b1++)
			st[id+nu+1].left[b1]=st[id].left[b];
	}
	int b3=b1;
	for(; st[id].left[end]!=NULL; end++,b3++,b2++) {
		st[id+nu].left[b2]=st[id].left[end];
		st[id+nu+1].left[b3]=st[id].left[end];
	}
	st[id].parent[0]=id+nu;
	st[id].parent[1]=id+nu+1;
	for(f=0; st[id].left[f]!=NULL; f++) {
		st[id+nu].right[f]=st[id].right[f];
		st[id+nu+1].right[f]=st[id].right[f];
	}
	id++;
}
int SearchFor() {
	int start=0,end=0,a=0,re=0,z,w1,w2;
	while(st[id].right[0]!=NULL||st[id].left[0]!=NULL) {
		while(st[id].right[start]!=NULL) {
			if(st[id].right[start]=='!') {
				move(start,2);
				start=-1;
			} else if(st[id].right[start]=='-'&&a==0) {
				moveRight(start);
				start=-1;
			}
			start++;
		}
		if(a!=0)
			return 0;
		while(st[id].left[end]!=NULL) {
			if(st[id].left[end]=='!') {
				move(end,1);
				end=-1;
			} else if(st[id].left[end]=='-') {
				moveLeft(end);
				end=-1;
			}
			end++;
		}
		if(a!=0)
			return 0;
		for(z=0; st[id].left[z]!=NULL; z++)
			if(st[id].left[z]=='-'||st[id].left[z]=='!')
				a++;
		for(z=0; st[id].right[z]!=NULL; z++)
			if(st[id].right[z]=='-'||st[id].right[z]=='!')
				a++;
		if(a==0) {
			for(w1=0; st[id].right[w1]!=NULL; w1++) {
				for(w2=0; st[id].left[w2]!=NULL; w2++) {
					if(st[id].right[w1]==st[id].left[w2]&&st[id].right[w1]!=',') {
						re++;
					}
				}
			}
			if(re==0)
				return 0;
			re=0;
			id++;
		}
		a=0;
		start=0;
		end=0;
	}
	return 1;
}
int main() {
	int g,i,j=0,k=0;
	printf("请输入要验证的式子\n");
	scanf("%s",&st[1].right);
	for(j=0; j<500; j++) {
		if(st[1].right[j]=='(')
			k++;
		else if(st[1].right[j]==')')
			k--;
	}
	if(k!=0) {
		printf("输入的命题公式有误\n");
		return 0;
	}
	g=SearchFor();
	if(g) {
		printf("该命题公式为真\n");
	} else
		printf("该命题公式为假\n");
	return 0;
}
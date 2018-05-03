/*
 * Arithmex1.cpp
 *
 *  Created on: 2018��4��17��
 *      Author: Yongbo
 */

#include "Arithmex1.h"
#include "string.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <queue>
#include <stack>
#include "windows.h"
struct helpsort{
	int id=-1;//����id
	int time=-1;//ԭid
};
//int *sort;//finish time ����
node *graph;
node *graphT;
nodePro* pro;
nodePro* Tpro;
int Time2nd=0;
bool change=false;
Arithmex1::Arithmex1(int ver,int edge) {
	// TODO Auto-generated constructor stub
	n=ver;
	e=edge;
//	graph=new node[n];
	pro= new nodePro[n];
	time=0;
}


Arithmex1::~Arithmex1() {
	// TODO Auto-generated destructor stub
}

bool Arithmex1::insertEdge(int a,int b){//�����
	if(!graph[a-1].existedge(b)){
		node* current=&graph[a-1];
		while(current->next!=NULL){
			current=current->next;
		}
		node *newnode=new node();
		newnode->init(1,b);
		current->next=newnode;
		graph[b-1].ini++;
		return true;

	}
	return false;
}

bool Arithmex1::insertEdgeT(int a,int b){//�����
	node* current=&graphT[a-1];
	while(current->next!=NULL){
		current=current->next;
	}
	node *newnode=new node();
	newnode->init(1,b);
	current->next=newnode;
	graphT[b-1].ini++;
	return true;


}

bool Arithmex1::eraseEdge(int a,int b){//ɾ����
	if(graph[a-1].existedge(b)){
		node* current=&graph[a-1];
		while(current->next!=NULL){
			if(current->next->id==b){
				if(current->next->next!=NULL){
					current->next=current->next->next;
					graph[b-1].ini--;
					return true;
				}else{
					current->next=NULL;
					graph[b-1].ini--;
					return true;
				}
			}
					current=current->next;
		}
//		return false;
	}
	return false;
}
bool Arithmex1::create(){
//	cout<<n<<e;
		srand(15);//�������������
//	srand((unsigned)time(NULL));
		graph=new node[n];//��һ��װ��node���ף�������
		for(int i=0;i<n;i++){
			graph[i].init(1,i+1);//���Ǹ��ϳ�ֵ��Ȩ��Ϊ1�����Ϊi+1;
		}
		int j=0;
		while(j<e){
			int tmp1=rand()%n+1;//��ӦID

			int tmp2=rand()%n+1;//dui
//			cout<<tmp1<<" "<<tmp2<<"wae"<<endl;
			if(!graph[tmp1-1].existedge(tmp2)){
				insertEdge(tmp1,tmp2);
//				graph[tmp2-1].ini++;
			}else{
				continue;
			}
			j++;
		}
}

bool Arithmex1::transpose(){
	graphT=new node[n];
	for(int i=0;i<n;i++){
		graphT[i].init(1,i+1);//���Ǹ��ϳ�ֵ��Ȩ��Ϊ1�����Ϊi+1;
	}
	for(int i=0;i<n;i++){
		node* current=&graph[i];
		while(current->next!=NULL){
//			cout<<current->next->id<<" ";
//			void print();
			insertEdgeT(current->next->id,i+1);
			current=current->next;
		}
//		cout<<endl;
	}
}

void Arithmex1::print(){
	for(int i=0;i<n;i++){
		cout<<graph[i].id<<" "<<"==>  ";
		node* current=&graph[i];
		while(current->next!=NULL){
			cout<<current->next->id<<" ";
			current=current->next;
		}
		cout<<endl;
	}
}

void Arithmex1::printT(){
	for(int i=0;i<n;i++){
		cout<<graphT[i].id<<"==>  ";
		node* current=&graphT[i];
		while(current->next!=NULL){
			cout<<current->next->id<<" ";
			current=current->next;
		}
		cout<<endl;
	}
}

void Arithmex1::dfs(int start){
	//��������
	node* current=&graph[start-1];//�õ�Դ��λ��

	stack<int> ppid;//��¼ѹ��ջʱ��������
	stack<node*> dfss;//��¼ѹ��ջ��node����һ���̶���id��ֻ��Ҫ��id�����
	ppid.push(-1);//��ʼ��������Ϊ-1
	dfss.push(current);//���뵱ǰ��
	while(!dfss.empty()){
		node* newnode=dfss.top();//�õ�node
//		cout<<"��һ��ѭ��"<<newnode->id<<endl;
		dfss.pop();
		int tpid=ppid.top();//��ǰ��newnodeѺ��ջʱ��������
		ppid.pop();//��ǰ�ڵ�������
		//tpid��ջ�ڣ���һ��=pro[newnode->id-1].pid
//		cout<<" "<<tpid<<"(()))(()"<<pro[newnode->id-1].pid<<"]]]]"<<endl;
		if(pro[newnode->id-1].color==0){//�������ɫ=0
			pro[newnode->id-1].color =1;//pop������ʽ�������㣬���ɫ
			pro[newnode->id-1].distime=++time;//����ʱ��
			node* current=&graph[newnode->id-1];//�ҵ�ͼ������λ�þͿ��Ա�������

			int num=0;//�Ƿ��ڣ�ֻҪpush��ȥ�ڵ㣬˵����û����ɣ���ɵĲű��
//			if(current->next==NULL||pro[current->next->id]==2)

			while(current!=NULL&&current->next!=NULL){//�������ڽ�����

				if(pro[current->next->id-1].color ==0){//���û���������

//					current->next->pid=newnode->id;//�õ���pid,������µõ����µģ�Ҳ����!!!!
					pro[current->next->id-1].pid=newnode->id;//��ʱ������µ�pid
					dfss.push(current->next);//ѹ��ջ
					ppid.push(newnode->id);//�����Ӧ��pid
//					cout<<"����"<<current->next->id<<endl;
					num++;//����δ���
				}else if(pro[current->next->id-1].color==1){//����ҵ��˻�ɫ�ģ����رߡ�

//					cout<<current->id<<"shiyan"<<endl;
//					cout<<current->next->id<<"shiyan"<<endl;
					change=eraseEdge(newnode->id,current->next->id);//ɾ��
//					print();
				}
				if(!change){

					current=current->next;
				}else{
					change=false;
				}
				//ȥ��һ��,next����=null��Ҳ���ܲ��ǣ���֮���˸�current-��next����û�б���
			}
//			cout<<num<<"wwwww"<<endl;

			if(num==0){//Ҷ�ӽڵ�������ýڵ㣬���ڵ����Ϊ0
				pro[newnode->id-1].color=2;//��ɫ
				pro[newnode->id-1].fintime=++time;
				//��ʼ׷����Դ

//				if(tpid!=ppid.top()){//��pid֮ͬǰ��һ��
				int tmpid=pro[newnode->id-1].pid;
				if(!ppid.empty()){

					while(tmpid!=ppid.top()){
//						/cout<<tmpid<<"out"<<endl;
						pro[tmpid-1].color=2;
						pro[tmpid-1].fintime=++time;
						tmpid=pro[tmpid-1].pid;
					}
				}else{
//					pro[tmpid-1].color=2;
//					pro[tmpid-1].fintime=++time;
//	//				tmpid=pro[tmpid-1].pid;
					while(tmpid!=-1){
//														cout<<tmpid<<"pout"<<endl;
										pro[tmpid-1].color=2;
										pro[tmpid-1].fintime=++time;
										tmpid=pro[tmpid-1].pid;
									}
				}
			}
		}else if(pro[newnode->id-1].color==2){//��֮ǰ�Ѿ�����
//			cout<<"weq???"<<tpid<<endl;
			int tmpid=tpid;
			if(!ppid.empty()){
				while(tmpid!=ppid.top()){
//					cout<<tmpid<<"pout"<<endl;
					pro[tmpid-1].color=2;
					pro[tmpid-1].fintime=++time;
					tmpid=pro[tmpid-1].pid;
				}
			}else{
//				pro[tmpid-1].color=2;
//				pro[tmpid-1].fintime=++time;
////				tmpid=pro[tmpid-1].pid;
				while(tmpid!=-1){
//									cout<<tmpid<<"pout"<<endl;
					pro[tmpid-1].color=2;
					pro[tmpid-1].fintime=++time;
					tmpid=pro[tmpid-1].pid;
				}
			}
		}

	}
}


int Arithmex1::maxdis(){
	int* maxpid;
	maxpid=new int[n];
	for(int j=0;j<n;j++){//���볤��
					maxpid[j]=-1;
				}
	int* tmppid;
	tmppid=new int[n];
	for(int j=0;j<n;j++){//���볤��
					tmppid[j]=-1;
				}
	int lastid=0;
	int realastid=-1;
	int maxdis=0;
	int cc=0;
	for(int i=0;i<n;i++){//��������
//		cout<<graph[i].ini<<endl;
		if((graph[i].ini==0)){//���==0
			cc++;
			int tis[n];//tip�����Դ��
			for(int j=0;j<n;j++){//���볤��
				tis[j]=-1;
			}
			tis[i]=0;//���Լ��ľ���Ϊ0
			int tmpdis=0;
//			tis[i]=1;
			node* current=&graph[i];//�õ�Դ��λ��
			queue<node*> tmp;
			tmp.push(current);//ͷ���

			while(!tmp.empty()){
				node* tt=tmp.front();//ͷ���
				tt=&graph[tt->id-1];//�ҵ��������е�λ��
				tmp.pop();
				node* cnode=tt;

				while(cnode->next!=NULL){//�������ڽ�����
					tmp.push(cnode->next);//�������
					tis[cnode->next->id-1]=tis[tt->id-1]+1;
					tmpdis=tis[cnode->next->id-1];
//					cout<<tt->id<<"->>"<<cnode->next->id<<"xs"<<tmpdis<<" "<<"]]";
					lastid=cnode->next->id;
//					cout<<"������"<<tt->id<<"now��"<<cnode->next->id<<" ";
					tmppid[cnode->next->id-1]=tt->id;
					cnode=cnode->next;//ȥ��һ��
				}
				if(cnode->next==NULL){
					lastid=cnode->id;
				}

			}


			if(maxdis<tmpdis){
				realastid=lastid;
				maxdis=tmpdis;
				maxpid=tmppid;
				for(int j=0;j<n;j++){//���볤��
					maxpid[j]=tmppid[j];
//					cout<<tmppid[j]<<"||"<<maxpid[j]<<" ";
				}
				cout<<endl;
				tmppid=new int[n];
				for(int j=0;j<n;j++){//���볤��
					tmppid[j]=-1;
				}
			}
		}

	}
	tmppid=new int[maxdis+1];
	for(int j=0;j<maxdis+1;j++){//���볤��
		tmppid[j]=-1;
	}
	if(realastid!=-1)lastid=realastid;
	int jianyan=lastid;
//	cout<<lastid<<"wqe"<<endl;
	tmppid[maxdis]=lastid;
	int count=maxdis-1;
//	count=count-1;
	while(jianyan!=-1){
//		cout<<jianyan<<" ";
		jianyan=maxpid[jianyan-1];
		tmppid[count]=jianyan;
		count--;
//		cout<<jianyan<<" ";
	}
	cout<<endl;
	for(int j=0;j<maxdis+1;j++){//���볤��
		cout<<tmppid[j]<<" ";
	}
	cout<<endl;
//	cout<<"ѭ��������"<<cc<<endl;
	return maxdis;
}
void Arithmex1::dag(){
	for(int i=0;i<n;i++){
		if(pro[i].color==0)
			dfs(i+1);
	}
//	print();
}

int Arithmex1::distance(int i){
	int source=i;
	node* current=&graph[source-1];//�õ�Դ��λ��
	int tip[n];//tip�����Դ��
	for(int j=0;j<n;j++){//��ǣ���û�б��ҵ���
		tip[j]=0;
	}
	int tis[n];//tip�����Դ��
	for(int j=0;j<n;j++){//���룬�ж�Զ
		tis[j]=-1;//��ʼ��Ϊ���ɴ�
	}
	tip[source-1]=-1;//��Ϊ�׽ڵ���Ϊ�ѱ��
	tis[source-1]=0;//��Դ��Ϊ0
	queue<node*> tmp;
	tmp.push(current);//ͷ���

	while(!tmp.empty()){
		node* tt=tmp.front();//ͷ���
		tt=&graph[tt->id-1];//�ҵ��������е�λ��
		tmp.pop();
		node* cnode=tt;
		while(cnode->next!=NULL){//�������ڽ�����
			if(tip[cnode->next->id-1]!=-1){//���û���������
				tmp.push(cnode->next);//�������
				tis[cnode->next->id-1]=tis[tt->id-1]+1;
				tip[cnode->next->id-1]=-1;//ͬʱ���ϱ�ǣ���ɨ��
//				cout<<cnode->next->id<<" "<<tis[cnode->next->id-1]<<" ]]";

			}
			cnode=cnode->next;//ȥ��һ��
		}
	}
	for(int i=0;i<n;i++){
		cout<<graph[i].id<<"�ľ�����==>  "<<tis[i];
		cout<<endl;
	}


}



void Arithmex1::qldfsT(int x){
	Tpro[x].color=1;//��ɫ
	Tpro[x].distime=++Time2nd;
	node* current=&graphT[x];//����xû�н���+1����ע�⡣
//	cout<<x<<" ";
	while(current->next!=NULL){
		int temp=current->next->id-1;
		if(Tpro[temp].color==0){
			cout<<temp+1<<" ";
			Tpro[temp].pid=x;
			qldfsT(temp);
		}
		current=current->next;
	}
	Tpro[x].color=2;
	Tpro[x].fintime=++Time2nd;
//	cout<<endl;
}
//void Arithmex1::qldfs(int x){
//	pro[x].color=1;//��ɫ
//	pro[x].distime=++time;
//	node* current=&graph[x];//����xû�н���+1����ע�⡣
////	cout<<x<<" ";
//	while(current->next!=NULL){
//		int temp=current->next->id-1;
//		if(pro[temp].color==0){
//			cout<<temp+1<<" ";
//			pro[temp].pid=x;
//			dfs(temp);
//		}
//		current=current->next;
//	}
//	pro[x].color=2;
//	pro[x].fintime=++time;
////	cout<<endl;
//}

void Arithmex1::qiangliantong(){
//	for(int i=0;i<n;i++){
//		if(pro[i].color==0){
//			qldfs(i);
////			cout<<endl;
////		cout<<"---------------------"<<endl;
//		}
//	}
	 helpsort sort[n];
//	 cout<<pro[0].fintime<<"[]";
	for(int i=0;i<n;i++){
		sort[i].time=pro[i].fintime;
		sort[i].id=i;
	}
	for(int i=0;i<n;i++){//ѡ��sort������ʱ������
		for(int j=i+1;j<n;j++){
			if(sort[i].time<sort[j].time){
				helpsort tmp=sort[j];
				sort[j]=sort[i];
				sort[i]=tmp;
			}
		}
	}
//	for(int j=0;j<n;j++){
//		cout<<sort[j].id+1<<"  "<<sort[j].time<<endl;
//	}
	Tpro=new nodePro[n];
	cout<<"ǿ��ͨ��֧"<<endl;
	for(int i=0;i<n;i++){
		if(Tpro[sort[i].id].color==0){//����ʱ��˳��Ӻ���ǰ����
			cout<<sort[i].id+1<<"-->";
			qldfsT(sort[i].id);
			cout<<endl;
		cout<<"---------------------"<<endl;
		}
	}

}

int main(){
	Arithmex1* ar=new Arithmex1(5,3);
	ar->create();
	ar->print();
	cout<<"----------------------------------------------------"<<endl;
//	ar->distance(2);
//	cout<<ar->eraseEdge(3,27);
	cout<<"----------------------------------------------------"<<endl;
	ar->transpose();
	ar->dag();
	ar->qiangliantong();
//	cout<<"��󳤶�Ϊ��"<<ar->maxdis()<<endl;
//	ar->printT();
	return 0;
}

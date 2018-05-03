/*
 * Arithmex1.cpp
 *
 *  Created on: 2018年4月17日
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
	int id=-1;//本身id
	int time=-1;//原id
};
//int *sort;//finish time 排序
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

bool Arithmex1::insertEdge(int a,int b){//插入边
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

bool Arithmex1::insertEdgeT(int a,int b){//插入边
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

bool Arithmex1::eraseEdge(int a,int b){//删除边
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
		srand(15);//设置随机数种子
//	srand((unsigned)time(NULL));
		graph=new node[n];//是一个装了node（首）的数组
		for(int i=0;i<n;i++){
			graph[i].init(1,i+1);//于是附上初值，权重为1，编号为i+1;
		}
		int j=0;
		while(j<e){
			int tmp1=rand()%n+1;//对应ID

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
		graphT[i].init(1,i+1);//于是附上初值，权重为1，编号为i+1;
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
	//链表属性
	node* current=&graph[start-1];//得到源点位置

	stack<int> ppid;//记录压入栈时的先驱点
	stack<node*> dfss;//记录压入栈的node，有一个固定的id，只需要用id与遍历
	ppid.push(-1);//起始点先驱点为-1
	dfss.push(current);//放入当前点
	while(!dfss.empty()){
		node* newnode=dfss.top();//得到node
//		cout<<"新一轮循环"<<newnode->id<<endl;
		dfss.pop();
		int tpid=ppid.top();//当前点newnode押出栈时的先驱点
		ppid.pop();//当前节点先驱点
		//tpid（栈内）不一定=pro[newnode->id-1].pid
//		cout<<" "<<tpid<<"(()))(()"<<pro[newnode->id-1].pid<<"]]]]"<<endl;
		if(pro[newnode->id-1].color==0){//如果其颜色=0
			pro[newnode->id-1].color =1;//pop出，正式找其它点，变灰色
			pro[newnode->id-1].distime=++time;//发现时间
			node* current=&graph[newnode->id-1];//找到图中它的位置就可以遍历链表

			int num=0;//是否变黑，只要push进去节点，说明都没有完成，完成的才变黑
//			if(current->next==NULL||pro[current->next->id]==2)

			while(current!=NULL&&current->next!=NULL){//遍历其邻接链表

				if(pro[current->next->id-1].color ==0){//如果没有做过标记

//					current->next->pid=newnode->id;//得到其pid,最后会更新得到最新的，也可以!!!!
					pro[current->next->id-1].pid=newnode->id;//随时会变会更新的pid
					dfss.push(current->next);//压入栈
					ppid.push(newnode->id);//这个对应的pid
//					cout<<"放入"<<current->next->id<<endl;
					num++;//操作未完成
				}else if(pro[current->next->id-1].color==1){//如果找到了灰色的，返回边。

//					cout<<current->id<<"shiyan"<<endl;
//					cout<<current->next->id<<"shiyan"<<endl;
					change=eraseEdge(newnode->id,current->next->id);//删除
//					print();
				}
				if(!change){

					current=current->next;
				}else{
					change=false;
				}
				//去下一个,next可能=null，也可能不是，总之，此个current-》next可能没有遍历
			}
//			cout<<num<<"wwwww"<<endl;

			if(num==0){//叶子节点或者无用节点，本节点可以为0
				pro[newnode->id-1].color=2;//黑色
				pro[newnode->id-1].fintime=++time;
				//开始追根溯源

//				if(tpid!=ppid.top()){//本pid同之前不一样
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
		}else if(pro[newnode->id-1].color==2){//早之前已经发现
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
	for(int j=0;j<n;j++){//距离长短
					maxpid[j]=-1;
				}
	int* tmppid;
	tmppid=new int[n];
	for(int j=0;j<n;j++){//距离长短
					tmppid[j]=-1;
				}
	int lastid=0;
	int realastid=-1;
	int maxdis=0;
	int cc=0;
	for(int i=0;i<n;i++){//遍历顶点
//		cout<<graph[i].ini<<endl;
		if((graph[i].ini==0)){//入度==0
			cc++;
			int tis[n];//tip，标记源点
			for(int j=0;j<n;j++){//距离长短
				tis[j]=-1;
			}
			tis[i]=0;//到自己的距离为0
			int tmpdis=0;
//			tis[i]=1;
			node* current=&graph[i];//得到源点位置
			queue<node*> tmp;
			tmp.push(current);//头结点

			while(!tmp.empty()){
				node* tt=tmp.front();//头结点
				tt=&graph[tt->id-1];//找到在链表中的位置
				tmp.pop();
				node* cnode=tt;

				while(cnode->next!=NULL){//遍历其邻接链表
					tmp.push(cnode->next);//推入队列
					tis[cnode->next->id-1]=tis[tt->id-1]+1;
					tmpdis=tis[cnode->next->id-1];
//					cout<<tt->id<<"->>"<<cnode->next->id<<"xs"<<tmpdis<<" "<<"]]";
					lastid=cnode->next->id;
//					cout<<"先驱是"<<tt->id<<"now是"<<cnode->next->id<<" ";
					tmppid[cnode->next->id-1]=tt->id;
					cnode=cnode->next;//去下一个
				}
				if(cnode->next==NULL){
					lastid=cnode->id;
				}

			}


			if(maxdis<tmpdis){
				realastid=lastid;
				maxdis=tmpdis;
				maxpid=tmppid;
				for(int j=0;j<n;j++){//距离长短
					maxpid[j]=tmppid[j];
//					cout<<tmppid[j]<<"||"<<maxpid[j]<<" ";
				}
				cout<<endl;
				tmppid=new int[n];
				for(int j=0;j<n;j++){//距离长短
					tmppid[j]=-1;
				}
			}
		}

	}
	tmppid=new int[maxdis+1];
	for(int j=0;j<maxdis+1;j++){//距离长短
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
	for(int j=0;j<maxdis+1;j++){//距离长短
		cout<<tmppid[j]<<" ";
	}
	cout<<endl;
//	cout<<"循环次数："<<cc<<endl;
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
	node* current=&graph[source-1];//得到源点位置
	int tip[n];//tip，标记源点
	for(int j=0;j<n;j++){//标记，有没有被找到过
		tip[j]=0;
	}
	int tis[n];//tip，标记源点
	for(int j=0;j<n;j++){//距离，有多远
		tis[j]=-1;//开始认为不可达
	}
	tip[source-1]=-1;//设为首节点认为已标记
	tis[source-1]=0;//距源点为0
	queue<node*> tmp;
	tmp.push(current);//头结点

	while(!tmp.empty()){
		node* tt=tmp.front();//头结点
		tt=&graph[tt->id-1];//找到在链表中的位置
		tmp.pop();
		node* cnode=tt;
		while(cnode->next!=NULL){//遍历其邻接链表
			if(tip[cnode->next->id-1]!=-1){//如果没有做过标记
				tmp.push(cnode->next);//推入队列
				tis[cnode->next->id-1]=tis[tt->id-1]+1;
				tip[cnode->next->id-1]=-1;//同时做上标记，已扫描
//				cout<<cnode->next->id<<" "<<tis[cnode->next->id-1]<<" ]]";

			}
			cnode=cnode->next;//去下一个
		}
	}
	for(int i=0;i<n;i++){
		cout<<graph[i].id<<"的距离是==>  "<<tis[i];
		cout<<endl;
	}


}



void Arithmex1::qldfsT(int x){
	Tpro[x].color=1;//灰色
	Tpro[x].distime=++Time2nd;
	node* current=&graphT[x];//这里x没有进行+1处理，注意。
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
//	pro[x].color=1;//灰色
//	pro[x].distime=++time;
//	node* current=&graph[x];//这里x没有进行+1处理，注意。
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
	for(int i=0;i<n;i++){//选择sort，根据时间排序
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
	cout<<"强连通分支"<<endl;
	for(int i=0;i<n;i++){
		if(Tpro[sort[i].id].color==0){//按照时间顺序从后向前遍历
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
//	cout<<"最大长度为："<<ar->maxdis()<<endl;
//	ar->printT();
	return 0;
}

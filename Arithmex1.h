/*
 * Arithmex1.h
 *
 *  Created on: 2018年4月17日
 *      Author: Yongbo
 */
#include<iostream>
#include<list>
#ifndef ARITHMEX1_H_
#define ARITHMEX1_H_
using namespace std;
struct nodePro{
public:
	int distime=-1;
	int fintime=-1;
	int pid=-1;//前驱点的id
	int color=0;//未发现
};

class Arithmex1 {
public:
	Arithmex1(int , int );
	virtual ~Arithmex1();

		int n=0;//顶点数
		int e=0;//边数
		int time=0;


		int numberOfV();
		int nummberofE();
		bool create() ;//是否存在边
		bool insertEdge(int,int);
			//这里应该有个edge的表示方式

		bool eraseEdge(int,int);
		int degree(int) ;
		int inDegree(int);
		int outDegree(int);
		int weight(int,int);//某一边的权重
		int distance(int);
		void dfs(int);
		int maxdis();
		void dag();
//		其他方法
		bool directed();
		void print();
};


struct node{
public:
	node* next=NULL;//下一个
	int weight=-1;
	int ini=0;//入度
	int id=-1;//本node的编号
//	int nid=-1;//下一个node的编号
public:
	void init(node* next,int length,int id){//初始化方法
		this->next=next;
		this->weight=length;
	}
	void init(int length,int id){//初始化方法
		weight=length;
		this->id=id;
	}
	void init(int id){//初始化方法
		this->id=id;
	}
	bool existedge(int i){
		node* current=this;
		if(i==id){
			return true;
		}//自环
		while(current->next!=NULL){
			if(current->next->id==i){
				return true;
			}
			current=current->next;
		}
		return false;
	}

};
#endif /* ARITHMEX1_H_ */

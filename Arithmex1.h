/*
 * Arithmex1.h
 *
 *  Created on: 2018��4��17��
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
	int pid=-1;//ǰ�����id
	int color=0;//δ����
};

class Arithmex1 {
public:
	Arithmex1(int , int );
	virtual ~Arithmex1();

		int n=0;//������
		int e=0;//����
		int time=0;


		int numberOfV();
		int nummberofE();
		bool create() ;//�Ƿ���ڱ�
		bool insertEdge(int,int);
			//����Ӧ���и�edge�ı�ʾ��ʽ

		bool eraseEdge(int,int);
		int degree(int) ;
		int inDegree(int);
		int outDegree(int);
		int weight(int,int);//ĳһ�ߵ�Ȩ��
		int distance(int);
		void dfs(int);
		int maxdis();
		void dag();
//		��������
		bool directed();
		void print();
};


struct node{
public:
	node* next=NULL;//��һ��
	int weight=-1;
	int ini=0;//���
	int id=-1;//��node�ı��
//	int nid=-1;//��һ��node�ı��
public:
	void init(node* next,int length,int id){//��ʼ������
		this->next=next;
		this->weight=length;
	}
	void init(int length,int id){//��ʼ������
		weight=length;
		this->id=id;
	}
	void init(int id){//��ʼ������
		this->id=id;
	}
	bool existedge(int i){
		node* current=this;
		if(i==id){
			return true;
		}//�Ի�
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

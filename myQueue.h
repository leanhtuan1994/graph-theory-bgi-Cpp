#pragma once
#include <iostream>

#define MAXSTACK 100
typedef struct node{
	int data;
	struct node *next;
}NODE;

typedef struct Queue{
	NODE *front;
	NODE *rear;
}QUEUE;

void pushQueue(QUEUE &Q, int x){
	NODE *p = new NODE;
	p->data = x;
	if (Q.front == NULL) Q.front = p;
	else Q.rear->next = p;
	Q.rear = p;
	p->next = NULL;
}
int popQueue(QUEUE &Q){
	NODE *p;
	int x;
	if (Q.front == NULL){
		return -1;
	}
	else{
		p = Q.front;
		x = p->data;
		Q.front = p->next;
		delete p;
		return x;
	}
}

typedef struct stack{
	int sp;
	int data[MAXSTACK];
}STACK;

bool empty(STACK &st){
	if (st.sp == -1){
		return true;
	}
	else return false;
}

int pushStack(STACK &stack, int x){
	if (stack.sp == MAXSTACK - 1) return 0;
	stack.data[++stack.sp] = x;
	return 1;
}

int popStack(STACK &stack, int &x){
	if (stack.sp == -1) return 0;
	x = stack.data[stack.sp--];
	return 1;
}

int getStack(STACK &stack)	 {
	return stack.data[stack.sp];
}
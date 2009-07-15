
#include "list.h"

void NodeInit(node_t& n,void *data)
{
	n.data=data;
	n.next=NULL;
	n.prev=NULL;
}

void ListInit(list_t& l)
{
	l.first=NULL;
	l.last=NULL;
	l.length=0;
}

void ListAppend(list_t& l,node_t& n)
{
	l.length++;
	if (l.first==NULL) {
		l.first=&n;
		l.last=&n;
		return;
	}
	n.prev=l.last;
	l.last->next=&n;
	l.last=&n;
}

void ListInsertAfter(list_t& l,node_t& n,node_t& ntarget)
{		
	if (&ntarget==l.last) {
		l.length++;	
		ntarget.next=&n;
		n.prev=&ntarget;
		n.next=NULL;
		l.last=&n;
		return;
	}
	
	ntarget.next->prev=&n;
	n.next=ntarget.next;
	ntarget.next=&n;
	n.prev=&ntarget;
}

void ListInsertBefore(list_t& l,node_t& n,node_t& ntarget)
{
	l.length++;
	if (&ntarget==l.first) {		
		l.first=&n;
		n.next=&ntarget;
		ntarget.prev=&n;
		return;
	}

	n.next=&ntarget;
	n.prev=ntarget.prev;
	ntarget.prev->next=&n;
	ntarget.prev=&n;
}

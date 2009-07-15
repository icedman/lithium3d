
#ifndef _LITH_LIST_H_
#define _LITH_LIST_H_

#include "stdtypes.h"

typedef struct _node_t {
	void *data;
	_node_t *prev;
	_node_t *next;
} node_t,*pnode_t;

void NodeInit(node_t& n,void *data);

typedef struct {
	pnode_t first;
	pnode_t last;
	int length;
} list_t,*plist_t;

void ListInit(list_t& l);
void ListAppend(list_t& l,node_t& n);
void ListInsertAfter(list_t& l,node_t& n,node_t& ntarget);
void ListInsertBefore(list_t& l,node_t& n,node_t& ntarget);

#endif // _LITH_LIST_H_
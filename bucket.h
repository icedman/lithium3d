
#ifndef _LITH_BUCKET_H_
#define _LITH_BUCKET_H_

#include "list.h"

#define MAX_BUCKETS 512

typedef struct {
	list_t buckets[MAX_BUCKETS];
} bucket_t,*pbucket_t;

void BucketInit(bucket_t& b);
void BucketAppend(bucket_t& b,node_t& n,int index);

#endif // _LITH_BUCKET_H_
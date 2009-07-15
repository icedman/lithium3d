
#include "bucket.h"

void BucketInit(bucket_t& b)
{
	for(int i=0;i<MAX_BUCKETS;i++) {
		ListInit(b.buckets[i]);
	}
}

void BucketAppend(bucket_t& b,node_t& n,int index)
{
	ListAppend(b.buckets[index],n);
}
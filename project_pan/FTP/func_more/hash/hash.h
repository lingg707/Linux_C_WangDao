#ifndef _HASH_H_
#define _HASH_H_
//双向链表的哈希
typedef struct hash hash_t;
typedef unsigned int (*hashfunc_t)(unsigned int,void*);//哈希函数

/*建立哈希表*/
hash_t* hash_alloc(unsigned int buckets,hashfunc_t hash_func); 
/*查找关键字*/
void* hash_lookup_entry(hash_t *hash,void* key,unsigned int key_size);
/*哈希表中添加记录*/
void hash_add_entry(hash_t *hash,void *key,unsigned int key_size,
                    void *value,unsigned int value_size);
/*释放哈希表*/
void hash_free_entry(hash_t *hash,void *key,unsigned int key_size);

#endif


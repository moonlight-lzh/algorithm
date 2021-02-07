/** 双链表节点 */
struct DNode {
    int key;                    // 键
    int value;                  // 值
    struct DNode *prior;        // 前驱指针
    struct DNode *next;         // 后继指针
    struct DNode *next_hash;    // 拉链法解决哈希冲突
};

/** 双链表 */
typedef struct {
    struct DNode *head;         // 双向链表头指针---Recently Used
    struct DNode *tail;         // 双向链表尾指针---Least Recently Used
    int size;                   // 节点数
} DLinkList;

/** 哈希表 */
typedef struct {
    struct DNode **map;         // 哈希表
    int capacity;               // 哈希容量
} HashMap;

/** LRUCache缓存机制 */
typedef struct {
    HashMap hashMap;          // 哈希表
    DLinkList linkedList;      // 双链表
    int capacity;              // 缓存容量
} LRUCache;

/** 生成双链表节点 */
struct DNode *createNode(int key, int value) {
    struct DNode *node = (struct DNode *) malloc(sizeof(struct DNode));
    node->key = key;
    node->value = value;
    node->next = NULL;
    node->prior = NULL;
    node->next_hash = NULL;
    return node;
}

/** 初始化双链表 */
void initLinkedList(DLinkList *L) {
    L->head = createNode(-1, -1);    // 虚拟头指针
    L->tail = createNode(-1, -1);    // 虚拟尾指针
    L->head->next = L->tail;
    L->tail->prior = L->head;
    L->size = 0;
}

/** 初始化哈希表 */
void initHashMap(HashMap *hashMap, int capacity) {
    hashMap->map = (struct DNode **) calloc(capacity, sizeof(struct DNode *));
    hashMap->capacity = capacity;
}

/** 创建LRU缓存机制 */
LRUCache *lRUCacheCreate(int capacity) {
    LRUCache *cache = (LRUCache *) malloc(sizeof(LRUCache));
    initLinkedList(&cache->linkedList);
    initHashMap(&cache->hashMap, capacity);
    cache->capacity = capacity;
    return cache;
}

/** 哈希表取值值 */
struct DNode *getMapValue(HashMap hashMap, int key) {
    int index = key % hashMap.capacity;     // 取余法
    for (struct DNode *cur = hashMap.map[index]; cur != NULL; cur = cur->next_hash) {
        if (cur->key == key) {
            return cur;
        }
    }
    return NULL;
}

/** 哈希表存值*/
void putMapValue(HashMap *hashMap, struct DNode *node) {
    int index = node->key % hashMap->capacity;     // 取余法
    node->next_hash = hashMap->map[index];      // 拉链法
    hashMap->map[index] = node;
}

/** 根据键移除哈希表数据 */
void removeMapKey(HashMap *hashMap, int key) {
    int index = key % hashMap->capacity;     // 取余法
    struct DNode *cur = hashMap->map[index];
    if (cur == NULL) {
        return;
    }
    if (cur->key == key) {      // 节点正好存放在哈希表（数组）上
        hashMap->map[index] = cur->next_hash;
        return;
    }
    while (cur && cur->next_hash) {
        if (cur->next_hash->key == key) {
            cur->next_hash = cur->next_hash->next_hash;     // 节点位于哈希表（数组）的拉链中
            return;
        }
        cur = cur->next_hash;
    }
}

/** 双链表删除节点 */
void removeNode(struct DNode *node) {
    node->prior->next = node->next;
    node->next->prior = node->prior;
}

/** 双链表头插节点 */
void insertHead(DLinkList *L, struct DNode *node) {
    node->next = L->head->next;
    node->prior = L->head;
    L->head->next->prior = node;
    L->head->next = node;
    L->size++;
}

/** 移动节点至链表头部 */
void moveToHead(DLinkList *L, struct DNode *node) {
    removeNode(node);
    L->size--;
    insertHead(L, node);
}

/** 移除双链表尾部节点 */
void removeTail(DLinkList *L) {
    if (L->head->next == L->tail) {   // 双链表为空
        return;
    }
    struct DNode *node = L->tail->prior;
    removeNode(L->tail->prior);
    free(node);
    L->size--;
}

/** 存放LRU缓存数据 */
void lRUCachePut(LRUCache *obj, int key, int value) {
    if (!obj) {
        return;
    }
    struct DNode *node = getMapValue(obj->hashMap, key);        // 查询哈希获取节点
    if (node) {
        node->value = value;
        moveToHead(&obj->linkedList, node);     // 更新为最新使用Recently Used
    } else {
        node = createNode(key, value);      // 存放一个不存在的数据，新增节点
        if (obj->linkedList.size == obj->capacity) {        // 双链表中数据达到缓存上限
            removeMapKey(&obj->hashMap, obj->linkedList.tail->prior->key);      // 移除HashMap中的值
            removeTail(&obj->linkedList);       // 删除尾部数据Least Recently Used
        }
        insertHead(&obj->linkedList, node);     // 头插法新增节点
        putMapValue(&obj->hashMap, node);
    }
}

/** 获取LRU缓存数据 */
int lRUCacheGet(LRUCache *obj, int key) {
    if (obj == NULL) {
        return -1;
    }
    struct DNode *node = getMapValue(obj->hashMap, key);
    if (node == NULL) {
        return -1;
    }
    moveToHead(&obj->linkedList, node);     // 更新为最新使用Recently Used
    return node->value;
}

/** 释放缓存数据 */
void lRUCacheFree(LRUCache *obj) {
    // 释放双链表中的所有节点
    struct DNode *node;
    for (struct DNode *cur = obj->linkedList.head; cur != NULL;) {
        node = cur->next;
        free(cur);
        cur = node;
    }
    free(obj->hashMap.map);     // 释放HashMap二级指针
}

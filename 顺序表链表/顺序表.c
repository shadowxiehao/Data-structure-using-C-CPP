#include<stdio.h>
#include<stdlib.h>

//软件1702 谢昊 171304214
typedef int SeqType; //存储单元类型

typedef struct {
    SeqType *elem; //存储空间基地址
    int length; //当前长度
    int listsize; //当前分配的存储容量（以sizeof(ElemType)为单位）
} SqList;

/**
* 创建顺序表
*/
SqList createList_sq() {
    //SqList list;
    //return list;

    SqList* list = (SqList*)malloc(sizeof(SqList));
    return *list;
}


/**
* 初始化顺序表
* 返回1 表示初始化成功
* 返回1 表示初始化成功
* 返回1 表示初始化成功
* 返回0 表示初始化失败
*/
int initList_sq(SqList *L, int LIST_INIT_SIZE) { //只有在C++中才会有引用的存在
    L->elem = (SeqType *)malloc(sizeof(SeqType) * LIST_INIT_SIZE);
    if (!L->elem)
        return 0; //内存分配失败，存储空间不够
    L->length = 0; //表示顺序表为空
    L->listsize = LIST_INIT_SIZE; //表示顺序表里，最大存储单元个数
    return 1;
}

/**
* 插入顺序表
* 下标是负数就插入到结尾
*/
int insertList_sq(SqList *L, int index, SeqType val, int LISTINCREMENT) {//LISTINCREMENT是指增加的elem长度
    ;
    int i;
    if (index > L->length) { //存储的下表超出顺序表实际的长度
        printf("%s", "插入的下标超出顺序表的实际长度");
        return 0;
    }
    if (index < 0) //下标是负数，插入到结尾
        index = L->length;
    if (L->length == L->listsize) { //顺序表的存储单元已经存满
        printf("%s", "顺序表的存储单元已满，继续分配新的存储单元。");
        SeqType *newBase = (SeqType*)realloc(L->elem,
            (L->listsize + LISTINCREMENT) * sizeof(SeqType)); //继续分配存储单元
        if (!newBase) {
            printf("%s", "分配内存单元失败");
            return 0;
        }
        L->elem = newBase;
        L->listsize += LISTINCREMENT;
    }
    //寻找合适的插入位置，index后面的元素向后移动
    for (i = L->length; i > index; i--) {
        L->elem[i] = L->elem[i - 1]; //向后移动
    }
    L->elem[index] = val; //插入元素
    L->length++;
    return 1;
}
//将元素插入到指定的位置。插入之前，需要先判断顺序表中是否已经存满，再根据需要新增存储单元，最后插入元素。
/**
* 插入顺序表（结尾的位置）
* 与上面的函数是重名函数，这叫函数重载，在C++里面支持
*/


int insertList_st(SqList *L, SeqType val) {//这里val是一个SeqType型的值,之前定义SeqType为int 
    return insertList_sq(L, L->length, val, 1);
}

/**
* 删除指定的元素
* 返回0 找不到指定的元素，删除失败。
* 返回1 找到待删除的元素，删除成功。
*/
int removeList_sq(SqList *L, SeqType val) {
    int index = -1; //记录匹配到的下标
    for (int i = 0; i < L->length; i++) {
        if (L->elem[i] == val) {
            //找到匹配的val，结束循环
            index = i;
            break;
        }
    }
    if (index < 0)
        return 0;
    for (; index < L->length - 1; index++) {
        L->elem[index] = L->elem[index + 1];
    }
    L->length--;
    return 1;
}

//删除指定元素，需要先找到下标。依次移动下标后面的结点，修改length值。
/**
* 根据下标删除是指定的结点，并返回元素的值
* 返回0 下标超出顺序表长度，删除失败。
* 返回1 下标正确，删除元素，并且将已删除元素值转给elem
*/
int removeList_sqq(SqList *L, int index, SeqType elem) {
    if (index >= L->length) //下标超出顺序表的长度
        return 0;
    index = index < 0 ? L->length : index; //下标负数表示删除最后一个节点
    elem = L->elem[index];
    for (int i = index; i < L->length - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }
    L->length--;
    return 1;
}

/**
* 销毁顺序表
*/
void destoryList_sq(SqList *L) {
    free(L->elem); //释放存储空间
    L->length = 0;
    L->listsize = 0;
    //  free(&L);
}

int main_sequence_list()
{
    SqList L = createList_sq();
    printf("%d\n", initList_sq(&L, 10));//这里设置结构体中elem长度为10 可自行更改
    if (insertList_st(&L, 1)) {
        printf("%s\n", "insertsuccess");
    }
    if (removeList_sq(&L, 1))
        printf("delete success");
    destoryList_sq(&L);
    getchar();
    return 0;
}

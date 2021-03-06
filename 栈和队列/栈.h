// 栈和队列.c: 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 10
#define LISTINCREMENT 2
typedef char StackType; //存储单元类型
typedef struct stackNode {
    StackType *elem; //存储空间基地址
    int length; //当前长度
    int listsize; //当前分配的存储容量（以sizeof(ElemType)为单位）
}Stack;



Stack* initStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->elem = (StackType *)malloc(sizeof(StackType) * LIST_INIT_SIZE);
    if (!stack->elem)
        exit(0) ; //内存分配失败，存储空间不够
    stack->length = 0;
    stack->listsize = LIST_INIT_SIZE;
    return stack;
}

//栈为空，返回0，不为空返回非0。
int isEmptyStack(Stack *stack) {
    return stack->length;
}

//取出栈顶元素，传值给形参elem，但不删除栈顶元素。由于采用的是引用的方式，
//因此形参值的改变可以传给实参。如果栈为空，返回0，栈非空，返回1。
int top(Stack *stack, StackType *elem) {
    if (stack->length == 0)
        return 0;
    *elem = stack->elem[stack->length - 1];
    return 1;
}

//取出并删除栈顶元素，传值给形参elem。由于采用的是引用的方式，
//因此形参值的改变可以传给实参。如果栈为空，返回0，栈非空，返回1。
int pop(Stack *stack, StackType *elem) {
    if (stack->length > 0) {
        *elem = stack->elem[--stack->length];
        return 1;
    }
    return 0;
}

//在栈顶插入元素。若，当前栈已满，继续分配内存单元再插入。返回1表示入栈成功，返回0表示入栈失败。
int push(Stack *stack, StackType data) {
    if (stack->length == stack->listsize) { //顺序表的存储单元已经存满
        printf("顺序表的存储单元已满，继续分配新的存储单元。");
        StackType* newBase = (StackType*)realloc(stack->elem,
            (stack->listsize + LISTINCREMENT) * sizeof(StackType)); //继续分配存储单元
        if (!newBase) {
            printf("分配内存单元失败");
            return 0;
        }
        stack->elem = newBase;
        stack->listsize += LISTINCREMENT;
    }
    stack->elem[stack->length] = data;
    stack->length++;
    return 1;
}

/*
需要改StackType为int
*/
void conversion()
{// 把十进制转换为八进制
    StackType *e = (StackType*)malloc(sizeof(StackType));

    Stack *S = initStack();
    int N;
    scanf("%d", &N);

    while (N)
    {
        push(S, N % 8);	N = N / 8;
    }
    while (isEmptyStack(S))
    {
        pop(S, e); printf("%d", *e);
    }
}

int test_main()
{
    StackType *elem = (StackType*) malloc(sizeof(StackType));
    StackType data=0;

    Stack *stack = initStack();

    if (isEmptyStack(stack)==0) {//判断空链表
        printf("empty");
    }
    else {
        printf("not empty,the length is %d\n", isEmptyStack(stack));
    }

    data = 1;
    push(stack, data);

    if (top(stack, elem)) {
        printf("top%d\n",*elem);
    }

    if (isEmptyStack(stack)==0) {//判断空链表,或数量
        printf("empty");
    }
    else {
        printf("not empty,the length is %d\n", isEmptyStack(stack));
    }
    pop(stack, elem);
    printf("pop%d\n",*elem);
    getchar();
    return 0;
}


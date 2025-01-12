#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ListNode{
    char no[20];
    char name[50];
    float price;
    struct ListNode *next;
};

struct ListNode* locateelem(struct ListNode* head, char* name){
    struct ListNode* temp = head;
    while(temp != NULL){
        if(strcmp(temp->name, name) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void printbook(struct ListNode* book){
    if(book != NULL){
        printf("编号: %-10s 书名: %-20s 价格: %.2f\n", book->no, book->name, book->price);
    }else{
        printf("没有找到这本书。\n");
    }
}

void listinsert(struct ListNode** head, char* no, char* name, float price){
    struct ListNode* new_book = (struct ListNode*)malloc(sizeof(struct ListNode));
    strcpy(new_book->no, no);
    strcpy(new_book->name, name);
    new_book->price = price;
    new_book->next = *head;
    *head = new_book;
}

void printall(struct ListNode* head){
    struct ListNode* temp = head;
    while(temp != NULL){
        printbook(temp);
        temp = temp->next;
    }
}

void sortbook(struct ListNode* head){
    struct ListNode* i, *j;
    for(i = head; i != NULL; i = i->next){
        for(j = i->next; j != NULL; j = j->next){
            if(i->price > j->price){
                char temp_no[20];
                char temp_name[50];
                float temp_price;

                strcpy(temp_no, i->no);
                strcpy(temp_name, i->name);
                temp_price = i->price;

                strcpy(i->no, j->no);
                strcpy(i->name, j->name);
                i->price = j->price;

                strcpy(j->no, temp_no);
                strcpy(j->name, temp_name);
                j->price = temp_price;
            }
        }
    }
}

void deletebook(struct ListNode** head, struct ListNode* book){
    if(book == NULL){
        printf("没有找到这本书。\n");
        return;
    }
    if(*head == book){
        *head = book->next;
    }else{
        struct ListNode* temp = *head;
        while(temp != NULL && temp->next != book){
            temp = temp->next;
        }
        if(temp != NULL){
            temp->next = book->next;
        }
    }
    free(book);
}

int main()
{
    struct ListNode* l = NULL;
    int n = 0;
    do
    {
        
        printf("按键:1:按书名查找 2:按书名添加 3:按书名删除 4:按定价排序 -1:退出\n请输入:");
        scanf("%d", &n);
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
            if (c >= '0' && c <= '9')
            {
                ungetc(c, stdin); // 如果是数字，将其放回输入缓冲区
                break;
            }
        }
        switch (n)
        {
        case 1:
        {
            printf("输入要查找的书名(拼音&字母):");
            char name1[50];
            scanf("%s", name1);
            printbook(locateelem(l, name1));
            break;
        }
        case 2:
        {
            printf("输入要增加的书名(拼音&字母):");
            char name[50];
            scanf("%s", name);
            printf("输入编号:");
            char no[20];
            scanf("%s", no);
            printf("输入价格:");
            float price = 0;
            scanf("%f", &price);
            listinsert(&l, no, name, price);
            printall(l);
            break;
        }
        case 3:
        {
            printf("输入要删除的书名(拼音&字母):");
            char name[50];
            scanf("%s", name);
            deletebook(&l, locateelem(l, name));
            printall(l);
            break;
        }
        case 4:
        {
            sortbook(l);
            printall(l);
            break;
        }
        case -1:
            printf("退出程序。\n");
            break;
        default:
            printf("无效的选择。\n");
            break;
        }
    } while (n != -1);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int val;
    struct ListNode *next;
} ListNode;

static int
count(ListNode *node)
{
    int count;

    if (node)
    {
        count = 1;
    }

    while ((node = node->next))
        count++;

    return count;
}

static void
addNode(ListNode *list, int val)
{
    ListNode *node = list;

    if (!list)
        return;

    /* Move to end of list. */
    while (node->next)
        node = node->next;

    node->next = malloc(sizeof(ListNode));
    node = node->next;
    node->val = val;
    node->next = NULL;

    return;
}

static void
printList(ListNode *list)
{
    if (list)
    {
        printf("%d\n", list->val);
        printList(list->next);
    }
}

ListNode *
merge(ListNode *list1, ListNode *list2)
{
    ListNode *list = NULL;
    ListNode *newList = NULL;
    while (list1 || list2)
    {
        if (list1 && list2)
        {
            if (list1->val < list2->val)
            {
                if (!newList)
                {
                    newList = list1;
                    list = newList;
                }
                else
                {
                    newList->next = list1;
                    newList = newList->next;
                }
                list1 = list1->next;
                newList->next = NULL;
            }
            else
            {
                if (!newList)
                {
                    newList = list2;
                    list = newList;
                }
                else
                {
                    newList->next = list2;
                    newList = newList->next;
                }
                list2 = list2->next;
                newList->next = NULL;
            }
        }
        else if (list1)
        {
            newList->next = list1;
            list1 = list1->next;
            newList = newList->next;
            newList->next = NULL;
        }
        else
        {
            newList->next = list2;
            list2 = list2->next;
            newList = newList->next;
            newList->next = NULL;
        }
    }

    return list;
}

ListNode *
mergeSort(ListNode *list)
{
    ListNode *list1 = list;
    ListNode *list2 = list;
    ListNode *prevNode;
    int length = count(list);

    if (length == 1)
        return list;

    length = length / 2;
    while (length > 0)
    {
        prevNode = list2;
        list2 = list2->next;
        length--;
    }
    prevNode->next = NULL;


    list1 = mergeSort(list1);
    list2 = mergeSort(list2);


    list = merge(list1, list2);


    return list;
    /* merge(list1, list2); */
}


int
main(int argc, char *argv[])
{
    ListNode *head = malloc(sizeof(*head));

    addNode(head, 10);
    addNode(head, 1);
    addNode(head, 1);
    addNode(head, 1);
    addNode(head, 1);
    addNode(head, 1);
    addNode(head, 1);
    addNode(head, 1);
    addNode(head, 34);
    addNode(head, 3);
    addNode(head, 123);
    addNode(head, 456);
    addNode(head, 1);
    addNode(head, 1);
    addNode(head, 1);
    addNode(head, 9);

    printList(head);
    printf("count: %d\n", count(head));

    head = mergeSort(head);

    printf("Done?\n");
    printList(head);

    printf("count: %d\n", count(head));

    while (head)
    {
        ListNode *node = head;
        head = head->next;
        free(node);
    }

    return 0;
}

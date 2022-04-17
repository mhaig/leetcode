#include <stdlib.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode
{
    int val;
    struct ListNode *next;
};

int count(struct ListNode* list)
{
    int count = 1;
    while ((list = list->next))
    {
        count++;
    }
    return count;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode* head = NULL;
    struct ListNode* leftSide = NULL;
    struct ListNode* rightSide = NULL;
    struct ListNode* last = NULL;
    int carry = 0;

    // Figure out longer list.
    if (count(l1) > count(l2))
    {
        leftSide = l1;
        rightSide = l2;
    }
    else
    {
        leftSide = l2;
        rightSide = l1;
    }

    head = leftSide;
    while (leftSide)
    {
        int left = leftSide->val;
        int right = (rightSide) ? rightSide->val : 0;
        leftSide->val = left + right + carry;
        carry = 0;
        if (leftSide->val > 9)
        {
            leftSide->val -= 10;
            carry = 1;
        }
        last = leftSide;
        leftSide = leftSide->next;
        rightSide = (rightSide) ? rightSide->next : NULL;
    }

    if (carry)
    {
        last->next = malloc(sizeof(struct ListNode));
        last->next->val = 1;
        last->next->next = NULL;
    }

    return head;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashListNode
{
    int val;
    int pos;
    struct HashListNode *next;
} HashListNode;

#define HASH_MAP_SIZE (10000)

HashListNode *
linklistRemove(HashListNode *list, int pos, int val)
{
    HashListNode *node = list;
    HashListNode *first = list;

    while (node)
    {
        if (node->val == val && node->pos == pos)
        {
            HashListNode *tempNode = node;
            node = node->next;
            free(tempNode);
            if (tempNode == first)
            {
                list = node;
                first = list;
            }
        }
        else
            node = node->next;
    }

    return list;
}

void
hashRemove(HashListNode **hashMap, int pos, int val)
{
    int hash = val % HASH_MAP_SIZE;
    HashListNode *list = hashMap[hash];
    if (list)
    {
        list = linklistRemove(list, pos, val);
        hashMap[hash] = list;
    }
}

int
hashInsert(HashListNode **hashMap, int pos, int val)
{
    int hash = val % HASH_MAP_SIZE;
    if (hashMap[hash] == NULL)
    {
        hashMap[hash] = malloc(sizeof(HashListNode));
        hashMap[hash]->val = val;
        hashMap[hash]->pos = pos;
        hashMap[hash]->next = NULL;
        return -1;
    }
    else
    {
        /* Make sure the exact val is in the hashmap. */
        HashListNode *list = hashMap[hash];
        HashListNode *last = NULL;
        while (list)
        {
            if (list->val == val)
            {
                return list->pos;
            }
            if (!list->next)
                last = list;
            list = list->next;
        }
        /* Not found so insert into list. */
        last->next = malloc(sizeof(HashListNode));
        last = last->next;
        last->val = val;
        last->pos = pos;
        last->next = NULL;
    }

    return -1;
}


int maximumUniqueSubarray(int* nums, int numsSize)
{
    int i, j, k;
    int tempSum;
    int maxSum = -1;
    int repeatIndex;
    HashListNode *hashMap[HASH_MAP_SIZE];
    memset(hashMap, 0, sizeof(hashMap));

    for (i = 0; i < numsSize; i++)
    {
        tempSum = nums[i];
        hashInsert(hashMap, i, nums[i]);
        repeatIndex = -1;

        /*  OK, fix this.  Don't need to reset j, just need to subtract i to
            first repeat and then continue.
        */
        for (j = (i+1); j < numsSize; j++)
        {
            /* See if number is not unique. */
            if ((repeatIndex = hashInsert(hashMap, j, nums[j])) != -1)
            {
                break;
            }
            tempSum += nums[j];
        }

        if (tempSum > maxSum)
        {
            maxSum = tempSum;
        }

        if (i == 0 && j == numsSize)
        {
            break;
        }

        /* Since i is moving, "clean" the hashmap. */
        for (k = i; k < j && k < numsSize; k++)
        {
            printf("cleaning...\n");
            hashRemove(hashMap, k, nums[k]);
        }
        if (repeatIndex != -1)
            i = repeatIndex;
    }

    /* Clean all of hash map. */
    for (i = 0; i < HASH_MAP_SIZE; i++)
    {
        if (hashMap[i])
        {
            HashListNode *list = hashMap[i];
            HashListNode *node;
            while (list)
            {
                node = list;
                list = node->next;
                free(node);
            }
        }
    }

    return maxSum;
}

int
main(int argc, char *argv[])
{
    int nums1[] = {4,2,4,5,6};
    int nums2[] = {5,2,1,2,5,2,1,2,5};
    int nums3[] = {10000};
    int nums4[] = {10000,1,10000,1,1,1,1,1,1};
    int nums5[] = {4751,5697,197,3468,9548,1096,1979,515,5140,2235,8351};
    int nums6[10000];
    int i;
    for (i = 0; i < 10000; i++)
    {
        nums6[i] = i + 1;
    }

    printf("%d\n", maximumUniqueSubarray(nums1, sizeof(nums1)/sizeof(int)));
    printf("%d\n", maximumUniqueSubarray(nums2, sizeof(nums2)/sizeof(int)));
    printf("%d\n", maximumUniqueSubarray(nums3, sizeof(nums3)/sizeof(int)));
    printf("%d\n", maximumUniqueSubarray(nums4, sizeof(nums4)/sizeof(int)));
    printf("%d\n", maximumUniqueSubarray(nums5, sizeof(nums5)/sizeof(int)));
    printf("%d\n", maximumUniqueSubarray(nums6, sizeof(nums6)/sizeof(int)));
    return 0;
}

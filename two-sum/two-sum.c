#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int index1 = 0;
    int index2 = 0;
    int i;
    int j;
    int found = 0;
    int* returnArray;

    for (i = 0; i < numsSize; i++)
    {
        for (j = i+1; j < numsSize; j++)
        {
            if (nums[i] + nums[j] == target)
            {
                index1 = i;
                index2 = j;
                found = 1;
                break;
            }
        }
        if (found)
            break;
    }

    returnArray = malloc(2*sizeof(*returnArray));
    returnArray[0] = index1;
    returnArray[1] = index2;
    *returnSize = 2;
    return returnArray;
}

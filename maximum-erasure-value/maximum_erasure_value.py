class Solution(object):

    def maximumUniqueSubarray(self, nums):

        temp_sum = 0
        maximum_sum = -1
        i = 0

        while i < len(nums):
            temp_sum = nums[i]
            repeated_values = {}
            repeated_values[nums[i]] = i
            j = i + 1
            while j < len(nums):
                if nums[j] in repeated_values.keys():
                    for k in range(i, repeated_values[nums[j]]):
                        temp_sum -= nums[k]
                        repeated_values[nums[k]] = -1
                    i = repeated_values[nums[j]]
                    break

                temp_sum += nums[j]
                repeated_values[nums[j]] = j

            if temp_sum > maximum_sum:
                maximum_sum = temp_sum

            i += 1

        return maximum_sum


solution = Solution()

print('{}'.format(solution.maximumUniqueSubarray([4,2,4,5,6])))
print('{}'.format(solution.maximumUniqueSubarray([5,2,1,2,5,2,1,2,5])))
print('{}'.format(solution.maximumUniqueSubarray([10000])))
print('{}'.format(solution.maximumUniqueSubarray([10000,1,10000,1,1,1,1,1,1])))
print('{}'.format(solution.maximumUniqueSubarray([4751,5697,197,3468,9548,1096,1979,515,5140,2235,8351])))


def cubic_algorithm(array):
    global_max_sum = 0;
    index_i = 0;
    """for each element of the array"""
    for i in array:
        local_max_sum = 0;
        #print("\n ******************************************************* value i:", i)
        #print("\n i to end array", array[index_i:len(array)])
        index_j = index_i +1
        """from index i to end of array"""
        for j in array[index_i:len(array)]:
            #print("\n i to j array:", array[index_i:index_j])  
            local_max_sum = 0;
            """from index i to index j"""
            if index_j == index_i:
                """do nothing"""
               # print("\n j and i are the same index")
            else:
                for k in array[index_i:index_j]:
                    #print("\n k loop ********************")
                    local_max_sum += k
                    #print("\n sum:", local_max_sum)                
                    if local_max_sum > global_max_sum:
                        global_max_sum = local_max_sum
            index_j+=1     
        index_i+=1
    return global_max_sum


def quadratic_algorithm_1(array):
    global_max_sum = 0;
    index_i = 0;
    for i in array:
        local_max_sum = 0;
        #print("\n ******************************************************* value i:", i)
        for j in array[index_i:len(array)]:
           # print("\n", array[index_i:len(array)])
            local_max_sum += j
            if local_max_sum > global_max_sum:
                global_max_sum = local_max_sum
        index_i+=1
    return global_max_sum

def quadratic_algorithm_2(array):
    global_max_sum = 0 
    local_sum = 0    
    """Preprocess the cumulative sums of the array in linear time"""
    cumulative_sums_array = [0] * len(array)
    for i in range(1, len(array)):
        cumulative_sums_array[i] = cumulative_sums_array[i-1] + array[i]    
    for i in range(len(array)):
        for j in range(i,len(array)):
            #print("\n", j)
            local_sum = cumulative_sums_array[j] - cumulative_sums_array[i-1]
            #print("\n local sum", local_sum)
            if local_sum > global_max_sum:
                global_max_sum = local_sum
            
    
    return global_max_sum

def divide_and_conquer_algorithm(array):
    global_max_sum = 0        
    global_max_sum = subarray_max_sum(array, 0, len(array)-1)       
    return global_max_sum

def subarray_max_sum(subarray, start, end):    
    if start == end:
        return subarray[start]
    mid = (start+end)//2
    #recursive calls on left, right, and middle possible subarrays
    left_max_sum = subarray_max_sum(subarray, start, mid)
    right_max_sum = subarray_max_sum(subarray, mid+1, end)
    middle_max_sum = middle_subarray_max_sum(subarray, start, mid, end)
    return max(left_max_sum, right_max_sum, middle_max_sum)


def middle_subarray_max_sum(subarray, start, mid, end):    
    left_sum = 0
    left_max_sum = 0
    right_sum = 0
    right_max_sum = 0    
    #recursively go from mid to left/start
    for i in range(mid, start-1, -1):
        left_sum += subarray[i]
        if left_max_sum < left_sum:
            left_max_sum = left_sum    
    #recursively go from mid to right/end
    for i in range(mid+1, end+1) : 
        right_sum += subarray[i]
        if right_max_sum < right_sum:
            right_max_sum = right_sum  
    #sum is max for all subarrays that 'cross' the middle
    return left_max_sum + right_max_sum


def linear_algorithm(array):
    local_max_sum = 0
    global_max_sum = 0
    for i in array:
        local_max_sum += i
        if local_max_sum < 0:
            local_max_sum = 0
        elif global_max_sum < local_max_sum:
            global_max_sum = local_max_sum
    return global_max_sum        

#result = quadratic_algorithm_1([ 5, -3, -7, -2, 4, 2, 9, -6, -4, 8, 3])
#result = cubic_algorithm([ 5, -3, -7, -2, 4, 2, 9, -6, -4, 8, 3])
#result = linear_algorithm([ 5, -3, -7, -2, 4, 2, 9, -6, -4, 8, 3])
#result = divide_and_conquer_algorithm([ 5, -3, -7, -2, 4, 2, 9, -6, -4, 8, 3])
#result = quadratic_algorithm_2([ 5, -3, -7, -2, 4, 2, 9, -6, -4, 8, 3])
#print(result)

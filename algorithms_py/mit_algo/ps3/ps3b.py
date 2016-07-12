

def max_heapify(lst, start, end):
    pos = start
    while True:
        toswap = pos
        comp = lst[pos]
        left = pos * 2 + 1
        right = left + 1
        if left < end and comp > lst[left]:
            comp = lst[left]
            toswap = left
        if right < end and comp > lst[right]:
            comp = lst[right]
            toswap = right
        if toswap == pos:
            break
        else:
            lst[pos], lst[toswap] = lst[toswap], lst[pos]
            pos = toswap

def build_heap(lst):
    start = len(lst) // 2 - 1
    while start >= 0:
        max_heapify(lst, start, len(lst))
        start -= 1

# heap_sort() returns a copy of list A sorted in descending order.
# For example, heapsort([4,8,3,6]) should return [8,6,4,3].
# heap_sort() should NOT modify the list A.
def heap_sort(A):
    # YOUR CODE HERE
    lst = A[:]
    build_heap(lst)
    i = len(lst);
    while i >= 2:
        lst[0], lst[i - 1] = lst[i - 1], lst[0]
        max_heapify(lst, 0, i - 1)
        i -= 1
    return lst

# This function takes a list which contains the daily penalties for
# each problem set, and returns the smallest total penalty Ben can
# achieve. You should use your heap_sort() implementation.
def best_score(penalties):
    # YOUR CODE HERE
    sched = heap_sort(penalties)
    score, day = 0, 1
    for val in sched:
        score += day * val
        day += 1
    return score

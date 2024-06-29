# Fibonacci Heap

A C++ implementation of a Fibonacci Heap, a priority queue data structure designed to be extremely time-performant, assuming merges are performed often.

| Operation | Time complexity |
| --------- | --------------- |
| Extract min | O(logN) Amortized |
| Delete | O(logN) |
| Decrease key | O(1) |
| Insert | O(1) |
| Find min | O(1) |
| Merge | O(1) |

The sample program will display ```p``` smallest sums of elements from heaps ```heap1``` and ```heap2```, where the heaps consist of ```N - N/k``` random integers, where ```N = 10^i``` for ```i = 3, 4, 5, 6, 7```, and ```k = 10^i```, for ```i = 1, 2```. The heaps are populated in the main program, and after every ```k``` inserted elements, an ```extract_min``` operation is performed 





# System Operation Guide

This system relies on exactly two stacks (`mainStack` and `tempStack`) to perform all data management tasks. A stack follows the Last-In-First-Out (LIFO) principle, meaning you can only directly access the element at the top. 

To perform complex operations like searching, deleting, or updating a specific record, the program shifts elements back and forth between the two stacks to dig down to the required element and then restore the original order.

**Basic CRUD Operations (Delete, Update, Search)**
When a specific record needs to be found, the program continuously pops elements from `mainStack` and pushes them into `tempStack`. This digging process stops when the target ID is identified. If the operation is a deletion, the target element is simply discarded. If it is an update or search, the element is modified or displayed before being pushed back to `mainStack`. Finally, all elements resting in `tempStack` are popped and returned to `mainStack` to completely restore the initial order. Add operations are straightforward, simply pushing the new element directly onto the top of `mainStack`.

**Sorting Algorithm**
The sorting mechanism utilizes `tempStack` as a sorted holding area. The program pops the top element from `mainStack` and holds it as the current item. It then compares this current item with the top of `tempStack`. If the element in `tempStack` breaks the desired sorting order, it is pushed back into `mainStack` temporarily. Once the correct position is found, the current item is placed into `tempStack`. This loop continues until `mainStack` is completely empty. At this point, `tempStack` holds all elements perfectly sorted, and they are simply poured back into `mainStack`.

**File Initialization and Saving**
The program uses a standard `.csv` file as permanent storage. Upon initialization, it reads the file line by line. Since standard file reading proceeds from the first line to the last, pushing each read line into the stack naturally places the first line at the bottom of `mainStack` and the last line at the top. When the program terminates, `mainStack` transfers all elements into `tempStack` to reverse their order. The program then writes elements from `tempStack` to the file, ensuring the chronological order is preserved in the database.

# Time and Space Complexity Analysis

### 1. loadData()
* **Time Complexity:** O(n)  
* **Space Complexity:** O(1) (excluding stack memory)

**Explanation:** The function reads n lines from the file sequentially. Each line is processed in O(1) time, and pushing each element onto the stack is also O(1).

### 2. saveData()
* **Time Complexity:** O(n)  
* **Space Complexity:** O(1)

**Explanation:** The function transfers all n elements from mainStack to tempStack (O(n)), then writes each element to file and transfers back to mainStack (O(n)). Total is O(2n) = O(n).

### 3. displayStudents()
* **Time Complexity:** O(n)  
* **Space Complexity:** O(1)

**Explanation:** The function pops all n elements from mainStack to tempStack for display (O(n)), then pushes all back to mainStack (O(n)). Total is O(2n) = O(n).

### 4. addStudent()
* **Time Complexity:** O(n)  
* **Space Complexity:** O(1)

**Explanation:** The function calls `searchStudent()` to check for duplicate IDs. In the worst case, it must traverse the entire stack containing n elements. Then pushing the new element is O(1).

### 5. deleteStudent()
* **Time Complexity:** O(n)  
* **Space Complexity:** O(1)

**Explanation:** In the worst case, the function must traverse the entire stack of n elements to find and delete the target. Moving elements between mainStack and tempStack takes O(n) time.

### 6. updateStudent()
* **Time Complexity:** O(n)  
* **Space Complexity:** O(1)

**Explanation:** Similar to deleteStudent(), in the worst case it must traverse the entire stack. Moving elements between the two stacks takes O(n) time.

### 7. searchStudent()
* **Time Complexity:** O(n)  
* **Space Complexity:** O(1)

**Explanation:** The function must traverse all n elements in the worst case to find the target. Elements are moved to tempStack and back, which also takes O(n) time.

### 8. sortStudents()
* **Time Complexity:** O(n²)  
* **Space Complexity:** O(1)

**Explanation:** Uses an insertion-sort-like algorithm with stacks. Each element from mainStack must be compared with all elements in tempStack. In the worst case, O(n²) comparisons and transfers are required.

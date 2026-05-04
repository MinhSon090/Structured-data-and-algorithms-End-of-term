# System Operation Guide

This system relies on exactly two stacks (`mainStack` and `tempStack`) to perform all data management tasks. A stack follows the Last-In-First-Out (LIFO) principle, meaning you can only directly access the element at the top. 

To perform complex operations like searching, deleting, or updating a specific record, the program shifts elements back and forth between the two stacks to dig down to the required element and then restore the original order.

**Basic CRUD Operations (Delete, Update, Search)**
When a specific record needs to be found, the program continuously pops elements from `mainStack` and pushes them into `tempStack`. This digging process stops when the target ID is identified. If the operation is a deletion, the target element is simply discarded. If it is an update or search, the element is modified or displayed before being pushed back to `mainStack`. Finally, all elements resting in `tempStack` are popped and returned to `mainStack` to completely restore the initial order. Add operations are straightforward, simply pushing the new element directly onto the top of `mainStack`.

**Sorting Algorithm**
The sorting mechanism utilizes `tempStack` as a sorted holding area. The program pops the top element from `mainStack` and holds it as the current item. It then compares this current item with the top of `tempStack`. If the element in `tempStack` breaks the desired sorting order, it is pushed back into `mainStack` temporarily. Once the correct position is found, the current item is placed into `tempStack`. This loop continues until `mainStack` is completely empty. At this point, `tempStack` holds all elements perfectly sorted, and they are simply poured back into `mainStack`.

**File Initialization and Saving**
The program uses a standard `.csv` file as permanent storage. Upon initialization, it reads the file line by line. Since standard file reading proceeds from the first line to the last, pushing each read line into the stack naturally places the first line at the bottom of `mainStack` and the last line at the top. When the program terminates, `mainStack` transfers all elements into `tempStack` to reverse their order. The program then writes elements from `tempStack` to the file, ensuring the chronological order is preserved in the database.
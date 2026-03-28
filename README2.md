## How to Run

### Requirements
- C++ compiler 
- Standard C++ libraries
- Dataset file: `Car_DataRead.txt`
- Headers

### Compilation
Compile the program using:

g++ Results.cpp -o main

### Running the Program
Run the executable:

./main

### Some Notes
- The program will automatically load 100,000 car records at startup.
- You can interact with the menu to run benchmarks, search cars, and view tree statistics.

  
### Alternatively use an IDE
This specific project was made in Clion.


## What can be done
After running the program, you will see a menu with several options:

1. Run Red-Black Tree Benchmark  
   - Tests insertion, sequential search, and random search performance  
   - You can choose how many random searches to perform  

2. Run B-Tree Benchmark  
   - Same tests as above, but using a B-Tree  

3. Run Both Benchmarks  
   - Runs both structures back-to-back  
   - Displays a summary comparing total execution time  
   - Shows which structure is faster and by what percentage  

4. Search by Car ID  
   - Enter a specific car ID (e.g., 5543)  
   - Program searches both trees  
   - Displays:
     - Search time (microseconds)
     - Full car details  

5. Show Random Car  
   - Displays a randomly selected car from the dataset  

6. Print Tree Info  
   - Option 1: Show tree height (levels)
   - Option 2: Print all nodes level-by-level 

7. Exit  
   - Closes the program  



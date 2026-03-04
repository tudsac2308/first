Wine Cellar Management System
A robust C application designed for managing a wine inventory using dynamic memory allocation and advanced data structures.

Features
Dynamic Inventory: Uses realloc to expand the cellar capacity as you add more wines.
Detailed Records: Store wine details including Year, Price, Name, Producer, and a dynamic description (unlimited length).
Smart Sorting: Integrated qsort algorithm to sort your collection alphabetically by name.
Data Persistence: Automatically saves your inventory to wine_data.txt upon exit.
Advanced Formatting: Professional ID display (e.g., 00000001) and input handling for strings with spaces.

Technical Highlights
Memory Management: Implements malloc, realloc, and free to prevent memory leaks.
Pointer Arithmetic: Used for efficient string handling and structure navigation.
File I/O: Handles data streaming to external text files.

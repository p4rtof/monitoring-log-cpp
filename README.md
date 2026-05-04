# Application Monitoring & Activity Log System

A high-performance C++ backend system designed to manage large-scale activity logs (e.g., user logins, system errors, and API requests). This project focuses on implementing efficient data structures to ensure fast search, storage, and data management.

---

## Project Status (Final - Week 14)
- [x] **Core Logic**: Fully implemented system specifications and activity scenarios.
- [x] **Dual Data Structures**: Optimized data management using `std::vector` (linear storage) and `std::unordered_map` (Hash Table).
- [x] **Persistent Storage**: Data is stored in `data_log.txt` with immediate write-on-action to prevent data loss.
- [x] **Performance Benchmarking**: Integrated `<chrono>` library to measure execution time in microseconds.
- [x] **Case-Insensitive Search**: Enhanced user experience by allowing searches regardless of letter casing.
- [x] **Fast Deletion**: Optimized single-loop deletion mechanism to clear old logs efficiently.

---

## Key Features
1. **In-Memory Loading**: Automatically reads thousands of logs from a text file into RAM upon startup for instant access.
2. **Instant Search (O(1))**: Search logs by **Level** (INFO/WARNING/ERROR) using a Hash Table for near-zero latency.
3. **Flexible Search (O(n))**: Partial substring matching for **Timestamp** and **Source** using vectors.
4. **Persistent Insertion**: New logs are simultaneously added to the memory structures and appended to the physical file to ensure durability.
5. **Optimized Deletion**: A high-speed deletion feature that filters logs by date and updates the physical file in a single pass.
6. **Live Statistics**: Real-time count of logs per category and grand totals.

---

## Performance Analysis
This project serves as a benchmark for data structure efficiency:
*   **Vector**: Best for sequential data and partial string matching but slower for large-scale filtering ($O(n)$).
*   **Hash Map**: Provides ultra-fast access for categorized data ($O(1)$), solving the "slow error search" problem common in unindexed log files.

---

## How to Run
1.  **Generate Dummy Data** (Optional):
    ```bash
    python generate-dummy.py
    ```
2.  **Compile the C++ Program**:
    ```bash
    g++ main.cpp -o main
    ```
3.  **Execute**:
    ```bash
    ./main
    ```

---

## Project Structure
*   `main.cpp`: The core application logic.[cite: 1]
*   `data_log.txt`: The persistent database (flat-file).[cite: 1]
*   `generate-dummy.py`: Script to generate sample logs for testing.[cite: 1]
*   `README.md`: Project documentation.[cite: 1]

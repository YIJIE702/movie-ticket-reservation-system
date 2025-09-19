# 🎟️ Movie Ticket Reservation System (Linked List Implementation)

## 📌 Overview
This project is a **Movie Ticket Reservation System** implemented in **C programming language**, using **Linked Lists** to manage both movies and tickets.  
It supports **three modes**:  
- **USER** – View schedules, book tickets, cancel bookings, and review ticket history.  
- **MODERATOR** – View user tickets, delete tickets (like a ticket office).  
- **ADMIN** – Create new movies, delete movies, and manage the movie list.  
All data (movies and tickets) is stored in text files, allowing persistence between sessions.

---

## ⚙️ Features
### 👥 USER Mode
- View movie schedule (name, price, capacity).
- Book tickets (with name, number of tickets, payment method).
- Cancel booking (refund calculated and updated).
- View ticket list (saved in a text file for persistence).
- Data is stored in `<username>.txt` so users can reload their history on re-entry.

### 🛠️ MODERATOR Mode
- View movie schedule.
- View user tickets by entering username.
- Delete specific tickets (with confirmation).
- Updates ticket files after modification.

### 🖥️ ADMIN Mode
- Create new movie entries (name, price, capacity).
- Delete movies (with proper validation).
- View movie schedule.
- Updates `movieList.txt` after changes.

---

## 🏗️ System Design
### 🔗 Data Structure
- **Linked Lists** are used for both movies and tickets.
- Two separate files:
  - `movieList.c` – Manages the movie list.
  - `ticketList.c` – Manages the ticket list.

### 📂 File Storage
- **movieList.txt** – Stores available movies.
- **<username>.txt** – Stores user ticket history.

---

### 📊 Complexity Analysis
- O(n): Used in loops traversing linked lists (e.g., MovieListDestroy()).
- O(1): Used for constant-time operations (e.g., fopen()).

---

## 🚀 Installation & Compilation
Prerequisites
- GCC or any C compiler.
- Make utility (if using the provided Makefile).

---

## 💡 Suggested Improvements (Optional)
- GUI Version: Build a graphical interface using GTK or ncurses for a better user experience.
- Database Support: Replace text file storage with SQLite for scalability.
- Automated Testing: Add unit tests for core functions (insert, delete, booking, etc.).

---

## 📜 License
- This project is for educational purposes under EKT 224 – Algorithm and Data Structures coursework.
- You may modify and use this project for learning, but proper credit to the author is appreciated.

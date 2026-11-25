# CUSTOM_UNIQUE_PTR // RAII & MOVE SEMANTICS ENGINE

![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Memory Safety](https://img.shields.io/badge/MEMORY-RAII-00F5D4?style=for-the-badge)
![License](https://img.shields.io/badge/LICENSE-MIT-FF2A85?style=for-the-badge)
![Status](https://img.shields.io/badge/BUILD-ACTIVE-7B2CBF?style=for-the-badge)

> **Zero-overhead single-ownership smart pointer written from scratch in C++.** Built to master raw heap ownership, move semantics, variadic templates, and deterministic cleanup without training wheels.

---

## THE VISION

Raw `new` and `delete` lead to leaks, double-frees, and dangling pointers. `CUSTOM_UNIQUE_PTR` implements a custom `MyUniquePtr<T>` and `make_my_unique` factory from first principles so every byte on the heap has a single, unambiguous owner whose lifetime is bound to scope via **RAII**.

---

## ARCHITECTURE & MEMORY MODEL

```text
  [ Stack Frame ]                      [ Heap ]
  +------------------+                +-------------------------+
  | MyUniquePtr<T>   |--- ptr_ ---->| Managed Object T        |
  |  - copy = delete |                |  - constructed in-place |
  |  - move = active |                |  - freed in ~MyUniquePtr|
  +------------------+                +-------------------------+

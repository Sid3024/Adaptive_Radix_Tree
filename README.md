# Adaptive Radix Tree (ART) — C++ Implementation

A from-scratch C++ implementation of an **Adaptive Radix Tree (ART)** supporting variable-length string keys, **path compression**, and adaptive node expansion (`N4 → N16 → N48 → N256`).  
This repo focuses on **correctness + invariants + testing** first.

---

## Features

- **Adaptive node types**
  - `Node4`, `Node16`, `Node48`, `Node256`
  - Automatic expansion when capacity is exceeded
- **Path compression**
  - Prefix stored per internal node (`prefix[]`, `prefixLen`) with configurable `MAX_PREFIX_LEN`
  - Correct prefix splitting on partial matches during insert
- **Leaf nodes**
  - Store full key–value pairs
  - Exact-match verification
- **Operations**
  - `insert(key, value)`
  - `search(key)`
  - `pop(key)` *(partially implemented)*
  - `bulk_construct(...)` *(radix-sort based, WIP)*
- **Unit tests (GoogleTest)**
  - Functional correctness + structural checks (node type, prefix state, size, etc.)

---


---

## Design Overview

### Node Types

| Node Type | Max Children | Representation |
|----------|--------------|----------------|
| `Node4`  | 4            | Small sorted/unsorted key list + child list |
| `Node16` | 16           | Key list + child list (SIMD-ready lookup later) |
| `Node48` | 48           | 256-byte index map → 48 child array |
| `Node256`| 256          | Direct indexing (`children[256]`) |

Nodes expand automatically when `size == capacity`:
N4 → N16 → N48 → N256


---

### Prefix Compression

Each internal node stores a compressed prefix:
- `prefix[MAX_PREFIX_LEN]`
- `prefixLen`

Insertion logic:
- **Prefix matches fully** → descend to the next child
- **Prefix mismatch** → split:
  - create a new `Node4` as the replacement node
  - move the old node under the split node using the discriminating byte
  - insert the new leaf under the split node using the incoming key’s discriminating byte
  - adjust prefixes via `memcpy` / `memmove`

---

### Pointer / Mutation Model

- Nodes and leaves are dynamically allocated.
- Structural updates are done using **double pointers (`Node**`)** to safely replace pointers in-place.
- Expansion replaces the node pointer transparently.

---

## Testing Strategy

Tests are intentionally **structural**, not only “black-box” correctness.

### ART Tests (`test/ART_test.cpp`)

Covers:
- Empty tree initialization
- Single insert/search
- Double inserts/searches with:
  - different first letter
  - same first letter
  - long shared prefix
- Triple inserts/searches with deeper splits and different insertion orders
- Verifies:
  - correct `node_type` (`L`, `N4`, etc.)
  - correct `size`
  - correct `prefixLen` and `read_prefix()`
  - correct child pointers and stored key/value
  - `get_total_node_count()` sanity checks in small cases

Example scenarios:
- `"abc"`, `"bcd"`, `"acd"`
- `"abcdefghi"`, `"abcxyz"`, `"abcdefwxyz"`
- Order-independent insertion correctness

---

### Node Expansion Tests (`test/Node_test.cpp`)

Stress-tests root growth by inserting **256 distinct single-character keys** and verifying:
- correct expansion sequence:
Leaf → N4 → N16 → N48 → N256

- correct `size` at each step
- root stays in the expected node type after each threshold

This ensures the adaptive behavior is correct (not accidental).

---

## Build & Run Tests

### Prerequisites
- C++17 compiler (GCC / Clang / MSVC)
- CMake ≥ 3.16
- GoogleTest (usually fetched via CMake in many setups, or installed system-wide depending on your repo config)

### Build
```bash
mkdir build
cd build
cmake ..
cmake --build .

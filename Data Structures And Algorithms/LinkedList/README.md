# 🔗 Linked List Archives

Focus: Memory management, linear traversal, and efficient pointer synchronization.

## ⚔️ The Kill List

| Rank | Problem | Source | Logic | Status |
| :--- | :--- | :--- | :--- | :--- |
| **A** | **Y-Shaped Intersection** | [GFG](https://www.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1) | Two-Pointer Time Warp | ✅ Killed |

---

### 🛡️ Core Logic: The Two-Pointer Time Warp
To find the intersection point of two lists of lengths $L_1$ and $L_2$ without knowing their lengths:
1. Initialize `ptr1` at `head1` and `ptr2` at `head2`.
2. When a pointer reaches `NULL`, teleport it to the head of the *opposite* list.
3. This guarantees both pointers travel exactly $a + c + b$ distance, where $c$ is the common part.
   - **Math:** $a + c + b = b + c + a$
   - **Complexity:** $O(N+M)$ Time | $O(1)$ Space

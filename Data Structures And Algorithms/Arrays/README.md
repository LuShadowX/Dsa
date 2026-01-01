# 📂 Array Archives

Focus: Sequential memory access, in-place modifications, and overflow logic.

## ⚔️ The Kill List

| Rank | Challenge | Source | Logic | Status |
| :--- | :--- | :--- | :--- | :--- |
| **B** | **Plus One** | [LeetCode](https://leetcode.com/problems/plus-one/) | Backward Carry Propagation | ✅ Killed |

---

### 🛡️ Strategy Spotlight: Carry Propagation
When incrementing a large integer represented as an array, the primary obstacle is the cascading carry ($9 + 1 = 10$).
1. **The Scan:** Traverse from right to left.
2. **The Condition:** If a digit is $< 9$, increment and return immediately.
3. **The Transformation:** If a digit is $9$, set to $0$ and continue.
4. **The Overflow:** If the loop finishes without returning, insert $1$ at the beginning.

**Complexity:** $O(N)$ Time | $O(1)$ Space
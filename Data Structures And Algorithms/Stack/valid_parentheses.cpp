/**
 * @file valid_parentheses.cpp
 * @author LuShadowX
 * @brief Determine if a given string of parentheses is balanced.
 * @problem_link: https://www.geeksforgeeks.org/problems/parenthesis-checker2744/1
 * @difficulty: Easy (Rank C)
 * @tags: Stack, String, Parsing
 * @logic: Utilizes a `std::stack` to handle the nested structure of parentheses.
 * The core principle is LIFO (Last-In, First-Out): the most recently opened bracket
 * must be the first one closed.
 * 1. Iterate through the string character by character.
 * 2. Push any opening bracket ('(', '{', '[') onto the stack.
 * 3. For any closing bracket:
 * a. First, check if the stack is empty using `st.empty()`. If it is, there's
 * no matching opening bracket, so return false.
 * b. If not empty, access the top element (`st.top()`) and pop it (`st.pop()`).
 * c. Check if the popped opening bracket matches the current closing bracket.
 * If not, return false.
 * 4. After the loop, if the stack is empty, all brackets were matched correctly.
 * Return true. Otherwise, return false.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Stack as a Parsing Tool]
 * A stack is the ideal data structure for parsing nested structures because it
 * remembers the "state" of open scopes in the reverse order they were opened.
 *
 * Example trace for `({[]})`:
 * - Read '(': Push '('. Stack: [`(`]
 * - Read '{': Push '{'. Stack: [`(`, `{`]
 * - Read '[': Push '['. Stack: [`(`, `{`, `[`]
 * - Read ']': Matches top '['. Pop '['. Stack: [`(`, `{`]
 * - Read '}': Matches top '{'. Pop '{'. Stack: [`(`]
 * - Read ')': Matches top '('. Pop '('. Stack: []
 * - End of string. Stack is empty -> Valid.
 *
 * [Time Complexity Analysis]
 * We iterate through the string of length N exactly once. Each stack operation
 * (push, pop, top, empty) takes O(1) time.
 * Total Time: T(N) = O(N).
 *
 * [Space Complexity Analysis]
 * In the worst case (e.g., `(((((`), the stack will store all N characters.
 * Total Auxiliary Space: S(N) = O(N).
 * ============================================================================
 */

/**
 * MISSION: Parenthesis Balancing Protocol
 * RANK: C (Foundational Stack Application)
 * DEPARTMENT: parsing & Validation Algorithms
 * CHALLENGE:
 * Given a string `s` containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid. An input string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(N) allowed.
 */

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * Checks if the input string has balanced parentheses.
     * @param s The input string containing brackets.
     * @return true if balanced, false otherwise.
     */
    bool isBalanced(string& s) {
        stack<char> st;
        for (int i = 0; i < s.size(); i++) {
            // Case 1: Opening bracket. Push onto stack.
            if (s[i] == '[' || s[i] == '{' || s[i] == '(') {
                st.push(s[i]);
            }
            // Case 2: Closing bracket. Check for match.
            else {
                // CRITICAL CHECK: As noted, use st.empty() to check if stack is empty.
                // An empty stack here means a closing bracket appears without an opener.
                if (st.empty()) return false;

                char top = st.top();
                st.pop(); // Remove the matched opening bracket

                // Check for mismatch between current closing bracket and popped opening bracket.
                if (s[i] == ')' && top != '(') return false;
                else if (s[i] == '}' && top != '{') return false;
                else if (s[i] == ']' && top != '[') return false;
            }
        }
        
        // Final Check: If stack is not empty, there are unmatched opening brackets.
        if (st.empty()) return true;
        else return false;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    cout << "INITIATING PARENTHESIS BALANCING PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // Test cases
    vector<string> testCases = {
        "()",           // Simple balanced
        "()[]{}",       // Multiple balanced types
        "{[]}",         // Nested balanced
        "([)]",         // Interleaved unbalanced
        "]",            // Single closing
        "{{{{",         // All opening
        "",             // Empty string (balanced)
        "({[()]})"      // Complex balanced
    };

    for (string& s : testCases) {
        cout << "Testing string: \"" << s << "\"" << endl;
        bool result = solver.isBalanced(s);
        if (result) {
            cout << "Result: VALID (Balanced)" << endl;
        } else {
            cout << "Result: INVALID (Unbalanced)" << endl;
        }
        cout << "-----------------------------" << endl;
    }

    cout << "MISSION COMPLETE." << endl;

    return 0;
}
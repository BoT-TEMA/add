#include <iostream>
#include <vector>
#include <stack>
#include <iomanip> // for print

using namespace std;

vector<int> func(const vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<pair<int, int>> st;
    
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.top().first > nums[i]) {
            result[st.top().second] = i;
            st.pop();
        }
        st.push({nums[i], i});
    }
    return result;
}

void print(const vector<int>& nums, const vector<int>& indices) {
    const int colWidth = 12;
    
    cout << "\n" << string(80, '-') << "\n";
    cout << left << setw(colWidth) << "Index        " << " | ";
    for (int i = 0; i < nums.size(); ++i) {
        cout << setw(6) << i << " ";
    }
    
    cout << "\n" << string(80, '-') << "\n";
    cout << left << setw(colWidth) << "Value        " << " | ";
    for (int num : nums) {
        cout << setw(6) << num << " ";
    }
    
    cout << "\n" << string(80, '-') << "\n";
    cout << left << setw(colWidth) << "Nearest Right" << " | ";
    for (int idx : indices) {
        if (idx == -1) {
            cout << setw(7) << "Х" << " ";
        } else {
            cout << setw(6) << idx << " ";
        }
    }
    cout << "\n" << string(80, '-') << "\n";
}

int main() {
    cout << "NEAREST SMALLER RIGHT\n";
    cout << "Enter numbers separated by spaces (type 'exit' to quit)\n\n";
    
    while (true) {
        cout << "Input: ";
        string input;
        getline(cin, input);
        
        if (input == "exit") {
            break;
        }
        
        vector<int> nums;
        bool valid = true;
        
        // Parse input
        size_t pos = 0;
        while (pos < input.length()) {
            try {
                size_t next_pos;
                int num = stoi(input.substr(pos), &next_pos);
                nums.push_back(num);
                pos += next_pos;
                
                while (pos < input.length() && isspace(input[pos])) {
                    pos++;
                }
            } catch (...) {
                if (pos < input.length() && !isspace(input[pos])) {
                    cout << "Invalid input. Please enter numbers only.\n\n";
                    valid = false;
                    break;
                }
                pos++;
            }
        }
        
        if (!valid || nums.empty()) {
            continue;
        }
        
        vector<int> result = func(nums);
        print(nums, result);
        cout << endl;
    }
    
    cout << "\nProgram terminated.!\n";
    return 0;
}

#include "../bits/stdc++.h"

using namespace std;

class TreeNode {
public:
    int val;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    TreeNode(int val, TreeNode *left, TreeNode *right) {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

class Solution {
public:
    vector<vector<int>> answers;

    vector<int> preorderTraversal(TreeNode *root, vector<int> lists, int targetSum) {
        vector<int> tmp;
        if (root == nullptr) return tmp;

        if (root->left == nullptr && root->right == nullptr) {
            if (targetSum - root->val == 0) {
                lists.emplace_back(root->val);
                return lists;
            }
            lists.clear();
            return lists;
        }

        lists.emplace_back(root->val);
        vector<int> left = preorderTraversal(root->left, lists, targetSum - root->val);
        if (!left.empty()) answers.emplace_back(left);
        vector<int> right = preorderTraversal(root->right, lists, targetSum - root->val);
        if (!right.empty()) answers.emplace_back(right);

        return tmp;
    }

    vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
        if (!root) return answers;
        vector<int> lists;
        if (root->left == nullptr && root->right == nullptr) {
            if (targetSum == root->val) {
                lists.emplace_back(root->val);
                answers.emplace_back(lists);
                return answers;
            }
        }
        preorderTraversal(root, lists, targetSum);
        return answers;
    }
};


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    Solution s = *new Solution();
    TreeNode *treeNode = new TreeNode(1, nullptr, nullptr);

    s.pathSum(treeNode, 1);
    s.answers;
    return 0;
}
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
    bool answer;

    void inorderTraversal(TreeNode *root, int sum, int targetSum) {
        if (answer || root == nullptr) return;

        if (root->left == nullptr && root->right == nullptr) { // leaf
            if (sum + root->val == targetSum) {
                answer = true;
            }
            return;
        }

        inorderTraversal(root->left, sum + root->val, targetSum);
        inorderTraversal(root->right, sum + root->val, targetSum);
    }

    bool hasPathSum(TreeNode *root, int targetSum) {
        if (root == nullptr) return false;
        inorderTraversal(root, 0, targetSum);
        return answer;
    }

    bool hasPathSum_optimalAnswer(TreeNode *root, int targetSum) {
        if (root == nullptr) {
            return false;
        }

        if (root->left == nullptr && root->right == nullptr) {
            return targetSum == root->val;
        }

        bool left_sum = hasPathSum(root->left, targetSum - root->val);
        bool right_sum = hasPathSum(root->right, targetSum - root->val);

        return left_sum || right_sum;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    Solution s = *new Solution();
    TreeNode *treeNode = new TreeNode(1, nullptr, nullptr);
    treeNode->left = new TreeNode(2, nullptr, nullptr);

    cout << s.hasPathSum(treeNode, 1) << "\n";
    return 0;
}
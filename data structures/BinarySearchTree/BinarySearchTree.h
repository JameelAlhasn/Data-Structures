#include <iostream>
using namespace std;

template <typename T>
class BinarySearchTree {
private:
    struct TreeNode {
        T val;
        TreeNode *left, *right;
        TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;
    int size_;

    TreeNode* insert(TreeNode* node, T val, bool &inserted) {
        if (!node) {
            inserted = true;
            return new TreeNode(val);
        }
        if (val < node->val)
            node->left = insert(node->left, val, inserted);
        else if (val > node->val)
            node->right = insert(node->right, val, inserted);
        return node;
    }

    TreeNode* remove(TreeNode* node, T val, bool &removed) {
        if (!node) return nullptr;
        if (val < node->val)
            node->left = remove(node->left, val, removed);
        else if (val > node->val)
            node->right = remove(node->right, val, removed);
        else {
            removed = true;
            if (!node->left) {
                TreeNode* r = node->right;
                delete node;
                return r;
            }
            if (!node->right) {
                TreeNode* l = node->left;
                delete node;
                return l;
            }
            TreeNode* succ = node->right;
            while (succ->left) succ = succ->left;
            node->val = succ->val;
            node->right = remove(node->right, succ->val, removed = false); // don't double count
        }
        return node;
    }

    void Preorder(TreeNode* node) const {
        if (!node) return;
        cout << node->val << ' ';
        Preorder(node->left);
        Preorder(node->right);
    }

    void Inorder(TreeNode* node) const {
        if (!node) return;
        Inorder(node->left);
        cout << node->val << ' ';
        Inorder(node->right);
    }

    void Postorder(TreeNode* node) const {
        if (!node) return;
        Postorder(node->left);
        Postorder(node->right);
        cout << node->val << ' ';
    }

    void clear(TreeNode* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr), size_(0) {}
    ~BinarySearchTree() {
        clear(root);
    }

    void insert(T val) {
        bool inserted = false;
        root = insert(root, val, inserted);
        if (inserted) size_++;
    }

    void remove(T val) {
        bool removed = false;
        root = remove(root, val, removed);
        if (removed) size_--;
    }

    int size() const {
        return size_;
    }

    void printPreorder() const {
        Preorder(root);
        cout << endl;
    }

    void printInorder() const {
        Inorder(root);
        cout << endl;
    }

    void printPostorder() const {
        Postorder(root);
        cout << endl;
    }
};

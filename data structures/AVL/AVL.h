
#define max(a,b) a > b ? a : b
template <typename T>
class AVLTree {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        int height;
        Node(const T& val) : key(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root = nullptr;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* insert(Node* node, const T& key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        return balance(node);
    }

    Node* findMin(Node* node) {
        return node->left ? findMin(node->left) : node;
    }

    Node* eraseMin(Node* node) {
        if (!node->left) return node->right;
        node->left = eraseMin(node->left);
        return balance(node);
    }

    Node* erase(Node* node, const T& key) {
        if (!node) return nullptr;

        if (key < node->key)
            node->left = erase(node->left, key);
        else if (key > node->key)
            node->right = erase(node->right, key);
        else {
            Node* left = node->left;
            Node* right = node->right;
            delete node;

            if (!right) return left;

            Node* minNode = findMin(right);
            minNode->right = eraseMin(right);
            minNode->left = left;
            return balance(minNode);
        }
        return balance(node);
    }

    bool find(Node* node, const T& key) const {
        if (!node) return false;
        if (key == node->key) return true;
        if (key < node->key) return find(node->left, key);
        return find(node->right, key);
    }


    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    ~AVLTree() {
        clear(root);
    }

    void insert(const T& key) {
        root = insert(root, key);
    }

    void erase(const T& key) {
        root = erase(root, key);
    }

    bool find(const T& key) const {
        return find(root, key);
    }
};

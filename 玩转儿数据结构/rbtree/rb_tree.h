//
// Created by light on 19-10-17.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 *
 * 红黑树的性质：      保持"黑平衡"的二叉树：指的是最后一个性质  严格意义上，不是平衡二叉树   最大高度：O(2logn)
    每个节点或是红色的，或是黑色的。
    根节点是黑色的。
    每个叶节点（最后的空节点）是黑色的。
    如果一个节点是红色的,则它的两个孩子节点都是黑色的。
        阐述上述性质：对应到2-3树中,该红色节点的孩子要么是2节点,要么是3节点,如果是2节点,肯定为黑色,如果是3节点,肯定与3节点对应的红黑树的根节点连接，而根节点又是黑色，所以红色节点连接的孩子都是黑色节点。
        黑色节点右孩子一定是黑色，道理同前面阐述。但左孩子不一定,左孩子是红色的,表示原来是3节点，如果左孩子是黑色的，表示在原来2-3树中都是2节点。
    从任意一个节点到叶子节点,经过的黑色节点是一样的。
        阐述上述性质：根据2-3树与红黑树的关系对比图，可以发现，红黑树中一个黑色节点对应2-3树中一整个节点（“2节点”或“3节点”）。
        而2-3树是完全平衡的树，从根节点到任意路径的叶子节点，经过的节点个数都是相同的，对应红黑树中，即从任意节点到叶子节点，经过的黑色节点是一样的。

 * @tparam Key
 * @tparam Value
 */

template<typename Key, typename Value>
class RBTree {
    /**
     * 封装到私有,让外界不知道具体实现
     */
private:
    enum _Rb_tree_color {
        RED = true,
        BLACK = false
    };
private:
    struct Node {
        Key key;
        Value value;
        Node *left;
        Node *right;
        bool color;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
            this->color = RED;        // 对应的2-3树中节点融合 默认为RED
        }

        Node(Node *node) {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
            this->color = node->color;
        }
    };

public:
    Node *root;
    int count;
public:
    RBTree() {
        root = NULL;
        count = 0;
    }

    ~RBTree() {
        destroy(root);
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
//        return root==0;
    }

    // 判断节点node的颜色
    bool isRed(Node *node) {
        if (node == NULL) return BLACK;
        return node->color;
    }

    // 向红黑树中添加新的元素(key,value)
    void insert(Key key, Value value) {
        root = insert(root, key, value);
        root->color = BLACK;  // 维持根节点颜色为黑色
    }

    // 是否包含key
    bool contain(Key key) {
        return contain(root, key);
    }

    // 重复key设值
    void set(Key key, Value newValue) {
        Node *node = Search(root, key);
        if (node == NULL)
            cerr << key + " doesn't exist!" << endl;
        node->value = newValue;

    }

    // get 获取节点
    Value *search(Key key) {
        return search(root, key);
    }

    void preOrder() {
        perOrder(root);
    }

    void postOrder() {
        postOrder(root);
    }

    void levelOrder() {
        queue<Node *> q;
        q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int total = q.size();
            cout << "第" << depth << "层" << endl;
            while (total--) {
                Node *node = q.front();
                q.pop();
                print(node);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            depth++;
        }
    }

    // 向左找,为最小
    // 向右找,为最大
    Key minimum() {
        Node *minNode = minimum(root);
        return minNode->key;
    }

    Key maximum() {
        Node *maxNode = maximum(root);
        return maxNode->key;
    }

    void removeMin() {
        if (root)
            root = removeMin(root);
    }

    void removeMax() {
        if (root)
            root = removeMax(root);
    }

    void remove(Key key) {
        root = remove(root, key);
    }

    Node *predecessor(Key key) {
        return predecessor(root, key);
    }

    Node *successor(Key key) {
        return successor(root, key);
    }

    Node *ceil(Key key) {
        // 空树或给定的key超过树中最大的key
        if (count == 0 || key > maximum()) return NULL;
        return ceil(root, key);
    }

    Node *floor(Key key) {
        // 空树或给定的key超过树中最大的key
        if (count == 0 || key < minimum()) return NULL;
        return floor(root, key);
    }

private:

    //   node                     x
    //  /   \     左旋转         /  \
    // T1   x   --------->   node   T3
    //     / \              /   \
    //    T2 T3            T1   T2
    Node *leftRotate(Node *node) {      // 对应到2-3树中向2节点添加一个新元素
        Node *x = node->right;
        // 左旋转
        node->right = x->left;
        x->left = node;

        x->color = node->color;
        node->color = RED;

        return x;
    }


//       node                      x
//      /   \     右旋转         /  \
//     x    T2 -------------->  y  node
//    / \                         /   \
//   y T1                       T1   T2
    Node *rightRotate(Node *node) {      // 对应到2-3树中向2节点添加一个新元素
        Node *x = node->left;
        // 左旋转
        node->left = x->right;
        x->right = node;

        x->color = node->color;
        node->color = RED;

        return x;
    }


    // 颜色翻转
    void flipColors(Node *node) {         // 对应到2-3树中3节点添加一个新元素 右边插入
        node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
    }


    /**
     * 递归插入
     * 向以node为根的红黑树中插入元素(key,value)
     * 返回插入新节点后红黑树的根
     * @param node
     * @param key
     * @param value
     * @return
     */
    Node *insert(Node *node, Key key, Value value) {
        if (node == NULL) {
            count++;
            return new Node(key, value);    // 默认插入红色节点
        }

        if (key == node->key)
            node->value = value;
        else if (key < node->key)
            node->left = insert(node->left, key, value);
        else
            node->right = insert(node->right, key, value);

        // 左旋转
        if (isRed(node->right) && !isRed(node->left))
            node = leftRotate(node);

        // 右旋转
        if (isRed(node->left) && isRed(node->left->left))
            node = rightRotate(node);

        // 颜色翻转
        if (isRed(node->left) && isRed(node->right))
            flipColors(node);


        return node;
    }

    /**
     * 非递归插入
     * @param node
     * @param key
     * @param value
     * @return
     */
    Node *Non_Recursion_InsertNode(Node *node, Key key, Value value) {
        if (node == NULL) {
            node = new Node(key, value);
            return node;
        }
        Node *pre = node;
        Node *cur = node;

        while (cur) {
            pre = cur;
            if (key == node->key) {
                node->value = value;
                return node;
            } else if (key < node->key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        if (key < node->key)
            pre->left = new Node(key, value);
        else
            pre->right = new Node(key, value);
    }

    /**
     * 递归查找key是否存在
     * @param node
     * @param key
     * @return
     */
    bool contain(Node *node, Key key) {
        if (node == NULL) return false;
        if (key == node->key) return true;
        else if (key < node->key)
            return contain(node->left, key);
        else
            return contain(node->right, key);
    }

    /**
     * 非递归查找key是否存在
     * @param node
     * @param key
     * @return
     */
    bool Non_Recursion_Contain(Node *node, Key key) {
        if (node == NULL) {
            return false;
        }
        Node *cur = node;

        while (cur) {
            if (key == node->key) {
                return true;
            } else if (key < node->key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return false;
    }

    Value *search(Node *node, Key key) {
        if (node == NULL) return NULL;

        if (key == node->key) return &node->value;
        else if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    // getNode 获取对应节点
    Node *Search(Node *node, Key key) {
        if (node == NULL) return NULL;

        if (key == node->key) return node;
        else if (key < node->key)
            return Search(node->left, key);
        else
            return Search(node->right, key);
    }

    void preOrder(Node *node) {
        if (node) {
            cout << node->key << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void print(Node *node) {
        string c = node->color != RED ? "黑" : "红";
        cout << node->key << ":" << node->value << ":" << c << endl;
    }

    void inOrder(Node *node) {
        if (node) {
            inOrder(node->left);
            cout << node->key << endl;
            inOrder(node->right);
        }
    }

    void postOrder(Node *node) {
        if (node) {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->key << endl;
        }
    }

    void destroy(Node *node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            count--;
        }
    }

    Node *minimum(Node *node) {
        if (node->left == NULL) return node;
        return minimum(node->left);
    }

    // 非递归
    Node *minimum1(Node *node) {
        Node *currentNode = node;
        if (currentNode == NULL)
            return NULL;

        while (currentNode->left != NULL) {
            currentNode = currentNode->left;
        }
        return currentNode;
    }

    Node *maximum(Node *node) {
        if (node->right == NULL) return node;
        return maximum(node->right);
    }

    // 非递归
    Node *maximum1(Node *node) {
        Node *currentNode = node;
        if (currentNode == NULL)
            return NULL;

        while (currentNode->right != NULL) {
            currentNode = currentNode->right;
        }
        return currentNode;
    }

    Node *removeMin(Node *node) {
        if (node->left == NULL) {
            Node *rightNode = node->right;
            delete node;
            count--;
            return rightNode;
        }
        node->left = removeMin(node->left);
        return node;
    }

    // 非递归 返回curNode->right节点
    Node *removeMin1(Node *node) {
        Node *root = node;
        Node *currentNode = node, *p = node;
        Node *parentNode = node;
        // 空
        if (currentNode == NULL)
            return NULL;
        // 迭代
        while (currentNode->left != NULL) {
            parentNode = currentNode;
            currentNode = currentNode->left;
        }
        // 传递进来的左孩子本身就为空
        if (currentNode == parentNode) {
            Node *tmp = currentNode->right;
            delete currentNode; // 此时的currentNode为最大节点
            count--;
            return tmp;
        }
        // 传递进来的左孩子本身不为空,而是通过迭代到最小节点
        parentNode->left = currentNode->right;
        // 删除掉currentNode
        delete currentNode; // 此时的currentNode为最小节点
        count--;
        return p;
    }

    Node *removeMax(Node *node) {
        if (node->right == NULL) {
            Node *leftNode = node->left;
            delete node;
            count--;
            return leftNode;
        }
        return node;
    }

    // 非递归
    Node *removeMax1(Node *node) {
        Node *currentNode = node, *p = node;
        Node *parentNode = node;
        if (currentNode == NULL)
            return currentNode;

        while (currentNode->right != NULL) {
            parentNode = currentNode;
            currentNode = currentNode->right;
        }
        if (currentNode == parentNode) {
            Node *tmp = currentNode->left;
            delete currentNode; // 此时的currentNode为最大节点
            count--;
            return tmp;
        }
        parentNode->right = currentNode->left;
        delete currentNode; // 此时的currentNode为最大节点
        count--;
        return p;
    }

    /**
     * 删除节点
     * @param node
     * @param key
     * @return
     */
    Node *remove(Node *node, Key key) {
        if (node == NULL) return NULL;
        // 左孩子查找
        if (key < node->key) {
            node->left = remove(node->left, key);
            return node;
            // 右孩子查找
        } else if (key > node->key) {
            node->right = remove(node->right, key);
            return node;
            // 查找到了key
        } else { // key == node->key
            // 左孩子为空,就直接以右孩子取缔
            if (node->left == NULL) {         // 左孩子为空包含两部分(左孩子为空与左右孩子均为空)
                Node *rightNode = node->right;
                delete node;
                count--;
                return rightNode;
            }
            // 右孩子为空,就直接以左孩子取缔
            if (node->right == NULL) {
                Node *leftNode = node->left;
                delete node;
                count--;
                return leftNode;
            }
            // 左右孩子均不为空,取右孩子子树中最小或取左孩子子树中最大
            // node->left!=NULL && node->right!=NULL
            // 右孩子子树中最小方法
            Node *successor = new Node(
                    minimum(node->right));       // 在removeMin中将最小节点删除了,后面再次访问successor会为NULL,所以此时需要重新new 分配内存
            count++;
            successor->right = removeMin(node->right);
            successor->left = node->left;
            delete node;
            count--;


            // 左孩子子树中最大方法
            /**
            Node *successor = new Node(maximum(node->left));
            count++;
            successor->left= removeMin(node->left);
            successor->right= node->right;
            delete node;
            count--;
            */
            return successor;
        }
    }

    // 以左侧最大取代非递归删除
    Node *deleteNode(Node *root, Key key) {
        if (root == NULL) return NULL;
        Node *currentNode = root;
        Node *parentNode = root;

        //定位到要删除的key 的父节点,以及当前元素
        while (currentNode != NULL && currentNode->val != key) {
            parentNode = currentNode;
            if (currentNode->key > key) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }

        }
        // 表示没找到key,直接返回结果
        if (currentNode == NULL) return root;
        // 表示与key相等的是根节点,根节点直接处理,不需要保存父节点
        if (parentNode == currentNode) {
            // 左分支为空,以右分支取缔
            if (currentNode->left == NULL) {
                Node *tmp = currentNode->right;
                delete currentNode;
                count--;
                return tmp;
            }
            // 右分支为空,以左分支取缔
            if (currentNode->right == NULL) {
                Node *tmp = currentNode->left;
                delete currentNode;
                count--;
                return tmp;
            }
            // 取左分支最大节点取代当前节点,并删除当前节点
            Node *delnode = new Node(maximum1(currentNode->left)->val);
            delnode->left = removeMax1(currentNode->left);
            delnode->right = currentNode->right;
            delete currentNode;
            count--;
            return delnode;
        }
        // key不是根节点,需要判断父节点与当前节点的关系,有可能是右分支,也可能是左分支

        // 左分支关系
        if (parentNode->left == currentNode) {
            if (currentNode->left == NULL) {
                parentNode->left = currentNode->right;
                delete currentNode;
                count--;
                return root;
            }
            if (currentNode->right == NULL) {
                parentNode->left = currentNode->left;
                delete currentNode;
                count--;
                return root;
            }
            Node *delnode = new Node(maximum1(currentNode->left)->val);
            count++;
            delnode->left = deleteMax(currentNode->left);
            delnode->right = currentNode->right;
            // 父节点左孩子更新为左边最大的节点
            parentNode->left = delnode;
            delete currentNode;
            count--;
            return root;
        }
        // 右分支关系
        if (parentNode->right == currentNode) {
            if (currentNode->left == NULL) {
                parentNode->right = currentNode->right;
                delete currentNode;
                count--;
                return root;
            }
            if (currentNode->right == NULL) {
                parentNode->right = currentNode->left;
                delete currentNode;
                count--;
                return root;
            }
            Node *delnode = new Node(maximum1(currentNode->left)->val);
            count++;
            delnode->left = removeMax1(currentNode->left);
            delnode->right = currentNode->right;
            // 父节点右孩子更新为左边最大的节点
            parentNode->right = delnode;
            delete currentNode;
            count--;
            return root;
        }
        return root;
    }

    // 以右侧最小取代非递归删除
    Node *deleteNode1(Node *root, int key) {
        if (root == NULL) return NULL;
        Node *currentNode = root;
        Node *parentNode = root;

        //定位到要删除的key 的父节点,以及当前元素
        while (currentNode != NULL && currentNode->key != key) {
            parentNode = currentNode;
            if (currentNode->key > key) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }

        }

        if (currentNode == NULL) return root;
        // 根节点处理
        if (parentNode == currentNode) {
            if (currentNode->left == NULL) {
                Node *tmp = currentNode->right;
                delete currentNode;
                return tmp;
            }
            if (currentNode->right == NULL) {
                Node *tmp = currentNode->left;
                delete currentNode;
                return tmp;
            }
            Node *delnode = new Node(minimum1(currentNode->right)->val);
            delnode->right = removeMin1(currentNode->right);
            delnode->left = currentNode->left;
            delete currentNode;
            return delnode;
        }
        if (parentNode->left == currentNode) {

            if (currentNode->left == NULL) {
                parentNode->left = currentNode->right;
                delete currentNode;
                return root;
            }
            if (currentNode->right == NULL) {
                parentNode->left = currentNode->left;
                delete currentNode;
                return root;
            }
            Node *delnode = new Node(minimum1(currentNode->right)->val);
            delnode->right = removeMin1(currentNode->right);
            delnode->left = currentNode->left;
            parentNode->left = delnode;
            delete currentNode;
            return root;
        }
        if (parentNode->right == currentNode) {
            if (currentNode->left == NULL) {
                parentNode->right = currentNode->right;
                delete currentNode;
                return root;
            }
            if (currentNode->right == NULL) {
                parentNode->right = currentNode->left;
                delete currentNode;
                return root;
            }
            Node *delnode = new Node(minimum1(currentNode->right)->val);
            delnode->right = removeMin1(currentNode->right);
            delnode->left = currentNode->left;
            parentNode->right = delnode;
            delete currentNode;
            return root;
        }
        return root;
    }

    /**
     * 在node为根的二叉搜索树中,寻找key的祖先中,比key小的最大值所在节点.递归算法
     * 算法调用前已保证key存在在以node为根的二叉树中
     * @param node
     * @param key
     * @return
     */
    Node *predecessorFromAncestor(Node *node, Key key) {
        if (node->key == key)
            return NULL;
        if (key < node->key) {     // 我们目标是找比key小的最大key,如果比node的key小就应该在它的左子树中查找
            return predecessorFromAncestor(node->left, key);
        } else {      // 此时的key小于node的key在右子树中查找
            assert(key > node->key);
            /**
             * 如果当前节点小于key,则当前节点有可能是比key小的最大值
             * 向右继续搜索,将结果存储到tmpNode中
             */
            Node *tmpNode = predecessorFromAncestor(node->right, key);
            if (tmpNode)
                return tmpNode;
            else
                // 如果tmpNode为空,则当前节点即为结果
                return node;
        }
    }

    Node *predecessor(Node *root, Key key) {

        Node *node = Search(root, key);
        // 如果key所在的节点不存在, 则key没有前驱, 返回NULL
        if (node == NULL)
            return NULL;

        // 如果key所在的节点左子树不为空,则其左子树的最大值为key的前驱
        if (node->left != NULL)
            return maximum(node->left);

        // 否则, key的前驱在从根节点到key的路径上, 在这个路径上寻找到比key小的最大值, 即为key的前驱
        Node *preNode = predecessorFromAncestor(root, key);
        return preNode == NULL ? NULL : preNode;
    }

    /**
     * 找到目标为key的节点
     * 寻找key的父节点
     * 寻找距离key节点最近的右拐节点
     * @param node
     * @param key
     * @param parent
     * @param pRParent
     * @return
     */
    Node *getTargetNodeRParent(Node *node, Key key, Node *&parent, Node *&firstRParent) {
        while (node) {
            if (node->key == key) {
                return node;
            }
            parent = node;
            if (node->key > key) {
                node = node->left;
            } else if (node->key < key) {
                firstRParent = node;        //出现右拐点
                node = node->right;
            }
        }
        return NULL;
    }

    /**
     * 找到目标为key的节点
     * 寻找key的父节点
     * 寻找距离key节点最近的左拐节点
     * @param node
     * @param key
     * @param parent
     * @param pRParent
     * @return
     */
    Node *getTargetNodeLParent(Node *node, Key key, Node *&parent, Node *&firstLParent) {
        while (node) {
            if (node->key == key) {
                return node;
            }
            parent = node;
            if (node->key > key) {
                firstLParent = node;        //出现左拐点
                node = node->left;
            } else if (node->key < key) {
                node = node->right;
            }
        }
        return NULL;
    }
    // 非递归 查找对应节点的前继节点
    /**
     * (1)当前节点左孩子不为空,查找左孩子最大
     * (2)当前节点左孩子为空,判断当前节点与其父节点关系,若为右孩子,返回父节点
     * 若为左孩子.向上找,直到当前节点为某一节点的右分支,则返回某节点.
     * 这里分为两种数据结构:
     *  第一:带父节点的结构  直接使用父节点向上找
     *  第二:不带父节点结构  需要自上向下保存最后一个有右分支的节点(且目标节点在右分支)
     * @param node
     * @param key
     * @return
     */
    Node *predecessor1(Node *node, Key key) {
        if (node == NULL) return NULL;
        Node *parent = NULL;
        Node *firstRParent = NULL;
        Node *targetNode = getTargetNodeRParent(root, key, parent, firstRParent);
        if (targetNode == NULL) return NULL;    // 没有查找到目标为key的节点
        if (targetNode->left) return maximum(targetNode->left); // 有左子树,寻找左子树中最大节点
        if (parent == NULL || parent && firstRParent == NULL) return NULL;      // 父亲节点为空或者没有右拐点说明无前驱节点
        if (targetNode == parent->right) return parent;     // 当前节点为父亲节点的右孩子,直接返回父亲节点
        else
            return firstRParent;            // 当前节点为父亲节点的左孩子,直接返回从上到下搜索的最后一个右拐点
    }

    /**
     * 在node为根的二叉搜索树中,寻找key的祖先中,比key大的最小值所在节点.递归算法
     * 算法调用前已保证key存在在以node为根的二叉树中
     * @param node
     * @param key
     * @return
     */
    Node *successorFromAncestor(Node *node, Key key) {
        if (node->key == key)
            return NULL;
        if (key > node->key) {     // 我们目标是找比key大的最小key,如果比node的key大就应该在它的右子树中查找
            return successorFromAncestor(node->right, key);
        } else {      // 此时的key小于node的key在左子书中查找
            assert(key < node->key);
            /**
             * 如果当前节点大于key,则当前节点有可能是比key大的最小值
             * 向左继续搜索,将结果存储到tmpNode中
             */
            Node *tmpNode = successorFromAncestor(node->left, key);
            if (tmpNode)
                return tmpNode;
            else
                // 如果tmpNode为空,则当前节点即为结果
                return node;
        }
    }

    // 查找key的后继, 递归算法
    // 如果不存在key的后继(key不存在, 或者key是整棵二叉树中的最大值), 则返回NULL
    Node *successor(Node *root, Key key) {

        Node *node = Search(root, key);
        // 如果key所在的节点不存在, 则key没有前驱, 返回NULL
        if (node == NULL)
            return NULL;

        // 如果key所在的节点右子树不为空,则其右子树的最小值为key的后继
        if (node->right != NULL)
            return minimum(node->right);

        // 否则, key的后继在从根节点到key的路径上, 在这个路径上寻找到比key大的最小值, 即为key的后继
        Node *sucNode = successorFromAncestor(root, key);
        return sucNode == NULL ? NULL : sucNode;
    }

    // 非递归 查找对应节点的后继节点
    Node *successor1(Node *node, Key key) {
        if (node == NULL) return NULL;
        Node *parent = NULL;
        Node *firstLParent = NULL;
        Node *targetNode = getTargetNodeLParent(root, key, parent, firstLParent);
        if (targetNode == NULL) return NULL;           // 没有查找到目标哦为key的节点
        if (targetNode->right) return minimum(targetNode->right);        // 有右子树,寻找右子树中最小节点
        if (parent == NULL || parent && firstLParent == NULL) return NULL;            // 父亲节点为空或者没有左拐点说明无后继节点
        if (targetNode == parent->left) return parent;     // 当前节点为父亲节点的左孩子,直接返回父亲节点
        else
            return firstLParent;            //当前节点为父亲节点的右孩子,直接返回从上到下搜索的最后一个左拐点
    }

    //============================================================
    /**
     * 拓展:带父节点数据结构
     */
    //============================================================
    /**
     * 带父节点数据结构,查找前驱节点,直接使用父节点向上找
     * @param node
     * @param key
     * @return
     */
    Node *predecessor2(Node *node, Key key) {
        if (node->left) {
            return maximum(node->left);
        }
        Node *parent = node->parent;
        // 自下向上查找
        while (parent != NULL && node != parent->right) {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }

    /**
     * 带父节点数据结构,直接后继节点,直接使用父节点向上找
     */
    Node *successor2(Node *node, Key key) {
        if (node->right) {
            return minimum(node->right);
        }
        Node *parent = node->parent;
        while (parent != NULL && node != node->left) {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
    //============================================================
    /**
     * 拓展结束
     */
    //============================================================


    /**
     * 地板
     * 在以node为根的二叉搜索树中,寻找key的floor值所处的节点,递归算法
     * @param root
     * @param key
     * @return
     */
    Node *floor(Node *root, Key key) {
        if (root == NULL) return NULL;

        // 如果node的key值和要寻找的key值相等
        // 则node 本身就是key的floor节点
        if (key == root->key) return root;
        // 如果node的key比要寻找的key大
        // 则要寻找的key的floor节点一定在node的左边子树中
        if (root->key > key) return ceil(root->left, key);
        // 如果node的key小于要寻找的key
        // 则node有可能是key的floor节点,也有可能不是(存在比node->key大但小于key的其余节点)
        // 则要尝试向node的右子树寻找一下
        Node *tmpNode = ceil(root->right, key);
        if (tmpNode) return tmpNode;
        return root;
    }

    /**
     * 天花板
     * 在以node为根的二叉搜索树中,寻找key的ceil值所处的节点,递归算法
     * @param root
     * @param key
     * @return
     */
    Node *ceil(Node *root, Key key) {
        if (root == NULL) return NULL;

        // 如果node的key值和要寻找的key值相等
        // 则node 本身就是key的ceil节点
        if (key == root->key) return root;
        // 如果node的key比要寻找的key小
        if (root->key < key) return ceil(root->right, key);
        // 如果node的key大于要寻找的keyo
        // 则node有可能是key的ceil节点,也有可能不是(存在比node->key小但大于key的其余节点)
        // 则要尝试向node的左子树寻找一下
        Node *tmpNode = ceil(root->left, key);
        if (tmpNode) return tmpNode;
        return root;
    }

    template<typename k, typename v>
    friend ostream &operator<<(ostream &out, const RBTree<k, v> &rbTree);
};

//void shuffle(int arr[], int n) {
//    srand(time(NULL));
//    for (int i = n - 1; i >= 0; i--) {
//        int x = rand() % (i + 1);
//        swap(arr[i], arr[x]);
//    }
//}


template<typename k, typename v>
ostream &operator<<(ostream &out, const RBTree<k, v> &rbTree) {
    cout << "{key: " << rbTree.root->key << ", " << "value:" << rbTree.root->value << ", " << "color:"
         << rbTree.root->color << ", " << "left:" <<
         rbTree.root->left->key << "," << "right:" << rbTree.root->right->key << "}" << endl;
    return out;
}

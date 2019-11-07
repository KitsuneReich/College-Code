class BST {
    private:
        struct  Node
        {
            int data;
            Node* left= NULL;
            Node* right= NULL;
        };

        Node* root;
        void addLeafPrivate (int data, Node* ptr);
        void printPrivate (Node* ptr);
        Node* returnNodePrivate (int data, Node* ptr);
        void deletePrivate (int data, Node* parent);
        void deleteRoot();
        int findSmallestPrivate(Node* ptr);
        void deleteMatch(Node* parent, Node* match, bool left);

    public:
        BST ();
        Node* createLeaf(int data);
        void addLeaf(int data);
        void print();
        Node* returnNode(int data);
        void deleteNode(int data);
        int findSmallest();
        void search(int data);
    };




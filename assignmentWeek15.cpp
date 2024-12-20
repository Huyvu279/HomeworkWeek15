#include <iostream>
using namespace std;

struct Node {
    char ID[50];
    int pageCount;
    Node* left;
    Node* right;
};

void initNode(Node* root) {
    root->ID[0] = '\0';
    root->pageCount = 0;
    root->left = nullptr;
    root->right = nullptr;
}

Node* createNode() {
    Node* newNode = new Node;
    cout << "Enter ID: ";
    cin >> newNode->ID;
    cout << "Enter page number: ";
    cin >> newNode->pageCount;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}
void insertNode(Node*& root) {
    while (true) {
        if (root == nullptr) {
            root = createNode();
        }
        else {
            Node* current = root;
            char choice;
            cout << "Chuong nay co muc con khong(y/n): ";
            cin >> choice;

            if (choice != 'y' && choice != 'Y') {
                cout << "Ban co muon them chuong khong(y/n): ";
                cin >> choice;

                if (choice != 'y' && choice != 'Y') {
                    break;
                }
                else {
                    cout << "Moi ban nhap thong tin cho chuong" << endl;
                    insertNode(root->right);
                }
            }
            else {
                cout << "Moi ban nhap thong tin cho muc" << endl;
                insertNode(root->left);


            }
        }
    }
}
void printTree(Node* root) {
    if (root == nullptr) return;

    cout << "ID: " << root->ID << ", Page Count: " << root->pageCount << endl;

    if (root->left != nullptr) {
        cout << "Muc con:" << endl;
        printTree(root->left);
    }

    if (root->right != nullptr) {
        cout << "Chuong:" << endl;
        printTree(root->right);
    }
}
int countChapters(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countChapters(root->right);
}
Node* findLongestChapter(Node* root) {
    if (root == nullptr) return nullptr;
    Node* maxChapter = root;
    Node* rightMax = findLongestChapter(root->right);

    if (rightMax != nullptr && rightMax->pageCount > maxChapter->pageCount) {
        maxChapter = rightMax;
    }
    return maxChapter;
}
bool findAndDelete(Node*& root, const char* targetID, int& pageReduction) {
    if (root == nullptr) return false;

    if (string(root->ID) == targetID) {
        pageReduction = root->pageCount;

        Node* temp = root;

        if (root->left == nullptr && root->right == nullptr) {
            root = nullptr;
        }
        else if (root->left == nullptr) {
            root = root->right;
        }
        else if (root->right == nullptr) {
            root = root->left;
        }
        else {
            Node* successor = root->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            root->ID[0] = '\0';
            for (int i = 0; i < 50 && successor->ID[i] != '\0'; ++i) {
                root->ID[i] = successor->ID[i];
            }
            root->pageCount = successor->pageCount;
            findAndDelete(root->right, successor->ID, pageReduction);
            return true;
        }
        delete temp;
        return true;
    }

    if (findAndDelete(root->left, targetID, pageReduction)) {
        root->pageCount -= pageReduction;
        return true;
    }
    if (findAndDelete(root->right, targetID, pageReduction)) {
        return true;
    }

    return false;
}
int main() {
    Node* root = nullptr;  
    insertNode(root);

    cout << "\nThong tin cac chuong va muc đa nhap:" << endl;
    printTree(root);  
    int chapterCount = countChapters(root);
    cout << "\nSo chuong trong cuon sach: " << chapterCount << endl;
    Node* longestChapter = findLongestChapter(root);
    if (longestChapter != nullptr) {
        cout << "Chuong co nhieu trang nhat: " << longestChapter->ID
            << " voi " << longestChapter->pageCount << " trang." << endl;
    }
    else {
        cout << "Khong co chuong nao trong cuon sach." << endl;
    }
    char targetID[50];
    cout << "\nNhap ID cua muc can xoa: ";
    cin >> targetID;

    int pageReduction = 0;
    if (findAndDelete(root, targetID, pageReduction)) {
        cout << "\nMuc co ID " << targetID << " da bi xoa." << endl;
        cout << "Thong tin cap nhat sau khi xoa:" << endl;
        printTree(root);
    }
    else {
        cout << "Khong tim thay muc co ID " << targetID << endl;
    }
    return 0;
}
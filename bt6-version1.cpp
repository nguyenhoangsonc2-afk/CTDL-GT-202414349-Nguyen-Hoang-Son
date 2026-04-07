#include <iostream>
#include <string>
using namespace std;

// 1. Cấu trúc file
struct File {
    string name;
    long timestamp; // thời gian(số càng lớn càng mới)
    double size;    // Dung lượng (GB)
};

// 2. Node của danh sách liên kết
struct Node {
    File data; // dữ liêu là 1 file
    Node* next; // con trỏ trỏ tới nốt tiếp theo
};

// 3.Tạo node mới
Node* createNode(File f) {
    Node* p = new Node;  
    p->data = f;
    p->next = NULL;
    return p;
}

// 4. Chèn file theo thứ tự thời gian
void insertSorted(Node*& head, File f) {
    Node* p = createNode(f); //tạo node mới

 // nếu DS rỗng or file mới "cũ hơn" head
    if (head == NULL || f.timestamp < head->data.timestamp) {
        p->next = head; // node mới trỏ tới head
        head = p; // cập nhập head
        return;
    }

    Node* cur = head; //trỏ duyệt

    // tìm vị trí để chèn
    while (cur->next != NULL && cur->next->data.timestamp < f.timestamp) {
        cur = cur->next; // tới node tiếp theo
    }

    // chèn node vào giữa(cuối)
    p->next = cur->next;
    cur->next = p;
}

// 5. Tính tổng dung lượng
double totalSize(Node* head) {
    double sum = 0;
    while (head != NULL) {
        sum += head->data.size;
        head = head->next;
    }
    return sum;
}

// 5. Xóa file nhỏ nhất
void removeSmallest(Node*& head) {
    if (head == NULL) return;

    Node *cur = head, *prev = NULL;
    Node *minNode = head, *minPrev = NULL;

    double minSize = head->data.size;

    while (cur != NULL) {
        if (cur->data.size < minSize) {
            minSize = cur->data.size;
            minNode = cur;
            minPrev = prev;
        }
        prev = cur;
        cur = cur->next;
    }

    // Xóa node
    if (minNode == head) head = head->next;
    else minPrev->next = minNode->next;

    cout << "Xoa file: " << minNode->data.name << endl;
    delete minNode;
}

// 6. Tối ưu để <= 32GB
void optimize(Node*& head) {
    double sum = totalSize(head);

    while (sum > 32) {
        // tìm lại file nhỏ nhất để trừ size
        Node* cur = head;
        double minSize = cur->data.size;

        while (cur != NULL) {
            if (cur->data.size < minSize)
                minSize = cur->data.size;
            cur = cur->next;
        }

        removeSmallest(head);
        sum -= minSize;
    }
}

// 7. In danh sách
void printList(Node* head) {
    while (head != NULL) {
        cout << head->data.name << " | "
             << head->data.size << "GB | "
             << head->data.timestamp << endl;
        head = head->next;
    }
}

// 8. Main test
int main() {
    Node* head = NULL;

    insertSorted(head, {"file1", 3, 10});
    insertSorted(head, {"file2", 1, 8});
    insertSorted(head, {"file3", 5, 20});
    insertSorted(head, {"file4", 2, 6});

    cout << "Danh sach ban dau:\n";
    printList(head);

    cout << "\nTong dung luong: " << totalSize(head) << "GB\n";

    cout << "\nToi uu ve 32GB:\n";
    optimize(head);

    cout << "\nDanh sach sau khi toi uu:\n";
    printList(head);

    return 0;
}
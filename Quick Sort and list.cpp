#include <iostream>

// ��� ����
struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

// ��� ���� ��带 �߰��ϴ� ���
void append(Node*& head, int data) {
    if (!head) {
        head = new Node(data);
        return;
    }
    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new Node(data);
}

// ����� ������ ��带 �������� �Լ�
Node* getTail(Node* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

// ����� �����ϰ� �� �ǹ��� ��ȯ�մϴ�.
Node* partition(Node* head, Node* end, Node*& newHead, Node*& newEnd) {
    Node* pivot = end;
    Node* prev = nullptr, * cur = head, * tail = pivot;

    while (cur != pivot) {
        if (cur->data < pivot->data) {
            if (newHead == nullptr) newHead = cur;
            prev = cur;
            cur = cur->next;
        }
        else {
            if (prev) prev->next = cur->next;
            Node* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if (newHead == nullptr) newHead = pivot;
    newEnd = tail;

    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) {
    if (!head || head == end) return head;

    Node* newHead = nullptr, * newEnd = nullptr;

    Node* pivot = partition(head, end, newHead, newEnd);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void quickSort(Node*& head) {
    head = quickSortRecur(head, getTail(head));
}

//����Ʈ�� ����ϴ� �Լ�
void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    Node* list = nullptr;
    append(list, 10);
    append(list, 7);
    append(list, 8);
    append(list, 9);
    append(list, 1);
    append(list, 5);

    std::cout << "����Ʈ: ";
    printList(list);

    quickSort(list);

    std::cout << "����Ʈ ���: ";
    printList(list);

    return 0;
}

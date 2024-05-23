#include <iostream>

// 노드 정의
struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

// 목록 끝에 노드를 추가하는 기능
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

// 목록의 마지막 노드를 가져오는 함수
Node* getTail(Node* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

// 목록을 분할하고 새 피벗을 반환합니다.
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

//리스트를 출력하는 함수
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

    std::cout << "리스트: ";
    printList(list);

    quickSort(list);

    std::cout << "퀵쇼트 결과: ";
    printList(list);

    return 0;
}

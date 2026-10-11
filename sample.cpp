#include <iostream>
using namespace std;

namespace LIST {
    struct NODE {
        int data;
        NODE *prev = nullptr;
        NODE *next = nullptr;
    };

    NODE *head = nullptr, *tail = nullptr;
    int len = 0;

    void Pre() {
        head = tail = nullptr;
        len = 0;
    }

    // Return pointer to node at index i (0-based). Assumes i is valid.
    NODE* move(int i) {
        if (i < len / 2) {
            NODE *cur = head;
            for (int k = 0; k < i; ++k) cur = cur->next;
            return cur;
        } else {
            NODE *cur = tail;
            for (int k = len - 1; k > i; --k) cur = cur->prev;
            return cur;
        }
    }

    void insert(int i, int x) {
        NODE *node = new NODE();
        node->data = x;
        if (len == 0) { // first element
            head = tail = node;
        } else if (i == 0) { // insert at front
            node->next = head;
            head->prev = node;
            head = node;
        } else if (i == len) { // insert at end
            node->prev = tail;
            tail->next = node;
            tail = node;
        } else {
            NODE *cur = move(i);
            NODE *prevNode = cur->prev;
            node->prev = prevNode;
            node->next = cur;
            prevNode->next = node;
            cur->prev = node;
        }
        ++len;
    }

    void remove(int i) {
        if (len == 0) return;
        NODE *cur = move(i);
        if (cur->prev) cur->prev->next = cur->next; else head = cur->next;
        if (cur->next) cur->next->prev = cur->prev; else tail = cur->prev;
        delete cur;
        --len;
    }

    int Get_length() {
        return len;
    }

    int Query(int i) {
        if (i < 0 || i >= len) return -1;
        return move(i)->data;
    }

    void Print() {
        if (len == 0) {
            cout << -1 << endl;
            return;
        }
        NODE *cur = head;
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << ' ';
            cur = cur->next;
        }
        cout << endl;
    }

    void Clear() {
        while (head) {
            NODE *tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        len = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    int op, x, p, ans;
    LIST::Pre();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
            case 0:
                ans = LIST::Get_length();
                cout << ans << '\n';
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p, x);
                break;
            case 2:
                cin >> p;
                ans = LIST::Query(p);
                cout << ans << '\n';
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                LIST::Print();
                break;
        }
    }
    LIST::Clear();
    return 0;
}


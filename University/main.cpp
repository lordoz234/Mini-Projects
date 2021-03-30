#include <iostream>
#include <string>

struct Node1 {
    std::string Name;
    Node1* next;
    Node1* prev;
    Node1* t_child;
};

class University {
public:
    Node1* UNN;
    Node1* Facul;
    Node1* Kafedr;
    University();
    void insert(std::string s);
    void print();
    void print1(std::string s);
};

University::University() {
    Facul = new Node1;
    Facul -> next = NULL;
    Kafedr = new Node1;
    Kafedr -> next = NULL;
    UNN = new Node1;
    UNN-> t_child = Facul;
    Facul -> t_child = Kafedr;
    Kafedr -> next = NULL;
}

void University::insert(std::string s12) {
    std::string s, s1, s2;
    int k = 0;
    for (int i = 0; i < s12.size(); i++) {
        if (s12[i] != '.') {
            if (k == 0) {
                s += s12[i];
            }
            else if (k == 1) {
                s1 += s12[i];
            }
            else {
                s2 += s12[i];
            }
        }
        else {
            ++k;
        }
    }
    if (s == "UNN") {
        Node1 *temp1 = new Node1;
        temp1 -> Name = s1;
        temp1 -> next = NULL;
        Node1 *temp = Facul;
        bool f = true;
        while (temp -> next != NULL) {
            if (temp -> next -> Name == s1) {
                Node1 *kf = temp -> next -> t_child;
                if (kf == NULL) {
                    Node1 *kf1 = new Node1;
                    kf1 -> Name = s2;
                    kf1 -> next = NULL;
                    temp -> next -> t_child = kf1;
                    break;
                }
                else {
                    bool tr = true;
                    while (kf->next != NULL) {
                        if (kf->next->Name == s2) {
                            tr = false;
                            break;
                        }
                        kf = kf->next;
                    }
                    if (tr) {
                        Node1 *kf2 = new Node1;
                        kf2->Name = s2;
                        kf2->next = NULL;
                        Node1 *kf3 = kf;
                        kf->next = kf2;
                        kf2->prev = kf3;
                    }
                    f = false;
                    break;
                }
            }
            temp = temp -> next;
        }
        if (f) {
            Node1* tr = temp;
            temp -> next = temp1;
            temp1 -> prev = tr;
            if (s2 != "") {
                Node1 *kf = new Node1;
                kf -> Name = s2;
                kf -> next = NULL;
                temp1 -> t_child = kf;
            }
            else {
                temp1 -> t_child = NULL;
            }
        }
    }
    else {
        throw("Error");
    }
}

void University::print() {
    Node1 *temp = Facul;
    while (temp != NULL) {
        std::cout << temp -> Name << " ";
        temp = temp -> next;
    }
}

void University::print1(std::string s) {
    Node1 *temp = Facul;
    while (temp -> next != NULL) {
        if (temp -> next -> Name == s) {
            Node1 *temp1 = temp -> next -> t_child;
            while (temp1 != NULL) {
                std::cout << temp1 -> Name << " ";
                temp1 = temp1 -> next;
            }
        }
        temp = temp -> next;
    }
}
int main() {
    University jk;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        jk.insert(s);
    }
    std::cout << "ALL FACULTIES" << "\n";
    jk.print();
    std::cout << std::endl;
    std::cout << "VVEDITE FACULTIES" << "\n";
    std::string m;
    std::cin >> m;
    jk.print1(m);
}

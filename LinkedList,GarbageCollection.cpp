/*
* 미구현 코드
* 미완성 내용: BestFit(부분 완성), WorstFit(부분 완성), GarbageCollection(부분 완성)
* 완성 내용: FirstFit(완성)
* 

코드 작성 완료일: 2022.10.24(월) (06:43 A.M.)
학교            : 동의대학교 (Dong-Eui University)
코드 작성자     : 조민석
학번            : 20192471(2)
교과목          : 자료구조
교과목 담당 교수: 김진일 교수님
제출일          : 2022.10.24(월)

문제: 다음은 기억장소의 사용현황이다. 동적 기억장소 관리를 위한 메모리 할당
   알고리즘을 적용할 시에 메모리의 변화를 linked list 형태의 자료로 표현하라. 아울러,
   기억장소의 할당 후에는 이에 대한 garbage collection 하고(각각의 경우), 
   이에 대한 처리과정을 기술하라.
   (단, 후속적으로 P4=14K, P5=10K, P6=9K, P7=8K의 job이 들어온다고 가정함)
     (a) first fit의 경우    
     (b) best fit의 경우 
     (c) worst fit의 경우
*/

#include <iostream> // 표준 입출력 헤더파일 인클루드
using namespace std; // 이름 공간 std 선언
class Node { // Node 클래스 선언
public: // 퍼블릭 접근 수정자 공간 생성
    int size; // 작업 사이즈
    bool tagBit; // 가비지 컬렉션에서 쓰일 tagBit False=빈공간, True=작업
    int address; // 가비지 컬렉션에서 쓰일 시작 주소값
    Node* next; // 다음 노드를 가리킬 필드
    Node(int size = 0,bool tagBit=true) { // Node 생성자 디폴트 매개변수 size = 0, tagBit = true
        this->size = size; // size를 인스턴스 필드 size에 대입
        this->tagBit = tagBit; // tagBit를 인스턴스 필드 tagBit에 대입
        next = nullptr; // 다음 노드를 가리키는 곳을 nullptr로 설정
    }
};
class List { // 연결리스트 클래스 선언
public: // 퍼블릭 접근 수정자 공간 생성
    Node* head; // 리스트의 제일 앞 부분을 가리키는 head 선언
    
    List() { // 연결리스트 생성자 선언
        init(); // 초기화 하는 함수
    }

    void init() { // 연결리스트 초기화
        head = nullptr; // 리스트의 제일 앞 요소를 nullptr로 생성
    }

    bool is_empty() { // is_empty() 비었는지 확인하는 함수
        return head == nullptr; // head가 비었다면 true 반환
    }

    void Add_Node(int size, bool tagBit) { // 노드 추가 함수 (크기, 빈 or 작업)
        if (head == nullptr) { // head가 비었다면
            Node* new_Node = new Node(size,tagBit); // 새로운 노드 생성하고
            head = new_Node; // head가 새 노드를 가리키도록 
            new_Node->next = nullptr; // 새 노드의 다음 요소는 nullptr로 아무것도 가리키지 않음.
        }
        else { // head가 비었지 않다면 
            Node* new_Node = new Node(size,tagBit); // 새 노드를 생성 (크기, 빈 or 작업)
            Node* current = head; // current 포인터 객체 생성하여, 제일 앞 요소를 가리킴
            while (current->next != nullptr) { // current의 다음 값이 null값이 될때까지 리스트의 제일 마지막 부분까지
                current = current->next; // current를 current가 가리키는 다음 값으로 설정.
            }
            current->next = new_Node; // current가 다음 가리키는 값은 null이기 때문에 new_Node로 새 노드를 연결
            new_Node->next = nullptr; // new_Node는 nullptr로 리스트의 마무리 처리
        }
    }

    void FirstFit(string P,int size) { // FirstFit 함수
        Node* current = head; // current가 head를 가리키도록 설정
        bool tmp = false; // tmp로 체크하는것. 공간할당이 되면 true, 안될 경우 false
        while(1) { // 무한 반복문
            if (current->size >= size && current->tagBit == false) { // current의 size가 매개변수 size보다 크거나 같고, 빈 공간이라면
                Node* Ptr = new Node(size); // Ptr(작업)노드를 추가 size만큼 공간 할당
                current->size -= size; // current의 사이즈를 size매개변수만큼 삭제
                Ptr->next = current->next; // Ptr이 가리키는 다음 값을 current가 가리키는 다음 값으로 설정
                current->next = Ptr; // current가 가리키는 다음 값을 Ptr로 설정
                cout << P << " 공간 할당 성공! 크기: " << size << endl; // 공간 할당을 성공했다 알림.
                tmp = true; // 공간할당 성공 체크
                break; // 무한 반복문 탈출
            }
            current = current->next; // current가 가리키는 다음 값을 current로 설정
            if (current == nullptr) { // current가 ptr일 경우
                break; // 무한 반복문 탈출
            }
        }
        if (tmp == false) { // 위에서 공간할당에 실패했다면
            cout << P << " 공간 할당 실패" << endl; // 문자열 출력 후 줄넘김
        }
    }

    void BestFit(string P, int size) {
        Node* current = head; // current가 head를 가리키도록 설정
        bool tmp = false; // tmp로 체크하는것. 공간할당이 되면 true, 안될 경우 false
        Node* Best = nullptr; // 가장 적합한 빈공간의 위치를 가리키는 Best 노드
        int min = -1; // 가장 작은 수 선언
        while (1) { // 무한 반복문
            if (current->size >= size && current->tagBit == false) { // 만약 최근 노드의 사이즈가 매개변수 사이즈보다 크거나 같고 최근 노드의 공간이 비었을 경우
                if(min == -1){ // 만약 min값에 아무것도 없다면
                    cout << P << " 공간 할당 성공! 크기: " << size << endl; // 문자열 출력
                    tmp = true; // 공간 할당 성공으로 인정
                    min = current->size; // min에 가장 최근 값을 입력
                }
                else { // min값이 있다면
                    if (min > current->size) { // min이 current사이즈보다 크다면
                        min = current->size; // min에 current사이즈를 대입하여, size변수와 가장 가까운 작은 수를 구함.
                        Best = current; // Best노드에 current를 저장하여, 가장 적합한 공간을 가리킴
                    }
                }
            }
            current = current->next; // current가 가리키는 다음 값을 current로 설정
            if (current == nullptr) { // current가 ptr일 경우
                break; // 무한 반복문 탈출
            }
        }
        current = head; // current노드를 헤더가 가리키는 노드를 가리키게 함.
        while (1) { // 무한 반복문
            if (current == Best) { // current가 가리키는 노드가 Best일 경우
                Node* Ptr = new Node(size); // Ptr(작업)노드를 추가 size만큼 공간 할당
                current->size -= size; // current의 사이즈를 size매개변수만큼 삭제
                Ptr->next = current->next; // Ptr이 가리키는 다음 값을 current가 가리키는 다음 값으로 설정
                current->next = Ptr; // current가 가리키는 다음 값을 Ptr로 설정
            }
            current = current->next; // 다음 노드를 가리킴
            if (current == nullptr) { // 노드가 nullptr로 끝일 경우
                break; // 무한 반복문 탈출
            }
        }
        if (tmp == false) { // 위에서 공간할당에 실패했다면
            cout << P << " 공간 할당 실패" << endl; // 문자열 출력 후 줄넘김
        }
    }

    void WorstFit(string P, int size) {
        Node* current = head; // current가 head를 가리키도록 설정
        bool tmp = false; // tmp로 체크하는것. 공간할당이 되면 true, 안될 경우 false
        Node* Worst = nullptr;
        int max = -1; // 가장 작은 수 선언
        while (1) { // 무한 반복문
            if (current->size >= size && current->tagBit == false) { // 만약 최근 노드의 사이즈가 매개변수 사이즈보다 크거나 같고 최근 노드의 공간이 비었을 경우
                if (max == -1) { // 만약 min값에 아무것도 없다면
                    cout << P << " 공간 할당 성공! 크기: " << size << endl; // 문자열 출력
                    tmp = true; // 공간 할당 성공으로 인정
                    max = current->size; // max에 가장 최근 값을 입력
                }
                else { // min값이 있다면
                    if (max < current->size) { // max가 current사이즈보다 작다면
                        max = current->size; // max에 current사이즈를 대입하여, 가장 큰 공간의 크기를 구함.
                        Worst = current; // Worst노드에 current를 저장하여, 가장 큰 공간을 가리킴
                    }
                }
            }
            current = current->next; // current가 가리키는 다음 값을 current로 설정
            if (current == nullptr) { // current가 ptr일 경우
                break; // 무한 반복문 탈출
            }
        }
        current = head; // current노드를 헤더가 가리키는 노드를 가리키게 함.
        while (1) { // 무한 반복문
            if (current == Worst) { // current가 가리키는 노드가 Best일 경우
                Node* Ptr = new Node(size); // Ptr(작업)노드를 추가 size만큼 공간 할당
                current->size -= size; // current의 사이즈를 size매개변수만큼 삭제
                Ptr->next = current->next; // Ptr이 가리키는 다음 값을 current가 가리키는 다음 값으로 설정
                current->next = Ptr; // current가 가리키는 다음 값을 Ptr로 설정
            }
            current = current->next; // 다음 노드를 가리킴
            if (current == nullptr) { // 노드가 nullptr로 끝일 경우
                break; // 무한 반복문 탈출
            }
        }
        if (tmp == false) { // 위에서 공간할당에 실패했다면
            cout << P << " 공간 할당 실패" << endl; // 문자열 출력 후 줄넘김
        }
    }

    void GarbageCollection() { // 가비지 컬렉션 함수
        if (head == nullptr) {
            cout << "연결리스트가 비어서 가비지 컬렉션을 실행할 수 없습니다." << endl; // 문자열 출력 후 줄넘김
        }
        else {
            Node* current = head; // current가 head를 가리키도록 설정
            Node* free = nullptr; // free 노드 생성 및 nullptr로 생성
            Node* prev= nullptr;
            while (1) { // 마지막 요소까지를 돌리기 위해 무한 반복문
                if (current->tagBit == false) { // 만약 current가 가리키는 노드의 공간이 비었다면
                    if (free == nullptr) { // free노드에 아무것도 없다면
                        free = current; // free노드를 current노드가 가리키는 값을 가리킴
                        current = current->next; // current노드는 다음 노드로 넘어감.
                    }
                    else { // 비었지 않았다면
                        free->next = current; // free가 가리키는 다음 노드를 current로 설정
                        free = current; // free를 curent가 가리키는 값을 가리킴
                        current = current->next; // current노드는 다음 노드로 넘어감.
                    }
                }
                else { // free 공간이 아니라면
                    current = current->next; // current노드는 다음 노드로 넘어감.
                }
                if (current == nullptr) { // 만약 current가 nullptr 마지막 노드를 넘었을 경우
                    current = free;
                    break; // 무한 반복문 탈출
                }
            }
        }
    }
    void Print() { // 공간이 제대로 할당 되었는지 보여주는 구문
        Node* current = head; // current가 head를 가리키도록 설정
        while (1) { // 무한 반복문
            for (int i = 0; i < current->size; i++) { // current의 size만큼 반복
                if (current->tagBit) { // 공간이 작업 공간이라면 할당된거기에
                    cout << "■"; // 가득 찼음을 표시
                }
                else { // 비었다면(free공간)
                    cout << "▧"; // 비었음을 표시
                }
            }
            current = current->next; // current가 가리키는 값에 current 다음 값을 가리킴
            if (current == nullptr) { // current가 마지막 노드를 지나쳤을 경우
                break; // 무한 반복문 탈출
            }
        }
    }
};


int main() {
    List* FirstFit = new List();
    List* BestFit = new List();
    List* WorstFit = new List();

    // 교수님 강의자료 공간할당
    //Linkedlist->Add_Node(10, true); // P1 10K 할당
    //Linkedlist->Add_Node(12, false); // FREE 12K 할당
    //Linkedlist->Add_Node(5, true); // P2 5K 할당
    //Linkedlist->Add_Node(5, true); // P3 5K 할당
    //Linkedlist->Add_Node(10, false); // FREE 10K 할당
    //Linkedlist->Add_Node(10, true); // P4 10K 할당
    //Linkedlist->Add_Node(30, false); // FREE 30k 할당
    

    // 과제 문제 공간 할당
    FirstFit->Add_Node(7, true); // P1 7K 할당
    FirstFit->Add_Node(12, false); // FREE 12K 할당
    FirstFit->Add_Node(8, true); // P2 8K 할당
    FirstFit->Add_Node(18, false); // FREE 18K 할당
    FirstFit->Add_Node(20, true); // P3 20K 할당
    FirstFit->Add_Node(15, false); // FREE 15K 할당
    FirstFit->Print();

    cout << "\n========== First-Fit ==========" << endl;
    // 교수님 강의자료 공간 할당
    //Linkedlist->FirstFit("P5",7);
    //Linkedlist->FirstFit("P6",5);
    //Linkedlist->FirstFit("P7",9);
    //Linkedlist->FirstFit("P8",22);
    

    // 과제 문제 공간 할당
    FirstFit->FirstFit("P4", 14); // FirstFit 알고리즘으로 작업 영역 할당
    FirstFit->FirstFit("P5", 10); // FirstFit 알고리즘으로 작업 영역 할당
    FirstFit->FirstFit("P6", 9); // FirstFit 알고리즘으로 작업 영역 할당
    FirstFit->FirstFit("P7", 8); // FirstFit 알고리즘으로 작업 영역 할당
    FirstFit->Print(); // FirstFit 알고리즘 결과 출력
    cout << endl; // 다음줄 넘김

    cout << "========== Best-Fit ==========" << endl;
    BestFit->Add_Node(7, true); // P1 7K 할당
    BestFit->Add_Node(12, false); // FREE 12K 할당
    BestFit->Add_Node(8, true); // P2 8K 할당
    BestFit->Add_Node(18, false); // FREE 18K 할당
    BestFit->Add_Node(20, true); // P3 20K 할당
    BestFit->Add_Node(15, false); // FREE 15K 할당

    BestFit->BestFit("P4", 14); // BestFit 알고리즘으로 작업 영역 할당
    BestFit->BestFit("P5", 10); // BestFit 알고리즘으로 작업 영역 할당
    BestFit->BestFit("P6", 9); // BestFit 알고리즘으로 작업 영역 할당
    BestFit->BestFit("P7", 8); // BestFit 알고리즘으로 작업 영역 할당
    BestFit->Print(); // BestFit 알고리즘 결과 출력
    cout << endl; // 다음줄 넘김

    cout << "========== Worst-Fit ==========" << endl;
    WorstFit->Add_Node(7, true); // P1 7K 할당
    WorstFit->Add_Node(12, false); // FREE 12K 할당
    WorstFit->Add_Node(8, true); // P2 8K 할당
    WorstFit->Add_Node(18, false); // FREE 18K 할당
    WorstFit->Add_Node(20, true); // P3 20K 할당
    WorstFit->Add_Node(15, false); // FREE 15K 할당

    WorstFit->WorstFit("P4", 14); // WorstFit 알고리즘으로 작업 영역 할당
    WorstFit->WorstFit("P5", 10); // WorstFit 알고리즘으로 작업 영역 할당
    WorstFit->WorstFit("P6", 9); // WorstFit 알고리즘으로 작업 영역 할당
    WorstFit->WorstFit("P7", 8); // WorstFit 알고리즘으로 작업 영역 할당
    WorstFit->Print(); // WorstFit 알고리즘 결과 출력
    cout << endl; // 다음줄 넘김
}
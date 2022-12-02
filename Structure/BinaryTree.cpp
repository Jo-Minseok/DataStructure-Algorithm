/*
코드 작성 완료일: 2022.11.21(월) (03:07 A.M.)
학교            : 동의대학교 (Dong-Eui University)
코드 작성자     : 조민석
학번            : 20192471(2)
교과목          : 자료구조
교과목 담당 교수: 김진일 교수님
제출일          : 2022.11.28(월)

문제: 1. (8장 10번에서) 문제의 예와 같은 트리를 구성하고 이로부터 순회하는 함수들을 작성하고 출력하는 프로그램을 작성하시오.

*/
#include <iostream> // 표준 입출력 헤더파일 인클루드
using namespace std; // 이름 공간 표준 사용
#define MAX 11 // 최대 원형큐의 사이즈를 11로 설정

template <typename T>
class CirQueue {
    T arr[MAX] = { 0 }; // 포인터 char형 배열 arr 선언 및 크기를 MAX(8)로 초기화
    int front, rear; // int형 front(큐의 제일 앞부분), rear(큐의 제일 마지막 부분)을 선언
    int flag; // flag형 선언(0일 경우, 공간이 존재, 1일 경우 가득 찬 상태)
public: // 공개형
    CirQueue() { // 생성자 선언
        front = flag = rear = 0; // 큐의 제일 앞부분, 마지막 부분, 공간 상태를 전부 0으로 초기화
    }
    void init() { // 큐를 초기화 하는 함수
        front = flag = rear = 0; // 큐의 상태들을 초기화
    }
    void add_queue(T x) { // 큐에 삽입하는 함수
        if (flag == 1) { // 만약 큐가 가득 찼다면
            cout << "원형 큐가 꽉 찬 상태입니다." << endl; // 문자열 출력
        }
        else { // 아닐 경우
            rear = (rear + 1) % MAX; // rear를 다음 값으로 넘김 0~MAX까지 MAX일 경우 0이 나오게 되어서 큐의 제일 처음으로 돌아감
            if (rear % MAX == front % MAX) { // 만약 둘의 위치가 같다면
                flag = 1; // 가득 찼기 때문에 flag를 1로 선언
            }
            arr[rear] = x; // arr배열의 rear 인덱스에 요소 x를 대입.
        }
    }

    T dequeue() { // 큐를 제거하는 함수
        if (front == rear && flag == 0) { // 만약 큐의 front와 rear가 같고 flag가 0으로써 꽉 차 있는게 아니라면
            cout << "원형 큐가 비어있습니다." << endl; // 문자열 출력
        }
        else { // 아닐 경우
            if (front == rear) { // front와 rear가 같다면
                flag = 0; // flag를 0으로 설정하여 비었다고 설정
            }
            front = (front + 1) % MAX; // front를 다음 요소로 넘기고
            return arr[front]; // 반환
        }
    }

    void Print() { // 큐의 요소들을 출력하는 함수
        int j = 0, i = 1; // int형 j,i변수 선언 및 i를 1로 초기화
        while (true) { // 무한 반복문
            if (flag == 0 && front == rear) { // 원형 큐가 비었을 경우
                cout << "원형 큐가 비어있습니다." << endl; // 문자열 출력
                break; // 무한 반복문 탈출
            }
            else {
                j = (front + i) % MAX; // j를 front+i%MAX 요소로 대입
                if (j % MAX == rear % MAX) { // j%MAX가 rear%MAX와 같다면
                    cout << arr[j] << endl; // 마지막 요소를 출력해야하기 때문에, 마지막 요소를 출력하고
                    break; // 무한 반복문 탈출
                }
                else { // j%MAX가 rear%MAX와 같지 않으면
                    cout << arr[j] << endl; // 같을때까지의 요소들을 출력
                }
                i++; // i의 값을 추가하여 다음 요소들에 접근
            }
        }

    }
    void peek() { // 큐의 제일 앞 요소를 출력하는 함수
        if (flag == 0 && rear == front) { // 큐가 비었을 경우
            cout << "큐가 빈 상태입니다." << endl; // 큐의 제일 앞 요소를 출력
        }
        else { // 아닐 경우
            cout << "최상단   : " << arr[front + 1 % MAX]; // 큐의 제일 앞 요소를 출력
        }
    }
    int size() { // 큐의 요소 개수를 출력하는 함수
        if (flag == 1) { // 만약 flag가 1일 경우 큐가 가득 찼을 경우
            return MAX; // 가득 찼기 때문에 MAX값을 출력
        }
        else { // flag가 가득 안찼을 경우
            return (rear - front + MAX) % MAX; // rear-front가 -가 나올 수도 있기 때문에 +MAX를 시켜주고, MAX로 나눔으로써 몇개가 존재하는지 반환
        }
    }
    int Front_get() { // 프론트값 리턴 함수 선언
        return front; // 프론트 값 리턴
    }
    int Rear_get() { // 리어 값 리턴 함수 선언
        return rear; // 리어 값 리턴
    }

    bool is_empty() { // 원형 큐가 비었을 함수
        if (front == rear && flag == 0) { // 만약 앞과 뒤의 인덱스가 같고 flag가 0일 경우 원형 큐가 비었기 때문에
            return true; // 비었다고 true를 반환
        }
        else { // 아닐 경우
            return false; // 비었지 않았기 때문에 false를 반환
        }
    }
};

class BTnode { // 노드 클래스 정의
public: // public 접근 수정자로 외부에서 접근 가능하게 설정
	int data; // int data로 한 노드의 실질적인 데이터를 포함하는 멤버 변수
	BTnode* left; // 노드의 좌측 서브 트리를 가리키는 포인터 객체
	BTnode* right; // 노드의 우측 서브 트리를 가리키는 포인터 객체
    BTnode() { // 생성자
        left = nullptr; // 왼쪽 대상을 null객체로 설정
        right = nullptr; // 오른쪽 대상을 null객체로 설정
        data = 0; // 데이터를 0으로 설정
    }
};

class BTree { // 트리 클래스 정의
public: // public 접근 수정자로 외부에서 접근 가능하게 설정
    BTnode* root;
    BTree() { // 생성자
        init(); // 초기화 함수 호출
    }
    void init() { // 초기화 함수
        root = nullptr; // 루트가 가리키는 객체를 nullptr로 설정
    }

    bool is_empty_tree() { // 트리가 비었는지 확인하는 함수
        return root == nullptr; // 루트가 가리키는 객체가 없을 경우, true, 있을 경우 false 를 반환
    }

    BTnode* get_root() { // 트리의 root가 무엇인지 확인하는 함수
        return root; // 루트를 리턴
    }

    BTnode * create_tree(int data) { // 트리 생성 함수
        BTnode* n = new BTnode();
        n->data = data; // 포인터 노드 n이 가리키는 data에 data 값을 대입
        return n;
    }

	void preorder(BTnode * n) { // 전위 순회 방식(VLR)
		if (n != nullptr) { // 만약 입력된 노드 n이 가리키는 객체가 있다면
			cout << "[" << n->data << "] "; // 노드 데이터를 출력(루트) V
			preorder(n->left); // 먼저 왼쪽 서브트리들로 가서 데이터들을 출력(계속 순회하여 끝까지 감) , 만약 왼쪽 끝으로 가게 되어 nullptr을 만났을 경우 L
			preorder(n->right); // 이전 루트의 오른쪽 트리로 경로를 틀어서, 오른쪽 트리의 루트를 출력하고, 이후 오른쪽 루트의 왼쪽 서브트리부터 또 검사하여 루트들을 출력, 왼쪽 출력, 오른쪽 출력 R
		}
	}

	void inorder(BTnode* n) { // 중위 순회 방식
		if (n != nullptr) { // 만약 입력된 노드 n이 가리키는 객체가 있다면
			inorder(n->left); // 노드의 왼쪽 자식으로 쭉쭉 내려가서 nullptr을 만났다면 루트로 올라가서 L
			cout << "[" << n->data << "] "; // 해당 데이터를 출력 V
			inorder(n->right); // 노드의 오른쪽 자식으로 이동, 이후 왼쪽으로 쭉쭉 내려가기를 반복 R
		}
	}

	void postorder(BTnode* n) { // 후위 순회 방식
		if (n != nullptr) { // 만약 입력된 노드 n이 가리키는 객체가 있다면
			postorder(n->left); // 왼쪽 자식으로 쭉쭉 내려가서 nullptr을 만났다면 루트로 올라가서 L
			postorder(n->right); // 오른쪽 자식으로 방향을 틀어서, 다시 왼쪽으로 쭉쭉내려가기 해당 방식을 반복 R
			cout << "[" << n->data << "] "; // 데이터(루트)를 출력 V
		}
	}

    void levelorder(BTnode* root) { // 레벨 순회 방식
        BTnode* n; // 포인터 노드 객체 n 선언
        if (root == nullptr) { // 루트가 가리키는 객체가 없다면
            return; // 함수를 종료
        }
        CirQueue<BTnode *> circleque; // 원형 큐를 자료형 BTnode 포인터로 하고, circleque 객체 생성
        circleque.init(); // 원형큐를 초기화 하는 함수
        circleque.add_queue(root); // 원형 큐에 제일 첫 요소로 루트를 삽입
        while (!circleque.is_empty()) { // 원형큐가 공백이 될때까지 반복
            n = circleque.dequeue(); // n에 원형큐에서 삭제된 값을 저장(왼쪽부터 오른쪽으로 내려가는 형식)
            if (n != nullptr) { // n 이 가리키는 객체가 공백이 아닐 경우
                    cout << "[" << n->data << "] "; // 데이터를 출력
                    circleque.add_queue(n->left); // 루트 노드의 왼쪽 자식을 원형 큐에 삽입(얘가 우선적으로 들어감)
                    circleque.add_queue(n->right); // 루트 노드의 오른쪽 자식을 원형 큐에 삽입(얘가 다음)
            }
        }
    }
    
    void connect(BTnode* parent, BTnode* leftChild, BTnode* rightChild) { // 연결 함수, 부모 노드, 왼쪽에 들어올 자식의 노드, 오른쪽에 들어올 자식의 노드를 입력 받음.
        parent->right = rightChild; // 부모 노드의 오른쪽이 가르키는 값을 오른쪽 자식의 노드로 설정
        parent->left = leftChild; // 부모 노드의 왼쪽이 가리키는 값을 왼쪽 자식의 노드로 설정 
    }
};

int main() { // 메인 함수 선언
    BTree btree; // 트리 객체 생성 생성자를 통해서 init() 함수 호출 - root가 nullptr을 가리키게 하여 초기화
    BTnode* node[10]; // 포인터 노드 객체를 10개 생성 create_tree에서 포인터 노드를 반환하기 때문에, 포인터로 설정
    btree.root = btree.create_tree(6); // 바이너리 트리의 루트의 데이터를 6으로 설정
    node[0] = btree.create_tree(4); // 바이너리 트리의 루트의 데이터를 4로 설정
    node[1] = btree.create_tree(9); // 바이너리 트리의 루트의 데이터를 9로 설정
    node[2] = btree.create_tree(2); // 바이너리 트리의 루트의 데이터를 2로 설정
    node[3] = btree.create_tree(5); // 바이너리 트리의 루트의 데이터를 5로 설정
    node[4] = btree.create_tree(7); // 바이너리 트리의 루트의 데이터를 7로 설정
    node[5] = btree.create_tree(10); // 바이너리 트리의 루트의 데이터를 10으로 설정
    node[6] = btree.create_tree(1); // 바이너리 트리의 루트의 데이터를 1로 설정
    node[7] = btree.create_tree(3); // 바이너리 트리의 루트의 데이터를 3로 설정
    node[8] = btree.create_tree(8); // 바이너리 트리의 루트의 데이터를 8로 설정
    node[9] = btree.create_tree(11); // 바이너리 트리의 루트의 데이터를 11로 설정

    btree.connect(btree.root, node[0], node[1]); // 루트의 왼쪽 자식, 오른쪽 자식을 각각 인자 노드에 연결함
    btree.connect(node[0], node[2], node[3]); // 루트의 왼쪽 자식, 오른쪽 자식을 각각 인자 노드에 연결함
    btree.connect(node[1], node[4], node[5]); // 루트의 왼쪽 자식, 오른쪽 자식을 각각 인자 노드에 연결함
    btree.connect(node[2], node[6], node[7]); // 루트의 왼쪽 자식, 오른쪽 자식을 각각 인자 노드에 연결함
    btree.connect(node[5], node[8], node[9]); // 루트의 왼쪽 자식, 오른쪽 자식을 각각 인자 노드에 연결함

    cout << "In-Order : "; // 문자열 출력
    btree.inorder(btree.root); // 중위 순회 함수에 트리의 루트를 대입
    cout << "\nPre-Order : "; // 문자열 출력
    btree.preorder(btree.root); // 전위 순회 함수에 트리의 루트를 대입
    cout << "\nPost-Order : "; // 문자열 출력
    btree.postorder(btree.root); // 후위 순회 함수에 트리의 루트를 대입
    cout << "\nLevel-Order : "; // 문자열 출력
    btree.levelorder(btree.root); // 레벨 순회 함수에 트리의 루트를 대입
}
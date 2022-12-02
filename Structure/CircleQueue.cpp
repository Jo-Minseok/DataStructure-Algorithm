/*
코드 작성 완료일: 2022.10.17(월) (10:31 P.M.)
학교            : 동의대학교 (Dong-Eui University)
코드 작성자     : 조민석
학번            : 20192471(2)
교과목          : 자료구조
교과목 담당 교수: 김진일 교수님
제출일          : 2022.10.24(월)

문제: 원형큐(Circular Queue)를 구성하는 프로그램을 작성하시오.
Queue size는 8개로 하며, AddQue와 DelQue를 작성하고 Data의 입출력을 보이시오. % 연산자를 사용하며, Flag를 사용한 프로그램을 작성해 보시오.)
 (예) J-삽입  K-삽입  L-삽입  삭제  M-삽입  N-삽입  O-삽입  P-삽입  삭제  삭제
         Q-삽입  R-삽입  삭제   S-삽입  삭제  T-삽입   U-삽입  삭제  W-삽입

*/

#include <iostream> // 입출력 전처리기 선언

using namespace std; // std 이름 공간 사용
#define MAX 8 // 기호상수 MAX 선언후 Queue Size가 8이므로, 8 선언

class CirQueue {
    char arr[MAX] = { 0 }; // 포인터 char형 배열 arr 선언 및 크기를 MAX(8)로 초기화
    int front, rear; // int형 front(큐의 제일 앞부분), rear(큐의 제일 마지막 부분)을 선언
    int flag; // flag형 선언(0일 경우, 공간이 존재, 1일 경우 가득 찬 상태)
public: // 공개형
    CirQueue() { // 생성자 선언
        front = flag =  rear = 0; // 큐의 제일 앞부분, 마지막 부분, 공간 상태를 전부 0으로 초기화
    }
    void init() { // 큐를 초기화 하는 함수
        cout << "큐를 초기화하였습니다." << endl; // 문자열 출력
        front = flag = rear = 0; // 큐의 상태들을 초기화
    }
    void add_queue(char x) { // 큐에 삽입하는 함수
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

    void dequeue() { // 큐를 제거하는 함수
        if (front == rear && flag == 0) { // 만약 큐의 front와 rear가 같고 flag가 0으로써 꽉 차 있는게 아니라면
            cout << "원형 큐가 비어있습니다." << endl; // 문자열 출력
        }
        else { // 아닐 경우
            if (front == rear) { // front와 rear가 같다면
                flag = 0; // flag를 0으로 설정하여 비었다고 설정
            }
            front = (front + 1) % MAX; // front를 다음 요소로 넘기고
            cout << arr[front] << endl;; // arr의 front요소를 반환
        }
    }

    void Print() { // 큐의 요소들을 출력하는 함수
        int j = 0,i=1; // int형 j,i변수 선언 및 i를 1로 초기화
        while (true) { // 무한 반복문
            if (flag == 0&&front == rear) { // 원형 큐가 비었을 경우
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
        if(flag == 0 && rear == front){ // 큐가 비었을 경우
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
};

void Pro_CirQue(CirQueue cirqueue) {
    cout << "\n========== [ 남은 큐의 상태 ] ==========" << endl; // 문자열 출력
    cout << "개수     : " << cirqueue.size() << endl; // 문자열 출력 및 개수 출력
    cirqueue.peek(); // 문자열 출력 및 제일 앞의 요소 출력
    cout << "front    : " << cirqueue.Front_get() << endl; // 문자열 출력 및 front값 출력
    cout << "rear     : " << cirqueue.Rear_get() << endl; // 문자열 출력 및 rear값 출력
    cout << "[ 남은 요소 ]" << endl; // 문자열 출력
    cirqueue.Print(); // 요소들 출력
}

int main() {
    CirQueue cirqueue;
    cout << "========== [ 교수님 예제 ] ==========" << endl; // 문자열 출력
    cout << "J - 삽입, "; // 문자열 출력
    cirqueue.add_queue('J'); // 큐의 삽입 함수에 문자 'J'를 삽입
    cout << "K - 삽입, "; // 문자열 출력
    cirqueue.add_queue('K'); // 큐의 삽입 함수에 문자 'K'를 삽입
    cout << "L - 삽입"; // 문자열 출력
    cirqueue.add_queue('L'); // 큐의 삽입 함수에 문자 'L'을 삽입
    cout << "\n삭제: "; // 문자열 출력
    cirqueue.dequeue();// 큐의 제거 함수로 제거된 문자를 출력 (J)
    cout << "M - 삽입, "; // 문자열 출력
    cirqueue.add_queue('M'); // 큐의 삽입 함수에 문자 'M'을 삽입
    cout << "N - 삽입, "; // 문자열 출력
    cirqueue.add_queue('N'); // 큐의 삽입 함수에 문자 'N'을 삽입
    cout << "O - 삽입, "; // 문자열 출력
    cirqueue.add_queue('O'); // 큐의 삽입 함수에 문자 'O'를 삽입
    cout << "P - 삽입"; // 문자열 출력
    cirqueue.add_queue('P'); // 큐의 삽입 함수에 문자 'P'를 삽입
    cout << "\n삭제: "; // 문자열 출력
    cirqueue.dequeue(); // 큐의 제거 함수로 제거된 문자를 출력 (K)
    cout << "삭제: "; // 문자열 출력
    cirqueue.dequeue(); // 큐의 제거 함수로 제거된 문자를 출력 (L)
    cout << "Q - 삽입, "; // 문자열 출력
    cirqueue.add_queue('Q'); // 큐의 삽입 함수에 문자 'Q'를 삽입
    cout << "R - 삽입"; // 문자열 출력
    cirqueue.add_queue('R'); // 큐의 삽입 함수에 문자 'R'를 삽입
    cout << "\n삭제: "; // 문자열 출력
    cirqueue.dequeue(); // 큐의 제거 함수로 제거된 문자를 출력 (M) 
    cout << "S - 삽입"; // 문자열 출력
    cirqueue.add_queue('S'); // 큐의 삽입 함수에 문자 'S'를 삽입
    cout << "\n삭제: "; // 문자열 출력
    cirqueue.dequeue(); // 큐의 제거 함수로 제거된 문자를 출력
    cout << "T - 삽입, "; // 문자열 출력
    cirqueue.add_queue('T'); // 큐의 삽입 함수에 문자 'T'를 삽입
    cout << "U - 삽입"; // 문자열 출력
    cirqueue.add_queue('U'); // 큐의 삽입 함수에 문자 'U'를 삽입
    cout << "\n삭제: "; // 문자열 출력
    cirqueue.dequeue(); // 큐의 제거 함수로 제거된 문자를 출력 (N)
    cout << "W - 삽입" << endl; // 문자열 출력
    cirqueue.add_queue('W'); // 큐의 삽입 함수에 문자 'W'를 삽입
    Pro_CirQue(cirqueue);
    cout << endl; // 공백 출력
    cirqueue.init(); // 큐 초기화 함수 호출

    string command; // string형 command(명령어) 선언
    char alpha; // char형 alpha 선언(요소)
    while (true) { // 무한 반복문
        cout << "\n==================== [ 명령어 ] ====================\n삽입 / 삭제 / 초기화 / 최상단 / 개수 / 출력 / 종료" << endl; // 문자열 출력
        cin >> command; // command 문자열에 문자열 입력 받기
        if (command == "삽입") { // 만약 command가 삽입일 경우
            cout << "\n========== [ 삽입 모드 ] ==========" << endl; // 문자열 출력
            while (true) { // 무한 반복문
                cout << "삽입할 문자 입력(0 입력시 나감):"; // 문자열 출력
                cin >> alpha; // alpha 문자에 문자 입력 받기
                if (alpha != '0') { // 만약 입력된 문자가 0일 경우
                    cirqueue.add_queue(alpha); // 큐에 alpha 문자를 삽입
                }
                else { // 위의 조건이 아닐 경우
                    break; // 입력 무한 반복문을 탈출
                }
            }
        }
        else if (command == "삭제") { // // 만약 command가 삭제일 경우
            cirqueue.dequeue(); // 삭제된 값을 출력
        }
        else if (command == "초기화") { // 만약 command가 초기화일 경우
            cirqueue.init(); // 큐를 초기화
        }
        else if (command == "최상단") { // 만약 command가 최상단일 경우
            cirqueue.peek();  // 큐의 제일 앞 요소를 출력
        }
        else if (command == "개수") { // 만약 command가 개수일 경우
            cout << "큐의 요소 개수: " << cirqueue.size() << " 입니다." << endl; // 큐의 개수를 출력
        }
        else if (command == "출력") { // 만약 command가 출력일 경우
            cirqueue.Print(); // 큐의 원소들을 전부 출력
            cirqueue.Front_get(); // Fornt값 출력
            cirqueue.Rear_get(); // Rear값 출력
        }
        else if (command == "종료") { // 만약 command가 종료일 경우
            Pro_CirQue(cirqueue);
            cout << "프로그램을 종료합니다." << endl; // 문자열 출력
            break;
        }
        else { // 위의 모든 명령어에 해당하지 않는다면
            cout << "잘못된 입력입니다." << endl; // 문자열 출력
        }
    }
}
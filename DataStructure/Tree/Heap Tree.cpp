/*
코드 작성 완료일: 2022.11.22(화) (04:04 A.M.)
학교            : 동의대학교 (Dong-Eui University)
코드 작성자     : 조민석
학번            : 20192471(2)
교과목          : 자료구조
교과목 담당 교수: 김진일 교수님
제출일          : 2022.11.28(월)

문제: 2. (10장 8번에서) 1) 최대 힙 트리를 구성하는 프로그램을 작성하시오. 입력 데이터는 문제와 동일함. 2) 여기서 차례로 루트를 제거하여 내림차순 정렬하는 프로그램을 작성하시오.

*/
#include <iostream> // 표준 입출력 헤더파일 인클루드
#define MAX_NODE 100 // 최대 노드 개수를 100개로 설정
using namespace std; // 네임 스페이스 표준을 사용

class Heap_Tree { // 힙 트리 클래스를 생성
	int heap[MAX_NODE] = { 0 }; // 힙의 노드 개수를 최대 100개로 하고 모든 노드를 0으로 초기화
	int heap_size; // 힙 트리 노드 개수 변수 생성
	int i = 0; // 임시로 힙 사이즈 +1 을 저장할 변수
public: // 접근 지정자를 public으로 설정
	Heap_Tree() { // 힙 트리의 생성자
		init(); // 힙 트리를 초기화 하는 함수
	}
	void init() { // 힙 트리 초기화 함수
		heap_size = 0; // 힙 사이즈를 0으로 설정
	}
	bool is_empty() { // 힙 트리가 비었는지 확인
		return heap_size == 0; // 힙 사이즈가 0이라면 비었으므로 true를 반환, 안비었다면 false를 반환
	}
	bool is_full() { // 힙 트리가 가득 찼는지 확인
		return (heap_size == MAX_NODE - 1); // 힙 사이즈가 MAX_NODE-1이라면 가득 찼기 때문에 true를 반환, 안찼다면 false를 반환
	}
	int find_heap() { // 힙 트리의 루트를 찾는 함수
		return heap[1]; // 힙 트리의 제일 첫 인덱스 값을 반환
	}

	void insert_heap(int e) { // 노드를 힙 트리에 추가하는 함수
		if (is_full()) { // 힙이 가득 찼다면 더이상 힙에 요소를 추가할 수 없으므로
			return; // 해당 함수를 실행하지 않음.
		}
		i = ++heap_size; // 변수 i에 힙 사이즈 +1 값을 저장하여서 처음 요소가 인서트 될때 배열의 인덱스 1부터 넣을 수 있도록 설정
		while (i != 1 &&e > heap[i/2]) // 만약 인덱스가 1이 아니고 요소가 노드의 루트보다 크다면 반복
		{
			heap[i] = heap[i/2]; //  노드의 루트를 자식으로 강등
			i /= 2; // i/2를 통해서 해당 노드의 루트에 접근
		}
		heap[i] = e; // i에는 해당 노드의 루트에 접근되어있으므로, 노드의 루트에 e를 대입
	}

	int delete_heap() { // 노드를 힙 트리에서 삭제하는 함수
		int root, last; // 노드의 루트 변수, last 변수를 생성
		int parent = 1, child = 2; // 부모 변수를 1, 자식 변수를 2로 설정
		if (is_empty()) { // 힙이 비었을 경우 제거할 노드가 없기 때문에
			cout << "힙 트리 공백 에러"; // 문자열 출력
			return 1; // 오류 발생했다는 것을 알려야 하기 때문에 return 1을 반환
		}
		root = heap[1]; // 루트에 heap[1]로 힙 트리의 제일 최상단 루트 값을 저장
		last = heap[heap_size--]; // 마지막 변수에 힙의 가장 마지막 말단 값을 저장, heap_size가 노드의 개수이므로 마지막 노드를 저장
		while (child <= heap_size) { // 자식의 수(2)가 노드의 개수보다 작거나 같다면
			if (child < heap_size && heap[parent * 2] < heap[parent * 2 + 1]) { // 만약 child가 노드의 개수보다 작고 힙의 부모*2로 왼쪽 자식 노드의 값이 오른쪽 자식 노드의 값보다 작다면
				child++; // 자식 개수에 1을 더해줌
			}
			if (last >= heap[child]) { // 만약 말단부의 값이 좌 or 우측(위의 child++에 따라 달라짐) 자식의 값보다 크거나 같을 경우
				break; // 반복문을 탈출
			}
			heap[parent] = heap[child]; // 부모 노드에 자식 노드를 대입
			parent = child; // 부모 인덱스에 자식 인덱스를 대입
			child *= 2; // 자식 인덱스를 *2를 하여 그다음 자식으로 넘어감
		}
		heap[parent] = last; // 힙 트리 노드의 부모 노드에 말단 값을 대입
		return root; // 루트를 반환하여 최대값을 반환
	}

	void print_heap() { // 힙의 모든 노드를 출력하는 함수
		int level; // 레벨 변수 선언
		if (is_empty()) { // 트리가 비었을 경우
			cout << "힙 트리가 공백 상태입니다!"; // 문자열 출력
			return; // 함수 종료
		}
		for (int i = 1, level = 1; i <= heap_size; i++) { // 힙 트리의 배열 인덱스는 1부터 시작하므로, i와 레벨을 1로 초기화, i가 힙 트리 노드 개수보다 작거나 같을 경우 반복
			if (i == level) { // 만약 i가 레벨과 같다면
				cout << "\n"; // 다음줄 넘김
				level *= 2; // 레벨에 *2를 처리 // 한 레벨당 가질 수 있는 최대 노드의 수만큼만 출력
			}
			cout << "  [" << heap[i] << "] "; // 힙의 노드를 출력
		}
		cout << "\n"; // 다음줄 넘김
	}
};

int main() { // 메인 함수 선언
	Heap_Tree HPtree; // 힙 트리 객체 생성
	HPtree.insert_heap(10); // 힙 트리에 10을 추가
	HPtree.insert_heap(40); // 힙 트리에 40을 추가
	HPtree.insert_heap(30); // 힙 트리에 30을 추가
	HPtree.insert_heap(5); // 힙 트리에 5를 추가
	HPtree.insert_heap(12); // 힙 트리에 12를 추가
	HPtree.insert_heap(6); // 힙 트리에 6을 추가
	HPtree.insert_heap(15); // 힙 트리에 15를 추가
	HPtree.insert_heap(9); // 힙 트리에 9를 추가
	HPtree.insert_heap(60); // 힙 트리에 60을 추가

	cout << "\n[ 모든 노드의 내용 출력 ]\n"; // 문자열 출력
	HPtree.print_heap(); // 힙 트리의 모든 노드를 출력

	cout << "\n\n[ 루트 제거 내림차순 정렬 ]\n"; // 문자열 출력
	for (int i = 0; i < 9; i++) { // 총 힙 트리의 개수는 9개이므로, 9번 반복
		cout << "[" << HPtree.delete_heap()<<"] "; // 힙의 값을 제거함으로써 제일 최상단의 값이 나옴, 제일 최상단의 값은 힙 트리의 최대값임
	}
	cout << "\n\n\n"; // 다음줄로 넘김(공백)
	HPtree.print_heap(); // 힙 트리의 모든 노드를 출력, 비었기 때문에 공백상태라고 출력
	cout << "\n\n\n"; // 다음줄로 넘김(공백)
}
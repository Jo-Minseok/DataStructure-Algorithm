#include <iostream> // 입출력 스트림 헤더파일 인클루드
#include <ctime> // C에 있는 time 헤더파일 인클루드
#include <cstdlib> // C에 있는 표준 라이브러리 헤더파일 인클루드

using namespace std; // 표준 이름 공간 사용

class Node { // 노드 클래스 생성
public: // 접근 지정자 public 선언
	int data; // int형 data 변수 선언
	Node* next; // 다음으로 가리킬 노드 포인터 객체 선언
	Node(int x) // 생성자 선언
	{
		data = x; // 객체의 data 멤버 변수에 x를 대입 
		next = NULL; // 다음 가리킬 객체를 NULL로 대입
	}
};

class Merge_Sort {
public: // public 접근 지정자 그룹 생성
	Node* head; // head 포인터 객체 생성

	Merge_Sort() { // 병합 정렬 생성자 선언
		this->head = NULL; // head가 가리키는 값을 NULL로 설정
	}

	// 연결리스트 삽입
	void insert(Node* node, int data)
	{
		if (node->next == NULL) // 노드의 다음 가리키는 값이 없을 경우
		{
			Node* newnode = new Node(data);  // 새로운 노드에 동적 할당
			node->next = newnode; // 노드의 다음 가리키는 값을 새로운 노드로 연결
		}

		else
		{
			Node* cur = node; // 현재 노드를 대입
			while (cur->next != NULL) // 최근 노드의 다음 값이 가리키는 값이 공백이 아닐 경우 반복
			{
				cur = cur->next; // 최근 노드에 다음 노드가 가리키는 값을 대입
			}
			// 즉, 빈 노드를 만날때까지 반복
			Node* newnode = new Node(data); // 새 노드 생성
			cur->next = newnode; // 최근 노드 다음 노드가 새로 만든 노드를 가리키도록 설정
		}

	}

	// 연결 리스트의 중간 지점을 찾기 위한 함수
	Node* findMiddle(Node* head) {

		if (head == NULL) // 만약 입력된 노드가 가리키는 값이 없다면
			return head; // 입력된 노드를 반환

		Node* left = head, * right = head; // 왼쪽 리스트와 오른쪽 리스트가 가리키는 값을 head로 초기화

		while (right->next != NULL && right->next->next != NULL) { // 우측 리스트의 다음 객체, 왼쪽 리스트의 다다음 객체가 NULL이 아닐 경우 반복
			right = right->next->next; // 우측 노드가 가리키는 값을 우측 다다음 노드로 설정
			left = left->next; // 왼쪽 노드가 가리키는 값을 왼쪽 다음 노드로 설정
		}

		// 중간 노드 반환
		return left;
	}
	// 연결리스트 출력
	void printlist(Node* root)
	{
		this->head = root->next; // 머지 소트의 헤드가 가리키는 값을 루트 노드의 다음 값으로 설정
		while (this->head != NULL) { // 노드가 NULL이 아니라면
			cout << this->head->data << " "; // 노드의 데이터를 출력
			this->head = this->head->next; // 현재 노드가 가리키는 노드를 다음 노드로 설정
		}
	}

	// 연결리스트 난수 출력
	void printRandom(Node* head) {
		this->head = head->next; // 해당 머지 소트의 첫 노드를 루트 노드의 다음 값을 가리키게 설정
		int i = 0; // int형 정수 i 선언 및 0 초기화
		while (this->head != NULL) { // 노드가 가리키는 값이 NULL이 아니라면 반복
			if (i % 10 == 0 && i != 0) { // i가 10의 배수이면서 0이 아닐 경우
				cout << "\n"; // 줄 넘김
			}
			printf("%4d ", this->head->data); // 노드의 값을 출력
			this->head = this->head->next; // 현재 노드가 가리키는 노드를 다음 노드로 설정
			i++; // i에 1을 추가
		}
	}

	// 병합 정렬 연결리스트 병합
	Node* Merge(Node* left, Node* right) {

		if (left == NULL) // 만약 왼쪽 리스트가 NULL이라면
			return right; // 오른쪽 리스트 반환
		if (right == NULL) // 만약 오른쪽 리스트가 NULL이라면
			return left; // 왼쪽 리스트 반환

		Node* result = NULL; // 결과 리스트를 NULL로 설정

		if (left->data <= right->data) { // 왼쪽 데이터가 오른쪽 데이터보다 작거나 같을 경우
			result = left; // 결과 노드에 왼쪽 리스트를 대입
			result->next = Merge(left->next, right); // 결과 노드의 다음 노드에 왼쪽 리스트의 다음 가리키는 값을 넣고, 오른쪽 리스트를 대입
		}

		else { // 아닐 경우
			result = right; // 결과 노드에 오른쪽 리스트를 대입
			result->next = Merge(left, right->next); // 결과 노드의 다음 노드에 왼쪽 리스트를 대입하고, 오른쪽 다음 리스트를 대입
		}

		return result; // 결과 리스트 반환
	}

	// 병합 정렬 연결리스트 정렬
	Node* Merge_sort(Node* head) {
		if (head == NULL || head->next == NULL) { // 노드가 가리키는 값 또는 노드가 가리키는 다음 값이 없을 경우
			return head; // 입력된 노드를 반환
		}

		// 연결리스트의 중간 노드를 찾음
		Node* mid = findMiddle(head);

		// 중간 노드의 다음 노드를 대입
		Node* nextToMid = mid->next;


		mid->next = NULL; // 중간 노드의 다음 노드를 끊어줌

		Node* left = Merge_sort(head); // 왼쪽 리스트를 형성
		Node* right = Merge_sort(nextToMid); // 오른쪽 리스트를 형성

		// 분할된 노드를 병합하여 정렬
		Node* result = Merge(left, right);

		return result; // 결과 리스트를 반환
	}
};

// 메인 함수
int main()
{
	Merge_Sort list; // list 객체 생성, 병합 정렬의 리스트, 생성자 실행
	Node* root = new Node(0); // 제일 첫 노드 생성 루트 노드

	// 리스트 삽입
	int size; // 입력받을 데이터 개수
	int data; // 데이터 값


	while (true) // 무한 반복문 실행
	{
		cout << "[연결 리스트 병합 정렬]\n"; // 문자열 출력
		cout << "데이터의 개수를 입력하세요.(10 이상) : "; // 문자열 출력
		cin >> size; // 정수 size 입력 받기
		if (size < 10) // 10보다 작을 경우
		{
			cout << "10 이상을 입력하세요\n"; // 문자열 출력
			continue; // while의 조건문으로 이동
		}
		break; // 클 경우, break문으로 무한 반복문 탈출
	}
	for (int i = 0; i < size; i++) // size만큼 반복
	{
		cout << i + 1 << "번째 숫자 입력 : "; // 문자열 출력
		cin >> data; // data를 입력받고
		list.insert(root, data); // 노드에 데이터를 대입하여 리스트에 추가
	}

	cout << "\n[ 병합 정렬 전 ]\n"; // 문자열 출력
	list.printlist(root); // 리스트를 출력
	cout << "\n\n"; // 줄넘김

	list.head = list.Merge_sort(root); /// 병합 정렬 후

	cout << "[ 병합 정렬 후 ]\n"; // 문자열 출력
	list.printlist(root); // 정렬된 리스트를 출력
	cout << "\n"; // 줄 넘김

	cout << "\n---------- 100개 난수 입력 정렬(1~200) ----------\n\n"; // 문자열 출력
	root->next = NULL; // 루트가 가리키는 객체를 NULL로 정의함으로써 연결 리스트 초기화
	srand((long)time(NULL)); // 난수 씨드 값을 time(NULL)로 시스템 시간을 사용함으로써 프로그램 실행마다 다른 값을 불러옴
	for (int i = 0; i < 100; i++) { // 0~99까지 총 100번 반복
		list.insert(root,rand() % 200+1); // 리스트의 i번째에 난수 1~200 사이의 수를 입력
	}
	cout << "[ 병합 정렬 전 ]\n"; // 문자열 출력
	list.printRandom(root); // 난수 리스트 출력 함수
	cout << "\n\n"; // 줄 넘김

	list.head = list.Merge_sort(root); /// 병합 정렬 후
	cout << "[ 병합 정렬 후 ]\n"; // 문자열 출력
	list.printRandom(root); // 난수 리스트 출력 함수
	cout << "\n\n"; // 줄 넘김
	cout << "-------------------------------------------------\n"; // 문자열 출력
	return 0; // 0 반환과 함께 프로그램 정상 종료
}
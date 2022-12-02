#include <iostream> // 입출력 스트림 헤더파일 인클루드
#include <ctime> // C에 있는 time 헤더파일 인클루드
#include <cstdlib> // C에 있는 표준 라이브러리 헤더파일 인클루드

using namespace std; // 표준 이름 공간 사용

// 배열 출력
void print_arr(int arr[], int size) { // 형식 인자는 배열, 배열의 크기
    for (int i = 0; i < size; i++) { // 0부터 size-1번째까지 반복
        cout << arr[i] << ' '; // arr의 i번째 요소를 출력
    }
    cout << "\n"; // 줄 넘김
}

// 병합 함수
void Merge(int arr[], int start_index, int mid_index, int end_index) {
    int start_indexTmp, new_start_indexTmp, mid_indexTmp, end_indexTmp; // 시작 임시 인덱스, 새 배열 인덱스, 중간 임시 인덱스, 마지막 임시 인덱스 선언

    start_indexTmp = new_start_indexTmp = start_index; // 기존 배열 시작 인덱스, 새 배열 시작 인덱스를 스타트 인덱스로 설정
    mid_indexTmp = mid_index + 1; // mid_index + 1 의 인덱스 값을 mid_indexTmp에 설정
    end_indexTmp = end_index; // 마지막 인덱스 임시로 설정

    int* tmp_arr = new int[end_indexTmp + 1] { 0 }; // 마지막 인덱스 + 1을 한 크기를 동적 배열로 tmp_arr에 할당하고 모든 배열 요소를 0으로 초기화

    // start_index 부터 mid_index 까지의 블록과 mid_index + 1 부터 end_index 까지의 블록을 서로 비교
    while (start_indexTmp <= mid_index && mid_indexTmp <= end_index) { // 시작 인덱스 값이 중간 인덱스보다 작거나 같고 중간 인덱스는 마지막 인덱스보다 작거나 같을 경우
        if (arr[start_indexTmp] < arr[mid_indexTmp]) { // 만약 arr의 시작 인덱스 값이 arr의 중간 인덱스 값보다 작을 경우
            tmp_arr[new_start_indexTmp++] = arr[start_indexTmp++]; // tmp_arr의 새 배열 시작 인덱스 값에 시작 인덱스 값을 대입하고 각각의 인덱스 값을 +1 
        }
        else { // 아닐 경우
            tmp_arr[new_start_indexTmp++] = arr[mid_indexTmp++]; // tmp_arr의 새 배열 시작 인덱스 값에 중간 인덱스 값을 대입하고 각각의 인덱스 값을 +1 
        }
    }

    // start_index 블록의 값이 다 처리되었지만, end_index 블록의 index가 남아 있는 경우
    // end_index 블록의 남은 부분을 순차적으로 tmp_arr에 복사
    if (start_indexTmp > mid_index) { // 만약 시작 임시 인덱스가 입력된 중간 인덱스보다 클 경우
        for (int m = mid_indexTmp; m <= end_index; m++) { // 중간 임시 인덱스부터 입력된 마지막 인덱스랑 같아질때까지 반복
            tmp_arr[new_start_indexTmp++] = arr[m]; // tmp_arr의 새 인덱스번째 값에 arr의 m번째 요소를 대입
        }
    }
    // start_index 블록의 남은 부분을 순차적으로 tmp_arr에 복사
    else if (start_indexTmp <= mid_index) { // 위의 if조건에 부합하지 않을 경우
        for (int m = start_indexTmp; m <= mid_index; m++) { // 시작 임시 인덱스부터 입력된 중간 인덱스랑 같아질때까지 반복
            tmp_arr[new_start_indexTmp++] = arr[m]; // tmp_arr의 새 인덱스번째 값에 arr의 m번째 요소를 대입
        }
    }

    // 임시 배열인 tmp_arr의 값을 원본 배열에 복사한다.
    for (int m = start_index; m <= end_index; m++) { // 시작 인덱스부터 끝 인덱스까지
        arr[m] = tmp_arr[m]; // arr배열의 m번째에 tmp_arr의 m번째의 값을 대입
    }
}

// 분할 및 정복(비교)
void Merge_sort(int arr[], int start_index, int end_index) { // 인자값으로 배열, 시작 인덱스, 마지막 인덱스를 대입
    int mid_index; // 중간 인덱스 변수 선언

    if (start_index < end_index) { // 만약 시작 인덱스가 마지막 인덱스 값보다 작을 경우
        // 절반으로 나누기 위해 중간 위치 찾기
        mid_index = (start_index + end_index) / 2;

        // 분할
        Merge_sort(arr, start_index, mid_index); // 재귀 함수 호출로 값들을 대입, 좌측 배열 생성
        Merge_sort(arr, mid_index + 1, end_index); // 재귀 함수 호출로 값들을 대입, 우측 배열 생성

        // 합병
        Merge(arr, start_index, mid_index, end_index); // 합병 함수 호출
    }
}

// 메인 함수
int main() {
    int size = 0; // 배열 크기를 0으로 설정
    while (true) { // 무한 반복문 실행
        cout << "[배열 병합정렬]\n"; // 문자열 출력
        cout << "데이터의 개수를 입력하세요.(10 이상) : "; // 문자열 출력
        cin >> size; // size를 입력 받기
        if (size < 10) { // size가 10보다 작을 경우
            cout << "10 이상을 입력하세요\n"; // 문자열 출력
            continue; // 다시 반복문 실행
        }
        break; // 클 경우, 무한 반복문 탈출
    }
    int* arr = new int[size]; // size 변수 만큼 arr에 배열을 동적 할당

    for (int i = 0; i < size; i++) // size만큼 반복
    {
        cout << i + 1 << "번째 숫자 입력 : "; // 문자열 출력
        cin >> arr[i]; // 배열 i번째 요소에 숫자를 입력 받기
    }
    cout << "\n"; // 문자열 출력

    cout << "[ 병합 정렬 전 ]\n"; // 문자열 출력
    print_arr(arr, size); // 배열 크기만큼 출력
    cout << "\n"; // 문자열 줄 넘김
    
    Merge_sort(arr, 0, size-1); // 병합 정렬 함수에 입력, 분할 하는 함수로써, arr배열의 0번째 인덱스, 마지막 인덱스 값을 실인자로 대입
    cout << "[ 병합 정렬 후 ]\n"; // 문자열 출력
    print_arr(arr, size); // 정렬된 배열을 크기만큼 출력

    cout << "\n---------- 100개 난수 입력 정렬(1~200) ----------\n\n"; // 문자열 출력
    arr = new int[100]; // arr 배열에 새로운 배열 크기 100을 할당
    srand((long)time(NULL)); // 난수 씨드 값을 time(NULL)로 시스템 시간으로 설정하여 실행마다 랜덤하게 나올 수 있도록 설정
    for (int i = 0; i < 100; i++) { // 0~99까지 총 100번 반복
        arr[i] = rand() % 200 + 1; // 1~200까지의 랜덤 난수를 arr 배열의 i번째 요소에 대입
    }
    cout << "[ 병합 정렬 전 ]\n"; // 문자열 출력
    for (int i = 0; i < 100; i++) { // 0~99까지 총 100번 반복
        if (i % 10 == 0 && i != 0) { // i가 0이 아니면서 10의 배수일 경우
            cout << "\n"; // 줄 넘김
        }
        printf("%4d ", arr[i]); // arr 배열의 i번째 요소를 출력
    }
    cout << "\n\n"; // 문자열 출력

    Merge_sort(arr, 0, 100 - 1); // 병합 정렬 함수에 입력, 분할 하는 함수로써, arr배열의 0번째 인덱스, 마지막 인덱스 값을 실인자로 대입
    cout << "[ 병합 정렬 후 ]\n"; // 문자열 출력
    for (int i = 0; i < 100; i++) { // 0~99까지 총 100번 반복
        if (i % 10 == 0 && i != 0) { // i가 0이 아니면서 10의 배수일 경우
            cout << "\n"; // 줄 넘김
        }
        printf("%4d ", arr[i]); // arr 배열의 i번째 요소를 출력
    }
    cout << "\n\n-------------------------------------------------"; // 문자열 출력
    return 0; // 0 반환 후 프로그램 정상 종료
}
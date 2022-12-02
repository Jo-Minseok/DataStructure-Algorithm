/*
코드 작성 완료일: 2022.09.29(목) (23:45 P.M.)
학교            : 동의대학교 (Dong-Eui University)
코드 작성자     : 조민석
학번            : 20192471(2)
교과목          : 자료구조
교과목 담당 교수: 김진일 교수님
제출일          : 2022.10.05(수)

문제: 희소행렬(Sparse Matrix)을 배열로 읽고.
1) 이를 3원소로 저장하는 표현법을 보이고,
2) 이 표현법으로 표기된 행렬을 원 상태의 행렬로 복원하라.
3) 이의 전치행렬(Matrix Transpose)을 구한 결과를 출력하라.
단, 1),2),3)을 각각의 함수를 사용하여 프로그램을 작성하라.

[사용 함수 및 기능]
input : matrix라는 일반형 2차원 배열의 요소들을 입력하고 요소가 0이 아닌 곳의 개수를 측정
three_element : 3원소 표현법 및 행 좌표와 열 좌표, 요소 값들을 main 함수 내의 배열에 저장 및 3원소 표현법으로 출력
remake : 위에서 적은 3원소 표현법을 원본 배열로 복원하여 출력
three_element_transpose : 전치하여 3원소 표현법으로 출력하고, 전치형 배열에 전치형 3원소 표현법의 요소들을 입력하여 배열을 생성
transpose_remake : 위의 함수에서 만든 전치형 결과 배열을 출력

main : 행 위치 배열과 열 위치 배열, 값 위치 배열을 각각 위의 함수들에서 나온 0이 아닌 곳의 개수만큼 동적 배열 할당 한 후, 각 함수들에 대입.
*/

#include <iostream> // 입출력 전처리기 선언
#define col 15 // col 이름의 15 지시문 선언
#define row 8 // row 이름의 8 지시문 선언
using namespace std; // std 이름 공간 사용


int count = 0; // 전역 변수 count 선언 및 0 초기화


// 입력 및 희소행렬 내에서 0이 아닌 값의 개수를 찾는 input 함수
void input(int matrix[][row]) { // 반환형 없음, 함수 이름: input, 매개변수로 matrix라는 일반형 2차원 배열을 입력(열은 8)
	cout << "행 [" << col << "] 열 [" << row << "] 인 배열 입력: " << endl; // 출력
	for (int i = 0; i < col; i++) { // 밑의 for문까지 해서, 2차원 배열 matrix[15][8] 일반형에 cin을 이용하여 입력받음, 행 반복
		for (int j = 0; j < row; j++) { // 열 반복
			cin >> matrix[i][j]; // 입력
			if (matrix[i][j] != 0) { // 만약 입력받은 요소가 0이 아니라면,
				::count++; // 일반형 배열안에 몇개의 요소가 0이 아닌지를 +1씩 증가시켜서 카운트
			}
		}
	}
	cout << "=====================================================" << endl << endl << endl << endl; // 출력 후 줄 넘기고 3줄 띄움
}


// 3원소 표현법 및 행 좌표와 열 좌표, 요소 값 배열에 각 값들을 저장해주는 three_element 함수
void three_element(int matrix[][row], int* col_index, int* row_index, int* element_result) { // 반환형 없음, 함수 이름: three_element, 매개변수로 matrix 일반형 2차원 배열, 행 좌표 배열(col_index), 열 좌표 배열(row_index), 요소 값 배열(element_result) 입력
	int count_element = 0; // int형 count_element 변수 선언 : 0이 아닌 곳을 확인
	for (int i = 0; i < col; i++) { // 행 반복
		for (int j = 0; j < row; j++) { // 열 반복
			if (matrix[i][j] != 0) { // 만약 요소값이 0이 아니라면
				col_index[count_element] = i; // 행 좌표 배열에 행을 저장
				row_index[count_element] = j; // 열 좌표 배열에 열을 저장
				element_result[count_element] = matrix[i][j]; // 요소 배열에 요소를 저장
				count_element++; // 0이 아닌 곳 개수를 올리면서 좌표들을 다음 요소들에 저장할 수 있게끔 설정
			}
		}
	}

	cout << "    『     3원소 표현법       』  " << endl; // 출력 후 줄넘김
	cout << "===== " << col << "(행)\t" << row << "(열)\t" << count_element << "(개)" << " =====" << endl; // 출력 후 줄넘김
	for (int i = 0; i < count_element; i++) { // 0이 아닌 요소 개수만큼 반복
		cout.width(11); cout << col_index[i]; // 11칸 공백 출력하여서 다음에 나올 출력을 우측 정렬하여 출력, 행 좌표를 출력
		cout.width(9); cout << row_index[i]; // 9칸 공백 출력하여서 다음에 나올 출력을 우측 정렬하여 출력, 열 좌표를 출력
		cout.width(9); cout << element_result[i] << endl; // 9칸 공백 출력하여서 다음에 나올 출력을 우측 정렬하여 출력, 요소 값을 출력 후 줄넘김
	}
	cout << "====================================" << endl << endl << endl << endl; // 출력 후 줄 넘기고 3줄 띄움
}


// 위에서 적은 three_element 함수에서 얻은 3원소 표현법들을 복원시키는 함수
void remake(int* col_index, int* row_index, int* element_result) { // 반환형 없음, 함수 이름: remake, 매개 변수로 행 좌표 배열(col_index), 열 좌표 배열(row_index), 요소 값 배열(element_result) 입력
	int remake_arr[col][row] = { 0 }; // 복원 시킬 배열 15행 8열을 선언, 요소를 0으로 다 초기화
	for (int i = 0; i < ::count; i++) { // 0이 아닌 요소 개수만큼 반복
		remake_arr[col_index[i]][row_index[i]] = element_result[i]; // remake_arr 배열의 행 요소에 0이 아닌 좌표의 행 좌표를 입력, 열 요소에 0이 아닌 좌표의 열 좌표를 입력하고, 요소 값에는 0이 아닌 좌표의 요소를 입력
	}

	cout << "『 3원소 표현법 원 상태 행렬 복원 』" << endl; // 출력 후 줄넘김
	cout << "====================================" << endl; // 출력 후 줄넘김
	for (int i = 0; i < col; i++) { // 행 반복
		for (int j = 0; j < row; j++) { // 열 반복
			cout.width(3);  cout << remake_arr[i][j] << " "; // 공백 3칸씩 주면서 우측 정렬하여 remake_arr 배열의 요소를 하나하나 출력하여, 다음 요소랑 겹쳐서 보이지 않게 공백을 출력
		}
		cout << endl; // 빈 공백 출력 후 다음줄 넘김
	}
	cout << "====================================" << endl << endl << endl << endl; // 출력 후 줄 넘기고 3줄 띄움
}


// three_element 함수에서 얻은 행 좌표 배열, 열 좌표 배열, 요소 값 배열을 결과 배열(전치형)에 대입하고, 전치하여 3원소 형태로 출력하는 함수
void three_element_transpose(int result_arr[][col], int* col_index, int* row_index, int* element_result) { // 반환형 없음, 함수 이름: three_element_transpose, 매개 변수로 결과 배열(전치형), 행 좌표 배열(col_index), 열 좌표 배열(row_index), 요소 값 배열(element_result) 입력
	cout << "    『    전치 3원소 표현법   』" << endl; // 출력 후 줄넘김
	cout << "===== " << col << "(열)\t" << row << "(행)\t" << ::count << "(개)" << " =====" << endl; // 출력 후 줄넘김
	for (int i = 0; i < ::count; i++) { // 0이 아닌 요소 개수만큼 반복
		cout.width(11); cout << col_index[i]; // 11칸 공백 출력하면서 우측 정렬하여, 열 라인에 행 값들을 출력
		cout.width(9); cout << row_index[i]; // 9칸 공백 출력하면서 우측 정렬하여, 행 라인에 열 값들을 출력
		cout.width(9); cout << element_result[i] << endl; // 9칸 공백 출력하면서 우측 정렬하여, 값 라인에 요소들을 출력하고 줄넘김
		result_arr[row_index[i]][col_index[i]] = element_result[i]; // result_arr(결과 배열(전치형))의 인덱스의 행에 열 좌표, 열에 행 좌표를 입력, 요소 값을 대입
	}
	cout << "====================================" << endl << endl << endl << endl; // 출력 후 줄 넘기고 3줄 띄움
}


// three_element_transpose 함수에서 얻은 결과 전치형 배열[8][15]을 출력하는 함수
void transpose_remake(int result_arr[][col]) {
	cout << "\t   『 전치행렬(matrix transpose) 행렬 』" << endl; // 출력 후 줄넘김
	cout << "============================================================" << endl; // 출력 후 줄넘김
	for (int i = 0; i < row; i++) { // row 열 만큼 반복
		for (int j = 0; j < col; j++) { // col 행 만큼 반복
			cout.width(3); cout << result_arr[i][j] << " "; // 3칸 공백 띄우고 우측 정렬 후 최종 배열(전치형)의 요소들을 출력하고 요소들끼리 겹치지 않게 공백을 출력
		}
		cout << endl; // 빈 공백 출력 후 다음줄 넘김
	}
	cout << "============================================================" << endl << endl << endl << endl; // 출력 후 줄 넘기고 3줄 띄움
}


// main함수에서 col_index(행 위치), row_index(열 위치), element_result(요소 값) 배열들을 선언하고 동적할당하며, 다른 함수들을 호출하는 함수
int main() {
	int matrix[col][row] = { 0 }, result_arr[row][col] = { 0 }; // 2차원 int형 배열 matrix[15][8] 일반형 선언, 2차원 int형 배열 result_arr[8][15] 결과(전치형) 선언 및 모든 요소를 0으로 초기화
	cout << "===== [ 자료구조 1차 레포트 3번 전치행렬 문제 ] =====" << endl; // 출력
	cout << "학과     : 컴퓨터 공학과" << endl; // 출력
	cout << "담당 교수: 김진일 교수님" << endl; // 출력
	cout << "학번     : 20192471" << endl; // 출력
	cout << "이름     : 조민석" << endl; // 출력
	cout << "제출일   : 2022.10.05(수)" << endl << endl; // 출력
	input(matrix); // input함수 호출 및 인자로 일반형 2차원 배열 matrix[15][8]을 대입
	int* col_index = new int[::count]; // col_index 이름의 포인터를 선언후, 동적 할당으로 전역변수 count 만큼의 배열 선언 (행 좌표)
	int* row_index = new int[::count]; // row_index 이름의 포인터를 선언후, 동적 할당으로 전역변수 count 만큼의 배열 선언 (열 좌표)
	int* element_result = new int[::count]; // col_index 이름의 포인터를 선언후, 동적 할당으로 전역변수 count 만큼의 배열 선언 (요소 값)
	three_element(matrix, col_index, row_index, element_result); // three_element 함수 호출 및 인자로 일반형 2차원 배열 matrix[15][8] 대입, 위에서 선언한 배열 3가지들을 대입
	remake(col_index, row_index, element_result); // remake 함수 호출 및 인자로 행 좌표 배열, 열 좌표 배열, 요소 배열을 대입
	three_element_transpose(result_arr, col_index, row_index, element_result); // three_element_transpose 함수 호출 및 인자로 전치형 결과 배열, 행 좌표 배열, 열 좌표 배열, 요소 배열을 대입
	transpose_remake(result_arr); // transpose_remake 함수 호출 및 전치형 결과 배열을 입력
}

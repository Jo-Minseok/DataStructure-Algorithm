/*
코드 작성 완료일: 2022.10.03/4:45(A.M.)
학교            : 동의대학교 (Dong-Eui University)
코드 작성자     : 조민석
학번            : 20192471(2)
교과목          : 자료구조
교과목 담당 교수: 김진일 교수님
제출일          : 2022.10.05(수)

문제: 스택을 사용하여 infix로 표기된 연산식을 prefix와 postfix로 고치시오.
여기서 postfix 결과는 스택을 사용하여 연산하고 그 결과치를 출력하는 과정을 보이시오.
즉, 수식을 트리형식으로 그리고, 이를 순회(ordering)하여 표기(2가지)하고, postfix 표기로부터 연산 과정을 보이시오.
(단, 연산자는 +, -, *, / 로 한정하며, 아래의 연산식 1, 2를 적용해 보일 것)
    (예) (연산식 1) 8+4*3-6/2+3        (연산식 2)   24*10+3-(5-2)
                                                    (10+12)*3-36/6

[사용 함수 및 기능]
class Stack = 스택 기능들이 구현되어 있는 클래스
check_bracket = 괄호 검사 함수
oper_compare = 연산자 우선순위 비교 함수
infix_to_postfix = 중위식 표현을 후위식 표현으로 바꿔주는 함수 + 공백 포함
remove_space = 공백 포함된 후위식을 출력에서 공백을 지워주기 위해 공백을 지우는 함수
one_remove_space = 공백 포함된 후위식을 2자리 이상 연산을 하기 위해 연속된 공백을 지우고, 공백을 1칸씩 나두는 함수
calc_postfix = infix_to_postfix 함수에서 만들어진 후위식을 스택을 통해 연산하는 함수
*/

#include <iostream> // 표준 입출력 인클루드
#include <string> // string에서 stoi 함수를 사용하기 위해 인클루드
#define STACK_SIZE 100 // 스택의 최대 크기 설정

using namespace std; // 네임 스페이스(이름공간) std 공간 사용

// 템플릿 클래스 Stack
template<typename T> // 스택의 자료형이 숫자를 저장하는 스택, 연산자를 저장하는 스택 2가지로 char, int형으로 사용되어야 하기 때문에 템플릿 형성
class Stack { // 스택 클래스
    string postfix; // 후위연산식 문자열을 private 접근형으로 선언
    T array[STACK_SIZE] = { 0 }; // 자료형을 템플릿에 맞게 설정. (연산자, 숫자 올 수도 있기 때문, 스택 사이즈를 100, 원소를 0으로 초기화)
    int top; // 스택의 top을 선언, private형으로 선언
public: // public 접근형
    Stack() { // 생성자를 통해서 스택을 초기화
        top = -1; // top이 -1일 경우, 스택이 비었음.
    }

    void init() { // 스택을 초기화 해주는 함수
        top = -1; // top이 -1일 경우, 스택이 비었음.
    }

    void push(T element) { // 스택에 원소를 푸시(추가)해주는 함수, 연산자 or 숫자가 와야하기 때문에, 자료형을 템플릿화 시킴
        if (is_full() == true) { // is_full 함수로 스택이 꽉 찼을 경우 true를 반환함. top == STACK_SIZE-1
            cout << "스택이 가득 찬 상태라서 push 함수를 실행할 수 없습니다." << endl; // 문자열 출력
        }
        else { // 스택이 꽉 안찼을 경우
            array[++top] = element; // 배열의 top의 다음 값에 element(요소)를 저장
        }
    }

    T pop() { // 스택에 원소를 팝(제거)하는 함수, 연산자 or 숫자가 반환되어야 하기 때문에, 자료형을 템플릿화 시킴
        if (is_empty() == true) { // is_empty 함수로 스택이 비었을 경우, true를 반환함 top == -1
            cout << "스택이 빈 상태라 pop 함수를 실행할 수 없습니다." << endl; // 문자열 출력
        }
        else { // 스택이 안비었을 경우
            return array[top--]; // 스택의 요소를 반환하면서, top을 1 감소 시킴으로써, 배열 하나를 없앰. [실질적으로 없어지진 않음]
        }
    }

    T peek() { // 스택의 top에 존재하는 요소를 반환하는 함수로, pop과 다르게 top이 줄어들지 않아서, 배열이 줄어들지 않음. 확인용 함수
        if (is_empty() == true) { // is_empty 함수로 스택이 비었을 경우, true를 반환함 top == -1
            cout << "스택이 빈 상태라 peek 함수를 실행할 수 없습니다." << endl; // 문자열 출력
        }
        else { // 스택이 안비었을 경우
            return array[top]; // 스택의 요소를 반환하면서, top을 1 감소 시킴으로써, 배열 하나를 없앰. [실질적으로 없어지진 않음]
        }
    }

    bool is_empty() { // 스택이 비었는지 확인하는 함수, true or false 반환
        if (top == -1) { // top이 -1일 경우, 스택이 비었다고 판단
            return true; // 비었기 때문에 true 반환
        }
        else { // 위의 조건이 아닐 경우
            return false; // 비었지 않기 때문에 false 반환
        }
    }

    bool is_full() { // 스택이 가득 찼는지 확인하는 함수, true or false 반환
        if (top == STACK_SIZE - 1) { // top이 STACK_SIZE-1(배열은 0부터 시작) 일 경우, 스택이 가득 찾다고 판단
            return true; // 가득찼기 때문에 true 반환
        }
        else { // 위의 조건이 아닐 경우
            return false; // 가득 안찼기 때문에 false 반환
        }
    }
};

// 연산식의 괄호들이 제대로 존재하는지, 짝이 맞는지 확인하는 함수
int check_bracket(string mathmetic) { // 반환형은 에러코드인 1~3 반환, 0일 경우: 정상, 입력값: main에서 입력된 연산식
    Stack<char> splash; // Stack 템플릿 클래스 char형 괄호 스택 객체 splash를 선언
    char prev_splash; // char형 prev_splash로, 가장 최근에 존재하는 괄호를 저장하는 변수
    for (int i = 0; mathmetic[i] != '\0'; i++) { // 연산식의 i번째 인덱스 값이 \0이 아닐 경우 반복
        switch (mathmetic[i]) { // 스위치문에 연산식의 i번째 인덱스 값을 대입
        case'[': case '{': case'(': // 요소에 맞을 경우
            splash.push(mathmetic[i]); // splash 괄호 스택에 푸시(추가)
            break; // 이후 구문 실행하지 않게 스위치문을 나감.
        case ']': case'}': case')': // 요소에 맞을 경우
            if (splash.is_empty()) { // splash 괄호 스택이 비었는지 확인. 비었을 경우 실행
                cout << endl << endl << "조건 2번에 위반됩니다.(가장 가깝게 연 괄호와 맞지 않습니다.)" << endl << endl << endl; // 문자열 출력
                return 2; // 에러코드 2 반환 닫는게 여는 개수와 맞지 않을때
            }
            prev_splash = splash.pop(); // prev_splash에 splash의 스택의 팝 값을 저장
            if (mathmetic[i] == ']' && prev_splash != '[' || (mathmetic[i] == '}' && prev_splash != '{') || (mathmetic[i] == ')' && prev_splash != '(')) { // 만약, 연산식의 i번째 인덱스 값과 prev_splash(최근 괄호 스택의 값)이 아닐 경우, 조건에 부합할 경우
                cout << endl << endl << "조건 3번에 위반됩니다.(괄호의 짝이 맞지 않습니다.)" << endl << endl << endl; // 문자열 출력
                return 3; // 에러코드 3 반환 괄호의 종류가 서로 다를때
            }
        }
    }
    if (splash.is_empty() == false) { // 위에서 짝이 다 맞았는데, 스택에 남았을 경우
        cout << endl << endl << "조건 1번에 위반됩니다.(괄호의 개수가 맞지 않습니다.)" << endl << endl << endl; // 문자열 출력
        return 1; // 에러코드 1 반환 연 괄호가 더 많을때
    }
    return 0; // 정상일 경우 에러코드 0 반환
}

// 연산자 우선순위 비교 함수
int oper_compare(char oper) { // 연산자를 char형으로 입력 받고
    switch (oper) { // switch문에서 적절한 값을 찾음.
    case '+': case '-': // +,-일 경우 1
        return 1; // 우선순위 1 반환
        break; // 스위치문 break; 문으로 나가기
    case '*':case '/': // *,/일 경우 2
        return 2; // 우선순위 2 반환
        break; // 스위치문 break; 문으로 나가기
    case '(': case ')': case '{': case '}': case '[': case ']': // 괄호들일 경우 0 괄호는 무조껀 넣어야하고, 스택에서는 +보다 *가 나중에 들어가므로, *가 우선순위가 낮음.
        return 0; // 우선순위 0 반환
        break; // 스위치문 break; 문으로 나가기
    }
}

// 중위식을 후위식으로 바꿔주는 함수
string infix_to_postfix(string mathmetic) { // main에서 입력 받은 중위 연산식 
    Stack<char> oper; // Stack클래스 템플릿을 이용하여 char형 연산자 스택 객체 oper 생성
    string postfix; // 후위 연산식 문자열 생성(반환값)
    char tmp = 0; // 임시로 연산자를 저장하고 있을 문자형 변수 tmp 선언 및 0으로 초기화
    oper.init(); // 연산자 스택 초기화
    for (int i = 0; i < mathmetic.length(); i++) { // 입력 받은 중위 연산식의 길이만큼 반복
        if (mathmetic[i] >= '0' && mathmetic[i] <= '9') { // 중위 연산식의 i번째 요소가 숫자이면
            postfix += mathmetic[i]; // 후위 연산식에 추가
        }
        else { // 숫자가 아닐 경우
            postfix += ' '; // 숫자가 아니기 때문에, 이후에 2자리 이상 연산을 하기 위해서 구분자 공백을 포함
            if (mathmetic[i] == '+' || mathmetic[i] == '-' || mathmetic[i] == '*' || mathmetic[i] == '/') { // 만약 사칙연산자라면
                while (oper.is_empty() == false && oper_compare(mathmetic[i]) <= oper_compare(oper.peek())) { // 스택이 비었는지 확인하여, 비었지 않았을 경우, 중위 연산식의 i번째 요소의 연산자가 스택의 top에 존재하는 연산자보다 우선순위가 높을 경우
                    postfix += oper.pop(); // 스택에 pop을 하여 후위 연산식에 문자열을 추가하고 스택에서 제거
                    postfix += ' '; // 연산자 뒤에서 피연산자가 존재하기 때문에, 공백을 추가
                }
                oper.push(mathmetic[i]); // 위에서 스택이 비었을 경우, 연산식의 i번째 요소를 푸시(추가)
            }

            else if (mathmetic[i] == '(' || mathmetic[i] == '{' || mathmetic[i] == '[') { // 만약 연산식의 i번째 요소가 괄호의 여는 것이라면
                oper.push(mathmetic[i]); // 비교를하지 않고 연산식을 푸시, 이유: main에서 이미 check를 하고 넘어왔기 때문에. 괄호의 우선순위는 신경쓰지 않음.
            }

            else if (mathmetic[i] == ')' || mathmetic[i] == '}' || mathmetic[i] == ']') { // 만약 연산식의 i번째 요소가 괄호의 닫는 것이라면
                tmp = oper.pop(); // 임시 연산자 저장 공간인 tmp에 연산자 스택의 제일 위에 있는 연산자를 저장.
                while (tmp != '(' && tmp != '{' && tmp != '[') { // 임시 연산자가 여는 괄호가 아닐 경우 반복
                    postfix += tmp; // 후위 연산식에 임시 연산자를 더해줌.
                    postfix += ' '; // 연산자 뒤에는 숫자가 올 수 있기 때문에, 공백을 줘서 나눠줌.
                    tmp = oper.pop(); // 임시 연산자 저장 공간인 tmp에 연산자 스택의 제일 위에 있는 연산자를 저장
                } // 여는 괄호를 만날때까지 반복
            }
        }
    }
    while (oper.is_empty() == false) { // 위의 반복문을 통해 연산자를 다 후위 연산식으로 보냈어도 스택에 남았을 경우
        postfix += oper.pop(); // 후위 연산식에 스택에 남아있는 연산자들을 전부 저장
        postfix += ' '; // 연산자들 사이에 공백 추가
    }
    return postfix; // 후위 연산식 반환
}

// 출력에서 후위식의 공백들이 없는 상태로 출력되기 위해 만들어주는 함수
string remove_space(string postfix) { // 반환형은 후위식에서 공백이 사라진 문자열을 반환, 입력에는 공백을 포함한 후위식을 입력
    for (int i = 0; i < postfix.length(); i++) { // 공백+후위식 길이 만큼 반복,
        if (postfix[i] == ' ') { // 공백+후위식에서 인덱스 값이 공백일 경우
            postfix[i] = '\0'; // 공백을 \0 빈칸으로 설정
        }
    }
    return postfix; // 공백이 지워진 문자열을 반환
}

// 공백을 한칸씩만 남기고 나머지 공백을 지우는 함수
string one_remove_space(string postfix) { // 반환형은 후위식에서 공백이 한칸씩만 남기고 사라진 문자열을 반환, 입력에는 공백을 포함한 후위식을 입력
    string result; // 공백을 한칸씩만 남긴 후위식 문자열 (반환값)
    int count = 1; // 공백이 연속으로 나올시 증가시킬 카운트 변수 1인 이유는, 제일 첫 칸이 공백일 수도 있기 때문에 설정.
    // 연속 공백 칸들을 빈칸으로 만들어주는 구간
    for (int i = 0; i < postfix.length(); i++) { // 공백+후위식의 길이만큼 반복
        if (postfix[i] == ' ' && count == 0) { // 만약 공백+후위식의 i번째 값이 공백이면서, 연속 카운트가 0이라면
            count++; // 연속 카운트 1 증가하여 다음 칸에 공백이 오는것을 거부
        }
        else if (postfix[i] == ' ' && count >= 1) { // 만약 공백+후위식의 i번째 값이 공백이면서, 연속 카운트가 1보다 크거나 같다면
            postfix[i] = '\0'; // 공백+후위식의 인덱스 값을 \0으로 변환하여 공백 다음 공백의 칸을 제거
            count++; // 연속 카운트 1 증가하여 다음 칸에도 공백이 오는 것을 거부
        }
        else if (postfix[i] != ' ') { // 만약 공백+후위식의 i번째 값이 공백이 아닐 경우,
            count = 0; // 연속 카운트를 0으로 설정해서, 공백이 오는것을 허용
        }
    }

    // 위에서 연속된 공백을 빈칸으로 만들고, 빈칸도 지워서 다시 문자열을 만드는 구간
    for (int i = 0; i < postfix.length(); i++) { // 공백+후위식의 길이만큼 반복
        if (postfix[i] == '\0') { // 만약 공백+후위식의 값이 \0일 경우,
            continue; // for문의 조건으로 다시 이동
        }
        else { // \0 = 연속 공백이 아닐 경우
            result += postfix[i]; // 공백을 한칸씩만 남긴 후위식 문자열에 저장
        }
    }
    return result; // 공백 한칸+후위식 문자열 반환
}

// 후위식 연산 함수
int calc_postfix(string postfix) { // 반환 : int(후위식 연산 결과값), 입력 : 후위식+공백 포함 
    int num1, num2; // 피연산자 2개 num1,num2 선언
    string tmp; // 문자열을 숫자로 바꿔주기 위해서 사용하는 임시 문자열
    Stack<int> num; // Stack 템플릿 클래스의 int형 피연산자 스택 객체 num 선언 (반환값)
    num.init(); // 스택 객체 num의 스택을 초기화하는 함수
    for (int index = 0; postfix[index] != '\0'; index++) { // 후위식의 문자열을 반복하는데, 문자가 '\0'(문자열의 끝)이 아닐 경우 반복, 후위식의 인덱스 값으로 증가 반복을 함.
        if (postfix[index] >= '0' && postfix[index] <= '9') { // 후위식의 문자열중 인덱스 값에 맞는 문자가 숫자일 경우, 
            tmp += postfix[index]; // 임시 문자열에 문자를 추가 ex) 12 = 1+2 처리
            if (!(postfix[index + 1] >= '0' && postfix[index + 1] <= '9')) { // 문자의 다음 문자가 숫자가 아닐 경우, 숫자가 끝나기에
                num.push(stoi(tmp)); // 숫자 스택에 stoi(문자열을 숫자로 바꾸는 함수 string 헤더파일에 포함)에 임시 문자열 tmp를 입력하여, 숫자 스택에 푸쉬하여 추가
                tmp = ""; // tmp를 초기화
            }
        }
        else if (postfix[index] == '+' || postfix[index] == '-' || postfix[index] == '*' || postfix[index] == '/') { // 만약, 문자열의 인덱스 값이 사칙연산일 경우
            switch (postfix[index]) { // 스위치문에 문자열의 인덱스 값을 넣고
            case '+': // +일 경우
                tmp = ""; // tmp를 초기화
                num1 = num.pop(); // num1(피연산자)에 num 스택의 팝을 통해서, 숫자를 전달
                num2 = num.pop(); // num2(피연산자)에 num 스택의 팝을 통해서, 숫자를 전달
                num.push(num2 + num1); // 피연산자 두개를 연산하여 num 스택에 푸시
                break; // 이후 case 구문을 실행하지 않기 위한 스위치 문을 나가는 break;
            case '-': // -일 경우
                tmp = ""; // tmp를 초기화
                num1 = num.pop(); // num1(피연산자)에 num 스택의 팝을 통해서, 숫자를 전달
                num2 = num.pop(); // num2(피연산자)에 num 스택의 팝을 통해서, 숫자를 전달
                num.push(num2 - num1); // 피연산자 두개를 연산하여 num 스택에 푸시
                break; // 이후 case 구문을 실행하지 않기 위한 스위치 문을 나가는 break;
            case '*': // *일 경우
                tmp = ""; // tmp를 초기화
                num1 = num.pop(); // num1(피연산자)에 num 스택의 팝을 통해서, 숫자를 전달
                num2 = num.pop(); // num2(피연산자)에 num 스택의 팝을 통해서, 숫자를 전달
                num.push(num2 * num1); // 피연산자 두개를 연산하여 num 스택에 푸시
                break; // 이후 case 구문을 실행하지 않기 위한 스위치 문을 나가는 break;
            case '/': // /일 경우
                tmp = ""; // tmp를 초기화
                num1 = num.pop(); // num1(피연산자)에 num 스택의 팝을 통해서, 숫자를 전달
                num2 = num.pop(); // num2(피연산자)에 num 스택의 팝을 통해서, 숫자를 전달
                num.push(num2 / num1); // 이후에 받은 피연산자가 먼저 들어간 피연산자기 때문에, 나중에 나온 수 / 먼저 나온 수 연산을 함. 
                break; // 이후 case 구문을 실행하지 않기 위한 스위치 문을 나가는 break;
            }
        }
    }
    return num.pop(); // 스택에 저장된 수(결과물)을 팝 하여 리턴.
}

// 메인 함수
int main() {
    string mathmetic; // 입력 받을 연산식
    string postfix; // 후위 연산식
    cout << "===== [자료구조 1차 레포트 4번 Infix to Postfix 문제] =====" << endl; // 문자열 출력 후 줄 바꿈
    cout << "학과 \t\t: 컴퓨터 공학과" << endl; // 문자열 출력 후 줄 바꿈
    cout << "담당 교수\t: 김진일 교수님" << endl; // 문자열 출력 후 줄 바꿈
    cout << "학번 \t\t: 20192471" << endl; // 문자열 출력 후 줄 바꿈
    cout << "이름 \t\t: 조민석" << endl; // 문자열 출력 후 줄 바꿈
    cout << "제출일 \t\t: 2022.10.05(수)" << endl << endl; // 문자열 출력 후 줄 바꿈x2
    cout << "코드 작성 완료일: 2022.10.03/04:45(A.M.)" << endl << endl << endl; // 문자열 출력 후 줄 바꿈x3
    while (true) { // 무한 반복문 실행
        cout << "========== [ Infix to Postfix ] ==========" << endl; // 문자열 출력 후 줄 바꿈
        cout << "※프로그램 종료시 \"end\" 입력" << endl << endl; // 문자열 출력 후 줄 바꿈x2
        cout << "중위 연산식 입력 : "; // 문자열 출력
        cin >> mathmetic; //연산식 입력
        if (mathmetic == "end") { // 연산식이 end 라면
            cout << "프로그램을 종료합니다."; // 문자열 출력
            return 0; // main함수 0 반환 및 프로그램 종료
        }
        if (check_bracket(mathmetic) > 0) { // 연산식이 0이 아닐경우, 식에 괄호가 제대로 구성되어 있는지를 확인함. (에러코드 1~3)
            continue; // 에러코드 1~3 값을 리턴 받았을때, 1~3이 아닐 경우, 정상으로 인식, 1~3일 경우, 다시 while문의 조건 true로 이동
        }
        postfix = infix_to_postfix(mathmetic); // 중위식에서 후위식으로 바꿔주는 함수로, 연산식 mathmetic 을 함수 인자에 대입 반환값은 후위식 + 공백
        cout << endl << endl << "Postfix 식 : " << remove_space(postfix) << endl << endl << endl; // 2줄 공백 후 문자열 출력, remove_space 함수를 통해서, 공백 포함된 후위식의 공백들을 제거, 줄 바꿈 x3
        cout << "Postfix 연산 결과: " << calc_postfix(one_remove_space(postfix)) << endl << endl << endl; // 문자열 출력, one_remove_space 함수를 통해서, 공백 포함된 후위식의 공백들을 1칸씩만 남기고 제거, 제거된 후 반환된 문자열을 calc_postfix 함수에 대입하여 후위식 연산 후 출력, 줄 바꿈x3
    }
}
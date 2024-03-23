# 고급 알고리즘<br>

1. 도형 문제
2. 계차와 누적합
3. 미분 (뉴턴법)
4. 에라토스네스의 체
5. 그래프 알고리즘
6. 나머지 계산
7. 행렬의 거듭제곱

## 도형 문제

### 계산기하학이란?
기하학적인 문제를 컴퓨터로 풀기 위해 효율적인 알고리즘을 연구하는 학문

### 벡터란?
크기와 방향을 가진 힘. 크기와 방향이 같다면 시작점이 달라도 같은 벡터<br>
계산기하학을 풀기위해 알아야 하는 벡터의 기본개념은 다음과 같다.

벡터의 덧셈과 뻴셈
<br>
$\overrightarrow{a}+\overrightarrow{b}=(a_x+b_x,a_y+b_y)$<br>
$\overrightarrow{a}-\overrightarrow{b}=(a_x-b_x,a_y-b_y)$
<br>
벡터의 크기
<br>
$|\overrightarrow{a}|=\sqrt{(a_x)^2+(a_y)^2}$
<br>
벡터의 내적
<br>
$\overrightarrow{a}\cdot\overrightarrow{b}=a_xb_x+a_yb_y$<br>
내적의 세 가지 성질
```
두 벡터가 이루는 각이 90도 미만 - 내적은 양수
두 벡터가 이루는 각이 90도     - 내적은 0
두 벡터가 이루는 각이 90도 초과 - 내적은 음수
```
<br>
벡터의 외적
<br>

$|\overrightarrow{a} \times \overrightarrow{b}|=|a_xb_y-a_yb_x|$<br>
외적의 두가지 성질
1. 외적의 크기는 두 벡터가 만드는 평행사변형의 면젹과 같다.
2. 외적의 식에서 절댓값을 제외한다고 생각하면
   <br>ex) 
   $\overrightarrow{BA}\times\overrightarrow{BC}$<br>
   점 A,B,C가 시계방향으로 배치되어 있다면   - 양수<br>
   점 A,B,C가 반시계방향으로 배치되어 있다면 - 음수<br>
   점 A,B,C가 일직선으로 배치되어 있다면     - 0
<br>

### 예제 : 점과 선분의 거리
이 문제를 풀기 위해서는 3가지 패턴이 나온다는 것을 알아야 합니다.
1. 각 ABC가 90도 초과 
2. 각 ACB가 90도 초과
3. 각 ABC와 ACB가 90도 이하 

1번과 2번의 경우는 고민할것도 없이 A와 B사이의 거리, A와 C사이의 거리가 최단 경로일 것입니다.<br>
하지만 3번의 경우는 선분 $\overline{BC}$와 수직을 이루는 지점이 최단경로일 것입니다.<br><br>
이를 구하기 위한 공식은 다음과 같습니다.
1. 벡터 $\overrightarrow{BA}$와 $\overrightarrow{BC}$의 외적을 구합니다.(평행 사변형의 면적을 구하기 위해)
2. 평행사변형 면적을 구하는 공식은 $밑변\times높이$임으로 구한 외적에 밑변인 $\overline{BC}$를 나누어 높이를 구합니다.

이를 구현한 코드는 다음과 같습니다.
```cpp
#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

int main()
{
    int arr[2][3];
    int pattern=2;
    int vecter[2][4];
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<2; j++)
        {
            cin>>arr[j][i];
        }
    }
   
    vecter[0][0]=arr[0][0]-arr[0][1];
    vecter[1][0]=arr[1][0]-arr[1][1];

    vecter[0][1]=arr[0][2]-arr[0][1];
    vecter[1][1]=arr[1][2]-arr[1][1];

    vecter[0][2]=arr[0][0]-arr[0][2];
    vecter[1][2]=arr[1][0]-arr[1][2];
    
    vecter[0][3]=arr[0][1]-arr[0][2];
    vecter[1][3]=arr[1][1]-arr[1][2];

    if(vecter[0][0]*vecter[0][1]+vecter[1][0]*vecter[1][1]<0)
        pattern=1;
    else if(vecter[0][2]*vecter[0][3]+vecter[1][2]*vecter[1][3]<0)
        pattern=3;

    if(pattern==1)
        cout<<setprecision(13)<<sqrt(pow(vecter[0][0],2)+pow(vecter[1][0],2));
    else if(pattern==2)
    {
       cout<<setprecision(13)<<abs(vecter[0][0]*vecter[1][1]-vecter[1][0]*vecter[0][1])/sqrt(pow(vecter[0][1],2)+pow(vecter[1][1],2));
    }
    else if(pattern==3)
        cout<<setprecision(13)<<sqrt(pow(vecter[0][2],2)+pow(vecter[1][2],2));
    return 0;
}
```
arr 배열에 입력된 값은 책 기준 다음과 같습니다.

| |0(x)|1(y)|
|-|-|-|
|a|0|5|
|b|1|1|
|c|3|0|

<br><br>
vecter 배열에 입력된 값은 책 기준 다음과 같습니다.

| |0(x)|1(y)|
|-|-|-|
|BA|-1|4|
|BC|2|-1|
|CA|-3|5|
|CB|-2|1|

<br><br>
pattern은 다음과 같음을 나타냅니다

1. ABC의 각이 90가 초과했을시($\overrightarrow{BA}\cdot\overrightarrow{BC}<0$)
2. 패턴 1, 3 둘다 아닐시
3. ACB의 각이 90가 초과했을시($\overrightarrow{CA}\cdot\overrightarrow{CB}<0$)
<br><br>

### #include<iomanip>
입출력 조작과 관련된 도구를 제공하는 헤더파일<br>
setprecision()을 사용하기 위해 사용하였고, 해당 메서드는 출력할 소수점의 몇번째 자리까지 출력할지 결정하는 메서드


이 외의 계산기하학문제는
1. 가장 가까운 점 찾기
2. 볼록 다각형 만들기
3. 보로노이 다이어그램
4. 미술관 문제등이 있습니다.


## 계차와 누적합
### 계차란?
n+1번 항과 n번 항의 차
### 누적합
1번항 부터 n번 항까지의 합

ex) 
|1|2|4|8|16|
|-|-|-|-|-|
|1|2|3|4|5|

의 계차는

|1|1|3|4|8|
|-|-|-|-|-|
|0-1|2-1|3-2|4-3|5-4|

### 예제1 : 입장 인원 계산하기
이 문제는 누접합을 이용하여 푸는 문제입니다.<br>
2번 줄에 기록된 배열의 누접합을 구하고, n부터 m까지 구한다고 가정했을시<br>
누접합 배열의 $m의 값-(n-1)의 값$을 구한다면 O(NQ)가 아닌 O(N+Q)의 시간복잡도로 이 문제를 풀 수 있습니다.

```cpp
#include<iostream>
#include<vector>

using namespace std;
int main()
{
    int N,Q,X,Y;
    cin>>N>>Q;
    vector<int> sum;
    cin>>X;
    sum.push_back(X);
    for(int i=1; i<N; i++)
    {
        cin>>X;
        sum.push_back(X+sum[i-1]);
    }
    vector<pair<int,int>> input;
    for(int i=0; i<Q; i++)
    {
        cin>>X>>Y;
        input.push_back(make_pair(X-1,Y-1));
    }
    for(int i=0; i<Q; i++)
    {
        if(input[i].first==0)
        {
            cout<<sum[input[i].second]<<endl;
        }
        else
        {
            cout<<sum[input[i].second]-sum[input[i].first-1]<<endl;
        }
    }
    return 0;
}
```

### 예제2 : 눈 시뮬레이션
이 문제는 계차를 이용하여 푸는 문제입니다.<br>
n일 부터 m일까지 k만큼의 눈이 내렸다면 계차 배열에는 n번 항에 k를 더하고 m-1항에 k를 빼주면 됩니다. 이렇게 모두 기록하고 난 후 1번부터 m번까지가(0번 제외) 구하고자한 값이고 비교 연산자를 사용해 출력만 해주면 됩니다.<br>
이 역시 시간 복잡도는 O(N+Q)입니다. 

```cpp
#include<iostream>
#include<vector>

using namespace std;
int main()
{
    int N,Q,X,Y,Z;
    cin>>N>>Q;
    vector<int> sum(N+2);
    for(int i=0; i<Q; i++)
    {
        cin>>X>>Y>>Z;
        sum[X]+=Z;
        sum[Y+1]-=Z;
    }
    for(int i=2; i<N+1; i++)
    {
        if(sum[i]>0)
        {
            cout<<"<";
        }
        else if(sum[i]==0)
        {
            cout<<"=";
        }
        else if(sum[i]<0)
        {
            cout<<">";
        }
    }
    return 0;
}
```


## 미분
### 미분이란?
특정 점에서 함수의 기울기 같은것을 구하는 것<br><br>
$기울기=\frac{y 증가량}{x 증가량}$<br><br>

다항식에서의 미분 : 각 항마다 차수만큼을 곱하여 주고 차수를 1줄임

### 뉴턴법이란?
뉴턴-랩슨법(Newton-Raphson method)이라고도 불리며, 폐구간 [a,b]에서 실수R 에 대하여 정의된 f:[a,b]->R이 미분가능할 때 방정식 f(x) = 0 의 해를 근사적으로 찾을 때 유용하게 사용되는 방법이다.

1. 구하고자 하는 수와 가까운 초깃값과 함수와 그 함수에서 구하고자 하는 수가 나오는 y좌표 기준으로 그래프를 그립니다
2. 처음 구했던 초기값을 x에 대입하여 y값을 구합니다(이 숫자를 a라고 하겠음). 그 후 미분한 함수에도 초기값을 대입하여 숫자 하나를 구합니다(이 숫자를 b라고 하겠음).
3. $y=(b)x-a$ 의 직선과 맨 처음 구하고자 하는 숫자가 있는 y좌표의 그래프와 교차하는 교점의 x좌표를 초기값에 대입함
4. 2~3번 과정을 반복함, 반복할수록 일치하는 자릿수가 배수로 증가하게됨

구현
```cpp
#include<iostream>
#include<iomanip>

using namespace std;

int main()
{
    double a=2;//초기값임 교제와 동일
    int repeat=5;//반복 횟수 교제와 동일
    int f_x, f_y;
    for(int i=0; i<=repeat; i++)
    {
        cout <<setw(2)<<i<<"번 반복시 :"<< setprecision(27) << a << endl;
        
        double f_x = a * a + 2;
        double f_prime_x = 2 * a;
        
        a = f_x / f_prime_x;
    }
    return 0;
}
```
결과
```
 0번 반복시 :2
 1번 반복시 :1.5
 2번 반복시 :1.41666666666666674068153498
 3번 반복시 :1.4142156862745098866440685
 4번 반복시 :1.41421356237468986982719343
 5번 반복시 :1.41421356237309492343001693
```
$y=(2\times a)x-a^2$<br>
이 식에서 y가 2일때를 구함으로<br>
$2=(2\times a)x-a^2$<br>
$2+a^2=(2\times a)x$<br>
$(2+a^2)\div(2\times a)=x$<br>


이 외의 수치계산 문제는
1. 수치 미분과 수치 적분
2. 아주 큰 정수 계산 문제가 있음
   
## 에라토스네스의 체
### 에라토스네스의 체란?
1. 2부터 N까지의 정수를 기록한다
2. 표시가 없는 가장 작은수에 O표시를 하고 그 수의 배수에 X표시를 한다(소수는 1과 본인빼고는 약수가 없어야 하기 때문)
3. 2번 과정을 반복하여 N번까지 반복한다
4. O표시가 있는 것이 소수이다.

구현
```cpp
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int main()
{
    int N,limit;
    cin>>N;
    vector<bool> arr(N+1);
    fill(arr.begin(),arr.end(),true);
    
    limit=sqrt(N);
    for(int i=2; i<limit+1; i++)
    {
        if(arr[i]==true)
        {
            for(int j=i*i; j<N+1; j+=i)
            {
                arr[j]=false;
            }
        }
    }
    for(int i=2; i<N+1; i++)
    {
        if(arr[i]==true)
        {
            cout<<i<<", ";
        }
    }

    return 0;
}
```
limit가 $\sqrt{N}$인 이유<br>
N이 100이라고 가정했을시, 100의 루트인 10의 배수에 100이 있기에 그 이상의 값은 확인하지 않아도 되기 때문

### 적분이란>
어떤 함수로 만들어진 영역의 면적을 구하는 조작. y가 0이하의 값에 대해서는 양수가 아닌 음수임을 기억해야한다.

다항식의 적분의 경우 : 차수를 1 증가시키고 차수만큼 나누어 줌

$\frac{1}{x}$의 적분 : $\int\limits_a^b\frac{1}{x}dx=(\log_eb-\log_ea)$ (에라토스네스의 체의 시간복잡도를 구하는 데 사용됨)

역수의 합이 $\log$임을 증명하기 : 
<br>


## 그래프 알고리즘

## 나머지 계산

## 행렬의 거듭제곱
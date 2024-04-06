A, B, C, D, E라는 5명의 선수가 100미터 달리기에 참가했습니다. 순위를 알기 위해서, 다음과 같은 형식의 질문을 할 수 있습니다. 참고로 동시에 도착하는 경우는 없다고 가정합니다.<br><br>
- 3명의 선수를 선택하고, 그 중에서 누가 가장 먼저 들어왔는지 질문할 수 있습니다.
- 3명의 선수를 선택하고, 그 중에서 누가 중간에 들어왔는지 질문할 수 있습니다.
- 3명의 선수를 선택하고, 그 중에서 누가 마지막에 들어왔는지 질문할 수 있습니다.

이때 다음과 같은 질문에 답해 주세요.
1. 4번 이내의 질문으로는 모든 사람의 순위를 알 수 있는 방법이 없다는 것을 증명해 주세요.
2. 5번의 질문을 했을 때, 모든 사람의 순위를 맞히는 방법을 구성해 주세요.



1번 질문에 대해서는 5명의 순위의 경우의 수는 $5!$일 것입니다. 문제에서 4번 이내의 질문을 하여 얻을수 있는 경우의 수는 $3^4$입니다. 당연하게 $5!$(120)은 $3^4$(81)보다 크기에 4번의 질문만으로는 모든 사람의 순위를 알 수 없습니다.

2번 질문에 대해서는 경우의 수를 줄이기 위해 가장 빠른 선수든, 가장 느린 선수를 찾아서 경우의 수에서 제거 하겠습니다.<br> 선수가 5이기에 이것을 구하는 것은 쉽습니다. A,B,C의 선수중 가장 빠른/느린 선수를 구하고, 그 선수를 포함하여 D,E 중 가장 빠른/느린 선수를 구한다면, 2번의 질문으로 경우의 수를 %5!%에서 $4!$으로 줄일 수 있게 됩니다.<br>

$4!$의 경우의 수는 24가지이고, $3^3$의 경우의 수는 27가지이기에 모든 경우의 수에 대하여 질문이 가능하게 되어, 모든 선수의 순위에 대해 알 수 있게 됩니다.

코드 없이도 질문의 답을 제공하였지만, 이를 구현한 것은 다음과 같습니다.

![image](https://github.com/bloodmoon3929/Algorithm/assets/144004857/1c65b32f-df86-40b0-af44-3424f4dbfcb6)
![image](https://github.com/bloodmoon3929/Algorithm/assets/144004857/1a3019ba-f276-4d7c-bbd4-9055a4b16a27)
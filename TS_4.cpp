#include <string>
#include <vector>
#include <cmath>
using namespace std;

long long solution(long long orderAmount, long long taxFreeAmount, long long serviceFee) {
    // orderAmount : 주문금액
    // taxFreeAmount : 비과세금액
    // serviceFee : 봉사료
    long long answer = 0;


    if(orderAmount-serviceFee - taxFreeAmount == 1)
        answer = 0;
    else
        answer = (orderAmount - taxFreeAmount - serviceFee) / 11 ;

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);



    return 0;
}
#include <iostream>
using namespace std;

bool isValid(long long number);
int sumOfDoubleEvenPlace(long long number);
int getDigit(int number);
int sumOfOddPlace(long long number);
bool prefixMatched(long long number, int d);
int getSize(long long d);
long long getPrefix(long long number, int k);

int main() {
    
    long long cardNumber;

    cout << "Enter a credit card number as an integer: ";
    cin >> cardNumber;

    if (isValid(cardNumber))
        cout << cardNumber << " is valid" << endl;
    else
        cout << cardNumber << " is invalid" << endl;

    return 0;
}

bool isValid(long long number) {
    int size = getSize(number);
    if (size < 13 || size > 16)
        return false;

    if (!prefixMatched(number, 4) && !prefixMatched(number, 5) &&
        !prefixMatched(number, 37) && !prefixMatched(number, 6))
        return false;

    int total = sumOfDoubleEvenPlace(number) + sumOfOddPlace(number);
    return total % 10 == 0;
}

int sumOfDoubleEvenPlace(long long number) {
    int sum = 0;

    while (number > 0) {
        number /= 10;
        sum += getDigit(static_cast<int>(number % 10) * 2);
        number /= 10;
    }

    return sum;
}

int getDigit(int number) {
    return number / 10 + number % 10;
}

int sumOfOddPlace(long long number) {
    int sum = 0;

    while (number > 0) {
        sum += static_cast<int>(number % 10);
        number /= 100;
    }

    return sum;
}

bool prefixMatched(long long number, int d) {
    int size = getSize(static_cast<long long>(d));
    return getPrefix(number, size) == d;
}

int getSize(long long d) {
    int count = 0;

    while (d > 0) {
        d /= 10;
        count++;
    }

    return count;
}

long long getPrefix(long long number, int k) {
    int size = getSize(number);

    if (size <= k)
        return number;

    for (int i = 0; i < size - k; i++)
        number /= 10;

    return number;
}
//credit card
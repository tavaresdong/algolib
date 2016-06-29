#include "../Leetcode.h"

using namespace leetcode;

string BullsAndCows::getHint(string secret, string guess)
{
    int bulls = 0, cows = 0;
    map<char, int> digitCount;
    for (int i = 0; i < secret.size(); i++)
    {
        char s = secret[i], g = guess[i];
        if (s == g)
        {
            ++bulls;
        }
        else
        {
            if (digitCount[s] < 0)
            {
                cows += 1;
            }
            digitCount[s]++;

            if (digitCount[g] > 0)
            {
                cows += 1;
            }
            digitCount[g]--;
        }
    }
    return to_string(bulls) + "A" + to_string(cows) + "B";
}

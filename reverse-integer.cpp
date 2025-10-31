
// https://leetcode.com/problems/reverse-integer/description/
class Solution {
public:
    int reverse(int x) {
        char output[32];
        bool originalSign = std::signbit(x);
        memset(output, 0, sizeof(output));
        int i = 0;

        x = x > 0 ? -x : x;
        while (x != 0) {
            output[i] = -(x % 10);
            x = x / 10;
            i++;
        }
        
        int result = 0;
        int j = i - 1;
        i = 0;
        while (j >= 0) {
            int delta;

            /*
             * Dirty hack: if the 9th power of 10 is greater than 2
             * we cannot possibly keep going as we are certain to overflow
             * the allowed value of a singed integer
             */
            if (i == 9 && output[j] > 2)
                delta = INT_MAX;
            else    
                delta = output[j] * pow(10, i);
            if (result > INT_MAX - delta)
                return 0;
            result += delta;
            j--;
            i++;
        }
        return originalSign ? -result : result;
    }
};

// https://leetcode.com/problems/divide-two-integers/
// Not bit wise implementation
class Solution {
public:

    int divide(int dividend, int divisor) {

        if (dividend == divisor)
            return 1;

        bool negative = (std::signbit(dividend) || std::signbit(divisor)) && 
                            !(std::signbit(dividend) && std::signbit(divisor));
        bool originalSign = std::signbit(dividend);
        int q = 0;

        // Normalise to negative sign to make the matter simpler
        dividend = dividend > 0 ? -dividend : dividend;
        divisor = divisor > 0 ? -divisor : divisor;

        if (divisor < dividend)
            return 0;

        if (divisor == -1) {

            if (!negative && dividend == INT_MIN){
                dividend = dividend + 1;
            }    
            return negative ? dividend : -dividend;    
        }



        // Perform division
        while (true) {
            dividend = dividend - divisor;
            if (dividend > 0)
                break;
            q--;
        }
       

        if (negative) {
            return q;
        }

        if (q == INT_MIN) {
            q = q + 1;
        }
        return -q;
    }

    
};

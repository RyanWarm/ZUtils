class Solution {
public:
    int divide(int dividend, int divisor) {
        bool neg = (dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0);
        if( dividend < 0 ) dividend = 0 - dividend;
        if( divisor < 0 ) divisor = 0 - divisor;
        int result = 0;
        
        int tmp = 1;
        while( divisor < dividend ) {
            divisor <<= 1;
            tmp <<= 1;
        }
        while( dividend > 0 ) {
            result += tmp;
            dividend -= divisor;
            while( divisor > dividend ) {
                divisor >>= 1;
                tmp >>= 1;
            }
        }
        
        if( neg ) return 0 - result;
        else return result;
    }
};
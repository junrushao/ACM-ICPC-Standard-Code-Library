bool test(LL n, int base) {
	LL m = n - 1, ret = 0; int s = 0;
	for ( ; m % 2 == 0; ++s) m >>= 1; ret = pow_mod(base, m, n);
	if (ret == 1 || ret == n - 1) return true;
	for (--s; s >= 0; --s) {
		ret = multiply_mod(ret, ret, n); if (ret == n - 1) return true;
	} return false;
}
LL special[7] = {
	1373653LL,         25326001LL, 
	3215031751LL,      25000000000LL,
	2152302898747LL,   3474749660383LL, 341550071728321LL};
/*
 * n < 2047                         test[] = {2}
 * n < 1,373,653                    test[] = {2, 3}
 * n < 9,080,191                    test[] = {31, 73}
 * n < 25,326,001                   test[] = {2, 3, 5}
 * n < 4,759,123,141                test[] = {2, 7, 61}
 * n < 1,122,004,669,633            test[] = {2, 13, 23, 1662803}
 * n < 2,152,302,898,747            test[] = {2, 3, 5, 7, 11}
 * n < 3,474,749,660,383            test[] = {2, 3, 5, 7, 11, 13}
 * n < 341,550,071,728,321          test[] = {2, 3, 5, 7, 11, 13, 17}
 * n < 3,825,123,056,546,413,051    test[] = {2, 3, 5, 7, 11, 13, 17, 19, 23}
 */
bool is_prime(LL n) {
	if (n < 2) return false;
	if (n < 4) return true;
	if (!test(n, 2) || !test(n, 3)) return false;
	if (n < special[0]) return true;
	if (!test(n, 5)) return false;
	if (n < special[1]) return true;
	if (!test(n, 7)) return false;
	if (n == special[2]) return false;
	if (n < special[3]) return true;
	if (!test(n, 11)) return false;
	if (n < special[4]) return true;
	if (!test(n, 13)) return false;
	if (n < special[5]) return true;
	if (!test(n, 17)) return false;
	if (n < special[6]) return true;
	return test(n, 19) && test(n, 23) && test(n, 29) && test(n, 31) && test(n, 37);
}
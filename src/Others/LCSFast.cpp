ULL *a, *b, *s, c, d;
for (i = 0, a = appear[(int)B[k]], b = row[max(k - 1, 0)], s = X; i < bitSetLen; ++i)
	*s++ = *a++ | *b++;                     // `X = row[i - 1] or appear[ B[i] ]`
for (i = 0, a = dp, c = d = 0; i < bitSetLen; ++a, c = d, ++i)
	d = *a >> 63, *a = ~((*a << 1) + c);    // `row[i] = -((row[i] << 1) + 1)`
for (i = 0, a = dp, b = X, c = 0; i < bitSetLen; ++a, ++b, ++i)
	d = *b + c, c = (*a >= -d), *a += d;    // `row[i] += X`
for (i = 0, a = dp, b = X; i < bitSetLen; ++a, ++b, ++i)
	*a = (*a ^ *b) & *b;                    // `row[i] = X and (row[i] xor X)`

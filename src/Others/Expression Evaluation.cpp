inline int getLevel(char ch) {
	switch (ch) { case '+': case '-': return 0; case '*': return 1; } return -1;
}
int evaluate(char *&p, int level) {
	int res;
	if (level == 2) {
		if (*p == '(') ++p, res = evaluate(p, 0);
		else res = isdigit(*p) ? *p - '0' : value[*p - 'a'];
		++p; return res;
	} res = evaluate(p, level + 1);
	for (int next; *p && getLevel(*p) == level; ) {
		char op = *p++; next = evaluate(p, level + 1);
		switch (op) {
			case '+': res += next; break;
			case '-': res -= next; break;
			case '*': res *= next; break;
		}
	} return res;
}
int makeEvaluation(char *str) { char *p = str; return evaluate(p, 0); }
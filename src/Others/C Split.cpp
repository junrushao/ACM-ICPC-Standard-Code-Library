for (char *tok = strtok(ins, delimiters); tok; tok = strtok(NULL, delimiters))
	puts(tok); // '会破坏原字符串ins'
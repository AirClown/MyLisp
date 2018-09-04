#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static const int L = 2048;
static char input[L];
static char help[] = { "help" };
static char end[] = { "end" };

bool equalString(char *str1, char *str2) {
	if (strlen(str1) != strlen(str2)) {
		return false;
	}

	for (int i = 0; str1[i] != '\0'; i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}

	return true;
}

//计算
int Calculate(char fu,int re,int num) {
	switch (fu) {
	case '+':
		return re + num;
	case '*':
		return re * num;
	case '-':
		return re - num;
	case '/':
		return re / num;
	default:
		return 0;
	}
}

//字符串转整型
int StringToInt(char *str, int &length) {
	int num = 0;
	for (int i = 0; str[i] >= '0'&&str[i] <= '9'; length=i++) {
		num *= 10;
		num += str[i] - '0';
	}

	return num;
}

//语法解释
int AnalysisLanguage(char *str, int *length) {
	int index = 0;
	while (str[index] == ' ') {
		++index;
	}
	++index;
	while (str[index] == ' ') {
		++index;
	}

	char fu = str[index];
	int result = INT_MAX;
	while (str[++index]!='\0'&&str[index]!=')'){
		if (str[index] == ' ') {
			continue;
		}

		int l = 0;
		int num = 0;

		if (str[index] == '(') {
			num= AnalysisLanguage(str + index, &l);
		}
		else {
			num = StringToInt(str + index, l);
		}

		if (result == INT_MAX) {
			result = num;
		}
		else {
			result = Calculate(fu, result, num);
		}

		index += l;
	}

	if (length != NULL) {
		*length = index;
	}

	return result;
}

//语法检查
bool LanguageAnalysis(char *str,int *length) {
	int index = 0;
	while (str[index] == ' ') {
		++index;
	}

	if (str[index++] == '(') {
		while (str[index] == ' ') {
			++index;
		}

		if (str[index] == '*' || str[index] == '+' || str[index] == '-' || str[index] == '/') {
			while (str[++index] != '\0'&&str[index] != ')') {
				int l = 0;
				if (str[index] == '(') {
					if (!LanguageAnalysis(str + index, &l)) {
						return false;
					}
				}
				else {
					if ((str[index] >= '0'&&str[index] <= '9') || str[index] == ' ') {
						continue;
					}
					return false;
				}
				index += l;
			}

			if (length != NULL) {
				*length = index;
			}
			return true;
		}
	}
	return false;
}

int main(int argc, char** argv) {

	/* Print Version and Exit Information */
	puts("YuLisp Version 0.0.0.0.1");
	puts("input \"help\" to know how it works");
	puts("input \"end\" to exit\n");

	while (1) {
		fputs("YuLisp>",stdout);

		fgets(input,L,stdin);

		input[strlen(input) - 1] = '\0';

		if (LanguageAnalysis(input,NULL)) {
			printf("result=%d\n", AnalysisLanguage(input, NULL));
		}
		else {
			if (equalString(input,end)){
				break;
			}

			if (equalString(input, help)) {
				printf("this lisp only support calculate +,-,*,/ for example: \n\n");
			    printf("input:(+ 1 2), get 3\n");
				printf("input:(* 2 3), get 6\n");
				printf("input:(- 5 4 3), get -2\n");
				printf("input:(/ 8 2 4), get 1\n\n");
				printf("you can also use hybrid computation like:\n");
				printf("input:(+ 1 1 (* 1 2) (- 2 (/ 5 6))),get 6\n");
				continue;
			}
			printf("No command like \"%s\"\n", input);
		}
	}

	return 0;
}
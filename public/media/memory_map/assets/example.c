#include <stdio.h>

int g_init_1 = 99;
double g_non_init;

long const g_init_2 = 72;

void greet();
int add(int, int);

int main() {

	greet();
	add(3, 4);

	char const *str_ptr0 = "my_string_0";
	char const *str_ptr1 = "my_string_1";

	char const str_arr[] = "my_string_1";
}

void greet() { printf("Hello!\n"); }
int add(int a, int b) { return a + b; }

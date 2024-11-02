#include <std2/stdlib2.h>

int main() {
	File_t fil = open("example.c", "r");
	print((char*)fil->data);
	close(fil);
	return 0;
}

#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, char **argv) {
	const char *verbose[] = { "", "-v" };
	return CommandLineTestRunner::RunAllTests(2, verbose);
	//return CommandLineTestRunner::RunAllTests(argc, argv);
}

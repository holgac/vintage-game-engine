/*
 * THIS FILE IS AUTOGENERATED
 * MODIFY setup.py INSTEAD
*/
#include "vge.h"
void list_init();
void list_addremove();
void rbtree_init();
void rbtree_insert();
void rbtree_delete();
void rbtree_duplicate();
void matrix_identity();
void vector4_set_and_equals();
void vector4_consts();
void vector4_dot();

void expect(int result, char *errormsg)
{
	if(!result) {
		printf("%s\n", errormsg);
	}
}
void run_tests()
{
	struct vge_stopwatch sw;
	float time_elapsed;
	vge_stopwatch_reset(&sw);
	list_init();
	list_addremove();
	rbtree_init();
	rbtree_insert();
	rbtree_delete();
	rbtree_duplicate();
	matrix_identity();
	vector4_set_and_equals();
	vector4_consts();
	vector4_dot();
	time_elapsed = vge_stopwatch_elapsed(&sw);
	printf("Ran 10 tests in %2.3f\n", time_elapsed);
}
int main(int argc, char **argv)
{
	if(argc>1 && strcmp(argv[1], "test")==0) {
		run_tests();
	} else {
		printf("Running game_main()...\n");
		game_main(argc, argv);
	}
	return 0;
}

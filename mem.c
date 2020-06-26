#include"pmem.h"
#include"init.h"

void function_choice();
void get_ps_tree();

int main() {

    banner_init();

	function_choice();
	char flag, ch;
	scanf("%c", &flag);
    ch = getchar();

	while (flag != 'q')
	{
		switch (flag)
		{
		case '1':
			system("less /proc/meminfo");
			break;

		case '2':
			system("ps aux");
			break;

		case '3':
			get_ps_tree();
			break;

		case '4':
			system("clear");
            p_function_choice();
            system("clear");
            break;
            
		default:
			break;
		}

		function_choice();
        scanf("%c", &flag);
        ch = getchar();
		
	}
	
	return 0;
}

void function_choice() {
	printf("\n");
	printf("================================\n");
	printf("please chooce a function:\n");
	printf("1.system meminfo\n");
	printf("2.process info\n");
	printf("3.process tree\n");
	printf("4.scan memory\n");

	printf("type \'q\' to exit \n");
}

void get_ps_tree() {

	char *head = "pstree ";

    char dst[21] = {0};

    strcat(dst, head);

    char pid[6];
    int len = 0;

    char x = '0';

	printf("please input the pid:");
    scanf("%s", pid);
    getchar();
    
    strcat(dst, pid);

    // puts(dst);
    system(dst);
}
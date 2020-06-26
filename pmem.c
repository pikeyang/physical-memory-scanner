#include"pmem.h"

void p_function_choice() {
	// introduction();

    char flag;
    while (flag != 'q')
	{
		switch (flag)
		{
		case '1':
			read_p_mem();
			break;

		case '2':
			modify_p_mem();
			break;

		case '3':
			view_process_maps();
			break;

		case '4':
			access_mod_proc();
            break;

		default:
			break;
		}

        introduction();
		scanf("%c", &flag);
        getchar();
	}

    if (flag == 'q')
    {
        return;
    }
    
}

void introduction() {
    printf("\n");
	printf("================================\n");
	printf("please chooce a function:\n");
	printf("1.locate any physical address\n");
	printf("2.modify the contents of any physical address\n");
    printf("3.view process maps\n");
	printf("4.access and modify process's mem\n");

	printf("type \'q\' to back to previous \n");
}

void read_p_mem() {

    unsigned long addr;
    char str[20];
    printf("addr:");
    scanf("%s", str);
    getchar();

    addr = strtoul(str, 0, 0);

    unsigned char *start;
    unsigned char val;

    int fd = open("/dev/mem",O_RDWR|O_SYNC);
    if(fd < 0)
    {
        printf("Can't open /dev/mem\n");
        exit(0);
    }
    start = (unsigned char *) mmap(0, MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr &~ MAP_MASK);
    if(start == NULL)
    {
        printf("Can't mmap\n");
        exit(0);
    }
        // else
        //         printf("start=%x\n",start);

    int offset = addr % MAP_MASK;
    for(int i = 0; i < 20; i++)
    {
        int index = *(start + offset + i);
        printf("0x%lx :%c\n", (addr + i), index);
    }

    munmap(start, MAP_SIZE);
    close(fd);

    return;
}

void modify_p_mem() {

    unsigned long addr;
    char str[20];
    printf("addr:");
    scanf("%s", str);
    getchar();

    addr = strtoul(str, 0, 0);

    unsigned char *start;
    unsigned char val;

    int fd = open("/dev/mem",O_RDWR|O_SYNC);
    if(fd < 0)
    {
        printf("Can't open /dev/mem\n");
        exit(0);
    }
    start = (unsigned char *) mmap(0, MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr &~ MAP_MASK);
    if(start == NULL)
    {
        printf("Can't mmap\n");
        exit(0);
    }
    
    int len;
    char mod[20];
    printf("len:");
    scanf("%d", &len);
    getchar();
    printf("your str:");
    scanf("%s", mod);
    getchar();

    int offset = addr % MAP_MASK;
    memcpy(start+offset, mod, len);

    printf("modified:\n");
    for(int i = 0; i < 20; i++)
    {
        int index = *(start + offset + i);
        printf("0x%lx :%c\n", (addr + i), index);
    }

    munmap(start, MAP_SIZE);
    close(fd);
}

void view_process_maps() {


    char dst[21] = {0};

    char pid[6];
    int len = 0;

    char x = '0';

	printf("please input the pid:");
    scanf("%s", pid);
    getchar();
    
    sprintf(dst, "cat /proc/%s/maps", pid);

    // puts(dst);
    system(dst);
}

void access_mod_proc() {

    char pid[6];
    unsigned long addr;
    int len;
    char str[20];

    addr = strtoul(str, 0, 0);
    printf("pid addr len:");
    scanf("%s", pid);
    scanf("%s", str);
    scanf("%d", &len);
    getchar();

    addr = strtoul(str, 0, 0);

    char* proc_mem = malloc(50);
    sprintf(proc_mem, "/proc/%s/mem", pid);

    printf("opening %s, address is %ld\n", proc_mem, addr);
    int fd = open(proc_mem, O_RDWR);
    if (fd == -1) {
        printf("Could not open %s\n", proc_mem);
        exit(1);
    }

    char* buf = malloc(len);

    lseek(fd, addr, SEEK_SET);
    read (fd, buf , len     );

    printf("String at %ld in process %s is:\n", addr, pid);
    printf("  %s\n", buf);
    
    strncpy(buf, "hhhhhhhhhh", len);
    printf("\nNow, this string is modified\n");

    lseek(fd, addr, SEEK_SET);
    if (write (fd, buf , len) == -1) {
        printf("Error while writing\n");
        exit(1);
    }

    printf("modifed mem:\n");
    lseek(fd, addr, SEEK_SET);
    read (fd, buf , len     );
    printf("  %s\n", buf);

    free(buf);
    free(proc_mem);

    return;
}
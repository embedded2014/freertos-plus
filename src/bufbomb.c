#include "bufbomb.h"
#include "host.h"
#include "clib.h"

static unsigned int cursor = 0;
char content[512];

void send_byte(char ch);

static void bufbomb_init(void)
{
	int fd = host_action(SYS_OPEN, "exploit.bytes", 0);
	host_action(SYS_READ, fd, content, 512);
	cursor = 0;
}

static void put_hex(const char c)
{
	send_byte('0');
	send_byte('x');
	send_byte(((int)c / 16) + '0');
	send_byte(((int)c % 16) + '0');
}

static char *_gets(char *str)
{
	char c;
	char *buf = str;

	c = content[cursor++];
	*buf = '\0';

	fio_printf(1, "Your code: ");
	while(c != '\n') {
		*buf++ = c;
		put_hex(c);
		send_byte(' ');
		c = content[cursor++];
	}
	*buf = '\0';
	fio_printf(1, "\n\r");

	return str;
}

/*---- Level 1 ----*/
static int level1(void)
{
	int a = 0;
	char buf[20];

	_gets(buf);

	if(a == 0x58) {
		return 0;
	}

	return 1;
}
/*---- End of Level 1 ----*/

/*---- Level 2 ----*/
static void fizz(void)
{
	char buf[20];

	_gets(buf);

	return;
}

static int smoke(void) __attribute__((unused));
static int smoke(void)
{
	fio_printf(1, "Nice! You find the correct path.\n\r");

	return 0;
}

static int level2(void)
{
	fizz();

	fio_printf(1, "Should not reach here!!!\n\r");
	return 1;
}
/*---- End of Level 2 ----*/

/*---- Level 3 ----*/
int global_value = 0;

static void bang(void)
{
	char buf[20];

	_gets(buf);

	return;
}

static int level3(void)
{
	bang();

	if(global_value != 412) {
		return 1;
	}

	return 0;
}
/*---- End of Level 3 ----*/

void bufbomb(void)
{
	bufbomb_init();

	if(level1()) {
		fio_printf(1, "Fail, try again!\n\r");
		return;
	}
	fio_printf(1, "You pass level1!\n\r");

	if(level2()) {
		fio_printf(1, "Fail, try again!\n\r");
		return;
	}
	fio_printf(1, "You pass level2!\n\r");

	if(level3()) {
		fio_printf(1, "Fail, try again!\n\r");
		return;
	}
	fio_printf(1, "You pass level3!\n\r");

	fio_printf(1, "Congratulation! You finish this job!\n\r");
	return;
}

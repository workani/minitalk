#include "../include/minitalk.h"

//void print_binary(unsigned char octet)
//{
//	int i = 8;
//	unsigned char mask = 128;

//	while(i--)
//	{
//		if(octet & mask)
//			printf("1");
//		else
//			printf("0");
//		mask = mask >> 1;
//	}
//	printf("\n");
//}
void signal_handler(int sig)
{
	static int count = 0;
	static unsigned char buffer = 0;

	if (sig == SIGUSR1)
		buffer |= (128 >> count);

	count++;

	if (count == 8)
	{
		write(1, &buffer, 1);
		count = 0;
		buffer = 0;
	}
}

int main(void)
{
	struct sigaction sa;

	sa.sa_handler = &signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}


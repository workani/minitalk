#include "../include/minitalk.h"

int PID;
int i = 0;
char *str;

void send_signal(int sig)
{
	kill(PID, sig);
	usleep(1000);
}

void send_byte(unsigned char octet)
{
	int i;
	unsigned char mask;

	i = 8;
	mask = 128;
	while (i--)
	{
		if (octet & mask)
			send_signal(SIGUSR1);
		else
			send_signal(SIGUSR2);
		mask = mask >> 1;
	}
}

void send_str(char *str)
{
	size_t i;
	size_t str_len;

	i = 0;
	str_len = ft_strlen(str);
	while(str[i])
	{
		send_byte(str[i]);
		i++;
		pause();
		puts("I'm here!");
	}
	send_byte('\0');
} 	
void signal_handler(int sig, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	(void) sig;
	
	if (str[i + 1] != '\0')
	{
		send_byte(str[i + 1]);
		i++;
	}
	else
		exit(1);
}

void init_sigaction()
{
	struct sigaction sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
}
int main(int argc, char **argv)
{
	if(argc != 3)
	{
		ft_printf("ERROR Incorrect correct amount of argumnets! (%d vs 2)\n", argc - 1);
		exit(1);
	}
	PID = ft_atoi(argv[1]);
	if (kill(PID, 0) == -1)
	{
		ft_printf("ERROR Incorrect PID!\n", argc - 1);
		exit(1);
	}
	str = argv[2];
	
	init_sigaction();
	send_byte(str[i]);
	i++;
	pause();

	//send_str(argv[2]);
	return (0);
}

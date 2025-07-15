#include "../include/minitalk.h"

int PID;

void send_signal(int sig)
{
	kill(PID, sig);
	usleep(200);
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
	}
	send_byte('\0');
}


int main(int argc, char **argv)
{
	if(argc != 3)
	{
		ft_printf("ERROR Please, check if you're passing correct amount of argumnets! (%d vs 2)\n", argc - 1);
		exit(1);
	}
	PID = ft_atoi(argv[1]);

	send_str(argv[2]);
	return (0);
}
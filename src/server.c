#include "../include/minitalk.h"

void signal_handler(int sig)
{
	if (sig == SIGUSR1)
		ft_putchar_fd('1', 1);
	else if (sig == SIGUSR2)
		ft_putchar_fd('0', 1);
}

int main()
{
	printf("PID: %d\n", getpid());
	struct sigaction sa_action;
	sa_action.sa_handler = &signal_handler;
	sigaction(SIGUSR1, &sa_action, NULL);
	sigaction(SIGUSR2, &sa_action, NULL);
	while (1)
	{
		pause();
		ft_putchar_fd(' ', 1);
	}
} 
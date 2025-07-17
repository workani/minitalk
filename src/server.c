#include "../include/minitalk.h"

void signal_handler(int sig, siginfo_t *info, void *context)
{
	static int count = 0;
	static unsigned char buffer = 0;

	(void) context;
	if (sig == SIGUSR1)
		buffer |= (128 >> count);

	count++;
	if (count == 8)
	{
		write(1, &buffer, 1);
		count = 0;
		buffer = 0;
		kill(info->si_pid, SIGUSR2);
	}
}

int main(void)
{
	struct sigaction sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}


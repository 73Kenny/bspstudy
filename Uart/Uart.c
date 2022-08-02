#include <stdio.h>
#include <stdlib.h>		// The normal application lib
#include <unistd.h>		// Unix application lib
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>		// Sys file controller
#include <termios.h>	// PPSIX Controller
#include <error.h>		// Error return define

#define FALSE	-1
#define TRUE	0

int speed_arr[] = {B38400, B19200, B9600, B4800, B2400, B1200, B300, B38400, B19200, B9600, B4800, B2400, B1200, B300};
int name_arr[] = {38400, 19200, 9600, 4800, 2400, 1200, 300, 38400, 19200, 9600, 4800, 2400, 1200, 300};

void set_speed(int fd, int speed)
{
	int i;
	int status;
	struct termios Opt;
	tcgetattr(fd, &Opt);

	for (i = 0; i < sizeof(speed_arr)/sizeof(int); i++)
	{
		if (speed == name_arr[i])
		{
			tcflush(fd, TCOFLUSH);
			cfsetispeed(&Opt, speed_arr[i]);
			cfsetospeed(&Opt, speed_arr[i]);
			status = tcsetattr(fd, TCSANOW, &Opt);

			if (status != 0)
			{
				perror("tcsetattr fd1");
				return;
			}

			tcflush(fd, TCIOFLUSH);
		}
	}
	return;
}

int set_Parity(int fd, int databits, int stopbits, int parity)
{
	struct termios options;

	if (tcgetattr(fd, &options) != 0)
	{
		perror("SetupSerial 1");
		return FALSE;
	}

	options.c_cflag &= ~CSIZE;

	switch (databits)
	{
		case 7: options.c_cflag |= CS7;
				break;
		case 8: options.c_cflag |= CS8;
				break;
		default:
				fprintf(stderr, "Unsupported data size");
				return FALSE;
	}

	switch (parity)
	{
		case 'n':
		case 'N':
				options.c_cflag &= ~PARENB;
				options.c_cflag &= ~INPCK;
				break;
		case 'o':
		case 'O':
				options.c_cflag |= (PARODD | PARENB);
				options.c_iflag |= INPCK;
				break;
		case 'e':
		case 'E':
				options.c_cflag |= PARENB;
				options.c_cflag &= ~PARODD;
				options.c_iflag |= INPCK;
				break;
		case 's':
		case 'S':
				options.c_cflag &= ~PARENB;
				options.c_cflag &= ~CSTOPB;
				break;
		default:
				fprintf(stderr, "Unsupport parity");
				return FALSE;
	}

	switch (stopbits)
	{
		case 1:
				options.c_cflag &= ~CSTOPB;
				break;
		case 2:
				options.c_cflag |= CSTOPB;
				break;
		default:
				fprintf(stderr, "Unsupport stop bitsn");
				return  FALSE;
	}

	if (parity != 'n')
	{
		options.c_cflag |= INPCK;
	}

	tcflush(fd, TCIFLUSH);
	options.c_cc[VTIME] = 150;
	options.c_cc[VMIN] = 0;

	if (tcsetattr(fd, TCSANOW, &options) != 0)
	{
		perror("SetupSerial 3");
		return FALSE;
	}

	return TRUE;
}

int OpenDev(char* Dev)
{
	int fd = open(Dev, O_RDWR);

	if (-1 == fd)
	{
		perror("Can't Open Serial Port");
		return FALSE;
	}
	else
	{
		return fd;
	}
}

int main(int argc, char** argv)
{
	int fd;
	int nread;
	char buff[512] = {0};
	char* dev = "/dev/pts/2";

	fd = OpenDev(dev);
	set_speed(fd, 19200);

	if (set_Parity(fd, 8, 1, 'N') == FALSE)
	{
		printf("Set Parity Errorn");
		exit(0);
	}

	while (1)
	{
		while ((nread = read(fd, buff, 512)) > 0)
		{
			printf("nLen = %d\n", nread);
			printf("RX: %s\n", buff);
		}
	}

	close(fd);
	exit(0);
	return 0;
}



























#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int serial_setup (void);


void main(){
	char msg[] = "hello";
	char read_buf [256];

	int serial_port = serial_setup();

	// open status serial port 
	if (serial_port < 0) {
	    printf("Error opening port \n");
	}
	else {
	    printf("open serial succ \n");
	}
	while (1){
	if ( read(serial_port , &read_buf, sizeof(read_buf)) )
	printf("%s",read_buf);
	}
	printf("\n prog terminated");
}

int serial_setup (){
	int serial_port = open("/dev/ttyUSB0", O_RDWR);
	struct termios ser;
	ser.c_cflag = CS8 | CREAD | CLOCAL;
	ser.c_cflag &= ~( PARENB | CRTSCTS );
	ser.c_lflag &= ~(ICANON);
	ser.c_cc[VMIN] = 0;
	ser.c_cc[VTIME] = 0;

	cfsetspeed(&ser,B115200);
	/* cfsetispeed(&ser,B115200)	; */
	/* cfsetospeed(&ser,B115200)	; */

	int status = tcsetattr( serial_port, TCSANOW, &ser );
	if ( status ) {
		printf("Error Encountered while setting up attributes ..");
	}
	return serial_port;
}

#include <termios.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int serial_setup (void);


void main(){
	char msg[256] ;
	char c;
	char read_buf [256];
	memset(&read_buf,'\0',sizeof(read_buf));

	int serial_port = serial_setup();

	// open status serial port 
	if (serial_port < 0) {
		printf("Error opening port ..  \n");
	}
	else {
		printf("open serial succ \n");
	}
	while (1){

		memset(&read_buf,'\0',sizeof(read_buf));
		memset(&msg,'\0',sizeof(msg));
		int n  = read(serial_port , &read_buf, sizeof(read_buf)); 
		if (n){
			printf("%s",read_buf);
		}
		else{
			printf("Enter cmd.. ");
			while( c = getc(stdin) ){
				write(serial_port, &c, 1);
				if ( c == '\0')
					break;
			}
			
		}
		n = 0;
	}
	/*
	   scanf("%s",msg);
	   if(strlen(msg)){
	   write(serial_port, &msg, sizeof(msg));
	   }
	   }
	   */

	printf("\n prog terminated");
	}

int serial_setup (){

	int serial_port = open("/dev/ttyUSB1", O_RDWR);
	struct termios ser, def;
	tcgetattr( serial_port, &def );
	ser = def;
	ser.c_cflag = CS8 | CREAD | CLOCAL;
	ser.c_cflag &= ~( PARENB | CRTSCTS );
	ser.c_oflag &= ONLCR;
	ser.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
	/* ser.c_iflag |= IGNBRK; */
	ser.c_lflag &= ~ECHO; // Disable echo
	ser.c_cc[VMIN] = 0;
	ser.c_cc[VTIME] = 10;
	cfsetspeed(&ser,B115200);

	int status = tcsetattr( serial_port, TCSANOW, &ser );
	if ( status ) {
		printf("Error Encountered while setting up attributes ..");
	}
	return serial_port;
}

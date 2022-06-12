#include <time.h>
#include <stdio.h>
#include <stdlib.h>

enum protocol
{
	CAMERA,
	DCMOTOR,
	BLDC,
	PMSM,
	ACIM,
	LED,
	I2C,
	SPI,
	CAN,
	ECAP
};


void **syscall_arr;

void proc_camera (void)
{
	printf("Camera Processing\n");
}

int proc_dc_motor (void)
{
	printf("DC Motor Processing\n");

	return 3;
}

void init_syscall_arr (void)
{



	syscall_arr = (void **)malloc(sizeof(void *) * 10);

	syscall_arr[CAMERA] = proc_camera;
	syscall_arr[DCMOTOR] = proc_dc_motor;
	syscall_arr[BLDC] = proc_camera;
	syscall_arr[PMSM] = proc_camera;
	syscall_arr[ACIM] = proc_camera;
	syscall_arr[LED] = proc_camera;
	syscall_arr[I2C] = proc_camera;
	syscall_arr[SPI] = proc_camera;
	syscall_arr[CAN] = proc_camera;
	syscall_arr[ECAP] = proc_camera;
}

void recv_command_from_pc (void)
{
	int command;
	int (*p2)(void);
	void (*p)(void);

	printf("명령이 들어온다 가정하고 진행(랜덤으로 만들기)!\n");

	command = rand() % 10;
	printf("수신된 명령: %d(가정 - 랜덤)\n", command);



	command = CAMERA;
	p = syscall_arr[command];
	p();

	command = DCMOTOR;
	p2 = syscall_arr[command];
	printf("모터 gain값: %d\n", p2());









}

int main (void)
{
	srand(time(NULL));

	init_syscall_arr();
	recv_command_from_pc();

	return 0;
}

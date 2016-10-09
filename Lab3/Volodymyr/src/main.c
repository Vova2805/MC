#include "main.h" 
#include "leds.h"
#include "tasks.h"
#include "cmsis_os.h"

int main (void){
	init_leds();
	osKernelInitialize();
	init_timer();
	init_tasks();
	osKernelStart();
}


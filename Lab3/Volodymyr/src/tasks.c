#include "tasks.h" 
#include "leds.h"
#include "cmsis_os.h"

osThreadId tid_orangeLEDTask;
osThreadId tid_greenLEDTask;
osThreadId tid_redLEDTask;
osThreadId tid_blueLEDTask;
osThreadId tid_generalLEDTask;
osTimerId tid_TimerTasks;
int tim = 1;

osThreadDef(redLEDTask,osPriorityNormal,1,0);
osThreadDef(blueLEDTask,osPriorityNormal,1,0);
osThreadDef(greenLEDTask,osPriorityNormal,1,0);
osThreadDef(orangeLEDTask,osPriorityNormal,1,0);
osThreadDef(generalLEDTask,osPriorityNormal,1,0);
osTimerDef (TimerTasks, TimerTasks_Callback);

void init_tasks(void){
	tid_redLEDTask = osThreadCreate (osThread(redLEDTask), NULL);
	tid_blueLEDTask = osThreadCreate (osThread(blueLEDTask), NULL);
	tid_orangeLEDTask = osThreadCreate (osThread(orangeLEDTask), NULL);
	tid_greenLEDTask = osThreadCreate (osThread(greenLEDTask), NULL);
	tid_generalLEDTask = osThreadCreate (osThread(generalLEDTask), NULL);
}

void redLEDTask(void const *argument){
	turnOffAll();
	LEDSwitchOnOff(RED,ON);
	osDelay(10000);
}
void greenLEDTask(void const *argument){
	turnOffAll();
	LEDSwitchOnOff(GREEN,ON);
	osDelay(10000);
}
void blueLEDTask(void const *argument){
	turnOffAll();
	LEDSwitchOnOff(BLUE,ON);
	osDelay(10000);
}
void orangeLEDTask(void const *argument){
	turnOffAll();
	LEDSwitchOnOff(ORANGE,ON);
	osDelay(10000);
}
void generalLEDTask(void const *argument){
	turnOffAll();
	osDelay(10000);
}
void init_timer(void){
	tid_TimerTasks = osTimerCreate (osTimer(TimerTasks), osTimerPeriodic, &tim);
	if (tid_TimerTasks != NULL) {
		if(osTimerStart (tid_TimerTasks, 10) != osOK) {
			//std::cout<<"Error. Timer is not created correct";
		}
	}
}

short redLEDCounter = 0;
short blueLEDCounter;
void TimerTasks_Callback(void const *arg){
	/*if(redLEDCounter == 500){
	osSignalSet(tid_redLEDTask, 1);
	redLEDCounter = 0;
	}*/
	redLEDCounter++;
	blueLEDCounter++;
}

#include "stm32f4xx.h"
#include "cmsis_os.h"

void redLEDTask(void const *argument);
void greenLEDTask(void const *argument);
void blueLEDTask(void const *argument);
void orangeLEDTask(void const *argument);
void generalLEDTask(void const *argument);
void TimerTasks_Callback(void const *arg);

void init_timer(void);
void init_tasks(void);

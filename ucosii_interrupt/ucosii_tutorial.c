#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "includes.h"
#include "alt_ucosii_simple_error_check.h"
#include "altera_avalon_pio_regs.h"

#include "system.h"

/* Стеки задач */
#define   TASK_STACKSIZE       1024
OS_STK    initialize_task_stk[TASK_STACKSIZE];
OS_STK    get_sem_task2_stk[TASK_STACKSIZE];
OS_STK    getsem_task1_stk[TASK_STACKSIZE];
OS_STK    getsem_task2_stk[TASK_STACKSIZE];
OS_STK    receive_task1_stk[TASK_STACKSIZE];
OS_STK    receive_task2_stk[TASK_STACKSIZE];
OS_STK    send_task_stk[TASK_STACKSIZE];



/* Приоритеты задач */
#define INITIALIZE_TASK_PRIORITY   6
#define GET_SEM_TASK_PRIORITY      7
#define GETSEM_TASK1_PRIORITY      8
#define GETSEM_TASK2_PRIORITY      9
#define RECEIVE_TASK1_PRIORITY    10
#define RECEIVE_TASK2_PRIORITY    11
#define SEND_TASK_PRIORITY        12

INT32U button_pressed = 0;

#define BTN_RIGHT_PRESSED 0xE
#define BTN_CNTR_RIGHT 0xD
#define BTN_CNTR_LEFT 0xB
#define BTN_LEFT_PRESSED 0x7

#define ARRAY_SIZE 100

INT32U global_array[ARRAY_SIZE];
INT32U counter;


/* Объявление очереди */
#define   MSG_QUEUE_SIZE  30            //Size of message queue used in example
OS_EVENT  *msgqueue;                    //Message queue pointer 
void      *msgqueueTbl[MSG_QUEUE_SIZE]; // Storage for messages

/* Объявление семафора */
OS_EVENT *shared_resource_sem;

INT8U led;
INT32U led_counter = 10;
INT32U state = 1;

OS_TMR *LedTmr;
BOOLEAN status;

/* Глобальные переменные */
INT32U number_of_messages_sent = 0;
INT32U number_of_messages_received_task1 = 0;
INT32U number_of_messages_received_task2 = 0;
INT32U getsem_task1_got_sem = 0;
INT32U getsem_task2_got_sem = 0;
char sem_owner_task_name[20];

/* Прототипы функций */
int initOSDataStructs(void);
int initCreateTasks(void);

void TimerISRFnct() {

	led = 255;

	IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE,led);

}

void isr_button(void* context, alt_u32 id)
{

	//сигнализировать о входе в прерывание
	OSIntEnter();
	//считать значение из порта
	button_pressed = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);
	//сбросить статус прерываний
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE,0);
	//сигнализировать ждущему процессу
	//OSQPost(msgqueue, (void *)&value);
	//информировать ядро о выходе из прерывания
	OSIntExit();
}

void get_sem_task2(void* pdata)
{
	INT8U err;
    INT32U buf = -1;

  while (1)
  {

	    //printf("led_counter %lu\n", led_counter);

	    IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE,0);

    status = OSTmrStart(LedTmr, &err);

    OSTimeDlyHMSM(0, 0, 0, 10);

  }
}


void send_task(void* pdata)
{
  INT8U return_code = OS_NO_ERR;
  INT32U  msg = 0;
  OS_Q_DATA queue_data;  
  
  while (1)
  {
	if (button_pressed)
	{
		return_code = OSQQuery(msgqueue, &queue_data);
		alt_ucosii_check_return_code(return_code);
		if(queue_data.OSNMsgs < MSG_QUEUE_SIZE)
		{
		   msg = button_pressed;
		   return_code = OSQPostOpt(msgqueue, (void *)&msg, OS_POST_OPT_BROADCAST);
		   alt_ucosii_check_return_code(return_code);
		   number_of_messages_sent++;
		}
		button_pressed = 0;
	}
  }
}

void receive_task1(void* pdata)
{
  INT8U return_code = OS_NO_ERR;
  INT32U *msg;
  INT8U err;
  int i;
  
  while (1)
  {
    msg = (INT32U *)OSQPend(msgqueue, 0, &return_code);

    alt_ucosii_check_return_code(return_code);
    number_of_messages_received_task1++;

	switch(*msg)
	{
		case BTN_RIGHT_PRESSED:
			IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_BASE, 0x79);

			led_counter = 8;

			OSTmrDel(LedTmr,
			&err);

			 LedTmr = OSTmrCreate(
					 led_counter,
					    		0,
					    		OS_TMR_OPT_ONE_SHOT,
					    		TimerISRFnct,
					    		NULL,
					    		"TmrLed",
					    		&err);

			break;
		case BTN_LEFT_PRESSED:
			IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_BASE, 0x19);

			led_counter = 4;

			OSTmrDel(LedTmr,
			&err);

		    LedTmr = OSTmrCreate(
		    		led_counter,
		    		0,
		    		OS_TMR_OPT_ONE_SHOT,
		    		TimerISRFnct,
		    		NULL,
		    		"TmrLed",
		    		&err);

			break;
		case BTN_CNTR_RIGHT:
			IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_BASE, 0x24);

			led_counter = 2;

			OSTmrDel(LedTmr,
						&err);

			LedTmr = OSTmrCreate(
					led_counter,
					0,
					OS_TMR_OPT_ONE_SHOT,
					TimerISRFnct,
					NULL,
					"TmrLed",
					&err);

			break;
		case BTN_CNTR_LEFT:
			IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_BASE, 0x30);

			led_counter = 6;

			OSTmrDel(LedTmr,
						&err);

			LedTmr = OSTmrCreate(
					led_counter,
					0,
					OS_TMR_OPT_ONE_SHOT,
					TimerISRFnct,
					NULL,
					"TmrLed",
					&err);
			break;
		default:
			for (i = 0; i < counter; i++)
			//while (counter--)
				printf("%d Btn = %x\n", i, global_array[i]);
	}

    //printf("Msg task1 0x%8x\n", *msg);
    OSTimeDlyHMSM(0, 0, 0, 333);
  }
}

void receive_task2(void* pdata)
{
  INT8U return_code = OS_NO_ERR;
  INT32U *msg;
  
  while (1)
  {
    msg = (INT32U *)OSQPend(msgqueue, 0, &return_code);
    printf("Button pressed\n");
    if (counter < ARRAY_SIZE)
    {
    	switch(*msg) {
    	case BTN_RIGHT_PRESSED:
    		global_array[counter] = 1;
			break;
		case BTN_LEFT_PRESSED:
			global_array[counter] = 4;
			break;
		case BTN_CNTR_RIGHT:
			global_array[counter] = 2;
			break;
		case BTN_CNTR_LEFT:
			global_array[counter] = 3;
			break;
    	}
    }
    counter++;
    alt_ucosii_check_return_code(return_code);
    number_of_messages_received_task2++;
    OSTimeDlyHMSM(0, 0, 1, 0);
  }
}

void  initialize_task(void* pdata)
{
  INT8U return_code = OS_NO_ERR;
    
  initOSDataStructs();  

  initCreateTasks();
  
  return_code = OSTaskDel(OS_PRIO_SELF);
  alt_ucosii_check_return_code(return_code);
  while (1);
}

int main (int argc, char* argv[], char* envp[])
{
  INT8U return_code = OS_NO_ERR;
  counter = 0;

  //зарегистрировать вектор
  return_code = alt_irq_register(BUTTONS_IRQ,NULL,isr_button);
  //разрешить прерывания от периферийного модуля
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_BASE,0x000F);

  return_code = OSTaskCreate(initialize_task,
                             NULL,
                             (void *)&initialize_task_stk[TASK_STACKSIZE-1],
                             INITIALIZE_TASK_PRIORITY);
  alt_ucosii_check_return_code(return_code);
  OSStart();
  return 0;
}

int initOSDataStructs(void)
{
  msgqueue = OSQCreate(&msgqueueTbl[0], MSG_QUEUE_SIZE);
  shared_resource_sem = OSSemCreate(1);
  return 0;
}
 
int initCreateTasks(void)
{
  INT8U return_code = OS_NO_ERR;

  return_code = OSTaskCreate(receive_task1,
                             NULL,
                             (void *)&receive_task1_stk[TASK_STACKSIZE-1],
                             RECEIVE_TASK1_PRIORITY);
  alt_ucosii_check_return_code(return_code);

  return_code = OSTaskCreate(receive_task2,
							 NULL,
							 (void *)&receive_task2_stk[TASK_STACKSIZE-1],
							 RECEIVE_TASK2_PRIORITY);
  alt_ucosii_check_return_code(return_code);

  return_code = OSTaskCreate(send_task,
                             NULL,
                             (void *)&send_task_stk[TASK_STACKSIZE-1],
                             SEND_TASK_PRIORITY);
  alt_ucosii_check_return_code(return_code);

  return_code = OSTaskCreate(get_sem_task2,
                             NULL,
                             (void *)&get_sem_task2_stk[TASK_STACKSIZE-1],
                             GET_SEM_TASK_PRIORITY);
  alt_ucosii_check_return_code(return_code);

  return 0;
}

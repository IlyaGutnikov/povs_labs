/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include "altera_avalon_performance_counter.h"
#include <stdio.h>
#include "system.h"
#include <unistd.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include "stdlib.h"
#include "stdint.h"


#define NONE_PRESSED 0xF  // Value read from button PIO when no buttons pressed
#define DEBOUNCE 30000  // Time in microseconds to wait for switch debounce

#define KEY0 0x1
#define KEY1 0x2
#define KEY2 0x4
#define KEY3 0x8

#define MATRIX_SIZE 8
void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]);
int matrix_watch_you(void);
int matrix_watch_you_indus(void);

/* Declare a global variable to hold the edge capture value. */
volatile int edge_capture;
volatile int interrupt_exit_flag = 0;

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
	static void handle_button_interrupts(void* context)
#else
	static void handle_button_interrupts(void* context, alt_u32 id)
#endif
{
		PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, 2);
	//PERF_BEGIN (PERFORMANCE_COUNTER_0_BASE, 1);
	/* Cast context to edge_capture's type. It is important that this
	be declared volatile to avoid unwanted compiler optimization. */
	volatile int* edge_capture_ptr = (volatile int*) context;
	/*
	 * Read the edge capture register on the button PIO.
	 * Store value.
	 */
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE);
	/* Write to the edge capture register to reset it. */
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0);
	/* Read the PIO to delay ISR exit. This is done to prevent a
	spurious interrupt in systems with high processor -> pio
	latency and fast interrupts. */
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE);
	//printf("Handling completed!");
	//printf("%d\n", *edge_capture_ptr);

	//interrupt_exit_flag++;

	//PERF_END (PERFORMANCE_COUNTER_0_BASE, 2);
	PERF_END(PERFORMANCE_COUNTER_0_BASE, 2);
}

/* Initialize the button_pio. */
static void init_button_pio()
{
	/* Recast the edge_capture pointer to match the
	alt_irq_register() function prototype. */
	void* edge_capture_ptr = (void*) &edge_capture;
	/* Enable all 4 button interrupts. */
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_BASE, 0xf);
	/* Reset the edge capture register. */
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0x0);
	/* Register the ISR. */
	#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
		alt_ic_isr_register(BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID,
				BUTTONS_IRQ,
			handle_button_interrupts,
			edge_capture_ptr, 0x0);
	#else
		alt_irq_register( BUTTON_PIO_IRQ,
				edge_capture_ptr,
				handle_button_interrupts );
	#endif
	printf("Initiazile button completed!\n");
}


int main(void)
{
//	int buttons;  // Use to hold button pressed value
//	int led = 0x01;  // Use to write to led
//
//	edge_capture = 0xF;
//	init_button_pio();
	PERF_RESET (PERFORMANCE_COUNTER_0_BASE);
	PERF_START_MEASURING (PERFORMANCE_COUNTER_0_BASE);
	int count = 0;

	count = arrays(1000);


	PERF_STOP_MEASURING (PERFORMANCE_COUNTER_0_BASE);
	perf_print_formatted_report(PERFORMANCE_COUNTER_0_BASE, ALT_CPU_FREQ, 1, "all");

	//printf("%d", count);

//	IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE,led); // write initial value to pio
//
//
//	while (interrupt_exit_flag!=1)
//	{
//
//		buttons = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE); // read buttons via pio
//
//		if (edge_capture != NONE_PRESSED)  // if button pressed
//			{
//				if (edge_capture == KEY0) {
//					led = 0x01;
//			}
//				if (edge_capture == KEY3) {
//					led = 0x80;
//			}
//				if (edge_capture == KEY2) {
//					if (led >= 0x80)  // if pattern is 00000001 on board (leds in reverse order)
//						led = 0x01;  // reset pattern
//					else
//						led = led << 1;  // shift right on board (led0 is far left)
//
//			}
//				if (edge_capture == KEY1) {
//					if (led <= 0x01)  // if pattern is 00000001 on board (leds in reverse order)
//						led = 0x80;  // reset pattern
//					else
//						led = led >> 1;  // shift right on board (led0 is far left)
//			}
//
//			interrupt_exit_flag++;
//
//			IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE,led);  // write new value to pio
//			edge_capture = 0xF;
//
//			/* Switch debounce routine
//			   Wait for small delay after intial press for debouncing
//			   Wait for release of key
//			   Wait for small delay after release for debouncing */
//
//			usleep (DEBOUNCE);
//			while (buttons != NONE_PRESSED){  // wait for button release
//				buttons = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);  } // update
//			usleep (DEBOUNCE);
//		}
//
//	}
//			PERF_STOP_MEASURING (PERFORMANCE_COUNTER_0_BASE);
//	perf_print_formatted_report(PERFORMANCE_COUNTER_0_BASE, ALT_CPU_FREQ, 2, "printf", "interrupt");
//

}  // end


int arrays (int size) {

	int arraysize = size;

	int K = 1;
	int N = 1;
	int NVR = 1;
	int KVR = 1;

	int counter = 0;
	int counter_tmp = 0;

	int tmp = 0;

	int j = 0;
	int l = 0;

	int array [arraysize];
	int buf [arraysize];



	srand(time(NULL));
	while(l < arraysize) {

		array[l] = rand() % 10 + 1;
		//array[l] = 10 -l;
		//printf("%i",array[l]);
		//printf(" ");
		l++;
	}
	l = 0;
	//array[10]=99;

	/*for(j = 0; j < arraysize - 4; j++)
		array[j] = 0;
	array[arraysize - 4] = 10;
	array[arraysize - 3] = 9;
	array[arraysize - 2] = 8;
	array[arraysize - 1] = 7;
	//printf("\n");*/

	//printf("\n");

	PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, 1);

	int i = 0;
	int max = 1;
	int h=0;
	int k=0;
	int ind=0;
	int y = 0;

	int o = 0;

	int g = 0;

	int size1 = arraysize / 2;

	 for (g = 1; g <= size1; g++) {

		 if (array[o++] > array[i++])  k++;

		 else {if (k>h) {

			 h=k;

			 for(ind=i-k-1; ind<i; ind++) {

				 y=i-k;
				// printf(" %i",array[ind]);
			 }

			 k=0;}
		 }


		 if (array[o++] > array[i++])  k++;

		 else {if (k>h) {

			 h=k;

			 for(ind=i-k-1; ind<i; ind++) {

				 y=i-k;
				// printf(" %i",array[ind]);
			 }

			 k=0;}
		 }

	 }

 /*for (i = 1; i <= arraysize; i++) {

	 if (array[i-1]>array[i])  k++;

	 else {if (k>h) {

		 h=k;

		 for(ind=i-k-1;ind<i;ind++) {

			 y=i-k;
			// printf(" %i",array[ind]);
		 }

		 k=0;}
	 }
 }*/

	 printf("\n");
	 printf("\n");
printf("index %i",y-1);



   /* for (i = 0; i < arraysize; i++) buf[i] = 1;

    for (i = 1; i < arraysize; i++) {
    	for (j = 0; j < i; j++) {
    		if((array[i] < array[j]) && (buf[i] < buf[j] + 1)){
    			buf[i] = buf[j] + 1;
    		}
    	}
    }

    for(t = 0; t < arraysize; t++)
    	if (max < buf[t])
    		max = buf[t];
*/


	PERF_END(PERFORMANCE_COUNTER_0_BASE, 1);

	//printf("Size: %d", KVR - NVR -1);
	return h;

}

#include <stdio.h>
#include <unistd.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include "alt_types.h"
#include "sys/alt_irq.h"

#define NONE_PRESSED 0xF
#define DEBOUNCE 30000

#define BTN_RIGHT_PRESSED 0x1
#define BTN_LEFT_PRESSED 0x8
#define BTN_CNTR_LEFT 0x4
#define BTN_CNTR_RIGHT 0x2

volatile int edge_capture;

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
    static void handle_button_interrupts(void* context)
#else
    static void handle_button_interrupts(void* context, alt_u32 id)
#endif
{
    /* Cast context to edge_capture's type. It is important that this
    be declared volatile to avoid unwanted compiler optimization. */
    volatile int* edge_capture_ptr = (volatile int*) context;
    /*
    * Read the edge capture register on the button PIO.
    * Store value.
    */
    *edge_capture_ptr =
    IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE);
    /* Write to the edge capture register to reset it. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0);
    /* Read the PIO to delay ISR exit. This is done to prevent a
    spurious interrupt in systems with high processor -> pio
    latency and fast interrupts. */
    IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE);
    printf("Handler captured!\n");
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
        alt_irq_register( BUTTON_PIO_IRQ, edge_capture_ptr, handle_button_interrupts );
    #endif

    printf("Init done!\n");
}

int main(void)
{
    int led = 0x01;
    edge_capture = 0xF;

    init_button_pio();

    printf("Simple\n");   // print a message to show that program is running

    IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE,led); // write initial value
    while (1)
    {
        if (edge_capture != NONE_PRESSED)  // if button pressed
        {
            switch(edge_capture) {
                case BTN_RIGHT_PRESSED:
                    led = 0x01;
                    break;
                case BTN_LEFT_PRESSED:
                    led = 0x80;
                    break;
                case BTN_CNTR_RIGHT:
                    if (led == 0x1)
                        led = 0x80;
                    else
                        led = led >> 1;
                    break;
                case BTN_CNTR_LEFT:
                    if (led == 0x80)
                        led = 0x1;
                    else
                        led = led << 1;
                    break;

            }
            edge_capture = 0xF;

            IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, led);

            usleep (DEBOUNCE);
            while (edge_capture != NONE_PRESSED)  // wait for button release
                edge_capture = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);
            usleep (DEBOUNCE);
        }

    }

}  // end

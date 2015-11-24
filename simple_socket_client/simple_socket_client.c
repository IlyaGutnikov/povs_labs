/******************************************************************************
* Copyright (c) 2006 Altera Corporation, San Jose, California, USA.           *
* All rights reserved. All use of this software and documentation is          *
* subject to the License Agreement located at the end of this file below.     *
*******************************************************************************
* Date - October 24, 2006                                                     *
* Module - simple_socket_server.c                                             *
*                                                                             *
******************************************************************************/

/******************************************************************************
 * Simple Socket Server (SSS) example.
 *
 * This example demonstrates the use of MicroC/OS-II running on NIOS II.
 * In addition it is to serve as a good starting point for designs using
 * MicroC/OS-II and Altera NicheStack TCP/IP Stack - NIOS II Edition.
 *
 * -Known Issues
 *     None.
 *
 * Please refer to the Altera NicheStack Tutorial documentation for details on this
 * software example, as well as details on how to configure the NicheStack TCP/IP
 * networking stack and MicroC/OS-II Real-Time Operating System.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "altera_avalon_pio_regs.h"

/* MicroC/OS-II definitions */
#include "includes.h"

/* Simple Socket Server definitions */
#include "simple_socket_client.h"
#include "alt_error_handler.h"

/* Nichestack definitions */
#include "ipport.h"
#include "tcpport.h"

/*
 * Global handles (pointers) to our MicroC/OS-II resources. All of resources
 * beginning with "SSS" are declared and created in this file.
 */

/*
 * This SSSLEDCommandQ MicroC/OS-II message queue will be used to communicate
 * between the simple socket server task and Nios Development Board LED control
 * tasks.
 *
 * Handle to our MicroC/OS-II Command Queue and variable definitions related to
 * the Q for sending commands received on the TCP-IP socket from the
 * SSSSimpleSocketServerTask to the LEDManagementTask.
 */
OS_EVENT  *SSSLEDCommandQ;
#define SSS_LED_COMMAND_Q_SIZE  30  /* Message capacity of SSSLEDCommandQ */
void *SSSLEDCommandQTbl[SSS_LED_COMMAND_Q_SIZE]; /*Storage for SSSLEDCommandQ*/


/*
 * Handle to our MicroC/OS-II LED Event Flag.  Each flag corresponds to one of
 * the LEDs on the Nios Development board, D0 - D7.
 */
OS_FLAG_GRP *SSSLEDEventFlag;

/*
 * Handle to our MicroC/OS-II LED Lightshow Semaphore. The semaphore is checked
 * by the LED7SegLightshowTask each time it updates 7 segment LED displays,
 * U8 and U9.  The LEDManagementTask grabs the semaphore away from the lightshow task to
 * toggle the lightshow off, and gives up the semaphore to turn the lightshow
 * back on.  The LEDManagementTask does this in response to the CMD_LEDS_LIGHTSHOW
 * command sent from the SSSSimpleSocketServerTask when the user sends a toggle
 * lightshow command over the TCPIP socket.
 */
OS_EVENT *SSSLEDLightshowSem;

/* Definition of Task Stacks for tasks not invoked by TK_NEWTASK
 * (do not use NicheStack)
 */

OS_STK    LEDManagementTaskStk[TASK_STACKSIZE];
OS_STK    LED7SegLightshowTaskStk[TASK_STACKSIZE];



/*
 * Create our MicroC/OS-II resources. All of the resources beginning with
 * "SSS" are declared in this file, and created in this function.
 */
void SSSCreateOSDataStructs(void)
{
  INT8U error_code;

  /*
  * Create the resource for our MicroC/OS-II Queue for sending commands
  * received on the TCP/IP socket from the SSSSimpleSocketServerTask()
  * to the LEDManagementTask().
  */
  SSSLEDCommandQ = OSQCreate(&SSSLEDCommandQTbl[0], SSS_LED_COMMAND_Q_SIZE);
  if (!SSSLEDCommandQ)
  {
     alt_uCOSIIErrorHandler(EXPANDED_DIAGNOSIS_CODE,
     "Failed to create SSSLEDCommandQ.\n");
  }

 /* Create our MicroC/OS-II LED Lightshow Semaphore.  The semaphore is checked
  * by the SSSLEDLightshowTask each time it updates 7 segment LED displays,
  * U8 and U9.  The LEDTask grabs the semaphore away from the lightshow task to
  * toggle the lightshow off, and gives up the semaphore to turn the lightshow
  * back on.  The LEDTask does this in response to the CMD_LEDS_LIGHTSHOW
  * command sent from the SSSSimpleSocketServerTask when the user sends the
  * toggle lightshow command over the TCPIP socket.
  */
  SSSLEDLightshowSem = OSSemCreate(1);
  if (!SSSLEDLightshowSem)
  {
     alt_uCOSIIErrorHandler(EXPANDED_DIAGNOSIS_CODE,
                            "Failed to create SSSLEDLightshowSem.\n");
  }

 /*
  * Create our MicroC/OS-II LED Event Flag.  Each flag corresponds to one of
  * the LEDs on the Nios Development board, D0 - D7.
  */
  SSSLEDEventFlag = OSFlagCreate(0, &error_code);
  if (!SSSLEDEventFlag)
  {
     alt_uCOSIIErrorHandler(error_code, 0);
  }
}

/* This function creates tasks used in this example which do not use sockets.
 * Tasks which use Interniche sockets must be created with TK_NEWTASK.
 */

void SSSCreateTasks(void)
{
   INT8U error_code;

   error_code = OSTaskCreateExt(LED7SegLightshowTask,
                             NULL,
                             (void *)&LED7SegLightshowTaskStk[TASK_STACKSIZE-1],
                             LED_7SEG_LIGHTSHOW_TASK_PRIORITY,
                             LED_7SEG_LIGHTSHOW_TASK_PRIORITY,
                             LED7SegLightshowTaskStk,
                             TASK_STACKSIZE,
                             NULL,
                             0);

   alt_uCOSIIErrorHandler(error_code, 0);

   error_code = OSTaskCreateExt(LEDManagementTask,
                              NULL,
                              (void *)&LEDManagementTaskStk[TASK_STACKSIZE-1],
                              LED_MANAGEMENT_TASK_PRIORITY,
                              LED_MANAGEMENT_TASK_PRIORITY,
                              LEDManagementTaskStk,
                              TASK_STACKSIZE,
                              NULL,
                              0);

   alt_uCOSIIErrorHandler(error_code, 0);

}


/*
 * sss_reset_connection()
 *
 * This routine will, when called, reset our SSSConn struct's members
 * to a reliable initial state. Note that we set our socket (FD) number to
 * -1 to easily determine whether the connection is in a "reset, ready to go"
 * state.
 */
void sss_reset_connection(SSSConn* conn)
{
  memset(conn, 0, sizeof(SSSConn));

  conn->fd = -1;
  conn->state = READY;
  conn->rx_wr_pos = conn->rx_buffer;
  conn->rx_rd_pos = conn->rx_buffer;
  return;
}

/*
 * sss_send_menu()
 *
 * This routine will transmit the menu out to the telent client.
 */
void sss_send_menu(SSSConn* conn)
{
  char  tx_buf[SSS_TX_BUF_SIZE];
  char *tx_wr_pos = tx_buf;

  tx_wr_pos += sprintf(tx_wr_pos,"=================================\n\r");
  tx_wr_pos += sprintf(tx_wr_pos,"Nios II Simple Socket Server Menu\n\r");
  tx_wr_pos += sprintf(tx_wr_pos,"=================================\n\r");
  tx_wr_pos += sprintf(tx_wr_pos,"0-7: Toggle board LEDs D0 - D7\n\r");
  tx_wr_pos += sprintf(tx_wr_pos,"S: 7-Segment LED Light Show\n\r");
  tx_wr_pos += sprintf(tx_wr_pos,"Q: Terminate session\n\r");
  tx_wr_pos += sprintf(tx_wr_pos,"=================================\n\r");
  tx_wr_pos += sprintf(tx_wr_pos,"Enter your choice & press return:\n\r");

  send(conn->fd, tx_buf, tx_wr_pos - tx_buf, 0);

  return;
}

/*
 * sss_handle_accept()
 *
 * This routine is called when ever our listening socket has an incoming
 * connection request. Since this example has only data transfer socket,
 * we just look at it to see whether its in use... if so, we accept the
 * connection request and call the telent_send_menu() routine to transmit
 * instructions to the user. Otherwise, the connection is already in use;
 * reject the incoming request by immediately closing the new socket.
 *
 * We'll also print out the client's IP address.
 */
void sss_handle_accept(int listen_socket, SSSConn* conn)
{
  int                 socket, len;
  struct sockaddr_in  incoming_addr;

  len = sizeof(incoming_addr);

  if ((conn)->fd == -1)
  {
     if((socket=accept(listen_socket,(struct sockaddr*)&incoming_addr,&len))<0)
     {
         alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,
                                 "[sss_handle_accept] accept failed");
     }
     else
     {
        (conn)->fd = socket;
        sss_send_menu(conn);
        printf("[sss_handle_accept] accepted connection request from %s\n",
               inet_ntoa(incoming_addr.sin_addr));
     }
  }
  else
  {
    printf("[sss_handle_accept] rejected connection request from %s\n",
           inet_ntoa(incoming_addr.sin_addr));
  }

  return;
}

/*
 * sss_exec_command()
 *
 * This routine is called whenever we have new, valid receive data from our
 * sss connection. It will parse through the data simply looking for valid
 * commands to the sss server.
 *
 * Incoming commands to talk to the board LEDs are handled by sending the
 * MicroC/OS-II SSSLedCommandQ a pointer to the value we received.
 *
 * If the user wishes to quit, we set the "close" member of our SSSConn
 * struct, which will be looked at back in sss_handle_receive() when it
 * comes time to see whether to close the connection or not.
 */
void sss_exec_command(SSSConn* conn)
{
   int bytes_to_process = conn->rx_wr_pos - conn->rx_rd_pos;

   char  tx_buf[SSS_TX_BUF_SIZE];
   char *tx_wr_pos = tx_buf;

   INT8U error_code;


   /*
    * "SSSCommand" is declared static so that the data will reside
    * in the BSS segment. This is done because a pointer to the data in
    * SSSCommand
    * will be passed via SSSLedCommandQ to the LEDManagementTask.
    * Therefore SSSCommand cannot be placed on the stack of the
    * SSSSimpleSocketServerTask, since the LEDManagementTask does not
    * have access to the stack of the SSSSimpleSocketServerTask.
    */
   static INT32U SSSCommand;

   SSSCommand = CMD_LEDS_BIT_0_TOGGLE;

   while(bytes_to_process--)
   {
      SSSCommand = toupper(*(conn->rx_rd_pos++));

      if(SSSCommand >= ' ' && SSSCommand <= '~')
      {
         tx_wr_pos += sprintf(tx_wr_pos,
                              "--> Simple Socket Server Command %c.\n",
                              (char)SSSCommand);
         if (SSSCommand == CMD_QUIT)
         {
            tx_wr_pos += sprintf(tx_wr_pos,"Terminating connection.\n\n\r");
            conn->close = 1;
         }
         else
         {
            error_code = OSQPost(SSSLEDCommandQ, (void *)SSSCommand);

            alt_SSSErrorHandler(error_code, 0);
         }
      }
   }

  send(conn->fd, tx_buf, tx_wr_pos - tx_buf, 0);

  return;
}

/*
 * sss_handle_receive()
 *
 * This routine is called whenever there is a sss connection established and
 * the socket assocaited with that connection has incoming data. We will first
 * look for a newline "\n" character to see if the user has entered something
 * and pressed 'return'. If there is no newline in the buffer, we'll attempt
 * to receive data from the listening socket until there is.
 *
 * The connection will remain open until the user enters "Q\n" or "q\n", as
 * deterimined by repeatedly calling recv(), and once a newline is found,
 * calling sss_exec_command(), which will determine whether the quit
 * command was received.
 *
 * Finally, each time we receive data we must manage our receive-side buffer.
 * New data is received from the sss socket onto the head of the buffer,
 * and popped off from the beginning of the buffer with the
 * sss_exec_command() routine. Aside from these, we must move incoming
 * (un-processed) data to buffer start as appropriate and keep track of
 * associated pointers.
 */
void sss_handle_receive(SSSConn* conn)
{
  int data_used = 0, rx_code = 0;
  char *lf_addr;

  conn->rx_rd_pos = conn->rx_buffer;
  conn->rx_wr_pos = conn->rx_buffer;

  printf("[sss_handle_receive] processing RX data\n");

  while(conn->state != CLOSE)
  {
    /* Find the Carriage return which marks the end of the header */
    lf_addr = strchr((const char*)conn->rx_buffer, '\n');

    if(lf_addr)
    {
      /* go off and do whatever the user wanted us to do */
      sss_exec_command(conn);
    }
    /* No newline received? Then ask the socket for data */
    else
    {
      rx_code = recv(conn->fd, (char*)conn->rx_wr_pos,
        SSS_RX_BUF_SIZE - (conn->rx_wr_pos - conn->rx_buffer) -1, 0);

     if(rx_code > 0)
      {
        conn->rx_wr_pos += rx_code;

        /* Zero terminate so we can use string functions */
        *(conn->rx_wr_pos+1) = 0;
      }
    }

    /*
     * When the quit command is received, update our connection state so that
     * we can exit the while() loop and close the connection
     */
    conn->state = conn->close ? CLOSE : READY;

    /* Manage buffer */
    data_used = conn->rx_rd_pos - conn->rx_buffer;
    memmove(conn->rx_buffer, conn->rx_rd_pos,
       conn->rx_wr_pos - conn->rx_rd_pos);
    conn->rx_rd_pos = conn->rx_buffer;
    conn->rx_wr_pos -= data_used;
    memset(conn->rx_wr_pos, 0, data_used);
  }

  printf("[sss_handle_receive] closing connection\n");
  close(conn->fd);
  sss_reset_connection(conn);

  return;
}

/*
 * SSSSimpleSocketServerTask()
 *
 * This MicroC/OS-II thread spins forever after first establishing a listening
 * socket for our sss connection, binding it, and listening. Once setup,
 * it perpetually waits for incoming data to either the listening socket, or
 * (if a connection is active), the sss data socket. When data arrives,
 * the approrpriate routine is called to either accept/reject a connection
 * request, or process incoming data.
 */

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

void SSSSimpleSocketServerTask()
{

	// ���������� ������������ ����������
	  ...

	  // ������������ ���������� ���������� �� ������
	  init_button_pio();

	  while (1)
	  {
		  // ������� �����, ���� �� ������� �������, ������ ��������� � �������

		  // �������������� ��������� sockaddr_in, ������ ��������� �������,
	  // IP-����� � ����� ����� ���������� ����������
	  // (��� ������� ��. simple_socket_server)

		  // ������������� ���������� � ��������
		  errcode = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
		  if (errcode)
		  {
			  printf("Unable to connect to server!\n");
			  return -1;
		  }

		  // �������� ���� �� �������, ������� � �������

		  is_alive = 1;
		  do
		  {
			  // ������� ��������� � ������� ������ �� ����������� ����������

			  // ���������� ��������������� ������� �� ������

			  // ���� ���� ���������� ������� 'q', ������� �� �����������
	  // �����

			  // � ��������� ������ �������� ����� �� �������, ������� ���
	  // � �������

		  }
		  while (is_alive);

		  // ��������� ����������
		  ...
		  printf("Connection closed.\n");

		  // ������� ��������� � ������� ������ �� ����������� ����������
		  // ����� ��������� ������������� ����������
		  �
	  } /* while (1) */

	}



}



/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2009 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/

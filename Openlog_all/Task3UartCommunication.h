#ifndef _UART_COMMUNICATION_H
#define _UART_COMMUNICATION_H

void uart_send_char(char data);
void uart_send_str(char str[], int len);
void init_uart(void);
void send_data(void);
void echo_data(void);
void uart_communication(void);

#endif

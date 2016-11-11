#include "wiced.h"

void sendData(unsigned int pos1, unsigned int pos2)
{
	static wiced_ip_address_t serverAddress;

    SET_IPV4_ADDRESS( serverAddress, MAKE_IPV4_ADDRESS( 198,51,  100,  3 ) );
	char sendMessage[5];
	wiced_tcp_socket_t socket;
	wiced_packet_t* tx_packet;
    uint8_t *tx_data;
    uint16_t available_data_length;

    sprintf(sendMessage,"%02X%02X",pos1,pos2);
	WPRINT_APP_INFO(("Sent Message=%s\n",sendMessage));

	wiced_tcp_create_socket(&socket, WICED_STA_INTERFACE);
	wiced_tcp_bind(&socket,WICED_ANY_PORT);
	wiced_tcp_connect(&socket,&serverAddress,40508,2000); // 2 second timeout

	wiced_packet_create_tcp(&socket, strlen(sendMessage), &tx_packet, (uint8_t**)&tx_data, &available_data_length); // get a packet
    memcpy(tx_data, sendMessage, strlen(sendMessage)); // put our data in the packet
    wiced_packet_set_data_end(tx_packet, (uint8_t*)&tx_data[strlen(sendMessage)]); // set the end of the packet
    wiced_tcp_send_packet(&socket, tx_packet);
    wiced_packet_delete(tx_packet);

    wiced_tcp_delete_socket(&socket);
}

void application_start(void)
{
    wiced_init( );
    wiced_network_up( WICED_STA_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL );
	wiced_result_t result;

    const wiced_i2c_device_t i2cDevice = {
    	.port = WICED_I2C_1,
		.address = 0x08,
		.address_width = I2C_ADDRESS_WIDTH_7BIT,
		.speed_mode = I2C_STANDARD_SPEED_MODE
    };

    result = wiced_i2c_init(&i2cDevice);
    uint8_t rx_buffer[] = {0,0};
    wiced_i2c_message_t msg;
    result = wiced_i2c_init_rx_message(&msg, rx_buffer, sizeof(rx_buffer), 1, 0);


    uint8_t prev_pos1=0xFF,prev_pos2=0xFF;
	while(1)
	{
	    result = wiced_i2c_transfer(&i2cDevice, &msg, 1);
	    if(rx_buffer[0] != prev_pos1 || rx_buffer[1] != prev_pos2)
	    {
	    	sendData(rx_buffer[0],rx_buffer[1]);
	    }
	    prev_pos1 = rx_buffer[0];
	    prev_pos2 = rx_buffer[1];

		wiced_rtos_delay_milliseconds(50);
	}
}

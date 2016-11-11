#include "wiced.h"

static const wiced_ip_setting_t sta_ip_settings =
{
    INITIALISER_IPV4_ADDRESS( .ip_address, MAKE_IPV4_ADDRESS( 198,51,  100,  3 ) ),
    INITIALISER_IPV4_ADDRESS( .netmask,    MAKE_IPV4_ADDRESS( 255,255,255,  0 ) ),
    INITIALISER_IPV4_ADDRESS( .gateway,    MAKE_IPV4_ADDRESS( 198,51,  100,  1 ) ),
};

void application_start(void)
{
    wiced_result_t result;
    wiced_init( );
    wiced_network_up( WICED_STA_INTERFACE, WICED_USE_STATIC_IP, &sta_ip_settings );

    const wiced_i2c_device_t i2cDevice = {
    	.port = WICED_I2C_1,
		.address = 8,
		.address_width = I2C_ADDRESS_WIDTH_7BIT,
		.speed_mode = I2C_STANDARD_SPEED_MODE
    };

    wiced_i2c_init(&i2cDevice);
    uint8_t tx_buffer[] = {0, 50, 50};
    wiced_i2c_message_t msg;
    wiced_i2c_init_tx_message(&msg, tx_buffer, sizeof(tx_buffer), 1, 0);

    wiced_tcp_socket_t socket;
    result = wiced_tcp_create_socket(&socket, WICED_STA_INTERFACE);
	result = wiced_tcp_listen( &socket, 40508 );

    while (1 )
    {
        result = wiced_tcp_accept( &socket ); // this halts the thread until there is a connection
        if(result != WICED_SUCCESS) // this occurs if the accept times out
            continue;

        uint16_t        request_length, available_data_length;
        wiced_packet_t* temp_packet = NULL;
        uint8_t *rbuffer;
        uint32_t pos1,pos2;

        if(WICED_SUCCESS == wiced_tcp_receive( &socket, &temp_packet, WICED_WAIT_FOREVER ))
        {
        	wiced_packet_get_data( temp_packet, 0, (uint8_t**) &rbuffer, &request_length, &available_data_length );
        	sscanf(rbuffer,"%2x%2x",(unsigned int *)&pos1,(unsigned int *)&pos2);
        	tx_buffer[1] = pos1;
        	tx_buffer[2] = pos2;

        	wiced_packet_delete( temp_packet ); // free the packet
        	WPRINT_APP_INFO(("Pos1=%x Pos2=%x\n",pos1,pos2));
        	wiced_i2c_transfer(&i2cDevice, &msg, 1);
        }
    }
 }


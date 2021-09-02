#include "i2c_bus.h"

bool i2c_do_transaction(i2c_bus_message_t *message)
{
	/* send start */
	if (!message->bus->start_fn(message->device_address))
	{
		return false;
	}

	/* read or write */
	if (message->write)
	{
		if (!message->bus->write_fn(message->payload, message->payload_size))
		{
			return false;
		}
	}
	else
	{
		if (!message->bus->read_fn(message->payload, message->payload_size))
		{
			return false;
		}
	}

	/* send stop */
	if (!message->bus->stop_fn())
	{
		return false;
	}

	return true;
}

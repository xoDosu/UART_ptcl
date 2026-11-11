 What is UART?

UART (Universal Asynchronous Receiver / Transmitter) is a communication protocol that allows for communication between two devices. There is only two wires between these two devices, namely receiver and transmitter in both directions. Both ends also have a ground connection. Communication between these two devices can be simplex (data is sent in one direction only), half-duplex (each side speaks but only one at a time), or full duplex (both devices can communicate simultaneously). One of the biggest advantages of UART is that it is asynchronous - the transmitter and the receiver do not share a common clock signal. Since they do not have a common clock, both ends must transmit  the same pre determined speed in order to have the same bit timings. The most common baud rates are 4800, 9600, 19.2k, 57.6k and 1175.2k. Both ends must also have the same frame structure and parameters  


Example:
If we want to send the capital letter “S” in 7-bit ASCII, the bit sequence is 1 0 1 0 0 1 1. We first reverse the order of the bits to put them in least significant bit order, that is 1 1 0 0 1 0 1, before sending them out. After the last data bit is sent, the stop bit is used to end the frame and the line returns to the idle state 




In our case:

- The two systems are trying to interact with each other mostly from the pi to the esp32, the PI lets the ESP32 know if to avoid an object, walk towards it or if it can interact with it.
- The ESP32 sends back sensor readings, status, and acknoledgements.
- It can also detect foreign object and let the system know to hold back until it has gained further information on what is in front of it 
- 9 bytes each 
- heart beat that sends every 9m to check if the PI is working.



If the PI sees something it recognises, nothing much is done with it except avoidance. Essentially the PI becomes the brain of the whole operation, while the ESP32 proceeds with the actions. Message type are:

- avoid() - 117
- kick() - 155
- hold() - 123
- dance() - 111
- approach() - 156

The above fit into the byte 2 


- direction - centre is 128 sits in byte 3 
- start - 7 - byte 1 
- confidence - certainty of the object 4 
- 5-8 are unassigned
- 9 is checksum - XOR of bytes 1 - 8. A flipped bit, a 1 where a 0 was sent or the reverse, is the right idea. Here’s the full mechanism:
The sender XORs bytes 1-8 together and puts the result in byte 9.
The receiver XORs the same bytes itself and compares with byte 9.
If they differ, the message got corrupted, so the receiver throws it away. At 10 messages a second, losing one costs nothing.




`receive_byte` takes in the new byte **and a pointer to an output buffer** that the caller owns. It returns 1 only when a valid message has just been completed, and copies it into that buffer. Reasons:

- No shared global, so no clash when several FreeRTOS tasks run.
- It’s easy to test: you feed it bytes and read the output buffer.
- It doesn’t know about the hardware, so the same code runs on your laptop test and the ESP32.







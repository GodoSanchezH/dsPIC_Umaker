import serial
import time

uart_dspic = serial.Serial("COM4",115200,timeout=1)

while(True) :
	if(uart_dspic.inWaiting()>0):
		dato_rx = uart_dspic.read(size=4)
		uart_dspic.write('c'.encode( 'utf-8'))
		print("\nADC:",dato_rx.decode())

			
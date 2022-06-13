#include "mbed.h"
#include "rtos.h"
#include "thread_serial.h"
#include "thread_PWM.h"

// main() runs in its own thread in the OS
int main()
{
    BufferedSerial serial_PC(USBTX,USBRX,9600);

    thread_PWM PWM_thread(PA_0, PA_5, PA_6, PA_7);
    // output_pin_, encoder_A_, encoder_B_, encoder_Z_
    
    thread_serial serial_thread(&serial_PC);
    PWM_thread.set_mail(&serial_thread.mail_count);
    serial_thread.start();

    while (true) {
        PWM_thread.get_count();
        ThisThread::sleep_for(50ms);
    }
}

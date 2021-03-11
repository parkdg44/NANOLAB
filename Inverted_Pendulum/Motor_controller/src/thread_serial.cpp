#include "thread_serial.h"
#include <stdlib.h>

thread_serial::thread_serial(BufferedSerial *target) { serial = target; }

thread_serial::~thread_serial()
{
    this->thread.terminate();
}

void thread_serial::start()
{
    this->thread.start(callback(thread_serial::thread_handle,this));
}

int a = 0;

void thread_serial::thread_handle(thread_serial *thread) {
  char buffer[30] = "";

  while (1) {
    long *count = thread->mail_count.try_get();

    if (count != nullptr) {
      a++;
      sprintf(buffer, "count : %ld  %d \n", *count, a);
      thread->mail_count.free(count);

      thread->serial->write(buffer, sizeof(buffer));
    }

    ThisThread::sleep_for(10ms);
  }
}
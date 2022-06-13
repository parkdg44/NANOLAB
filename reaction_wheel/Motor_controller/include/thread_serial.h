#include "mbed.h"
#include "list"
#include "functional"

using namespace std;

class thread_serial
{
public:
  thread_serial(BufferedSerial *target);
  void start(thread_encoder *target);
  ~thread_serial();
  Mail<long, 10> mail_count;
    
private:
  BufferedSerial *serial;
  Thread thread;
  static void thread_handle(thread_encoder *thread);  
};
#include "mbed.h"
#include "list"
#include "functional"

using namespace std;

class thread_PWM {
public:
  thread_PWM(PinName output_pin_, PinName encoder_A, PinName encoder_B,
             PinName encoder_Z);
  ~thread_PWM();
  long get_count();
  void set_mail(Mail<long, 10>* mail_);
  InterruptIn intA, intB, intZ;
  PinName output_pin, encoder_A, encoder_B, encoder_Z;
  long count;

private:
  Thread thread;
  Mail<long, 10>* mail_count;
  static void thread_handle(thread_PWM *tareget);
  static void encoder_count(PinName pin_A, PinName pin_B, long &count);
  static void update_Encoder(thread_PWM* target);
  static void update_Encoder_init(thread_PWM *target);
  static void encoder_init(thread_PWM *target);
};
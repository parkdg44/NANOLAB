#include "thread_PWM.h"

thread_PWM::thread_PWM(PinName output_pin_, PinName encoder_A_, PinName encoder_B_, PinName encoder_Z_)
    : intA(encoder_A_), intB(encoder_B_), intZ(encoder_Z_)
{
    output_pin = output_pin_;
    encoder_A = encoder_A_;
    encoder_B = encoder_B_;
    encoder_Z = encoder_Z_;

    intA.rise(callback(thread_PWM::update_Encoder,this));
    intA.fall(callback(thread_PWM::update_Encoder,this));
    //intZ.rise(callback(thread_PWM::encoder_init,this));
}

void thread_PWM::set_mail(Mail<long, 10>* mail_)
{
    mail_count = mail_;
}

void thread_PWM::thread_handle(thread_PWM* target)
{

}

// ------------------------------------- encoder ----------------------------------- //

void thread_PWM::update_Encoder(thread_PWM *target) {
  int a = target->intA.read();
  int b = target->intB.read();

  if (a) {
    (b == 0) ? target->count++ : target->count--;
  }
  else {
    (b == 1) ? target->count++ : target->count--;
  }
  /*
  angle_M = encoderpos_Motor % 400 * MOTOR_TO_RAD + PI;
  if (angle_M > PI) angle_M -= 2 * PI;
  if (angle_M < -PI) angle_M += 2 * PI;
  */
}

void thread_PWM::encoder_init(thread_PWM *target)
{
    if (target->intZ.read())
    {
        target->count = 0;
    }
}

long thread_PWM::get_count()
{   
    long *target = new long(count); 
    if(!mail_count->full()) 
    {
        mail_count->put(target);    
    }
    
    else  {
        while(!mail_count->empty()){
            delete mail_count->try_get();
        }        
        delete target;
    }
    return count;
}

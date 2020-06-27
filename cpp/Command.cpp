#include<iostream>
using namespace std;

class Command {
public:
  virtual void execute() = 0;
};


class Light {
public:
  Light(){}

  void on() {
    cout<<"Light is on"<<endl;
  }

  void off() {
    cout<<"Light is off"<<endl;
  }
};

  
class LightOnCommand : public Command {
private:
  Light *light;


public:

  LightOnCommand(Light * light) {
    this->light = light;
  }
  
  void execute()
  {
    light->on();
  }
};


class SimpleRemoteControl{
private:
  Command *slot;
public:
  
  SimpleRemoteControl() {}

  void setCommand(Command * command)
  {
    slot = command;
  }

  void buttonWasPressed() {
    slot->execute();
  }
};


int main()
{
  SimpleRemoteControl * remote = new SimpleRemoteControl();

  Light * light = new Light();

  LightOnCommand * lightOn = new LightOnCommand(light);

  remote->setCommand(lightOn);
  remote->buttonWasPressed();
}

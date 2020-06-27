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

class GarageDoor{
public:
  GarageDoor(){}
  void up() {cout<<"Garage Door up!"<<endl;}
  void down() {cout<<"Garage Door down !" << endl;}
  void stop() { cout<<"Garage Door stop !" << endl;}
  void lightOn() {cout<<"Garage Door Light on"<<endl;}
  void lightOff() { cout<<"Garage Door Light off"<<endl;}
};
class GarageDoorOpenCommand : public Command{
public:
  GarageDoor * garageDoor;

  GarageDoorOpenCommand(GarageDoor * garageDoor)
  {
    this->garageDoor = garageDoor;
  }

  void execute() {
    this->garageDoor->up();
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
  GarageDoor * garageDoor = new GarageDoor();
  GarageDoorOpenCommand * garageOpen = new GarageDoorOpenCommand(garageDoor);

  remote->setCommand(lightOn);
  remote->buttonWasPressed();
  remote->setCommand(garageOpen);
  remote->buttonWasPressed();
}

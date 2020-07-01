#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Command {
public:
  virtual void execute() = 0;
  virtual void undo() = 0;
};


class Light {
private:
  string type;
public:
  Light(string type){ this->type = type;}

  void on() {
    cout<<"Light is on"<<endl;
  }

  void off() {
    cout<<"Light is off"<<endl;
  }
};

class Stereo{
private:
  int volume;
public:
  Stereo(){}
  
  void on(){
    cout<<"Stereo is on"<<endl;
  }  
  void off() {
    cout<<"Stereo is off"<<endl;  
  }
  void setCd()
  { cout<<"set cd"<<endl;}

  void setDvd() { cout<<"set dvd"<<endl;}

  void setRadio() {
  cout<<"set radio"<<endl;
  }

  void setVolume(int volume) 
  {
     this->volume = volume;
     cout<<"set volume"<<endl;
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
  void undo()
  {
    light->off();
  }
};

class LightOffCommand : public Command{
private:
  Light *light;
public:
  LightOffCommand(Light *light)
  {
    this->light = light;
  }

  void execute() {
    light->off();
  }
  void undo() {
    light->on();
  }
};

class StereoOnWithCDCommand : public Command{
private:
  Stereo *stereo;
public:
  StereoOnWithCDCommand(Stereo *stereo)
  {
    this->stereo = stereo;
  }

  void execute() {
    stereo->on();
    stereo->setCd();
    stereo->setVolume(11);
  }
  void undo(){} 
};

class StereoOffCommand : public Command{
private:
  Stereo *stereo;
public:
  StereoOffCommand(Stereo *stereo)
  { 
    this->stereo = stereo;
  }
  void execute(){
    stereo->off();
  }
  void undo(){}
};

class CeilingFan{
  public:
    static const int HIGH = 3;
    static const int MEDIUM = 2;
    static const int LOW = 1;
    static const int OFF = 0;
private:
  string location;
  int speed;
public:
  CeilingFan(string location) {
  this->location = location;
  speed = OFF;
}  

  void high() {
    speed = HIGH;
    // code to set fan to high  
  }
  void medium() {
    speed = MEDIUM;
  }
  void low() {
    speed = LOW;
  }

  void off (){
    speed = OFF;
  }
  int getSpeed(){
    return speed;
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

class CeilingFanHighCommand : public Command{
  CeilingFan * ceilingFan;
  int prevSpeed;
  
public:
  CeilingFanHighCommand(CeilingFan * ceilingFan) {
  this->ceilingFan = ceilingFan; 
}

  void execute() {
    prevSpeed = ceilingFan->getSpeed();
    ceilingFan->high();
  }
  void undo() {
    if(prevSpeed == CeilingFan::HIGH) {
      ceilingFan->high();
    }
    else if ( prevSpeed == CeilingFan::MEDIUM) {
      ceilingFan->medium();
    }
    else if (prevSpeed == CeilingFan::LOW) {
      ceilingFan->low();
    }
    else if ( prevSpeed == CeilingFan::OFF) {
      ceilingFan->off();
    }
  }
};


  
class NoCommand : public Command{
public:
  void execute(){}
  void undo(){}
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

class RemoteControlWithUndo{
private:
  vector<Command*> onCommands;
  vector<Command*> offCommands;
  Command * undoCommand;

public:
  friend ostream& operator<<(ostream &, const RemoteControlWithUndo &);
  RemoteControlWithUndo() {
    onCommands = vector<Command*>(7,nullptr);
    offCommands = vector<Command*>(7,nullptr);

    Command * noCommand = new NoCommand();
    for(int i = 0 ; i < 7 ; i++)
    {
      onCommands[i] = noCommand;
      offCommands[i]  = noCommand;
    }
    undoCommand = noCommand;
  }

  void setCommand(int slot, Command *onCommand,Command *offCommand)
  {
    onCommands[slot] = onCommand;
    offCommands[slot] = offCommand;
  }
  
  void onButtonWasPushed(int slot) {
    onCommands[slot]->execute();
    undoCommand = onCommands[slot];
  }

  void offButtonWasPushed(int slot){
    offCommands[slot]->execute();
    undoCommand = offCommands[slot];
  }
  void undoButtonWasPushed() {
    undoCommand->undo();
  }
};

ostream& operator<<(std::ostream &strm, const RemoteControlWithUndo &remote)
{
  string stringbuf ="";
  stringbuf += "\n----- Remote Control -------\n";

  for(int i = 0 ; i < remote.onCommands.size() ; i++)
  {
    stringbuf += "[slot ";
    stringbuf += to_string(i);
    stringbuf += "]";
  }
  return strm<<stringbuf;
}
int main()
{
  RemoteControlWithUndo *remoteControl = new RemoteControlWithUndo();

  Light * livingRoomLight = new Light("Living Room");
  Light * kitchenLight = new Light("Kitchen");  
  GarageDoor *garageDoor = new GarageDoor();

  Stereo * stereo = new Stereo();

  LightOnCommand * livingRoomLightOn = new LightOnCommand(livingRoomLight);
  LightOffCommand * livingRoomLightOff = new LightOffCommand(livingRoomLight);
  
  LightOnCommand * kitchenLightOn = new LightOnCommand(kitchenLight);
  LightOffCommand * kitchenLightOff = new LightOffCommand(kitchenLight);

  StereoOnWithCDCommand *stereoOnWithCD = new StereoOnWithCDCommand(stereo);
  StereoOffCommand *stereoOff = new StereoOffCommand(stereo); 

  remoteControl->setCommand(0,livingRoomLightOn,livingRoomLightOff);
  remoteControl->setCommand(1,kitchenLightOn,kitchenLightOff);
  remoteControl->setCommand(2,stereoOnWithCD,stereoOff);

  
  
  remoteControl->onButtonWasPushed(0);
  remoteControl->offButtonWasPushed(0);
  cout<<remoteControl<<endl;
  remoteControl->undoButtonWasPushed();
  remoteControl->offButtonWasPushed(0);
  remoteControl->onButtonWasPushed(0);
  cout<<remoteControl<<endl;
  remoteControl->undoButtonWasPushed();  
}

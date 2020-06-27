#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Command {
public:
  virtual void execute() = 0;
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

class NoCommand : public Command{
public:
  void execute(){}
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

class RemoteControl{
private:
  vector<Command*> onCommands;
  vector<Command*> offCommands;
public:
  friend ostream& operator<<(ostream &, const RemoteControl &);
  RemoteControl() {
    onCommands = vector<Command*>(7,nullptr);
    offCommands = vector<Command*>(7,nullptr);

    Command * noCommand = new NoCommand();
    for(int i = 0 ; i < 7 ; i++)
    {
      onCommands[i] = noCommand;
      offCommands[i]  = noCommand;
    }

  }

  void setCommand(int slot, Command *onCommand,Command *offCommand)
  {
    onCommands[slot] = onCommand;
    offCommands[slot] = offCommand;
  }
  
  void onButtonWasPushed(int slot) {
    onCommands[slot]->execute();
  }

  void offButtonWasPushed(int slot){
    offCommands[slot]->execute();
  }
};

ostream& operator<<(std::ostream &strm, const RemoteControl &remote)
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
  RemoteControl *remoteControl = new RemoteControl();

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

  
  cout<<remoteControl<<endl;
  
  remoteControl->onButtonWasPushed(0);

  remoteControl->onButtonWasPushed(1);
  remoteControl->onButtonWasPushed(2);


  remoteControl->offButtonWasPushed(0);
  remoteControl->offButtonWasPushed(1);
  remoteControl->offButtonWasPushed(2);
}

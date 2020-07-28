#include<iostream>
#include<list>
#include<string>
class Observer {
public:
  virtual void update(float temp, float humidity, float pressure) = 0;
};

class Subject{
public:

  virtual void registerObserver(Observer * o)= 0;
  virtual void removeObserver(Observer * o) = 0;
  virtual void notifyObservers() = 0;
};
class DisplayElement {
public:
  virtual void display() = 0;
};

class WeatherData : public Subject {
private:
  std::list<Observer*> observers;
  // instance variable declarations
  //
  float temperature;
  float humidity;
  float pressure;
public:

  void registerObserver(Observer * o) {
    this->observers.push_back(o);
  }

  void removeObserver(Observer * o) {
    this->observers.remove(o);
  }
  
  void notifyObservers() {
    for (auto observer: observers) {
      observer->update(temperature, humidity, pressure);
    }
  }
  void measurementsChanged() {
    notifyObservers();
  }

  void setMeasurements(float temperature, float humidity, float pressure) {
    this->temperature = temperature;
    this->humidity = humidity;
    this->pressure = pressure;
    measurementsChanged();
  }

  // other weatherData methods.

};

class CurrentConditionsDisplay :public Observer, public DisplayElement {
private:
  float temperature;
  float humidity;
  Subject * weatherData;
public:
  friend std::ostream& operator<<(std::ostream &, const CurrentConditionsDisplay &);
  CurrentConditionsDisplay(Subject * weatherData) {
    this->weatherData = weatherData;
    weatherData->registerObserver(this);
  }

  void update(float temperature, float humidity, float pressure) {
    this->temperature = temperature;
    this->humidity = humidity;
    display();
  }
  void display() {
     
  std::string stringbuf ="";
  stringbuf = "Current conditions: " + std::to_string(temperature) + " F degress and " \
  + std::to_string(humidity) + "% humidity";
  std::cout<<stringbuf;
  }
};


std::ostream& operator<<(std::ostream &strm, const CurrentConditionsDisplay &remote)
{
  std::string stringbuf ="";
  stringbuf = "Current conditions: " + std::to_string(remote.temperature) + " F degress and " \
  + std::to_string(remote.humidity) + "% humidity";
  return strm<<stringbuf;
}


int main() {
  WeatherData * weatherData = new WeatherData();
  
  CurrentConditionsDisplay *currentDisplay = new CurrentConditionsDisplay(weatherData);

  weatherData->setMeasurements(80, 65, 30.4f);
  return 0;
}

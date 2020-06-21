import abc



class Subject:
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def registerObserver(self,o):
        pass
    @abc.abstractmethod
    def removeObserver(self,o):
        pass
    @abc.abstractmethod
    def notifyObserver(self,o):
        pass



class Observer:
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def update(self,temp,humidity,pressure):
        pass

class DisplayElement:
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def display(self):
        pass


class WeatherData(Subject):
    def __init__(self):
        self.observers = []
        self.temperature = None
        self.humidity = None
        self.pressure = None
    def registerObserver(self,o):
        self.observers.append(o)
    def removeObserver(self,o):
        try:
            self.observers.pop(self.observers.index(3))
        except ValueError:
            print("observer {} is not in the list"%(o))
    def notifyObserver(self):
        for observer in self.observers:
            observer.update(self.temperature,self.humidity,self.pressure)
    def measurementsChanged(self):
        self.notifyObserver()
    def setMeasurements(self,temperature,humidity,pressure):
        self.temperature = temperature
        self.humidity = humidity
        self.pressure = pressure
        self.measurementsChanged()
    
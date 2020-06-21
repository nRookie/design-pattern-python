import abc


class Subject:
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def registerObserver(self, o):
        pass

    @abc.abstractmethod
    def removeObserver(self, o):
        pass

    @abc.abstractmethod
    def notifyObserver(self, o):
        pass


class Observer:
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def update(self, temp, humidity, pressure):
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

    def registerObserver(self, o):
        self.observers.append(o)

    def removeObserver(self, o):
        try:
            self.observers.pop(self.observers.index(3))
        except ValueError:
            print("observer {} is not in the list" % (o))

    def notifyObserver(self):
        for observer in self.observers:
            observer.update(self.temperature, self.humidity, self.pressure)

    def measurementsChanged(self):
        self.notifyObserver()

    def setMeasurements(self, temperature, humidity, pressure):
        self.temperature = temperature
        self.humidity = humidity
        self.pressure = pressure
        self.measurementsChanged()


class CurrentConditionsDisplay(Observer, DisplayElement):
    def __init__(self, weatherData):
        self.temperature = None
        self.humidity = None
        self.weatherData = weatherData
        weatherData.registerObserver(self)

    def update(self, temperature, humidity, pressure):
        self.temperature = temperature
        self.humidity = humidity
        self.display()

    def display(self):
        print("Current conditions:{0} F degrees and {1} humidity".format(self.temperature, self.humidity))


if __name__ == '__main__':
    weatherData = WeatherData()
    currentConditionsDisplay = CurrentConditionsDisplay(weatherData)
    #StatisticsDisplay statisticsDisplay = new StatisticsDisplay(weatherData)
    #ForecastDisplay forecastDisplay = new ForecastDisplay(weatherData)

    weatherData.setMeasurements(80, 65, 30.4)
    weatherData.setMeasurements(82, 70, 29.2)
    weatherData.setMeasurements(78, 90, 29.2)
import abc

class Beverage:
    __metaclass__= abc.ABCMeta

    def __init__(self):
        self.description = "Unknown Beverage"

    def getDescription(self):
        return self.description

    @abc.abstractmethod
    def cost(self):
        pass

class CondimentDecorator(Beverage):
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def getDescription(self):
        pass

class Espresso(Beverage):
    def __init__(self):
        self.description = "Espresso"

    def cost(self):
        return 1.99

class HouseBlend(Beverage):
    def __init__(self):
        self.description = "House Blend Coffee"

    def cost(self):
        return .89


class Mocha(CondimentDecorator):

    def __init__(self,beverage):
        self.beverage = beverage

    def getDescription(self):
        return self.beverage.getDescription() + ",Mocha"

    def cost(self):
        return .20 + self.beverage.cost()



if __name__ == "__main__":
    beverage = Beverage()

    print("%s $ %s"% (beverage.getDescription(),beverage.cost()))

    beverage2 = Espresso()
    beverage2 = Mocha(beverage2)
    beverage2 = Mocha(beverage2)

    print("%s $ %s"% (beverage2.getDescription(),beverage2.cost()))
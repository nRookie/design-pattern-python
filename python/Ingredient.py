import abc


class PizzaIngredientFactory:
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def createDough(self):
        pass

    @abc.abstractmethod
    def createSauce(self):
        pass

    @abc.abstractmethod
    def createCheese(self):
        pass

    @abc.abstractmethod
    def createVeggies(self):
        pass

    @abc.abstractmethod
    def createPepperoni(self):
        pass

    @abc.abstractmethod
    def createClam(self):
        pass


class NYPizzaIngredientFactory(PizzaIngredientFactory):
    def createDough(self):
        return ThinCrustDough()

    def createSauce(self):
        return MarinaraSauce()

    def createCheese(self):
        return ReggianoCheese()

    def createVeggies(self):
        veggies = [Garlic(),Onion(),Mushroom(),RedPepper()]
        return veggies

    def createClam(self):
        return FreshClams()


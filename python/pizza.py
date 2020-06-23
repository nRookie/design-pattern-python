import abc


class SimplePizzaFactory:

    def __init__(self, type):
        self.pizza = None
        if type == "cheese":
            self.pizza = CheesePizza()
        elif type == "pepperoni":
            self.pizza = PepperoniPizza()
        elif type == "clam":
            self.pizza = ClamPizza()
        elif type == "veggie":
            self.pizza = VeggiePizza()


class PizzaStore:
    __metaclass__ = abc.ABCMeta

    def __init__(self, factory):
        pass
        # self.factory = factory

    @abc.abstractmethod
    def createPizza(self, type):
        pass

    def orderPizza(self, type):
        self.pizza = None
        # Notice that we've replaced the new operator with a create method
        # No more concrete instantiation here!
        pizza = self.createPizza(type)
        # pizza = self.factory.createPizza(type)
        pizza.prepare()
        pizza.bake()
        pizza.cut()
        pizza.box()
        return pizza


class NYPizzaStore(PizzaStore):

    def __init__(self):
        pass

    def _createPizza(self, item):
        pizza = None
        ingredientFactory = NYPizzaIngredientFactory()

        if item == "cheese":
            pizza = CheesePizza(ingredientFactory)
            pizza.setName("New York Style Cheese Pizza")
        elif item == "veggie":
            pizza = VeggiePizza(ingredientFactory)
            pizza.setName("New York Style Veggie Pizza")
        elif item == "clams":
            pizza = ClamPizza(ingredientFactory)
            pizza.setName("New York Style Clam Pizza")
        elif item == "pepperoni":
            pizza = PepperoniPizza(ingredientFactory)
            pizza.setName("New York Style Pepperoni Pizza")
        return pizza


class Pizza:
    __metaclass__ = abc.ABCMeta

    def __init__(self):
        self.name = None
        self.dough = None
        self.sauce = None
        self.toppings = []
        self.veggies = []
        self.cheese = None
        self.pepperoni = None
        self.Clams = None

    @abc.abstractmethod
    def prepare(self):
        pass
        # print("preparing %s" % (self.name))
        # print("Tossing dough...")
        # print("Adding sauce")
        # print("Adding toppings: ")

        # for topping in self.toppings:
        #     print("  %s" % (topping))

    def bake(self):
        print("Bake for 25 minutes at 350")

    def cut(self):
        print("Cutting the pizza into diagonal slices")

    def box(self):
        print(" Place pizza in official PizzaStore box")

    def setName(self, name):
        self.name = name

    def getName(self):
        return self.name


class NYStyleCheesePizza(Pizza):
    def __init__(self):
        super(NYStyleCheesePizza, self).__init__()
        self.name = "NY Style Sauce and Cheese Pizza"
        self.dough = "Thin crust dough"
        self.sauce = "Marinara Sauce"

        self.toppings.append("Grated Reggiano Cheese")


class ChicagoStyleCheesePizza(Pizza):
    def __init__(self):
        super(ChicagoStyleCheesePizza, self).__init__()
        self.name = "Chicago Style Deep Dish Cheese Pizza"
        self.dough = "Extra Thick Crust Dough"
        self.sauce = "Plum Tomato Sauce"

        self.toppings.append("Shredded Mozzarella Cheese")

    def cut(self):
        print("Cutting the pizza into square slices")


if __name__ == "__main__":
    nyStore = NYPizzaStore()

    pizza = nyStore.orderPizza("cheese")
    print("Ethan ordered a %s \n" % (pizza.getName()))


class CheesePizza(Pizza):
    def __init__(self, ingredientFactory):
        self.ingredientFactory = ingredientFactory

    def prepare(self):
        print("Preparing " + self.name)
        self.dough = self.ingredientFactory.createDough()
        self.sauce = self.ingredientFactory.createSauce()
        self.cheese = self.ingredientFactory.createCheese()


class ClamPizza(Pizza):
    def __init__(self, ingredientFactory):
        self.ingredientFactory = ingredientFactory

    def prepare(self):
        print("Preparing " + self.name)
        self.dough = self.ingredientFactory.createDough()
        self.sauce = self.ingredientFactory.createSauce()
        self.cheese = self.ingredientFactory.createCheese()
        self.clam = self.ingredientFactory.createClam()

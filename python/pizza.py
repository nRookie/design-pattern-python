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
            self.pizza = VeggiePizza();



class PizzaStore:
    __metaclass__ = abc.ABCMeta
    def __init__(self, factory):
        pass
        #self.factory = factory

    @abc.abstractmethod
    def createPizza(self, type):
        pass
    def orderPizza(self, type):
        self.pizza = None
        #Notice that we've replaced the new operator with a create method
        #No more concrete instantiation here!
        pizza = self.createPizza(type)
        #pizza = self.factory.createPizza(type)
        pizza.prepare()
        pizza.bake()
        pizza.cut()
        pizza.box()
        return pizza

class NYPizzaStore(PizzaStore):

    def __init__(self):
        pass

    def createPizza(self, item):
        if item == "cheese":
            return NYStyleCheesePizza()
        elif item == "pepperoni":
            return NYStylePepperoniPizza()
        elif item == "clam":
            return  NYStyleClamPizza()
        elif item == "veggie":
            return  NYStyleVeggiePizza()
        else:
            return None


class Pizza:
    __metaclass__ = abc.ABCMeta


    def __init__(self):
        self.name = None
        self.dough = None
        self.sauce = None
        self.toppings = []

    def prepare(self):
        print("preparing %s"%(self.name))
        print("Tossing dough...")
        print("Adding sauce")
        print("Adding toppings: ")

        for topping in self.toppings:
            print("  %s"%(topping))

    def bake(self):
        print("Bake for 25 minutes at 350")
    def cut(self):
        print("Cutting the pizza into diagonal slices")
    def box(self):
        print(" Place pizza in official PizzaStore box")
    def getName(self):
        return self.name

class NYStyleCheesePizza(Pizza):
    def __init__(self):
        super(NYStyleCheesePizza,self).__init__()
        self.name = "NY Style Sauce and Cheese Pizza"
        self.dough = "Thin crust dough"
        self.sauce = "Marinara Sauce"

        self.toppings.append("Grated Reggiano Cheese")

class ChicagoStyleCheesePizza(Pizza):
    def __init__(self):
        super(ChicagoStyleCheesePizza,self).__init__()
        self.name = "Chicago Style Deep Dish Cheese Pizza"
        self.dough = "Extra Thick Crust Dough"
        self.sauce = "Plum Tomato Sauce"

        self.toppings.append("Shredded Mozzarella Cheese")

    def cut(self):
        print("Cutting the pizza into square slices")





if __name__ == "__main__":
    nyStore = NYPizzaStore()

    pizza = nyStore.orderPizza("cheese")
    print("Ethan ordered a %s \n"%(pizza.getName()))

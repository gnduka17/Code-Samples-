#this class represents a single menu item on the menu
class MenuItem(object):
    def __init__(self, nameparam, typeparam, priceparam, descripparam):
        self.name = nameparam
        self.type = typeparam
        self.price = priceparam
        self.description = descripparam

    #the getter functions for name, type, price, and description
    def getName(self):
        return self.name
    def getType(self):
        return self.type
    def getPrice(self):
        return self.price
    def getDescription(self):
        return  self.description

    # the setter functions for name, type, price, and description
    def setName(self, newName):
        self.name=newName
    def setType(self, newType):
        self.type=newType
    def setPrice(self, newPrice):
        self.price=newPrice
    def setDescription(self, newDescrip):
        self.description=newDescrip

    #return message with all the attributes
    def __str__(self):
        return self.name + " (" + self.type + "): " + str(self.price) + "\n\t" + self.description



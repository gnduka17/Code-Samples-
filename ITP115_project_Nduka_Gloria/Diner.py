from MenuItem import MenuItem

#class represents one of the diners and keeps tracks of their status and meal

class Diner(object):
    #static variable-list of diner status
    STATUSES = ["seated", "ordering", "eating", "paying", "leaving"]
    DINING_SPEED = ["hurried", "normal", "slow"]

    #constructor of a diner-name, order, status,progress,and speed
    def __init__(self, dinernameparam, diningspeedparam):
        self.name = dinernameparam
        self.order=[]
        self.status=0
        self.progress=diningspeedparam
        self.diningSpeed=diningspeedparam
    #accessor methods
    def getName(self):
        return self.name
    def getOrder(self):
        return self.order
    def getStatus(self):
        return self.status
    def getProgress(self):
        return self.progress
    def getDiningSpeed(self):
        return self.diningSpeed

    #setter methods
    def setName(self, newname):
        self.name=newname
    def setOrder(self, neworder):
        self.order=neworder
    def setStatus(self, newstatus):
        self.status=newstatus
    def setProgress(self, newprog):
        self.progress=newprog
    def setDiningSpeed(self, newspeed):
        self.diningSpeed=newspeed

    #increase diner status by one
    def updateStatus(self):
        self.status+=1

    #add diner new menu item to end of list of menu items for that diner
    def addToOrder(self,  menuitemobj):
        self.order.append(menuitemobj)

    #print the order of the diner
    def printOrder(self):
        print(self.name,"ordered:")
        for item in self.order:
            print("-", item)

    #calculates the total cost of what the diner ordered
    #returns a float
    def calculateMealCost(self):
        sum=0.0
        for item in self.order:
            sum+=item.getPrice()
        return sum

    #outputs message containing diner's name, status, and speed
    #returns string
    def __str__(self):
        return "Diner "+ self.name + " is dining at a "+Diner.DINING_SPEED[self.diningSpeed]+" speed and is currently "+ Diner.STATUSES[self.status]

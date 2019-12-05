from Menu import Menu
from Diner import Diner

#this class will represent the restaurant's waiter
class Waiter(object):
    #constructor -waiter's diners and the menu
    def __init__(self, menuobj):
        self.diners=[]
        self.menu = menuobj
    #add diner to list of waiter's diners
    def addDiner(self, dinerobj):
        self.diners.append(dinerobj)
    #return the number of diners the waiter keeps track of
    def getNumDiners(self):
        return len(self.diners)
    #print the diners the waiter is keeping track of based on diner status
    def printDinerStatuses(self):
        #lists of diners with certain statuses
        seatedlist=[]
        orderinglist=[]
        eatinglist=[]
        payinglist=[]
        leavinglist=[]

        #iterate through diners and place them in appropriate list
        for people in self.diners:
            if people.getStatus()==0:
                seatedlist.append(people)
            elif people.getStatus()==1:
                orderinglist.append(people)
            elif people.getStatus() == 2:
                eatinglist.append(people)
            elif people.getStatus() == 3:
                payinglist.append(people)
            elif people.getStatus() == 4:
                leavinglist.append(people)

        #prints diners and groups them based on statuses; if list is empty then don't iterate through it
        print("Diners who are seated:")
        if len(seatedlist) !=0:
            for item in seatedlist:
                print("\t", item)
        print("Diners who are ordering:")
        if len(orderinglist) !=0:
            for item2 in orderinglist:
                print("\t", item2)
        print("Diners who are eating:")
        if len(eatinglist) !=0:
            for item3 in eatinglist:
                print("\t", item3)
        print("Diners who are paying:")
        if len(payinglist) !=0:
            for item4 in payinglist:
                print("\t", item4)
        print("Diners who are leaving:")
        if len(leavinglist) !=0:
            for item5 in leavinglist:
                print("\t", item5)

    #taking the diner's order
    def takeOrders(self):
        # iterate through diners
        for people in self.diners:
            #if diner is ordering and has -1 progress then continue
            if people.getStatus() == 1:
                if people.getProgress()==-1:
                    #print drinks items
                    self.menu.printMenuItemsByType("Drink")
                    drinknum = int(input("\n"+people.getName()+", please select a Drink menu item number.\n>"))
                    #error checking
                    while drinknum > self.menu.getNumMenuItemsByType("Drink")-1 or drinknum<0:
                        print("Error: Invalid option, try again")
                        drinknum = int(input(">"))

                    #add item to diner
                    people.addToOrder(self.menu.getMenuItem("Drink", drinknum))

                    #print appetizer items
                    self.menu.printMenuItemsByType("Appetizer")
                    appetnum = int(input("\n"+people.getName() + ", please select a Appetizer menu item number.\n>"))

                    #error checking
                    while appetnum >= self.menu.getNumMenuItemsByType("Appetizer") or appetnum < 0:
                        print("Error: Invalid option, try again")
                        appetnum = int(input(">"))

                    # add item to diner
                    people.addToOrder(self.menu.getMenuItem("Appetizer", appetnum))

                    #print entree items
                    self.menu.printMenuItemsByType("Entree")
                    entreenum = int(input("\n"+people.getName() + ", please select a Entree menu item number.\n>"))

                    #error checking
                    while entreenum >= self.menu.getNumMenuItemsByType("Entree") or entreenum < 0:
                        print("Error: Invalid option, try again")
                        entreenum = int(input(">"))

                    # add item to diner
                    people.addToOrder(self.menu.getMenuItem("Entree", entreenum))

                    #print dessert items
                    self.menu.printMenuItemsByType("Dessert")
                    dessertnum = int(input("\n"+people.getName() + ", please select a Dessert menu item number.\n>"))

                    #error checking
                    while dessertnum >= self.menu.getNumMenuItemsByType("Dessert") or dessertnum < 0:
                        print("Error: Invalid option, try again")
                        dessertnum = int(input(">"))

                    # add item to diner
                    people.addToOrder(self.menu.getMenuItem("Dessert", dessertnum))

                    #prints diner's order
                    people.printOrder()

    #calculate the diners meal cost if they are paying and has -1 progress
    def ringUpDiners(self):
        for people in self.diners:
            if people.getStatus()==3:
                if people.getProgress()==-1:
                    print("\n\n"+people.getName()+", your meal cost $"+ str(people.calculateMealCost()))


    #if diner is leaving then remove them and output message
    def removeDoneDiners(self):
        for people in self.diners:
            if people.getStatus()==4:
                print("\n\n"+people.getName()+",thank you for dining with us! Come again soon!")
        #removes diner from waiter's list of diners
        for  x  in range(self.getNumDiners()-1, -1, -1):
            if self.diners[x].getStatus()==4:
                self.diners.remove(self.diners[x])

    #allows waiters to attend diners at their various stages and move diners onto the next stage
    def advanceDiners(self):
        self.printDinerStatuses()
        self.removeDoneDiners()
        for person in self.diners:
            person.setProgress(person.getProgress()-1)
            if person.getProgress()==-1:
                self.takeOrders()
                self.ringUpDiners()
                person.updateStatus()
                person.setProgress(person.getDiningSpeed())

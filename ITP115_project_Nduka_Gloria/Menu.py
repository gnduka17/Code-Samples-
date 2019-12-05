from MenuItem import MenuItem

#class represents the menu at the restaurant with 4 different categories

class Menu(object):
    #class variable-list of food types
    MENU_ITEM_TYPES = ["Drink", "Appetizer", "Entree", "Dessert"]

    def __init__(self,menuitemfile):
        self.menuItemDictionary={}
        filein = open(menuitemfile,"r")
        #taking info from csv file and inputting it in dictionary with key as type and value as list of menuitem objects
        for line in filein:
            line =line.strip()
            datalist=line.split(",")
            Fooditem = MenuItem(datalist[0], datalist[1], float(datalist[2]), datalist[3])
            if datalist[1] not in self.menuItemDictionary:
                MenuItemlist = [Fooditem]
                self.menuItemDictionary[datalist[1]]=MenuItemlist
            else:
                self.menuItemDictionary[datalist[1]].append(Fooditem)
        filein.close()

    #retrieves a specific menu item
    #return menuitem obj
    def getMenuItem(self,typeitem,indexpos):
        word = Menu.MENU_ITEM_TYPES[Menu.MENU_ITEM_TYPES.index(typeitem)]
        return self.menuItemDictionary[word][indexpos]

    #print menu items based on the type
    def printMenuItemsByType(self, typeitem):
        word = Menu.MENU_ITEM_TYPES[Menu.MENU_ITEM_TYPES.index(typeitem)]
        print("\n-----"+word+"-----")
        for obj in self.menuItemDictionary[word]:
            print(str(self.menuItemDictionary[word].index(obj))+")", end=' ')
            print(obj)

    #gets the amount of items for a specific type
    #returns integer - number of menuitems  of type
    def getNumMenuItemsByType(self, typeitem):
        word = Menu.MENU_ITEM_TYPES[Menu.MENU_ITEM_TYPES.index(typeitem)]
        return len(self.menuItemDictionary[word])






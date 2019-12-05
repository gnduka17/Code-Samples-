package nduka_CSCI201_Assignment1;

import java.util.Scanner;
import java.util.ArrayList;
import java.io.FileNotFoundException;
import java.util.InputMismatchException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.PatternSyntaxException;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.util.Collections;
import java.util.Comparator;

//This is the sorting comparator class...helps with sorting my arraylist of contacts 
class ContactsOrganizerComp implements Comparator<Person>{
    public int compare(Person p1, Person p2) {
        if(p1.getLName().toLowerCase().compareTo(p2.getLName().toLowerCase())>0){
            return 1;
        } else if(p1.getLName().toLowerCase().compareTo(p2.getLName().toLowerCase())==0){
        	if(p1.getFName().toLowerCase().compareTo(p2.getFName().toLowerCase())>0) {
        		return 1;
        	}
        	else {
        		return -1;
        	}
        }
        else {
        	return -1;
        }
    }
}
public class holder {
	//This method checks if the email inserted and in the input file are correct emails
	public static boolean correctEmail(String input, ArrayList<String> listOfEmails) {
		String com = ".com";
		String edu = ".edu";
		String net = ".net";
		char atSym = '@';
		Integer atIndex = 0;
		//if empty string return false 
		if(input.length()==0) {
			return false;
		}
		//if there's a space then return false
		if(input.contains(" ")) {
			return false;
		}
		//email should be greater than 7 characters 
		if(input.length()>=7) {
			//check if last part is either .com, .net, .edu
			if(com.toLowerCase().compareTo(input.substring(input.length()-4).toLowerCase())==0) {
				//check if @ isn't next to the "."
				if(!(input.charAt(input.length()-5)==atSym)){
					//check if the at symbol is not at the beginning of the email
					if(input.charAt(0)!=atSym) {
						//trying to find which index is the @ symbol to see if the words before and after it are valid 
						for(Integer i =0;i<input.length();i++) {
							if(input.charAt(i)==atSym) {
								atIndex = i;
								break;
							}
						}
						//checking if the words before and after @ are valid 
						if(correctNameFormat(input.substring(0,atIndex)) && correctNameFormat(input.substring(atIndex+1,input.length()-4))) {
							//checking to see if email already exists
							for(Integer i = 0; i<listOfEmails.size();i++) {
								if(listOfEmails.get(i).toLowerCase().compareTo(input.toLowerCase())==0) {
									return false;	
								}
							}
							return true;
						}
						
					}
				}
			}
			else if(edu.toLowerCase().compareTo(input.substring(input.length()-4).toLowerCase())==0) {
				if(!(input.charAt(input.length()-5)==atSym)){
					if(input.charAt(0)!=atSym) {
						for(Integer i =0;i<input.length();i++) {
							if(input.charAt(i)==atSym) {
								atIndex = i;
								break;
							}
						}
						if(correctNameFormat(input.substring(0,atIndex)) && correctNameFormat(input.substring(atIndex+1,input.length()-4))) {
							for(Integer i = 0; i<listOfEmails.size();i++) {
								if(listOfEmails.get(i).toLowerCase().compareTo(input.toLowerCase())==0) {
									return false;	
								}
							}
							return true;
						}
					}
				}	
			}
			else if(net.toLowerCase().compareTo(input.substring(input.length()-4).toLowerCase())==0) {
				if(!(input.charAt(input.length()-5)==atSym)){
					if(input.charAt(0)!=atSym) {
						for(Integer i =0;i<input.length();i++) {
							if(input.charAt(i)==atSym) {
								atIndex = i;
								break;
							}
						}
						if(correctNameFormat(input.substring(0,atIndex)) && correctNameFormat(input.substring(atIndex+1,input.length()-4))) {
							for(Integer i = 0; i<listOfEmails.size();i++) {
								if(listOfEmails.get(i).toLowerCase().compareTo(input.toLowerCase())==0) {
									return false;	
								}
							}
							return true;
						}
					}
				}	
			}
		}
		return false;
	}
	//Function that prints the menu
	public static void printMenu() {
		System.out.println("\n1. Contact Look Up");
		System.out.println("2. Add Contact");
		System.out.println("3. Delete Contact");
		System.out.println("4. Print to a File");
		System.out.println("5. Exit\n");
	}
	//checks if the names/word are in the correct format
	public static boolean correctNameFormat(String input) {
		input= input.replaceAll("\\s+","");
		return input.matches("[a-zA-Z]+");
	}
	//checks if boolean is in the correct format
	public static boolean correctBool(String input) {
		if(input.equalsIgnoreCase("false")) {
			return true;
		}
		else if(input.equalsIgnoreCase("true")) {
			return true;
		}
		return false;
	}

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		String userInputFile ="";
		String realuserInputFile ="";
		String fileLine = "";
		String userFname = "";
		String userLname = "";
		String userEmail = "";
		String ageholder = ""; 
		String wordholderNotes = "";
		Integer userAge = null;
		boolean userNearCamp;
		Integer count =0;
		//lists to hold notes of a contact, emails, and the contacts class
		ArrayList<String> userNotes = new ArrayList<String>();
		ArrayList<Person> peopleContacts = new ArrayList<Person>();
		ArrayList<String> emailList = new ArrayList<String>();
		boolean success = false;
		while(!success){
			try {
				System.out.print("What is the name of the contacts file?");
				userInputFile = input.nextLine();
				realuserInputFile = userInputFile.replaceAll("\\s+","");
				//opens file and reads it 
				BufferedReader reader = new BufferedReader(new FileReader(realuserInputFile));
				while((fileLine=reader.readLine())!=null) {
					if(fileLine.trim().length()>0) {
						String [] splitArray = fileLine.split(",");
						if(splitArray.length<6) {
							System.out.println("\nThis file "+userInputFile+" is not formatted properly.\n");
							System.out.println("Too few parameters on the line: ");
							System.out.println("\""+fileLine+"\"\n");
							success = false;
							break;
						}
						else {
							//parsing each item in each line and assigns it to a variable
							if(correctNameFormat(splitArray[0].trim())) {
								userFname = splitArray[0].trim();
								if(correctNameFormat(splitArray[1].trim())) {
									userLname = splitArray[1].trim();
									if(correctEmail(splitArray[2].trim(), emailList)) {
										userEmail = splitArray[2].trim();
										ageholder = splitArray[3].trim();
										userAge = Integer.parseInt(ageholder); 
										if(correctBool(splitArray[4].trim())) {
											userNearCamp = Boolean.parseBoolean(splitArray[4]);	
											//placing notes into an arraylist
											for(Integer i=0; i<splitArray.length-5;i++) {
												wordholderNotes = splitArray[i+5].trim();
												count=0;
												if(wordholderNotes.length() == 0){
													count++;
													System.out.println("Data cannot be converted to the proper type as shown above.\nThere is an empty note which is invalid.\n");
													success = false; 
													break;
												}
												else {
													userNotes.add(wordholderNotes);
												}
											}
											if(count>0) {
												break;
											}
											//create a Person then add to Array List 
											Person addPerson = new Person(userFname, userLname, userEmail, userAge, userNearCamp, userNotes);
											userNotes.clear();
											peopleContacts.add(addPerson);
											emailList.add(userEmail); 
											success=true;
										}
										else {
											System.out.println("The file "+userInputFile+" is not formatted properly.");
											System.out.println("The parameter \""+splitArray[4]+"\" is not a valid boolean.\n");
											success = false;
											break;	
										}
									}
									else {
										System.out.println("The file "+userInputFile+" is not formatted properly.");
										System.out.println("The parameter \""+splitArray[2]+"\" cannot be parsed as an email.\n");
										success = false;
										break;
									}
								}
								else {
									System.out.println("The file "+userInputFile+" is not formatted properly.");
									System.out.println("The parameter \""+splitArray[1]+"\" is not a valid last name.\n");
									success = false;
									break;
								}
							}
							else {
								System.out.println("The file "+userInputFile+" is not formatted properly.");
								System.out.println("The parameter \""+splitArray[0]+"\" is not a valid first name.\n");
								success = false;
								break;
							}
						}
						
					}
				}
				//sort the arraylist and close the buffer reader
				Collections.sort(peopleContacts, new ContactsOrganizerComp()); 
				reader.close();	
			}
			catch(InputMismatchException e) {
				System.out.println("That is not a valid option.\n");
			}
			catch(NumberFormatException e) {
				System.out.println("Data cannot be converted to the proper type. Age should be an integer.\n");
				success = false;
			}
			catch(FileNotFoundException e) {
				System.out.println("The file "+ userInputFile+" could not be found.\n");
				success = false;
			}
			catch(IOException e) {
				System.out.println("That is not a valid option.\n");
				success = false;
			}
			catch(PatternSyntaxException e) {
				System.out.println("File is not formatted correctly using commas.\n");
				success = false;
			}
		}
		Integer num = null;
		printMenu();
		success = false;
		while(!success) {
			try {
				System.out.print("\nWhat option would you like to select? ");
				String userInput = input.nextLine();
				if(userInput.equals("EXIT")) {
					num = 5;
					success = true;
				}
				else {
					num = Integer.parseInt(userInput);
					if(num>5) {
						throw new InputMismatchException();
					}
					else if(num<1) {
						throw new InputMismatchException();
					}
					else {
						success = true;
					}
					
				}
			}
			catch(InputMismatchException e) {
				System.out.println("That is not a valid option.");
				success = false;
			}
			catch(NumberFormatException e) {
				System.out.println("That is not a valid option.");
				success = false;
			}
		}
		while(num!=5) {
			//contact look up 
			if(num==1) {
				System.out.print("Enter the contact's last name: ");
				String inputName = input.nextLine();
				Integer counter = 0;
				//Find the person with that name and output their info
				//iterate thru list and use the findlastName
					//if true then print that person info
					//if false continue searching thru...if count is 0 
					//then output There is no one with that name. 
				for(Integer i = 0; i <peopleContacts.size();i++) {
					if(peopleContacts.get(i).findLastName(inputName)) {
						counter++;
						peopleContacts.get(i).printPersonInfo();
					}
				}
				if(counter==0) {
					System.out.println("There is no one with the last name "+ inputName+" in your contact book.");
				}
			}
			//add contact
			else if(num==2) {
				String addFname = null;
				String addLname = null;
				String addEmail = null;
				String stringaddAge = null;
				Integer addAge = 0;
				boolean addNearCamp = false;
				String addNote = null;
				boolean newsuccess = false;
				while(!newsuccess) {
					try {
						//adding first name and checking if it's a valid first name
						System.out.print("\nWhat is the first name of your new contact? ");
						addFname = input.nextLine();
						if(!correctNameFormat(addFname)) {
							throw new Exception();
						}
						newsuccess = true;
					}
					catch(InputMismatchException e) {
						System.out.println("That is not a valid input.");
						
					}
					catch(Exception e) {
						System.out.println("That is not a valid name. It should only contain letters and spaces.");
			
					}
					
				}
				newsuccess = false;
				while(!newsuccess) {
					try {
						//adding first name and checking if it's a valid first name
						System.out.print("\nWhat is the last name of your new contact? ");
						addLname = input.nextLine();
						if(!correctNameFormat(addLname)) {
							throw new Exception();
						}
						newsuccess = true;
					}
					catch(InputMismatchException e) {
						System.out.println("That is not a valid input.");
					}
					catch(Exception e) {
						System.out.println("That is not a valid name. It should only contain letters and spaces.");
			
					}
				}
				newsuccess = false;
				while(!newsuccess) {
					try {
						//adding email and checking if its a valid email and if it doesnt already exists 
						System.out.print("\nWhat is the email of your new contact? ");
						addEmail = input.nextLine();
						if(!(correctEmail(addEmail, emailList))) {
							throw new Exception();
						}
						newsuccess = true;
					}
					catch(InputMismatchException e) {
						System.out.println("That is not a valid input.");
						
					}
					catch(Exception e) {
						System.out.println("That is not a valid email. An email must have this formatting: xxx@yyy.com or email already exists.");
					}
				}
				newsuccess = false;
				while(!newsuccess) {
					try {
						//adding age 
						System.out.print("\nWhat is the age of your new contact? ");
						stringaddAge = input.nextLine();
						addAge = Integer.parseInt(stringaddAge);
						newsuccess = true;
					}
					catch(InputMismatchException e) {
						System.out.println("That is not a valid input.");
						newsuccess =false;
					}
					catch(NumberFormatException e) {
						System.out.println("That is not a valid input.");
						newsuccess =false;
					}
				}
				newsuccess = false;
				while(!newsuccess) {
					try {
						//adding if they live near campus 
						System.out.print("\nDoes your new contact live near campus? ");
						String addbool = input.nextLine();
						if(addbool.equalsIgnoreCase("Yes")) {
							addNearCamp = true;
							newsuccess = true;
						}
						else if(addbool.equalsIgnoreCase("True")) {
							addNearCamp = true;
							newsuccess = true;
						}
						else if(addbool.equalsIgnoreCase("No")) {
							addNearCamp = false;
							newsuccess = true;
						}
						else if(addbool.equalsIgnoreCase("false")) {
							addNearCamp = false;
							newsuccess = true;
						}
						else {
							throw new InputMismatchException();
						}
						
					}
					catch(InputMismatchException e) {
						System.out.println("That is not a valid input.");
						
					}
				}
				ArrayList<String> noteHolder = new ArrayList<String>();
				try {
					//adding notes then prompting user if they want to add an additional note 
					System.out.print("\nAdd a note about your new contact: ");
					addNote = input.nextLine();	
					noteHolder.add(addNote);
					System.out.print("\nDo you want to add another note? ");
					String userAnswer = input.nextLine();
					while((!userAnswer.equalsIgnoreCase("Yes")) && (!userAnswer.equalsIgnoreCase("No"))) {
						System.out.println("That is not a valid input. Enter Yes or No.");
						System.out.print("\nDo you want to add another note? ");
						userAnswer = input.nextLine();
					}
					while(userAnswer.equalsIgnoreCase("Yes")) {
						System.out.print("\nAdd a note about your new contact: ");
						addNote = input.nextLine();	
						noteHolder.add(addNote);
						System.out.print("\nDo you want to add another note? ");
						userAnswer = input.nextLine();
						//check this one!
						while((!userAnswer.equalsIgnoreCase("Yes")) && (!userAnswer.equalsIgnoreCase("No"))) {
							System.out.println("That is not a valid input. Enter Yes or No.");
							System.out.print("\nDo you want to add another note? ");
							userAnswer = input.nextLine();
						}
					}
					Person addNewPerson = new Person(addFname, addLname, addEmail, addAge, addNearCamp, noteHolder);
					emailList.add(addEmail);
					peopleContacts.add(addNewPerson);
					System.out.println(addFname + " "+ addLname +" has been added to your contact list.");
					Collections.sort(peopleContacts, new ContactsOrganizerComp()); 
				}
				catch(InputMismatchException e) {
					System.out.println("That is not a valid input.");	
				}
			}
			//deleting a contact
			else if(num==3) {
				success = false;
				while(!success) {
					System.out.print("\nEnter the email of the contact you would like to delete: ");
					String removeEmail = input.nextLine();
					Integer counter = 0;
					Person deletePer;
					String holderFname = "";
					String holderLname = "";
					if(peopleContacts.size()==0) {
						counter++;
						System.out.println("No contacts to delete.");
						success = true;
					}
					for(Integer i = 0; i <peopleContacts.size();i++) {
						if(peopleContacts.get(i).findEmail(removeEmail)) {
							counter++;
							holderFname = peopleContacts.get(i).getFName();
							holderLname = peopleContacts.get(i).getLName();
							//delete their info and in email list
							deletePer = peopleContacts.get(i);
							deletePer=null;
							peopleContacts.remove(peopleContacts.get(i));
							emailList.remove(emailList.get(i));
							System.out.println(holderFname+ " "+holderLname+" was successfully deleted from your contact list.");
							success = true;
							break;
						}
					}
					if(counter==0) {
						System.out.println(removeEmail+" does not exist in your contact list.");
						success = false;
					}
				}
			}
			//printing to a file
			else if(num==4) {
				System.out.print("\nEnter the name of the file that you would like to print your contact list to: ");
				String outputFile = input.nextLine();
				try {
					//writing out to a file using buffered writer 
					BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile));
					for(Integer i =0; i<peopleContacts.size();i++) {
						writer.write(peopleContacts.get(i).personInfoString());
					}
					writer.close();
				}catch(IOException e) {
					System.out.print("Invalid filename input");	
				}
				System.out.println("Successfully printed all your contacts to ");
			}
			printMenu();
			success = false;
			while(!success) {
				try {
					System.out.print("\nWhat option would you like to select? ");
					String userInput = input.nextLine();
					if(userInput.equals("EXIT")) {
						num = 5;
						success = true;
					}
					else {
						num = Integer.parseInt(userInput);
						if(num>5) {
							throw new InputMismatchException();
						}
						else if(num<1) {
							throw new InputMismatchException();
						}
						else {
							success = true;
						}
						
					}
				}
				catch(InputMismatchException e) {
					System.out.println("That is not a valid option.");
					success = false;
				}
				catch(NumberFormatException e) {
					System.out.println("That is not a valid option.");
					success = false;
				}
			}
			
		}
		//if num is 5 or they enter EXIT then program has ended 7
		System.out.print("\nThank you for using my contacts program. Goodbye!");
		input.close();
	}

}

//package nduka_CSCI201_Assignment1;
//
//import java.util.Scanner;
//import java.util.ArrayList;
//import java.io.FileNotFoundException;
//import java.util.InputMismatchException;
//import java.io.BufferedReader;
//import java.io.FileReader;
//import java.io.IOException;
//import java.util.regex.PatternSyntaxException;
//import java.io.FileWriter;
//import java.io.BufferedWriter;
//
//public class ContactsBook {
//	public static boolean correctEmail(String input, ArrayList<String> listOfEmails) {
//		String com = ".com";
//		String edu = ".edu";
//		String net = ".net";
//		char atSym = '@';
//		Integer atIndex = 0;
//		if(input.equals(null)) {
//			return false;
//		}
//		if(input.contains(" ")) {
//			return false;
//		}
//		
//		if(input.length()>=7) {
//			if(com.equalsIgnoreCase(input.substring(input.length()-4))) {
//				if(!(input.charAt(input.length()-5)==atSym)){
//					if(input.charAt(0)!=atSym) {
//						for(Integer i =0;i<input.length();i++) {
//							if(input.charAt(i)==atSym) {
//								atIndex = i;
//								break;
//							}
//						}
//						
//						if(correctNameFormat(input.substring(0,atIndex)) && correctNameFormat(input.substring(atIndex+1,input.length()-4))) {
//							if(!(listOfEmails.contains(input))){
//								return true;
//							}
//							
//						}
//						
//					}
//				}
//			}
//			else if(edu.equalsIgnoreCase(input.substring(input.length()-4))) {
//				if(!(input.charAt(input.length()-5)==atSym)){
//					if(input.charAt(0)!=atSym) {
//						for(Integer i =0;i<input.length();i++) {
//							if(input.charAt(i)==atSym) {
//								atIndex = i;
//								break;
//							}
//						}
//						if(correctNameFormat(input.substring(0,atIndex)) && correctNameFormat(input.substring(atIndex+1,input.length()-4))) {
//							if(!(listOfEmails.contains(input))){
//								return true;
//							}
//							
//						}
//					}
//				}	
//			}
//			else if(net.equalsIgnoreCase(input.substring(input.length()-4))) {
//				if(!(input.charAt(input.length()-5)==atSym)){
//					if(input.charAt(0)!=atSym) {
//						for(Integer i =0;i<input.length();i++) {
//							if(input.charAt(i)==atSym) {
//								atIndex = i;
//								break;
//							}
//						}
//						if(correctNameFormat(input.substring(0,atIndex)) && correctNameFormat(input.substring(atIndex+1,input.length()-4))) {
//							if(!(listOfEmails.contains(input))){
//								return true;
//							}
//							
//						}
//					}
//				}	
//			}
//		}
//		return false;
//	}
//	public static void printMenu() {
//		System.out.println("\n1. Contact Look Up");
//		System.out.println("2. Add Contact");
//		System.out.println("3. Delete Contact");
//		System.out.println("4. Print to a File");
//		System.out.println("5. Exit\n");
//	}
//	public static boolean correctNameFormat(String input) {
//		input= input.replaceAll("\\s+","");
//		return input.matches("[a-zA-Z]+");
//	}
//	public static boolean correctBool(String input) {
//		if(input.equalsIgnoreCase("false")) {
//			return true;
//		}
//		else if(input.equalsIgnoreCase("true")) {
//			return true;
//		}
//		return false;
//	}
//
//	public static void main(String[] args) {
//		Scanner input = new Scanner(System.in);
//		String userInputFile ="";
//		String realuserInputFile ="";
//		String fileLine = "";
//		String userFname = "";
//		String userLname = "";
//		String userEmail = "";
//		String ageholder = ""; 
//		String wordholderNotes = "";
//		Integer userAge = null;
//		boolean userNearCamp;
//		Integer count =0;
//		ArrayList<String> userNotes = new ArrayList<String>();
//		ArrayList<Person> peopleContacts = new ArrayList<Person>();
//		ArrayList<String> emailList = new ArrayList<String>();
//		boolean success = false;
//		while(!success) {
//			try {
//				System.out.print("What is the name of the contacts file? ");
//				userInputFile = input.nextLine();
//				realuserInputFile = userInputFile.replaceAll("\\s+","");
//				 BufferedReader reader = new BufferedReader(new FileReader(realuserInputFile));
//				//what if there's no lines
//				while((fileLine=reader.readLine())!=null) {
//					if(fileLine.trim().length()>0) {
//						String [] splitArray = fileLine.split(",");
//						if(splitArray.length<6) {
//							System.out.println("\nThis file "+userInputFile+" is not formatted properly.\n");
//							System.out.println("Too few parameters on the line: ");
//							System.out.println("\""+fileLine+"\"\n");
//							success = false;
//							break;
//						}
//						else {
//							if(correctNameFormat(splitArray[0].trim())) {
//								userFname = splitArray[0].trim();
//								if(correctNameFormat(splitArray[1].trim())) {
//									userLname = splitArray[1].trim();
//									if(correctEmail(splitArray[2].trim(), emailList)) {
//										userEmail = splitArray[2].trim();
//										ageholder = splitArray[3].trim();
//										userAge = Integer.parseInt(ageholder);
//										//userAge = Integer.parseInt(splitArray[3]); 
//										if(correctBool(splitArray[4].trim())) {
//											userNearCamp = Boolean.parseBoolean(splitArray[4]);	
//											for(Integer i=0; i<splitArray.length-5;i++) {
//												wordholderNotes = splitArray[i+5].trim();
//												count =0;
//												System.out.println("word: " + wordholderNotes);
//												if(wordholderNotes.length() == 0){
//													count++;
//													System.out.println("Data cannot be converted to the proper type as shown above.\nThere is an empty note which is invalid.\n");
//													success = false; 
//													break;
//												}
//												else {
//													userNotes.add(wordholderNotes);
//												}
//											}
//											if(count>0) {
//												break;
//											}
//											Person addPerson = new Person(userFname, userLname, userEmail, userAge, userNearCamp, userNotes);
//											userNotes.clear();
//											if(peopleContacts.size()==0) {
//												emailList.add(userEmail);
//												peopleContacts.add(addPerson);
//												System.out.println("here1");
//											}else {
//												peopleContacts.add(addPerson);
////												for(Integer i = 0; i<peopleContacts.size(); i++) {
////													if(addPerson.getLName().compareTo(peopleContacts.get(i).getLName())>0 && i==peopleContacts.size()-1) {
////														peopleContacts.add(addPerson);
////														emailList.add(addPerson.getEmail());
////														System.out.println("here2");
////														break;
////													}
////													else if(addPerson.getLName().compareTo(peopleContacts.get(i).getLName())>0 && addPerson.getLName().compareTo(peopleContacts.get(i+1).getLName())<0) {
////														peopleContacts.add(i+1, addPerson);
////														emailList.add(i+1, addPerson.getEmail());
////														System.out.println("here3");
////														break;
////													}
////													else if(addPerson.getLName().compareTo(peopleContacts.get(i).getLName())==0) {
////														//If the last name is the same then compare the first name at that same index. then compare the first to 
////														//the next cell
////														if(addPerson.getFName().compareTo(peopleContacts.get(i).getFName())>0 && i==peopleContacts.size()-1) {
////															peopleContacts.add(addPerson);
////															emailList.add(addPerson.getEmail());
////															System.out.println("here4");
////															break;
////														}
////														else if(addPerson.getFName().compareTo(peopleContacts.get(i).getFName())<0 && i==0) {
////															peopleContacts.add(0,addPerson);
////															emailList.add(0, addPerson.getEmail());
////															System.out.println("here5");
////															break;
////															
////														}
////														else if(addPerson.getFName().compareTo(peopleContacts.get(i).getFName())<0 && addPerson.getFName().compareTo(peopleContacts.get(i-1).getFName())<0) {
////															peopleContacts.add(i,addPerson);
////															emailList.add(i, addPerson.getEmail());
////															System.out.println("here6");
////															break;
////															
////														}
////														else if(addPerson.getFName().compareTo(peopleContacts.get(i).getFName())>0 && addPerson.getFName().compareTo(peopleContacts.get(i+1).getFName())<0) {
////															peopleContacts.add(i+1, addPerson);
////															emailList.add(i+1, addPerson.getEmail());
////															System.out.println("here7");
////															break;
////													
////														}
////														else {
////															System.out.println("no1");
////														}
////													}
////													else {
////														System.out.println("no2");
////													}
////												}
//											}
//											
//											success=true;
//										}
//										else {
//											System.out.println("The file "+userInputFile+" is not formatted properly.");
//											System.out.println("The parameter \""+splitArray[1]+"\" is not a valid boolean.\n");
//											success = false;
//											break;	
//										}
//									}
//									else {
//										System.out.println("The file "+userInputFile+" is not formatted properly.");
//										System.out.println("The parameter \""+splitArray[2]+"\" cannot be parsed as an email.\n");
//										success = false;
//										break;
//									}
//								}
//								else {
//									System.out.println("The file "+userInputFile+" is not formatted properly.");
//									System.out.println("The parameter \""+splitArray[1]+"\" is not a valid last name.\n");
//									success = false;
//									break;
//								}
//							}
//							else {
//								System.out.println("The file "+userInputFile+" is not formatted properly.");
//								System.out.println("The parameter \""+splitArray[0]+"\" is not a valid first name.\n");
//								success = false;
//								break;
//							}
//						}
//						
//					}
//				}
//				Collections.sort(peopleContacts); 
//				reader.close();	
//			}
//			catch(InputMismatchException e) {
//				System.out.println("That is not a valid option.\n");
//			}
//			catch(NumberFormatException e) {
//				System.out.println("Data cannot be converted to the proper type. Age should be an integer.\n");
//				success = false;
//			}
//			catch(FileNotFoundException e) {
//				System.out.println("The file "+ userInputFile+" could not be found.\n");
//				success = false;
//			}
//			catch(IOException e) {
//				System.out.println("That is not a valid option.\n");
//				success = false;
//			}
//			catch(PatternSyntaxException e) {
//				System.out.println("File is not formatted correctly using commas.\n");
//				success = false;
//			}
//		}
//		Integer num = null;
//		printMenu();
//		success = false;
//		while(!success) {
//			try {
//				System.out.print("\nWhat option would you like to select? ");
//				String userInput = input.nextLine();
//				if(userInput.equals("EXIT")) {
//					num = 5;
//					success = true;
//				}
//				else {
//					num = Integer.parseInt(userInput);
//					if(num>5) {
//						throw new InputMismatchException();
//					}
//					else if(num<1) {
//						throw new InputMismatchException();
//					}
//					else {
//						success = true;
//					}
//					
//				}
//			}
//			catch(InputMismatchException e) {
//				System.out.println("That is not a valid option.");
//				success = false;
//			}
//			catch(NumberFormatException e) {
//				System.out.println("That is not a valid option.");
//				success = false;
//			}
//		}
//		while(num!=5) {
//			if(num==1) {
//				System.out.print("Enter the contact's last name: ");
//				String inputName = input.nextLine();
//				Integer counter = 0;
//				//Find the person with that name and output their info
//				//iterate thru list and use the findlastName
//					//if true then print that person info
//					//if false continue searching thru...if count is 0 
//					//then output There is no one with that name. 
//				for(Integer i = 0; i <peopleContacts.size();i++) {
//					if(peopleContacts.get(i).findLastName(inputName)) {
//						counter++;
//						peopleContacts.get(i).printPersonInfo();
//					}
//				}
//				if(counter==0) {
//					System.out.println("There is no one with the last name "+ inputName+" in your contact book.");
//				}
//			}
//			else if(num==2) {
//				String addFname = null;
//				String addLname = null;
//				String addEmail = null;
//				String stringaddAge = null;
//				Integer addAge = 0;
//				boolean addNearCamp = false;
//				String addNote = null;
//				boolean newsuccess = false;
//				while(!newsuccess) {
//					try {
//						System.out.print("\nWhat is the first name of your new contact? ");
//						addFname = input.nextLine();
//						if(!correctNameFormat(addFname)) {
//							throw new Exception();
//						}
//						newsuccess = true;
//					}
//					catch(InputMismatchException e) {
//						System.out.println("That is not a valid input.");
//						
//					}
//					catch(Exception e) {
//						System.out.println("That is not a valid name. It should only contain letters and spaces.");
//			
//					}
//					
//				}
//				newsuccess = false;
//				while(!newsuccess) {
//					try {
//						System.out.print("\nWhat is the last name of your new contact? ");
//						addLname = input.nextLine();
//						if(!correctNameFormat(addLname)) {
//							throw new Exception();
//						}
//						newsuccess = true;
//					}
//					catch(InputMismatchException e) {
//						System.out.println("That is not a valid input.");
//						
//					}
//					catch(Exception e) {
//						System.out.println("That is not a valid name. It should only contain letters and spaces.");
//			
//					}
//				}
//				newsuccess = false;
//				while(!newsuccess) {
//					try {
//						System.out.print("\nWhat is the email of your new contact? ");
//						addEmail = input.nextLine();
//						if(!(correctEmail(addEmail, emailList))) {
//							throw new Exception();
//						}
//						newsuccess = true;
//					}
//					catch(InputMismatchException e) {
//						System.out.println("That is not a valid input.");
//						
//					}
//					catch(Exception e) {
//						System.out.println("That is not a valid email. An email must have this formatting: xxx@yyy.com or email already exists.");
//					}
//				}
//				newsuccess = false;
//				while(!newsuccess) {
//					try {
//						System.out.print("\nWhat is the age of your new contact? ");
//						stringaddAge = input.nextLine();
//						addAge = Integer.parseInt(stringaddAge);
//						newsuccess = true;
//					}
//					catch(InputMismatchException e) {
//						System.out.println("That is not a valid input.");
//						newsuccess =false;
//					}
//					catch(NumberFormatException e) {
//						System.out.println("That is not a valid input.");
//						newsuccess =false;
//					}
//				}
//				newsuccess = false;
//				while(!newsuccess) {
//					try {
//						System.out.print("\nDoes your new contact live near campus? ");
//						String addbool = input.nextLine();
//						if(addbool.equalsIgnoreCase("Yes")) {
//							addNearCamp = true;
//							newsuccess = true;
//						}
//						else if(addbool.equalsIgnoreCase("True")) {
//							addNearCamp = true;
//							newsuccess = true;
//						}
//						else if(addbool.equalsIgnoreCase("No")) {
//							addNearCamp = false;
//							newsuccess = true;
//						}
//						else if(addbool.equalsIgnoreCase("false")) {
//							addNearCamp = false;
//							newsuccess = true;
//						}
//						else {
//							throw new InputMismatchException();
//						}
//						
//					}
//					catch(InputMismatchException e) {
//						System.out.println("That is not a valid input.");
//						
//					}
//				}
//				ArrayList<String> noteHolder = new ArrayList<String>();
//				try {
//					System.out.print("\nAdd a note about your new contact: ");
//					addNote = input.nextLine();	
//					noteHolder.add(addNote);
//					System.out.print("\nDo you want to add another note? ");
//					String userAnswer = input.nextLine();
//					//check this one!
//					while((!userAnswer.equalsIgnoreCase("Yes")) && (!userAnswer.equalsIgnoreCase("No"))) {
//						System.out.println("That is not a valid input. Enter Yes or No.");
//						System.out.print("\nDo you want to add another note? ");
//						userAnswer = input.nextLine();
//					}
//					while(userAnswer.equalsIgnoreCase("Yes")) {
//						System.out.print("\nAdd a note about your new contact: ");
//						addNote = input.nextLine();	
//						noteHolder.add(addNote);
//						System.out.print("\nDo you want to add another note? ");
//						userAnswer = input.nextLine();
//						//check this one!
//						while((!userAnswer.equalsIgnoreCase("Yes")) && (!userAnswer.equalsIgnoreCase("No"))) {
//							System.out.println("That is not a valid input. Enter Yes or No.");
//							System.out.print("\nDo you want to add another note? ");
//							userAnswer = input.nextLine();
//						}
//					}
//					Person addNewPerson = new Person(addFname, addLname, addEmail, addAge, addNearCamp, noteHolder);
//					if(peopleContacts.size()<1) {
//						emailList.add(addEmail);
//						peopleContacts.add(addNewPerson);
//					}else {
//						for(Integer i = 0; i<peopleContacts.size(); i++) {
//							if(addNewPerson.getLName().compareTo(peopleContacts.get(i).getLName())>0 && i==peopleContacts.size()-1) {
//								peopleContacts.add(addNewPerson);
//								emailList.add(addNewPerson.getEmail());
//								break;
//							}
//							else if(addNewPerson.getLName().compareTo(peopleContacts.get(i).getLName())>0 && addNewPerson.getLName().compareTo(peopleContacts.get(i+1).getLName())<0) {
//								peopleContacts.add(i+1, addNewPerson);
//								emailList.add(i+1, addNewPerson.getEmail());
//								break;
//							}
//							else if(addNewPerson.getLName().compareTo(peopleContacts.get(i).getLName())==0) {
//								//If the last name is the same then compare the first name at that same index. then compare the first to 
//								//the next cell
//								if(addNewPerson.getFName().compareTo(peopleContacts.get(i).getFName())>0 && i==peopleContacts.size()-1) {
//									peopleContacts.add(addNewPerson);
//									emailList.add(addNewPerson.getEmail());
//									break;
//								}
//								else if(addNewPerson.getFName().compareTo(peopleContacts.get(i).getFName())<0 && i==0) {
//									peopleContacts.add(0,addNewPerson);
//									emailList.add(0, addNewPerson.getEmail());
//									break;
//									
//								}
//								else if(addNewPerson.getFName().compareTo(peopleContacts.get(i).getFName())<0 && addNewPerson.getFName().compareTo(peopleContacts.get(i-1).getFName())<0) {
//									peopleContacts.add(i,addNewPerson);
//									emailList.add(i, addNewPerson.getEmail());
//									break;
//									
//								}
//								else if(addNewPerson.getFName().compareTo(peopleContacts.get(i).getFName())>0 && addNewPerson.getFName().compareTo(peopleContacts.get(i+1).getFName())<0) {
//									peopleContacts.add(i+1, addNewPerson);
//									emailList.add(i+1, addNewPerson.getEmail());
//									break;
//							
//								}
//							}
//						}
//					}
//					
//					System.out.println(addFname + " "+ addLname +" has been added to your contact list.");
//				}
//				catch(InputMismatchException e) {
//					System.out.println("That is not a valid input.");	
//				}
//			}
//			else if(num==3) {
//				success = false;
//				while(!success) {
//					System.out.print("\nEnter the email of the contact you would like to delete: ");
//					String removeEmail = input.nextLine();
//					Integer counter = 0;
//					Person deletePer;
//					String holderFname = "";
//					String holderLname = "";
//					if(peopleContacts.size()==0) {
//						counter++;
//						System.out.println("No contacts to delete.");
//						success = true;
//					}
//					for(Integer i = 0; i <peopleContacts.size();i++) {
//						if(peopleContacts.get(i).findEmail(removeEmail)) {
//							counter++;
//							holderFname = peopleContacts.get(i).getFName();
//							holderLname = peopleContacts.get(i).getLName();
//							//delete their info and on email list
//							deletePer = peopleContacts.get(i);
//							deletePer=null;
//							peopleContacts.remove(peopleContacts.get(i));
//							emailList.remove(emailList.get(i));
//							System.out.println(holderFname+ " "+holderLname+" was successfully deleted from your contact list.");
//							success = true;
//							break;
//						}
//					}
//					if(counter==0) {
//						System.out.println(removeEmail+" does not exist in your contact list.");
//						success = false;
//					}
//					
//				}
//				
//				
//			}
//			else if(num==4) {
//				System.out.print("\nEnter the name of the file that you would like to print your contact list to: ");
//				String outputFile = input.nextLine();
//				try {
//					BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile));
//					for(Integer i =0; i<peopleContacts.size();i++) {
//						writer.write(peopleContacts.get(i).personInfoString());
//					}
//					writer.close();
//				}catch(IOException e) {
//					System.out.print("Invalid filename input");	
//				}
//				System.out.println("Successfully printed all your contacts to ");
//			}
//			printMenu();
//			success = false;
//			while(!success) {
//				try {
//					System.out.print("\nWhat option would you like to select? ");
//					String userInput = input.nextLine();
//					if(userInput.equals("EXIT")) {
//						num = 5;
//						success = true;
//					}
//					else {
//						num = Integer.parseInt(userInput);
//						if(num>5) {
//							throw new InputMismatchException();
//						}
//						else if(num<1) {
//							throw new InputMismatchException();
//						}
//						else {
//							success = true;
//						}
//						
//					}
//				}
//				catch(InputMismatchException e) {
//					System.out.println("That is not a valid option.");
//					success = false;
//				}
//				catch(NumberFormatException e) {
//					System.out.println("That is not a valid option.");
//					success = false;
//				}
//			}
//			
//		}
//		System.out.print("\nThank you for using my contacts program. Goodbye!");
//		input.close();
//		
//		
//		
//		
//		
//		
//
//	}
//
//}

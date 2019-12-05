package nduka_CSCI201_Assignment1;

import java.util.ArrayList;

public class Person {
	public String fname;
	public String lname;
	public String email;
	public Integer age;
	public boolean nearCamp;
	public ArrayList<String> notesList;
	public Person(String firstName, String lastName, String theirEmail, Integer theirAge, boolean nearCampus, ArrayList<String>theirNotes) {
		fname = firstName;
		lname = lastName;
		email = theirEmail;
		age = theirAge;
		nearCamp = nearCampus;
		notesList = new ArrayList<String>();
		for(Integer i =0; i < theirNotes.size();i++) {
			notesList.add(theirNotes.get(i));
		}	
	}
	//accessor methods 
	public String getFName(){
		return fname;
	}
	public String getLName() {
		return lname;
	}
	public String getEmail() {
		return email;
	}
	//if this person has last name then return true
	public boolean findLastName(String name) {
		if(name.equalsIgnoreCase(lname)) {
			return true;
		}
		return false;
	}
	//if this person has this email then return true
	public boolean findEmail(String findemail) {
		if(findemail.equalsIgnoreCase(email)) {
			return true;
		}
		return false;
	}
	//prints person's info on console
	public void printPersonInfo() {
		System.out.println("\nName: "+fname+" "+lname);
		System.out.println("Email: " + email);
		System.out.println("Age: "+ age);
		if(nearCamp) {
			System.out.println("Near Campus: Yes");
		}
		else {
			System.out.println("Near Campus: No");
		}
		System.out.print("Notes: "+ notesList.get(0));
		for(Integer i = 1; i<notesList.size();i++) {
			System.out.print(", "+notesList.get(i));
		}
		System.out.println("\n");
		
	}
	//returns person info as string 
	public String personInfoString() {
		String str = "Name: "+fname+" "+lname+"\nEmail: "+email+"\nAge: "+ Integer.toString(age)+"\nNearCampus: ";
		if(nearCamp) {
			str+="Yes\nNotes: "+notesList.get(0);
		}
		else {
			str+="No\nNotes: "+notesList.get(0);
		}
		for(Integer i = 1; i<notesList.size();i++) {
			str = str+ ", "+notesList.get(i);
		}
		str = str+"\n\n";
		return str;
	}
}

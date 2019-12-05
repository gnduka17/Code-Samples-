package nduka_CSCI201_Assignment3;
import java.sql.PreparedStatement;
import java.util.ArrayList;
import java.sql.Connection;
import java.sql.ResultSet;



public class userSQLImplement implements userSQLInfo {
	static Connection connection;
	static PreparedStatement ps;
	
	
	

	@Override
	public void insertUser(User u) {
		// TODO Auto-generated method stub
		try {
			connection = SQLConnect.getCon();
			ps=connection.prepareStatement("INSERT INTO User(username,password) VALUES (?,?)");
			ps.setString(1, u.getUsername());
			ps.setString(2,u.getPassword());
			ps.executeUpdate();
			ps.close();
			
		}catch(Exception e) {
			e.printStackTrace();
			
		}
	}
	public void insertFavBook(String bookid, String username, String title, String author, String summary, String imglink) {
		// TODO Auto-generated method stub
		System.out.print("INSERTING INTO FAVORITES DATABASE!!!!!from implement function!1 author is: "+ author);
		try {
			ArrayList <String> holder = new ArrayList<String>();
			connection = SQLConnect.getCon();
			ps=connection.prepareStatement("INSERT INTO userFavorites(username,bookID,title,author,summary,img) VALUES (?,?,?,?,?,?)");
			ps.setString(1, username);
			ps.setString(2, bookid);
			ps.setString(3, title);
			ps.setString(4, author);
			ps.setString(5, summary);
			ps.setString(6, imglink);
			ps.executeUpdate();
			ps.close();
			
		}catch(Exception e) {
			e.printStackTrace();
			
		}
	}
	public void removeFavBook(String bookid, String username) {
		// TODO Auto-generated method stub
		try {
			connection = SQLConnect.getCon();
			ps=connection.prepareStatement("DELETE FROM userFavorites WHERE username=? AND bookID=?");
			ps.setString(1, username);
			ps.setString(2, bookid);
			ps.executeUpdate();
			ps.close();
			
		}catch(Exception e) {
			e.printStackTrace();
			
		}
	}

	@Override
	public ArrayList<ArrayList<String>> getFavorites(String username) {
		// TODO Auto-generated method stub
		ArrayList<ArrayList<String>> userfav = new ArrayList<ArrayList<String>>();
		
		
		
		
		try {
			connection = SQLConnect.getCon();
			ps=connection.prepareStatement("SELECT * FROM userFavorites WHERE username=? ORDER BY favID ASC");
			ps.setString(1, username);
			ResultSet rs = ps.executeQuery();
			while(rs.next()) {
				ArrayList<String> holder = new ArrayList<String>();
				holder.add(rs.getString(3));
				holder.add(rs.getString(4));
				holder.add(rs.getString(5));
				holder.add(rs.getString(6));
				holder.add(rs.getString(7));
				userfav.add(holder);
			}
//			ps.close();
//			rs.close();
			
		}catch(Exception e) {
			e.printStackTrace();
		}
		return userfav;
	}
	public User getUserPack(String username, String password) {
		// TODO Auto-generated method stub
		User person = new User();
		try {
			connection = SQLConnect.getCon();
			ps=connection.prepareStatement("SELECT * FROM User WHERE username=? AND password=?");
			ps.setString(1, username);
			ps.setString(2,password);
			ResultSet rs = ps.executeQuery();
			while(rs.next()) {
				person.setUsername(rs.getString(1));
				person.setPassword(rs.getString(2));
			}
//			ps.close();
//			rs.close();
			
		}catch(Exception e) {
			e.printStackTrace();
		}
		return person;
	}
	public boolean userExist(String un) {
		boolean userExist = false;
		try {
			connection = SQLConnect.getCon();
			ps=connection.prepareStatement("SELECT username FROM User WHERE username=?");
			ps.setString(1, un);
			ResultSet rs = ps.executeQuery();
			if(rs.next()) {
				userExist = true;
			}
			else {
				userExist = false;
			}
		}catch(Exception e) {
			e.printStackTrace();
			
		}
		return userExist;
		
	}
	public boolean favExists(String username, String bookid) {
		boolean favExist = false;
		try {
			connection = SQLConnect.getCon();
			ps=connection.prepareStatement("SELECT bookID FROM userFavorites WHERE username=? AND bookID=?");
			ps.setString(1, username);
			ps.setString(2, bookid);
			ResultSet rs = ps.executeQuery();
			if(rs.next()) {
				favExist = true;
			}
			else {
				favExist = false;
			}
		}catch(Exception e) {
			e.printStackTrace();
			
		}
		return favExist;
		
	}
	public boolean passExist(String pass) {
		boolean passExist = false;
		try {
			connection = SQLConnect.getCon();
			ps=connection.prepareStatement("SELECT password FROM User WHERE password=?");
			ps.setString(1, pass);
			ResultSet rs = ps.executeQuery();
			if(rs.next()) {
				passExist = true;
			}
			else {
				passExist = false;
			}
		}catch(Exception e) {
			e.printStackTrace();
			
		}
		return passExist;
		
	}
	public boolean regUserDNE(String user) {
		boolean regUserDNE = true;
		try {
			connection = SQLConnect.getCon();
			ps=connection.prepareStatement("SELECT username FROM User WHERE username=?");
			ps.setString(1, user);
			ResultSet rs = ps.executeQuery();
			if(rs.next()) {
				regUserDNE = false;
			}
			else {
				regUserDNE = true;
			}
		}catch(Exception e) {
			e.printStackTrace();
		}
		return regUserDNE;
	}
	public boolean passmatch(String pass1, String pass2) {
		if(pass1.equals(pass2)) {
			return true;
		}
		return false;
		
	}

}

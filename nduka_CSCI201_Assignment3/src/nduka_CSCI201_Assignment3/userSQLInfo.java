package nduka_CSCI201_Assignment3;

import java.util.ArrayList;
import java.util.Map;

public interface userSQLInfo {
	public void insertUser(User u);
	public User getUserPack(String username, String password);
	public boolean userExist(String un);
	public boolean passExist(String pass);
	public boolean passmatch(String pass1, String pass2);
	public boolean regUserDNE(String user);
	public void insertFavBook(String bookid, String username, String title, String author, String summary, String imglink);
	public void removeFavBook(String bookid, String username);
	public boolean favExists(String username, String bookid);
	public ArrayList<ArrayList<String>> getFavorites(String username);

}

package nduka_CSCI201_Assignment3;
import java.sql.Connection;
import java.sql.DriverManager;

public class SQLConnect implements SQLOverview {
	
	 static Connection connection = null;
	 public static Connection getCon() {
		 try {
				Class.forName("com.mysql.jdbc.Driver");
				connection = DriverManager.getConnection(CREDENTIALS_STRING);
			}
			catch(Exception e) {
				e.printStackTrace();
			}
		 return connection;
	 }
	 
}

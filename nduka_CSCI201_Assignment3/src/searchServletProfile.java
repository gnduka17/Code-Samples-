import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.stream.JsonReader;
import com.google.gson.stream.JsonToken;

//import toDetailsProfServlet.Bookid;
//import toDetailsProfServlet.VolumeP;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;

@WebServlet("/searchServletProfile")
public class searchServletProfile extends HttpServlet {
	
	private static final long serialVersionUID = 1L;
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try {
			HttpSession session = request.getSession();
			
			/*****************************/
			// Replace your API key here after removing the brackets---No use though
			String apiKey = ""; 
			String searchText = request.getParameter("searchText").trim().replaceAll("\\s", "+");
			if(searchText=="") {
				request.setAttribute("errormess", "Please enter a keyword");
				request.getRequestDispatcher("/homePageProfile.jsp").forward(request,response);
			}
				String radioSelect = request.getParameter("radioSelect");
				//System.out.println(searchedRadio+"here");
				String myUrl = "";
				if (radioSelect!=null){
					myUrl = "https://www.googleapis.com/books/v1/volumes?q="+ radioSelect + ":" + searchText;
				}else{
					myUrl = "https://www.googleapis.com/books/v1/volumes?q="+ searchText;
				}
				String jsonString = createJsonStringFromURL(myUrl);
				request.setAttribute("rawdata", jsonString);
				session.setAttribute("rawdata", jsonString);
				
				GsonBuilder builder = new GsonBuilder();
				builder.setPrettyPrinting();
				Gson gson = builder.create();
				
				SearchResultP results = gson.fromJson(jsonString, SearchResultP.class);
				String json = gson.toJson(results);
				
				request.setAttribute("data", json);
				session.setAttribute("data", json);
				RequestDispatcher dispatch = getServletContext().getRequestDispatcher("/searchResultsProfile.jsp");
		        dispatch.forward(request, response);
			
		}
		catch (Exception e) {
			System.out.println(e.toString());
		}
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		
	}
	
	private String createJsonStringFromURL(String desiredUrl) throws Exception {
		URL url = null;
		BufferedReader reader = null;
		StringBuilder stringBuilder;
		
		try {
			url = new URL(desiredUrl);
			HttpURLConnection connection = (HttpURLConnection)url.openConnection();
			connection.setRequestMethod("GET");
			connection.setReadTimeout(15*1000);
		    connection.connect();
		    
		    reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
		    stringBuilder = new StringBuilder();
		    
		    String line = null;
		    while ((line = reader.readLine()) != null)
		    {
		    	stringBuilder.append(line + "\n");
		    }
			
		    return stringBuilder.toString();
		}
		catch (Exception e) {
			e.printStackTrace();
			throw e;
		}
		finally {
			//close your reader!
			reader.close();
		}
	}
}

class SearchResultP {
	 ItemP[] items;
}
class ItemP {
	//Bookid id;
	VolumeP volumeInfo;
}
class Bookid {
	//String id;
}
class VolumeP {
	//String bookid;
	String title, publisher, publishedDate, description;
	String[] authors;
	double averageRating;
	IdentifierP[] industryIdentifiers;
	ImageP imageLinks;
}

class IdentifierP {
	String type;
	String identifier;
}

class ImageP {
	private String smallThumbnail, thumbnail;
}

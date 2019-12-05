import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.stream.JsonReader;
import com.google.gson.stream.JsonToken;
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

@WebServlet("/searchServ")
public class searchServlet extends HttpServlet {
	
	private static final long serialVersionUID = 1L;
	
	protected void service (HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try {
			HttpSession session = request.getSession();
			
			/*****************************/
			// Replace your API key here after removing the brackets---No use though
			String apiKey = ""; 
			String searchText = request.getParameter("searchText").trim().replaceAll("\\s", "+");
			if(searchText=="") {
				request.setAttribute("errormess", "Please enter a keyword");
				request.getRequestDispatcher("/homePage.jsp").forward(request,response);
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
				
				SearchResult results = gson.fromJson(jsonString, SearchResult.class);
				String json = gson.toJson(results);
				
				request.setAttribute("data", json);
				session.setAttribute("data", json);
				RequestDispatcher dispatch = getServletContext().getRequestDispatcher("/searchResults.jsp");
		        dispatch.forward(request, response);
			
			
		}
		catch (Exception e) {
			System.out.println(e.toString());
		}
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

class SearchResult {
	private Item[] items;
}

class Item {
	Volume volumeInfo;
}

class Volume {
	String title, publisher, publishedDate, description;
	String[] authors;
	double averageRating;
	Identifier[] industryIdentifiers;
	Image imageLinks;
}

class Identifier {
	String type;
	String identifier;
}

class Image {
	private String smallThumbnail, thumbnail;
}

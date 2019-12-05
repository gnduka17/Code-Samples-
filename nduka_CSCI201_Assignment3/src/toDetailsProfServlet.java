

import java.io.IOException;
//import com.google.gson.Gson;
//import com.google.gson.GsonBuilder;
//import com.google.gson.stream.JsonReader;
//import com.google.gson.stream.JsonToken;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import nduka_CSCI201_Assignment3.User;
import nduka_CSCI201_Assignment3.userSQLImplement;
import nduka_CSCI201_Assignment3.userSQLInfo;

//import com.google.gson.Gson;
//import com.google.gson.GsonBuilder;

/**
 * Servlet implementation class toDetailsProfServlet
 */
@WebServlet("/toDetailsProfServlet")
public class toDetailsProfServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public toDetailsProfServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		System.out.println("testing AJAXXXXXX");
		//String idnumstring = (String)request.getAttribute("indexvar");
		try {
			//int idnumstring = Integer.parseInt(request.getParameter("indexvar"));
			//int idnum = Integer.parseInt(request.getParameter("id"));
			//HttpSession session = request.getSession();
			HttpSession sess = request.getSession(false);
			String username = (String)sess.getAttribute("Username");
			if (username.equals("null")) {
				System.out.println("USERNAME IS LITERAILLY NULL!!!!!!!!!!!!!!");
			}
			String test = request.getParameter("holder");
			//String user = (String)request.getAttribute("Username");
			System.out.println("testing checking book idnum:" + test);
			System.out.println("testing checking username:" + username);
			userSQLInfo us = new userSQLImplement();
			if(us.favExists(username,test)) {
				System.out.println("enter if statement");
				//output remove
				//have variable outputbut set to remove;
				sess.setAttribute("outputButton", "Remove");
			}
			else {
				//output favorite
				//have variable outputbut set to favorite;
				System.out.println("testing  enter else statement");
				sess.setAttribute("outputButton", "favorite");
				
			}
			System.out.println("testing doesnt enter if statement");
			//User bookuser = us.getUserPack(logUN, logPass);
//			HttpSession sessio = request.getSession();
//			String data2  = (String)sessio.getAttribute("data");
//			GsonBuilder builder = new GsonBuilder();
//			builder.setPrettyPrinting();
//			Gson gson = builder.create();
//			SearchResultP data = gson.fromJson(data2, SearchResultP.class);
			
			
			//String = sessio.getAttribute("data");
			//System.out.println("data bookid is:"+data.items[idnumstring].id);
			
		}catch(Exception e) {
			e.printStackTrace();
		}
		
//		GsonBuilder builder = new GsonBuilder();
//		builder.setPrettyPrinting();
//		Gson gson = builder.create();
//		
//		SearchResultP results = gson.fromJson(data, SearchResultP.class);
//		String json = gson.toJson(results);
//		HttpSession session = request.getSession();
//		request.setAttribute("info", json);
//		session.setAttribute("info", json);
//		String info = session.getAttribute("info");
		
		
		
//		request.getRequestDispatcher("detailsProfile.jsp").forward(request, response);
		
	}
//	class SearchResultP {
//		 ItemP[] items;
//	}
//	class ItemP {
//		Bookid id;
//		VolumeP volumeInfo;
//	}
//	class Bookid {
//		//String id;
//	}
//
//	class VolumeP {
//		String bookid;
//		String title, publisher, publishedDate, description;
//		String[] authors;
//		double averageRating;
//		IdentifierP[] industryIdentifiers;
//		ImageP imageLinks;
//	}
//
//	class IdentifierP {
//		String type;
//		String identifier;
//	}
//
//	class ImageP {
//		private String smallThumbnail, thumbnail;
//	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}

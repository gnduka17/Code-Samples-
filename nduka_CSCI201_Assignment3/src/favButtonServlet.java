

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import nduka_CSCI201_Assignment3.userSQLImplement;
import nduka_CSCI201_Assignment3.userSQLInfo;

/**
 * Servlet implementation class favButtonServlet
 */
@WebServlet("/favButtonServlet")
public class favButtonServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public favButtonServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
//		String textSearch = request.getParameter("searchText");
//		String radioVal = request.getParameter("radioSelect");
//		request.setAttribute("testing", textSearch);
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		HttpSession sess = request.getSession(false);
		String setbutt = (String)sess.getAttribute("outputButton");
		userSQLInfo us = new userSQLImplement();
		String bookid = request.getParameter("holder");
		String booktitle = request.getParameter("booktitle");
		String bookauth = request.getParameter("bookauthor");
		String booksummary = request.getParameter("booksumm");
		String bookimg = request.getParameter("bookimg");
		//String y =  bookimg.substring(7);
		//System.out.println("img url is:"+ y);
		
		String currentState = request.getParameter("current");
//		String currentState = request.getParameter("favButton");
		String username = (String)sess.getAttribute("Username");
//		String cantpress = request.getParameter("pressed");
		
		
//		if(cantpress.equals("true")) {
//			System.out.print("YOU CANT PRESS IT ENTERED IF STATEMENT");
//			request.setAttribute("errormess5", "PLEASE LOG IN BEFORE ADDING TO FAVORITES");
//		}
		if(currentState.equals("favorite")) {
			//add to fav database
			
			us.insertFavBook(bookid, username, booktitle, bookauth, booksummary, bookimg);
			sess.setAttribute("outputButton", "Remove");
		}
		else {
			us.removeFavBook(bookid, username);
			sess.setAttribute("outputButton", "favorite");
		}
		
		

		
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}

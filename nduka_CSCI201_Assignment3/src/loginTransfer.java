

import java.io.IOException;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.google.gson.Gson;

import nduka_CSCI201_Assignment3.userSQLImplement;
import nduka_CSCI201_Assignment3.userSQLInfo;

/**
 * Servlet implementation class loginTransfer
 */
@WebServlet("/loginTransfer")
public class loginTransfer extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
  
    public loginTransfer() {
        super();
        // TODO Auto-generated constructor stub
    }


	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		HttpSession sess = request.getSession(false);
		if(sess!=null) {
			response.sendRedirect("profilePage.jsp");
			String username = (String)sess.getAttribute("Username");
			userSQLInfo us = new userSQLImplement();
			ArrayList<ArrayList<String>> holder = new ArrayList<ArrayList<String>>();
			holder = us.getFavorites(username);
			for(int i = 0; i<holder.size();i++) {
				for(int j=0; j<holder.get(i).size();j++) {
					String hold = holder.get(i).get(j);
					String dang = hold.replaceAll("\"", "");
					holder.get(i).set(j, dang);
				}
			}
			Gson gson = new Gson();
			String favs = gson.toJson(holder);
			
			sess.setAttribute("favbooks",favs);
			
		}
		else {
			//user is not logged in 
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

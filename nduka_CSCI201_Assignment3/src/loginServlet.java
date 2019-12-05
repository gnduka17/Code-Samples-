

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import nduka_CSCI201_Assignment3.userSQLInfo;
import nduka_CSCI201_Assignment3.userSQLImplement;
import nduka_CSCI201_Assignment3.User;
import javax.servlet.http.HttpSession;



/**
 * Servlet implementation class loginServlet
 */
@WebServlet("/loginServlet")
public class loginServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	//static Connection connection = null;
	//public static final String CREDENTIALS_STRING = "jdbc:mysql://google/hw3Info?cloudSqlInstance=my-project-lab8-256023:us-west1:hw3&socketFactory=com.google.cloud.sql.mysql.SocketFactory&useSSL=false&user=hw3assign&password=password";
      
    /**
     * @see HttpServlet#HttpServlet()
     */
    public loginServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#service(HttpServletRequest request, HttpServletResponse response)
	 */
//	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
//		// TODO Auto-generated method stub
//		
//		
//		
//		
//	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
//		try {
//			Class.forName("com.mysql.jdbc.Driver");
//			connection = DriverManager.getConnection(CREDENTIALS_STRING);
//			
//		}
//		catch(Exception e) {
//			e.printStackTrace();
//		}
		request.getRequestDispatcher("/login.jsp").forward(request,response);
		
		//response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		userSQLInfo us = new userSQLImplement();
		String logUN = request.getParameter("LoginUsername");
		String logPass = request.getParameter("LoginPassword");
		String regUN = request.getParameter("RegUsername");
		String regPass = request.getParameter("RegPassword");
		String regPass2 = request.getParameter("RegPassword2");
		String submitbut = request.getParameter("butt");
		User bookuser = us.getUserPack(logUN, logPass);
		HttpSession sess;
		System.out.println("HEY PRETTY LADY");
		if(submitbut.equals("Sign In")) {
			if(logUN.equals("")) {
				request.setAttribute("errormess1", "Username Does Not Exist");
				request.getRequestDispatcher("login.jsp").forward(request, response);
			}
			else {
				if(us.userExist(logUN)) {
					System.out.println("UN EXISTSSSS ENETERED");
					if(us.passExist(logPass)) {
						sess = request.getSession();
						sess.setAttribute("Username", logUN);
						response.sendRedirect("./profileServlet");
						//request.getRequestDispatcher("homePageProfile.jsp").forward(request, response);
					}
					else {
						request.setAttribute("errormess1", "Password Does Not exist");
						request.getRequestDispatcher("login.jsp").forward(request, response);
					}
				}
				else {
					request.setAttribute("errormess1", "Username Does Not Exist");
					request.getRequestDispatcher("login.jsp").forward(request, response);
					
				}
				
			}
			
		}
	
		else if(submitbut.equals("Register")) {
			if(us.regUserDNE(regUN)) {
				if(us.passmatch(regPass, regPass2)) {
					bookuser.setUsername(regUN);
					bookuser.setPassword(regPass);
					us.insertUser(bookuser);
					sess = request.getSession();
					sess.setAttribute("Username", regUN);
					response.sendRedirect("./profileServlet");
					//request.getRequestDispatcher("homePageProfile.jsp").forward(request, response);	
				}
				else {
					request.setAttribute("regerrormess", "Passwords Do Not Match");
					request.getRequestDispatcher("register.jsp").forward(request, response);
				}
			}
			else {
				
				request.setAttribute("regerrormess", "Username Already Taken");
				request.getRequestDispatcher("register.jsp").forward(request, response);
			}
			
		}
		else {
			request.setAttribute("errormess1", "Login Info not found. Please enter correct Info or register.");
			request.getRequestDispatcher("login.jsp").forward(request, response);
		}
		
		
		//doGet(request, response);
	}

}

<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
	<head>
	<meta charset="UTF-8">
		<link rel="stylesheet" href="HomePage.css">
		<title>HomePage</title>
		<style>
/* logo{
width:200px;
} */
#container{
background: linear-gradient( rgba(0,0,0,0.5), rgba(0, 0, 0, 0.5) ),url("background.jpg");
/* background-image:url("bookimage.png"); */
background-repeat:no-repeat;
height:100%;
background-size:100% 100%;
}
html, body{
width:100%;
height:100%;
}
body{
margin:0;
}
#content{
padding-top:200px;
width:1350px;
margin-right:auto;
margin-left:auto;
}
#searchInfo{
width:1350px;
height:20px;
}
h1{
color:white;
opacity:0.5;
font-family:Arial, Helvetica, sans-serif;
}
#firstrad{
width:300px;
padding-top:10px;
color:white;
}
#secrad{
width:300px;
padding-right:350px;
padding-top:10px;
float:right;
color:white;
}
#clear{
clear:both;
}
.button{
width:80px;
float:right;
margin-right:20px;
}
#buttons{
width:260px;
float:right;
margin-top:30px;
margin-right:40px;
}

</style>
	</head>
	<body>
	
	
	<div id="container">
		<div id = "logo" style="background-color:white; padding-bottom:2px; margin-bottom: 20px;">
					<img alt="Web Logo" width="110px" style = "margin-left:20px; margin-top:30px;" src="bookworm.png" />
			<form id = buttons method="GET" action="loginTransfer">
			<input type="submit"  name="profilebutton" value="Profile" />
			<input type="button"  value="Sign Out" name="profilebutton" onclick="location.href='logoutPage.jsp'" />
			</form>	
		</div>
		
		<div id="content">
				<h1>BookWorm: Just a Mini Program... Happy Days!</h1>
				<form method="GET" action="searchServletProfile">
					<input id = "searchInfo" type="text" name="searchText" placeholder="Search for your favorite book!"><br>
					<div  id="errormess" style="color:white; padding-top:10px;"> ${errormess} </div>
					
					<div id="secrad">
					<input id="radButtonISBN" type="radio" name="radioSelect" value="isbn"/> ISBN
					<br/>
					<input id="radButtonPub" type="radio" name="radioSelect" value="inpublisher"/> Publisher
					</div>
					<div id="firstrad">
					<input id="radButtonTitle" type="radio" name="radioSelect" value="intitle"/> Name
					<br/>
					<input id="radButtonAuthor" type="radio" name="radioSelect" value="inauthor"/> Author
					</div>
					
					<input id="button" type="submit" value="Search!" style="float:right; background-color:black; color:white;"/>
				</form>
		</div>
		</div>
		
		
	</body>
</html>
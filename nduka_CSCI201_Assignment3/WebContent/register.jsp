<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<style>
#clear{
clear:both;
}
</style>
<body>
<div id="containerSR" style="background-color:green; margin-left:auto; margin-right:auto; width:950px;">

<div id = "logoSR" style=" padding-bottom:10px;width:155px; float:left;">
<a href="homePage.jsp"><img src="bookworm.png" alt="Web Logo" width="100px" style = "margin-top:25px;"></a>
</div>
<form name = "bookForm" method = "GET" action="searchServ">
	<input id = "searchText" name="searchText" type="text" placeholder = "What book is on your mind?" style="float:left; width:200px; margin-top:57px;"/>
	<div style="background-color:gray;float:left;margin-top:57px;margin-left:10px; width:50px; padding-left:27px; padding-top:1px;border-radius:5px;height:25px;" >
	<input id="button" type="image" value="Search!" src="magnifying_glass.png" style="width:30px;"/>
	</div>
	<div id = "contentSR" style="width:400px;float:right;margin-top:37px;">
		<div id="errormess" style="color:black; padding-top:10px;">${errormess}</div>
		<div id="firstrad" style="float:left; margin-right:75px;">
			<input id="radButtonTitle" type="radio" name="radioSelect" value="intitle"/> Name
			<br/>
			<input id="radButtonAuthor" type="radio" name="radioSelect" value="inauthor"/> Author
		</div>
		<div id="secrad" style="float:left;">
			<input id="radButtonISBN" type="radio" name="radioSelect" value="isbn"/> ISBN
			<br/>
			<input id="radButtonPub" type="radio" name="radioSelect" value="inpublisher"/> Publisher
		</div>
	</div>	
</form>
	
</div>
<div id="clear"></div>
<hr style='border-top: dotted 1px;' />
<br/><br/>
<form style="width:1200px; margin-left:auto; margin-right:auto;" method="POST" action="loginServlet">
Username
<br/>
<input style="width:1200px; padding-top:5px; padding-bottom:5px;" type="text" name="RegUsername"/>
<br/><br/><br/>
Password
<br/>
<input style="width:1200px; padding-top:5px; padding-bottom:5px;" type="password" name="RegPassword"/>
<br/><br/><br/>
Confirm Password
<br/>
<input style="width:1200px; padding-top:5px; padding-bottom:5px;" type="password" name="RegPassword2"/>
<br/><br/>
<div style="color:red;">${regerrormess} </div>
<input style="width:1210px; padding-top:5px; padding-bottom:5px; background-color:#AAAAAA; color:white; font-size:20px;" type="submit" name="butt" value="Register">
</form>

</body>
</html>
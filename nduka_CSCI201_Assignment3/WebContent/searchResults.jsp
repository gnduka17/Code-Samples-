<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="HomePage.css">
	<meta charset="ISO-8859-1">
	<title>Search Results</title>
	<style>

#clear{
clear:both;
}
</style>
	
</head>
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
    <h1 style="margin-left:20px;"><i>Search Results: ${param.searchText}</i></h1>
    <div id="results" style="width:950px; margin-right:auto; margin-left:auto;"></div>
</body>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
<script>
		var data = <%= session.getAttribute("data") %>;
		$("#results").append("<hr style='border-top: dotted 1px;' />");
		if (data==null || data.items==null || data.items.length<1){
	        alert("No result found!");
			var link = document.createElement('a');
	        link.href = "homePage.jsp";
	        document.body.appendChild(link);
	        link.click();
		}
		
		for(i=0; i<data.items.length; i++) {
			$("#results").append('<table><tr><td rowspan="4">&nbsp'+'<a href="details.jsp?id='+i+'"><img src="'+data.items[i].volumeInfo.imageLinks.smallThumbnail+'"/></a>'+'</td><td>&nbsp</td></tr>'
			+'<tr><td>&nbsp'+data.items[i].volumeInfo.title+'</td></tr>'
			+'<tr><td>&nbsp'+data.items[i].volumeInfo.authors+'</td></tr>'
			+'<tr><td>&nbsp<i>Summary:</i> '+data.items[i].volumeInfo.description+'</td></tr></table>'
			+"<hr style='border-top: dotted 1px;' />");
		}
</script>
	
	
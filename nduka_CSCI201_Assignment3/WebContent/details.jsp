<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
	<link href="https://cdnjs.cloudflare.com/ajax/libs/rateYo/2.3.2/jquery.rateyo.min.css" rel="stylesheet"/>
	<!-- <link rel="stylesheet" href="HomePage.css"> -->
	<meta charset="ISO-8859-1">
	<title>Details</title>
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
						<script>
						$(document).ready(function(){
						    $("#favbuttonclick").click(function(){  
						       $('#erro').html('**PLEASE LOG IN FIRST BEFORE ADDING TO FAVORITES');
						   });
						});
						</script>

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
	<div id="results" style="width:950px;margin-left:auto; margin-right:auto;"></div>
	<button id = "favbuttonclick" style="margin-left:250px; padding-bottom:5px;padding-top:5px; width:90px;">&#9733;Favorite</button>
	<br/>
	<div id="erro" style="width:500px;"> ${errormess5}</div> 

	
</body>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/rateYo/2.3.2/jquery.rateyo.min.js"></script>
<script>

</script>
<script>

	var id = parseInt(window.location.search.substring(1).substring(3));
	var data = <%= session.getAttribute("data") %>;
	$("#results").append('<table style="width:900px;"><tr><td rowspan="8">&nbsp'+'<img src="'+data.items[id].volumeInfo.imageLinks.smallThumbnail+'" onclick="history.back()"/>'
			+'</td><td>&nbsp</td></tr>'
			+'<tr><td><h2>&nbsp'+data.items[id].volumeInfo.title+'</h2></td></tr>'
			+'<tr><td><i>Author:</i>&nbsp'+data.items[id].volumeInfo.authors+'</td></tr>'
			+'<tr><td><i>Publisher:</i>&nbsp'+data.items[id].volumeInfo.publisher+'</td></tr>'
			+'<tr><td><i>Publish Date:</i>&nbsp'+data.items[id].volumeInfo.publishedDate+'</td></tr>'
			+'<tr><td><i>ISBN:</i>&nbsp'+data.items[id].volumeInfo.industryIdentifiers[0].identifier+'</td></tr>'
			+'<tr><td><i>Summary:</i>&nbsp'+data.items[id].volumeInfo.description+'</td></tr>'
			+'<tr><td><i>Rating:</i><span id="star"></span></td></tr>'
			+'</table>');
	// Using a jQuery library for rating
	$(function () {
	  $("#star").rateYo({
	    rating: data.items[id].volumeInfo.averageRating,
	    readOnly: true
	  });
	});
</script>
</html>
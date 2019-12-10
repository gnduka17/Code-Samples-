<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Details Page</title>
<style>

#clear{
clear:both;
}
</style>
<script>
function validate(){
	var hasError=false;
	document.getElementById("errormess").innerHTML="";
	if(document.bookForm.searchInfo.value.length<=0){
		document.getElementById("errormess").innerHTML = "Please Enter a Keyword";
		hasError = true;
	}
	return !hasError;
}
</script>
</head>
<body>
<div id="containerSR" style="background-color:green; margin-left:auto; margin-right:auto; width:950px;">

<div id = "logoSR" style=" padding-bottom:10px;width:155px; float:left;">
<a href="HomePage.jsp"><img src="bookwormlogo.png" alt="Web Logo" width="100px" style = "margin-top:25px;"></a>
</div>
<form name = "bookForm" method = "GET" action="SearchResults.jsp" onsubmit="return validate();" >
	<input id = "searchInfo" type="text" placeholder = "What book is on your mind?" name="searchInfo" style="float:left; width:200px; margin-top:57px;"/>
	<div style="background-color:gray;float:left;margin-top:57px;margin-left:10px; width:50px; padding-left:27px; padding-top:1px;border-radius:5px;height:25px;" >
	<input id="button" type="image" value="Search!" src="magnifying_glass.png" style="width:30px;"/>
	</div>
	<div id = "contentSR" style="width:400px;float:right;margin-top:37px;">
		<div id="errormess" style="color:black; padding-top:10px;"></div>
		<div id="firstrad" style="float:left; margin-right:75px;">
			<input id="radButtonTitle" type="radio" name="radButton" value="intitle:" checked/> Name
			<br/>
			<input id="radButtonAuthor" type="radio" name="radButton" value="inauthor:"/> Author
		</div>
		<div id="secrad" style="float:left;">
			<input id="radButtonISBN" type="radio" name="radButton" value="isbn:"/> ISBN
			<br/>
			<input id="radButtonPub" type="radio" name="radButton" value="inpublisher:"/> Publisher
		</div>
	</div>	
</form>
	
</div>
<br/>
<br/>
<div id="clear"></div>
<hr style="margin:0; border:0.2px solid gray;opacity:0.5;"/>
<table style="width:950px; margin-right:auto; margin-left:auto;">
		<tr style="margin-bottom:20px;">
			<td id="img" onclick = "location.href = 'SearchResults.jsp';" style="padding-right:50px; margin-top:20px;"></td>
			<td id="desc" style="margin-top:10px;">
				<div id="titleDesc" style="font-size:20px; font-weight:bold;"></div>
				<div id="authorDesc" style="font-style:italic">Author: </div>
				<div id="pub" style="font-style:bold">Publisher: </div>
				<div id="pubDate" style="font-style:bold">Published Date: </div>
				<div id="isbnnum" style="font-weight:bold">ISBN: </div>
				<div id="storyDesc">Summary: </div>
			</td>
		</tr>
</table>
<hr style="width:950px; margin-right:auto; margin-left:auto;border:0.2px solid gray;opacity:0.5;"/> 

</body>
<script>
var img = localStorage.getItem("volImg"); 
var tit = localStorage.getItem("volTitle");
var auth = localStorage.getItem("volAuth");
var pub = localStorage.getItem("volpub");
var pubdate = localStorage.getItem("volpubdate");
var isbn = localStorage.getItem("volISBN"); 
var sum = localStorage.getItem("volsumm");
document.getElementById("titleDesc").innerHTML = tit
document.getElementById("authorDesc").innerHTML = auth
document.getElementById("pub").innerHTML = pub
document.getElementById("storyDesc").innerHTML = sum
document.getElementById("pubDate").innerHTML = pubdate
document.getElementById("isbnnum").innerHTML = isbn
document.getElementById("img").innerHTML = img
//detailsinfo.innerHTML= isbn
</script>
</html>
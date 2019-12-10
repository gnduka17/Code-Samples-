<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>

<meta charset="UTF-8">
<title>Search Results Page</title>
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
<script>
function bookHolder(num) {
	var thold = document.getElementById("titleDesc"+num.toString()).innerHTML;
	window.localStorage.setItem("volTitle",thold)
    var ahold = document.getElementById("authorDesc"+num.toString()).innerHTML;
	window.localStorage.setItem("volAuth",ahold)
	var shold = document.getElementById("storyDesc"+num.toString()).innerHTML;
	window.localStorage.setItem("volsumm",shold)
	var phold = document.getElementById("publisher"+num.toString()).innerHTML;
	window.localStorage.setItem("volpub",phold)
    var pdhold = document.getElementById("publish"+num.toString()).innerHTML;
	window.localStorage.setItem("volpubdate",pdhold)
	var ihold = document.getElementById("img"+num.toString()).innerHTML;
	window.localStorage.setItem("volImg",ihold)
	var isbnhold = document.getElementById("lish"+num.toString()).innerHTML;
	window.localStorage.setItem("volISBN",isbnhold)
}
</script>
</head>
<body onload = "getBook()">

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
<h2 style="width:600px; margin-left:30px;" id="resultsfor"></h2>
<hr style="width:950px; margin-right:auto; margin-left:auto;border:0.2px solid gray;opacity:0.5;"/>

<table id = "tableID1" style="width:950px; margin-right:auto; margin-left:auto;">
		<tr style="border-bottom: 1px solid gray; margin-bottom:20px;">
			<td id="img1" onclick="bookHolder(1);" style="padding-right:50px;"></td>
			<td id="desc1">
			<div id="titleDesc1" style="font-size:20px; font-weight:bold;"></div>
			<div id="authorDesc1" style="font-style:italic"></div>
			<div id="storyDesc1"></div>
			</td>
		</tr>
</table>
<hr style="width:950px; margin-right:auto; margin-left:auto; border:0.2px solid gray;opacity:0.5;"/> 
<table id = "tableID2" style="width:950px; margin-right:auto; margin-left:auto;">
		<tr style="border-bottom: 1px solid gray; margin-bottom:20px;">
			<td id="img2" onclick="bookHolder(2);"  style="padding-right:50px;"></td>
			<td id="desc2">
			<div id="titleDesc2" style="font-size:20px; font-weight:bold;"></div>
			<div id="authorDesc2"  style="font-style:italic"></div>
			<div id="storyDesc2"></div>
			</td>
		</tr>
</table>
<hr style="width:950px; margin-right:auto; margin-left:auto;border:0.2px solid gray;opacity:0.5;"/> 
<table id = "tableID3"  style="width:950px; margin-right:auto; margin-left:auto;">
		
		<tr style="border-bottom: 1px solid gray; margin-bottom:20px;">
			<td id="img3" onclick="bookHolder(3);"  style="padding-right:50px;"></td>
			<td id="desc3">
			<div id="titleDesc3" style="font-size:20px; font-weight:bold;"></div>
			<div id="authorDesc3" style="font-style:italic"></div>
			<div id="storyDesc3"></div>
			</td>
		</tr>
		</table>
		<hr style="width:950px; margin-right:auto; margin-left:auto;border:0.2px solid gray;opacity:0.5;"/>
	<table id = "tableID4"  style="width:950px; margin-right:auto; margin-left:auto;">
		<tr style="border-bottom: 1px solid gray; margin-bottom:20px;">

			<td id="img4" onclick="bookHolder(4);" style="padding-right:50px;"></td>
			<td id="desc4">
			<div id="titleDesc4" style="font-size:20px; font-weight:bold;"></div>
			<div id="authorDesc4" style="font-style:italic"></div>
			<div id="storyDesc4"></div>
			</td>
		</tr>
		</table>
		<hr style="width:950px; margin-right:auto; margin-left:auto;border:0.2px solid gray;opacity:0.5;"/>
		<table id = "tableID5"  style="width:950px; margin-right:auto; margin-left:auto;">
		<tr style="border-bottom: 1px solid gray; margin-bottom:20px;">
			<td id="img5" onclick="bookHolder(5);"  style="padding-right:50px;"></td>
			<td id="desc5">
			<div id="titleDesc5" style="font-size:20px; font-weight:bold;"></div>
			<div id="authorDesc5" style="font-style:italic"></div>
			<div id="storyDesc5"></div>
			</td>
		</tr>
		</table>
		<hr style="width:950px; margin-right:auto; margin-left:auto;border:0.2px solid gray;opacity:0.5;"/>
		<table id = "tableID6"  style="width:950px; margin-right:auto; margin-left:auto;">
		<tr style="border-bottom: 1px solid gray; margin-bottom:20px;">
			<td id="img6" onclick="bookHolder(6);"  style="padding-right:50px;"></td>
			<td id="desc6">
			<div id="titleDesc6" style="font-size:20px; font-weight:bold;"></div>
			<div id="authorDesc6" style="font-style:italic"></div>
			<div id="storyDesc6"></div>
			</td>
		</tr>
		</table>
		<hr style="width:950px; margin-right:auto; margin-left:auto;border:0.2px solid gray;opacity:0.5;"/>
		<table id = "tableID7"  style="width:950px; margin-right:auto; margin-left:auto;">
		<tr style="border-bottom: 1px solid gray; margin-bottom:20px;">
			<td id="img7" onclick="bookHolder(7);"  style="padding-right:50px;"></td>
			<td id="desc7">
			<div id="titleDesc7" style="font-size:20px; font-weight:bold;"></div>
			<div id="authorDesc7" style="font-style:italic"></div>
			<div id="storyDesc7"></div>
			</td>
		</tr>
		</table>
		<hr style="width:950px; margin-right:auto; margin-left:auto;border:0.2px solid gray;opacity:0.5;"/>
		<table id = "tableID8"  style="width:950px; margin-right:auto; margin-left:auto;">
		<tr style="border-bottom: 1px solid gray; margin-bottom:20px;">

			<td id="img8" onclick="bookHolder(8);"  style="padding-right:50px;"></td>
			<td id="desc8">
			<div id="titleDesc8" style="font-size:20px; font-weight:bold;"></div>
			<div id="authorDesc8" style="font-style:italic"></div>
			<div id="storyDesc8"></div>
			</td>
		</tr>
		</table>
		<hr style="width:950px; margin-right:auto; margin-left:auto;border:0.2px solid gray;opacity:0.5;"/>
		<table id = "tableID9"  style="width:950px; margin-right:auto; margin-left:auto;">
		<tr style="border-bottom: 1px solid gray; margin-bottom:20px;">
			<td id="img9" onclick="bookHolder(9);"  style="padding-right:50px;"></td>
			<td id="desc9">
			<div id="titleDesc9" style="font-size:20px; font-weight:bold;"></div>
			<div id="authorDesc9" style="font-style:italic"></div>
			<div id="storyDesc9"></div>
			</td>
		</tr>
		</table>
		<hr style="width:950px; margin-right:auto; margin-left:auto;border:0.2px solid gray;opacity:0.5;"/>
		<table id = "tableID10"  style="width:950px; margin-right:auto; margin-left:auto;">
		<tr style="border-bottom: 1px solid gray; margin-bottom:20px;">
			<td id="img10" onclick="bookHolder(10);"  style="padding-right:50px;"></td>
			<td id="desc10">
			<div id="titleDesc10" style="font-size:20px; font-weight:bold;"></div>
			<div id="authorDesc10" style="font-style:italic"></div>
			<div id="storyDesc10"></div>
			</td>
		</tr>
	</table>
	<p id="publisher1" style="display:none;"></p><p id="publisher2" style="display:none;"></p><p id="publisher3" style="display:none;"></p><p id="publisher4" style="display:none;"></p><p id="publisher5" style="display:none;"></p><p id="publisher6" style="display:none;"></p><p id="publisher7" style="display:none;"></p><p id="publisher8" style="display:none;"></p><p id="publisher9" style="display:none;"></p><p id="publisher10" style="display:none;"></p>
	<p id="publish1" style="display:none;"></p><p id="publish2" style="display:none;"></p><p id="publish3" style="display:none;"></p><p id="publish4" style="display:none;"></p><p id="publish5" style="display:none;"></p><p id="publish6" style="display:none;"></p><p id="publish7" style="display:none;"></p><p id="publish8" style="display:none;"></p><p id="publish9" style="display:none;"></p><p id="publish10" style="display:none;"></p>
	<p id="lish1" style="display:none;"></p><p id="lish2" style="display:none;"></p><p id="lish3" style="display:none;"></p><p id="lish4" style="display:none;"></p><p id="lish5" style="display:none;"></p><p id="lish6" style="display:none;"></p><p id="lish7" style="display:none;"></p><p id="lish8" style="display:none;"></p><p id="lish9" style="display:none;"></p><p id="lish10" style="display:none;"></p>
</body>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>

<script>
function getBook(){
	var keyWord = "${param.searchInfo}";
	document.getElementById("resultsfor").innerHTML = "Results for \""+keyWord+"\"";
	var identifier="${param.radButton}";
	$.ajax({
		url:"https://www.googleapis.com/books/v1/volumes?q=" + identifier + keyWord, 
		dataType: "json",
		success: function(data){
			
				for(i=1; i<data.items.length;i++){
					var holder = "img"+i.toString();
					var holder1 = "titleDesc"+i.toString();
					var holder2 = "authorDesc"+i.toString();
					var holder3 = "storyDesc"+i.toString();
					var holder4 = "publisher"+i.toString();
					var holder5 = "publish"+i.toString();
					var holder6 = "lish"+i.toString();
					document.getElementById(holder).innerHTML = "<a href='Details.jsp'><img src=\""+ data.items[i].volumeInfo.imageLinks.thumbnail +"\"></a>"
					document.getElementById(holder1).innerHTML = data.items[i].volumeInfo.title + "<br/>"
					document.getElementById(holder4).innerHTML = data.items[i].volumeInfo.publisher + "<br/>"
					document.getElementById(holder5).innerHTML = data.items[i].volumeInfo.publishedDate + "<br/>"
					document.getElementById(holder6).innerHTML = data.items[i].volumeInfo.industryIdentifiers[1].identifier + "<br/>"
					if (data.items[i].volumeInfo.authors === undefined){
						document.getElementById(holder2).innerHTML = "N/A"
					}
					else{
						document.getElementById(holder2).innerHTML = data.items[i].volumeInfo.authors+ "<br/>"	
					}
					if (data.items[i].volumeInfo.description === undefined){
						document.getElementById(holder2).innerHTML = "N/A"
					}else{
						document.getElementById(holder3).innerHTML = '<span style="font-weight:bold">Summary:</span>' + data.items[i].volumeInfo.description
					}
				}
		},
		type: 'GET'		
	})
}

</script>

</html>
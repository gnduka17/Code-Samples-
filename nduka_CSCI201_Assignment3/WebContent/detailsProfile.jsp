<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
	<link href="https://cdnjs.cloudflare.com/ajax/libs/rateYo/2.3.2/jquery.rateyo.min.css" rel="stylesheet"/>
	<!-- <link rel="stylesheet" href="HomePage.css"> -->
	<meta charset="ISO-8859-1"/>
	<title>Details</title>
</head>
<style>
	#clear{
clear:both;
}
	</style>
<body>
<div id="containerSR" style="background-color:green; margin-left:auto; margin-right:auto; width:950px;">

<div id = "logoSR" style=" padding-bottom:10px;width:155px; float:left;">
<a href="homePageProfile.jsp"><img src="bookworm.png" alt="Web Logo" width="100px" style = "margin-top:25px;"></a>
</div>
<form name = "detailPForm" method = "GET" action="searchServletProfile">
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
		<a href= "loginTransfer"><img style="margin-left:10px; width:40px;" src="profileicon.png" ></a>
	</div>	
</form>
	
</div>
<div id="clear"></div>
<hr style='border-top: dotted 1px;' />
	<div id="resultsP" style="width:950px;margin-left:auto; margin-right:auto;"></div>
	<div id="error_msg"></div>
	<div>${testing}</div>
	<%HttpSession sess = request.getSession(false);  %>
	<input type="button" name="favButton" id="favbuttonclick" style="margin-left:250px; padding-bottom:5px;padding-top:5px; width:90px;" onclick="favbuttfunc()" value='<%=(String)sess.getAttribute("outputButton")%>'/>
	
</body>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/rateYo/2.3.2/jquery.rateyo.min.js"></script>
<script>
var rawdata = <%= session.getAttribute("rawdata") %>;
function favbuttfunc(){
	var currentoutput = document.getElementById("favbuttonclick");
	<%-- <%
	session.setAttribute("dang",currentoutput.value);
	%>
	console.log('<%= session.getAttribute("dang") %>'); --%>
	<%-- var buttout ='<%=sess.getAttribute("outputButton")%>';
	var test = '<%= session.getAttribute( "mySessionVar" ) %>'; --%>
	/* var Status = $(this).val(); */
	/* var num = parseInt(window.location.search.substring(1).substring(3)); */
/* if(Object.entries(rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.authors).length === 0 && rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.authors.constructor === Object){
	Object.entries(rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.authors).length === 0 && rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.authors.constructor === Object
} */
    $.ajax({
        url: 'favButtonServlet',
        data: {
            idnum: window.location.search.substring(1).substring(3),
            holder: rawdata.items[parseInt(window.location.search.substring(1).substring(3))].id,
            booktitle: typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.title === "undefined" || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.title  === "" || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.title.length < 1 || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.title === "null" ? "undefined" : rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.title,
            bookauthor: typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.authors === "undefined" || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.authors === "" || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.authors.length < 1 ? "undefined" : rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.authors[0],
            booksumm: typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.description === "undefined" || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.description  === "" || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.description.length < 1 || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.description === "null" ? "undefined" : rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.description,
            bookimg:typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.imageLinks.smallThumbnail === "undefined" || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.imageLinks.smallThumbnail  === "" || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.imageLinks.smallThumbnail.length < 1 || typeof rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.imageLinks.smallThumbnail === "null" ? "" : rawdata.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.imageLinks.smallThumbnail,
            <%-- current: '<%=sess.getAttribute("outputButton")%>' --%>
            current: currentoutput.value
            
        },
        type: 'GET',
        success: function(data){
        	
        	if(currentoutput.value=="favorite"){
        		currentoutput.value="Remove";
        		<%-- <%=sess.setAttribute("outputButton", "Remove")%>;  --%>
        	}
        	else {
        		currentoutput.value="favorite";
        		<%-- <%=sess.setAttribute("outputButton", "favorite")%>;  --%>
        	}
        	
        	console.log('favvvv button clicked bookid:'+ window.location.search.substring(1).substring(3))
        }
        	
        

    });
	
}
</script>

<script>
console.log("havent enterd if statement yetttttttttttttttt")
var loser
var id = parseInt(window.location.search.substring(1).substring(3));
var data = <%= session.getAttribute("data") %>;
if(typeof data.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.industryIdentifiers === "undefined" || typeof data.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.industryIdentifiers  === "" || typeof data.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.industryIdentifiers.length < 1 || typeof data.items[parseInt(window.location.search.substring(1).substring(3))].volumeInfo.industryIdentifiers === "null" ){
	console.log("ENTERD INRO IF STATEMNT DETAILS PROFILE")
	loser = "undefined";
}else{
	loser = data.items[id].volumeInfo.industryIdentifiers[0].identifier;

}

	$("#resultsP").append('<table style="width:900px;"><tr><td rowspan="8">&nbsp'+'<img src="'+data.items[id].volumeInfo.imageLinks.smallThumbnail+'" onclick="history.back()"/>'
			+'</td><td>&nbsp</td></tr>'
			+'<tr><td><h2>&nbsp'+data.items[id].volumeInfo.title+'</h2></td></tr>'
			+'<tr><td><i>Author:</i>&nbsp'+data.items[id].volumeInfo.authors+'</td></tr>'
			+'<tr><td><i>Publisher:</i>&nbsp'+data.items[id].volumeInfo.publisher+'</td></tr>'
			+'<tr><td><i>Publish Date:</i>&nbsp'+data.items[id].volumeInfo.publishedDate+'</td></tr>'
			+'<tr><td><i>ISBN:</i>&nbsp'+ loser +'</td></tr>'
			/* +'<tr><td><i>ISBN:</i>&nbsp'+data.items[id].volumeInfo.industryIdentifiers[0].identifier+'</td></tr>' */
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
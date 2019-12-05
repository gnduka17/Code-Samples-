<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
	<link href="https://cdnjs.cloudflare.com/ajax/libs/rateYo/2.3.2/jquery.rateyo.min.css" rel="stylesheet"/>
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
<form name = "bookForm" method = "GET" action="searchServletProfile">
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
	<!-- <form name = "favbuttonForm" method="GET" action=""> -->
	<%HttpSession sess = request.getSession(false);  %>
	<input type="button" name="favButton" id="favbuttonclick" style="margin-left:250px; padding-bottom:5px;padding-top:5px; width:90px;" onclick="favbuttfunc()" value='<%=(String)sess.getAttribute("outputButton")%>'/>
	<!-- </form> -->
</body>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/rateYo/2.3.2/jquery.rateyo.min.js"></script>
<script>
var rawdata = JSON.parse('<%=session.getAttribute("favbooks") %>');
function favbuttfunc(){
	var currentoutput = document.getElementById("favbuttonclick");
	<%-- var buttout ='<%=sess.getAttribute("outputButton")%>';
	var test = '<%= session.getAttribute( "mySessionVar" ) %>'; --%>
	/* var Status = $(this).val(); */
	/* var num = parseInt(window.location.search.substring(1).substring(3)); */
    $.ajax({
        url: 'favButtonServlet',
        data: {
            idnum: window.location.search.substring(1).substring(3),
            holder: rawdata[parseInt(window.location.search.substring(1).substring(3))][0],
            booktitle: rawdata[parseInt(window.location.search.substring(1).substring(3))][1],
            bookauthor: rawdata[parseInt(window.location.search.substring(1).substring(3))][2],
            booksumm: rawdata[parseInt(window.location.search.substring(1).substring(3))][3],
            bookimg: rawdata[parseInt(window.location.search.substring(1).substring(3))][4],
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


	var id = parseInt(window.location.search.substring(1).substring(3));
	var data = JSON.parse('<%=session.getAttribute("favbooks") %>');
	var data3 = <%=session.getAttribute("data") %>;
	
	$("#resultsP").append('<table style="width:900px;"><tr><td rowspan="8">&nbsp'+'<img src="'+data[parseInt(window.location.search.substring(1).substring(3))][4]+'" onclick="history.back()"/>'
			+'</td><td>&nbsp</td></tr>'
			+'<tr><td><h2>&nbsp'+data[parseInt(window.location.search.substring(1).substring(3))][1]+'</h2></td></tr>'
			+'<tr><td><i>Author:</i>&nbsp'+data[parseInt(window.location.search.substring(1).substring(3))][2]+'</td></tr>'
			+'<tr><td><i>Publisher:</i>&nbsp'+data3.items[id].volumeInfo.publisher+'</td></tr>'
			+'<tr><td><i>Publish Date:</i>&nbsp'+data3.items[id].volumeInfo.publishedDate+'</td></tr>'
			/* +'<tr><td><i>ISBN:</i>&nbsp'+ loser +'</td></tr>' */
			/* +'<tr><td><i>ISBN:</i>&nbsp'+data3.items[id].volumeInfo.industryIdentifiers[0].identifier+'</td></tr>' */
			+'<tr><td><i>Summary:</i>&nbsp'+data[parseInt(window.location.search.substring(1).substring(3))][3]+'</td></tr>'
			+'<tr><td><i>Rating:</i><span id="star"></span></td></tr>'
			+'</table>');
	// Using a jQuery library for rating
	$(function () {
	  $("#star").rateYo({
	    rating: data3.items[id].volumeInfo.averageRating,
	    readOnly: true
	  });
	});
</script>
</html>
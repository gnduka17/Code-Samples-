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

<h1 style="width:950px; margin-right:auto; margin-left:auto;"><center><%=session.getAttribute("Username") %>'s Profile Page</center></h1>


<div id="results" style="width:950px; margin-right:auto; margin-left:auto;"></div>



</body>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
<script>
var data = JSON.parse('<%=session.getAttribute("favbooks") %>');
function removeButton(index){
	//hide the book at this index
	//call servlet to delete in favorite database
	$.ajax({
        url: 'deleteFav',
        data: {
            userN:'<%=session.getAttribute("Username") %>',
            bookI:data[index][0]
        },
        type: 'GET',
        success: function(data){
        } 

    });
	document.getElementById(index).style.display = 'none';

	
	
	
	
}
function goBack(index){
	//click 
	var data1 = JSON.parse('<%=session.getAttribute("favbooks") %>');
			$.ajax({
                url: 'toDetailsProfServlet',
                data: {
                    indexvar: index,
                    holder: data1[index][0]
                },
                type: 'GET',
                success: function(data){
                  location.href = "detailsFromProf.jsp?id="+index
                } 
            });	
}
		
		console.log(data);
		
		<%-- var data = <%= (String)session.getAttribute("favbooks") %>; --%>
		$("#results").append("<hr style='border-top: dotted 1px;' />");
		if (data==null || data.length<1){
			$("#results").append("NO FAVORITES JUST YET");
	        
		}
		else{
			/* '<a href="detailsProfile.jsp?id='+i+'"> */
			for(i=0; i<data.length; i++) {
				console.log("book:"+i+"\n"+ data[i][4]+ " \n "+ data[i][1]+ " \n "+data[i][2]+ " \n "+data[i][3]+ " \n " );
					console.log("testinggggggggg");
					$("#results").append('<table id="'+i+'" ><tr><td rowspan="4">&nbsp'+'<img src="'+data[i][4]+'" onclick="goBack('+i+')"/>'+'</td><td>&nbsp</td></tr>'
					+'<tr><td>&nbsp'+data[i][1]+'</td></tr>'
					+'<tr><td>&nbsp'+data[i][2]+'</td></tr>'
					+'<tr><td>&nbsp<i>Summary:</i> '+data[i][3]+'</td></tr>'
					+'<tr><td>&nbsp<button style="padding-bottom:5px;padding-top:5px;width:90px;" onclick="removeButton('+i+')">&#9733;REMOVE</button></td></tr></table>'
					+"<hr style='border-top: dotted 1px;' />");
					
				
				
			}
			
		}
	
</script>
	
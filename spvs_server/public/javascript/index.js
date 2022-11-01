function loadingSearch(elementID){
    document.getElementById(elementID).style.display = "none";
    document.getElementById(elementID).style.visibility = "hidden";
    document.getElementById("loading").innerHTML ="<p>Fetching Results...</p>";
}
function searchBox(elementID){
    document.getElementById(elementID).style.display = "block";
    document.getElementById(elementID).style.visibility = "visible";
    document.getElementById("loading").innerHTML ="";
}

$( document ).ready(function() {
    form = document.getElementById('search_form');
    form.addEventListener('submit', (event) => {
        event.preventDefault();
    });
});

var send = function() {
    var search = document.getElementById('search').value;
    loadingSearch("search_div");
    $.ajax({

        url : '/',
        type : 'POST',
        data : {
            'userInput' : search
        },
        dataType:'text',
        success : function(data) {        
            searchBox('search_div');   
            var returnedData = JSON.parse(data);
            document.getElementById("results").innerHTML = returnedData.userInput;
        },
        error : function(request,error)
        {
            alert("nope");
        }
    });
 }
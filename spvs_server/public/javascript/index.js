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
    var $result = $('#results');
    var userInput = {};
    var host_name = document.getElementById('search').value;
    userInput['host_name'] = host_name;
    if(document.getElementById('needs_port_scan').checked) {
        if(!error_check_port()) return false;
        var port_number = document.getElementById('portScan').value;
        userInput['port_number'] = port_number;
    }

    //TODO: copy the above line and replace the IDs with their respective checkbox and text input IDs
    loadingSearch("search_div");
    $.ajax({
        url : '/',
        type : 'POST',
        data : userInput,
        dataType:'text',
        success : function(data) {        
            searchBox('search_div');  
            //alert(data); 
            //var returnedData = JSON.parse(data);
            document.getElementById("results").innerHTML = data;
            // $('#results').append('<p>' + data + '</p>');
        },
        error : function(request,error){
            searchBox('search_div');
            document.getElementById("results").innerHTML = "no results found";
            // alert("nope");
        }
    });

    /*$.ajax({
        url : '/',
        type: 'GET',
        success: function(data) {
            document.getElementById("results").innerHTML = data;
        },
        error: function(request, error) {
            alert("something wrong");
        }
    });*/
 }

 function unlock_filter(check_ID, input_ID){
  if (document.getElementById(check_ID).checked) {
      document.getElementById(input_ID).disabled = false;
  } else {
        document.getElementById(input_ID).value = "";
        document.getElementById(input_ID).disabled = true;
  }
}

function error_check_port(){
    var input = document.getElementById("portScan");
    var dash_found = false;
    if(input.value[0] >= '9' || input.value[0] <= '0') {
        input.setSelectionRange(0, 1);
        input.focus();
        document.getElementById("portScan").className = document.getElementById("portScan").className + " error"; 
        document.getElementById("portError").innerHTML = "Invalid format must match: 1234 or 1234-4567 <br>";
        return false;
    }
    for(var i = 1; i < input.value.length; i++){
        // if the char is not a number && the char is not a '-' || the char is a '-' && a '-' has been seen before
        if(((input.value[i] >= '9' || input.value[i] < '0') && input.value[i] != '-')  || (input.value[i] == '-' && dash_found == true)){
            
            //if(dash_found == true) console.log("why?");
            input.setSelectionRange(i, i+1);
            input.focus();
            document.getElementById("portScan").className = document.getElementById("portScan").className + " error"; 
            document.getElementById("portError").innerHTML = "Invalid format must match: 1234 or 1234-4567 <br>";
            return false;
        }
        if(input.value[i] == '-') dash_found = true;
    }
    document.getElementById("portScan").className = document.getElementById("portScan").className.replace(" error", "");
    document.getElementById("portError").innerHTML = "";
    return true;
}

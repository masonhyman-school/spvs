function loadingSearch(elementID){
    document.getElementById(elementID).style.display = "none";
    document.getElementById(elementID).style.visibility = "hidden";
    //document.getElementById("loading").innerHTML ="<p>Fetching Results...</p>";
    document.getElementById("loading").style.display = "block";
    document.getElementById("loading").style.visibility = "visible";
    document.getElementById("results_here").innerHTML ="";
    document.getElementById("results").style.display = "none";
}

function searchBox(elementID){
    document.getElementById(elementID).style.display = "block";
    document.getElementById(elementID).style.visibility = "visible";
    document.getElementById("loading").style.display = "none";
    document.getElementById("loading").style.visibility = "hidden";
}

let form = document.getElementById('search_form');
form.addEventListener('submit', (event) => {
    event.preventDefault();
});

var send = function() {
    var userInput = {};
    var host_name = document.getElementById('search').value;
    userInput['host_name'] = host_name;

    document.getElementById("search").className = document.getElementById("search").className.replace(" error", "");
    document.getElementById("searchError").innerHTML = "";
    if(host_name.length == 0) {
        document.getElementById("search").className = document.getElementById("search").className + " error"; 
        document.getElementById("searchError").innerHTML = "<br>Please enter a hostname<br>";
        return false;
    }
    document.getElementById("portScan").className = document.getElementById("portScan").className.replace(" error", "");
    document.getElementById("portError").innerHTML = "";
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
            var results = document.getElementById("results_here");

            const res = JSON.parse(data);
            var i;
            var is_table = false;
            var table = document.createElement("table");
            for(key in res){
                var partsArray = res[key].split(' ');
                if(is_table){
                    if(partsArray[0] == "SPVS"){
                        is_table = false; 
                        results.appendChild(table);
                    } else {
                        var x = document.createElement("tr");
                        for(var y = 0; y < partsArray.length; y++){
                            var z = document.createElement("td");
                            z.innerHTML = partsArray[y];
                            x.appendChild(z);
                        }
                        table.appendChild(x);
                    }
                }
                if(!is_table) {
                    if(partsArray[0] == "PORT"){
                        var x = document.createElement("tr");
                        for(var y = 0; y < partsArray.length; y++){
                            var z = document.createElement("th");
                            z.style.width = "33%";
                            z.innerHTML = partsArray[y];
                            x.appendChild(z);
                        }
                        table.appendChild(x);
                        is_table = true;
                    } else {
                        i = document.createElement('p');
                        i.innerText = res[key];
                        results.appendChild(i);
                    }
                }
            }
            document.getElementById("download-btn").disabled = false;
            document.getElementById("results").style.display = "block";
        },
        error : function(request,error){
            searchBox('search_div');
            document.getElementById("results_here").innerHTML = "No results found";
        }
    });
}

const fuform = document.getElementById('fileUploadForm');
const fSend = async() => {
    loadingSearch('search_div');
    const myFile = document.getElementById('myFile').files;
    const formData = new FormData();

    Object.keys(myFile).forEach(key => {
        formData.append(myFile.item(key).name, myFile.item(key));
    });
    console.log(formData);

    const response = await fetch('http://localhost:3000/upload', {
        method: 'POST',
        body: formData
    });

    const json = await response.json();
    /************************************************************ */
    searchBox('search_div');
    var results = document.getElementById("results_here");
    const res = JSON.parse(json);
    var i;
            var is_table = false;
            var table = document.createElement("table");
            for(key in res){
                var partsArray = res[key].split(' ');
                if(is_table){
                    if(partsArray[0] == "SPVS"){
                        is_table = false; 
                        results.appendChild(table);
                    } else {
                        var x = document.createElement("tr");
                        for(var y = 0; y < partsArray.length; y++){
                            var z = document.createElement("td");
                            z.innerHTML = partsArray[y];
                            x.appendChild(z);
                        }
                        table.appendChild(x);
                    }
                }
                if(!is_table) {
                    if(partsArray[0] == "PORT"){
                        var x = document.createElement("tr");
                        for(var y = 0; y < partsArray.length; y++){
                            var z = document.createElement("th");
                            z.style.width = "33%";
                            z.innerHTML = partsArray[y];
                            x.appendChild(z);
                        }
                        table.appendChild(x);
                        is_table = true;
                    } else {
                        i = document.createElement('p');
                        i.innerText = res[key];
                        results.appendChild(i);
                    }
                }
            }
    document.getElementById("download-btn").disabled = false;
    document.getElementById("results").style.display = "block";
    //document.getElementById("results").innerHTML = json;
    //document.getElementById("download-btn").disabled = false;
    //document.getElementById("download-btn").style.display = "block";

    console.log(json);
}

fuform.addEventListener('submit', (e) => {
    e.preventDefault();
    fSend();
});



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
    if(input.value[0] >= '9' || input.value[0] < '0' || input.value[input.value.length-1] >= '9' || input.value[input.value.length-1] < '0' ) {
        if(input.value[0] >= '9' || input.value[0] < '0') input.setSelectionRange(0, 1);
        else input.setSelectionRange(input.value.length-1, input.value.length);
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
    //document.getElementById("portScan").className = document.getElementById("portScan").className.replace(" error", "");
    //document.getElementById("portError").innerHTML = "";
    return true;
}
const modal = document.querySelector(".modal");
const trigger = document.querySelector(".trigger");
const closeButton = document.querySelector(".close-button");

function toggleModal() {
    modal.classList.toggle("show-modal");
}

function windowOnClick(event) {
    if (event.target === modal) {
        toggleModal();
    }
}

trigger.addEventListener("click", toggleModal);
trigger.
window.addEventListener("click", windowOnClick);
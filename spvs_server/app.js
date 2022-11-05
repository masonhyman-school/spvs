/**
 * app.js
 * Sets up a server currently on local host and handles basic post and get requests.
*/
// jshint esversion: 6

// requiring npm modules
const express = require("express");
const bodyParser = require("body-parser");
const fs = require("fs"); 

const app = express();
app.use(express.json());

// using modules
//app.use(express.static("public"));
app.use(express.static(__dirname + '/public'));
app.use(bodyParser.urlencoded({extended: true}));

// displays the landing page
app.get("/", function(req, res) {
    res.sendFile(__dirname + "/index.html");
});

// process the user input: get the port number and return its status
app.post("/", function(req, res) {
    var portNumber = req.body.userInput;
    console.log(req.body);
    res.send(portNumber);
    //TODO: THIS is where output will be piped to a variable and returned

    /*fs.writeFile('../spvs_cli/test.txt', portNumber, err => {
        if (err) {
          console.error(err);
        }
    });*/
});

// server location
app.listen(5000, function() {
    console.log("Server is running on port 5000.");
});

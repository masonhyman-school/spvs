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

// using modules
app.use(express.static("public"));
app.use(bodyParser.urlencoded({extended: true}));

// displays the landing page
app.get("/", function(req, res) {
    res.sendFile(__dirname + "/index.html");
});

// process the user input: get the port number and return its status
app.post("/", function(req, res) {
    var portNumber = req.body.userInput;
    console.log(portNumber);
    fs.writeFile('../spvs_cli/test.txt', portNumber, err => {
        if (err) {
          console.error(err);
        }
    });
    res.sendFile(__dirname + "/results.html");
});

// server location
app.listen(5000, function() {
    console.log("Server is running on port 5000.");
});

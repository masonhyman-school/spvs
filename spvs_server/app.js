/**
 * app.js
 * Sets up a server currently on local host and handles basic post and get requests.
*/
// jshint esversion: 6

// requiring npm modules
const express = require("express");
const bodyParser = require("body-parser");
const fs = require("fs"); 
const {execFile, spawn} = require("child_process");

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
    const json = req.body;
    console.log(json);
    //const obj = JSON.parse(json);
    const hostName = json.host_name;
    const portNumber = json.port_number;
    // console.log(hostName);
    // console.log(portNumber);

    if (hostName !== "" && portNumber !== "") {
        const cp = execFile('../spvs_cli/bin/spvs', [-p, portNumber, hostName], (error, stdout, stderr) => {
            if (error) {
                throw error;
            }
            res.send(stdout);
            res.end();
        });
    }

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

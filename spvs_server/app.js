/**
 * app.js
 * Sets up a server currently on local host and handles basic post and get requests.
*/
// jshint esversion: 6

// requiring npm modules
const express = require("express");
const bodyParser = require("body-parser");
const fs = require("fs"); 
const cp = require("child_process");

const app = express();
app.use(express.json());

app.use(express.static(__dirname + '/public'));
app.use(bodyParser.urlencoded({extended: true}));

// displays the landing page
app.get("/", function(req, res) {
    res.sendFile(__dirname + "/index.html");
});

app.get('/results.html', function(req, res) {
    res.sendFile(__dirname + '/results.html');
})
// process the user input: get the port number and return its status
app.post("/", function(req, res) {
    
    const json = req.body;
    
    const hostName = json.host_name;
    const portNumber = json.port_number;
    var count = Object.keys(json).length;
    console.log(count);

    if (count == 1) {
        const child = cp. execFile('../spvs_cli/bin/spvs', [hostName], {cwd: '../spvs_cli'}, (error, stdout, stderr) => {
            if (error) {
                throw error;
            }
            console.log(stdout);
            res.send(stdout);
        });
    } else {
        const child = cp.execFile('../spvs_cli/bin/spvs', ['-p', portNumber, hostName], {cwd: '../spvs_cli'}, (error, stdout, stderr) => {
            if (error) {
                throw error;
            }
            console.log(stdout);
            res.send(stdout);
        });
    }
    
});

// server location
app.listen(3000, function() {
    console.log("Server is running on port 3000.");
});

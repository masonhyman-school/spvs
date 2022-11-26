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
const fileUpload = require("express-fileupload");
const path = require("path");

const app = express();

app.use(express.json());
app.use(express.static(__dirname + '/public'));
app.use(bodyParser.urlencoded({extended: true}));

// displays the landing page
app.get("/", function(req, res) {
    res.sendFile(__dirname + "/index.html");
});

app.get("/download", function(req, res) {
    res.download("output.txt");
})

// process the user input: get the port number and return its status
app.post("/", function(req, res) {
    
    const json = req.body;
    const hostName = json.host_name;
    const portNumber = json.port_number;
    var count = Object.keys(json).length;

    if (count == 1) {
        const child = cp. execFile('../spvs_cli/bin/spvs', [hostName], {cwd: '../spvs_cli'}, (error, stdout, stderr) => {
            if (error) {
                throw error;
            }
            console.log(stdout);
            if (createFile(stdout)) {
                var formattedResponse = processOutputFile();
                console.log(formattedResponse);
            }
            const jsonRes = JSON.stringify(formattedResponse);
            res.end(jsonRes);
        });
    } else if (count == 2) {
        const child = cp.execFile('../spvs_cli/bin/spvs', ['-p', portNumber, hostName], {cwd: '../spvs_cli'}, (error, stdout, stderr) => {
            if (error) {
                throw error;
            }
            console.log(stdout);
            if (createFile(stdout)) {
                var formattedResponse = processOutputFile();
                console.log(formattedResponse);
            }
            const jsonRes = JSON.stringify(formattedResponse);
            res.end(jsonRes);
        });
    } 
});

app.post("/upload", fileUpload({ createParentPath: true }), function(req, res) {
    
    const files = req.files;

    if (!files && Object.keys(files).length === 0) {
        return res.send({
            status: false,
            message: 'no file uploaded'
        });
    }
    console.log(files);

    Object.keys(files).forEach(key => {
        const filePath = path.join(__dirname + "../spvs_cli/uploads/" + files[key].name);
        files[key].mv(filePath, function(err) {
            if (err) return res.status(500).send(err);
        });
        console.log('file moved');
        const child = cp.execFile('../spvs_cli/bin/spvs', ['-f', filePath], {cwd: '../spvs_cli'}, (error, stdout, stderr) => {
            if (error) {
                throw error;
            }
            console.log(stdout);
            if (createFile(stdout)) {
                var formattedResponse = processOutputFile();
                console.log(formattedResponse);
            }
            const jsonRes = JSON.stringify(formattedResponse);
            return res.json(jsonRes);
        });
    });
    
});

// server location
app.listen(3000, function() {
    console.log("Server is running on port 3000.");
});

function createFile(contents) {
    const fileName = "output.txt";
    
    try {
        fs.writeFileSync(fileName, contents);
        console.log(`${fileName} changed.`);
    } catch(err) {
        console.log(err);
        return 0;
    }
    return 1;
}

function processOutputFile() {
    var rv = {};
    let i = 0;
    const fileName = "output.txt";
    const fileContents = fs.readFileSync(fileName, 'utf-8');
    fileContents.split(/\r?\n/).forEach(line => {
        if(line.length !== 0) {
            rv[i.toString()] = line;
            i++;
        }
    });

    return rv;
}
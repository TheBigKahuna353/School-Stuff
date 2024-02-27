const http = require('http');
const URL = require('url').URL;

http.createServer((req, res) => { 
    const url = new URL(req.url, `http://localhost:8081`);
    const parameters = url.searchParams;

    //write the response
    res.writeHead(200, {'Content-Type': 'text/plain'});

    res.end('Here is your data: ' + parameters)

}).listen(8081);
const http = require('http');
const URL = require('url').URL;

const shoppingList = ['bread', 'butter', 'milk', 'eggs', 'cheese'];

http.createServer((req, res) => { 
    const url = new URL(req.url, `http://localhost:8081`);
    const parameters = url.searchParams;

    //write the response
    res.writeHead(200, {'Content-Type': 'text/plain'});

    if (parameters.get('itemNum')) {
        const num = parameters.get('itemNum');
        res.end('You selected item ' + num + ": " + shoppingList[num]);
    }


    res.end()

}).listen(8081);
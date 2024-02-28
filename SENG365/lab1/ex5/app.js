const express = require('express');
const app = express();
app.get('/', (req, res) => {
    res.send('Hello World');
    });
app.use((req, res, next) => {
    res.status(404)
    .send('Sorry, that route does not exist.');
    });
app.listen(3000, () => {
    console.log('The application is running on localhost:3000');
    });

const data = require('./users.json');
const users = data.users;

const express = require('express');
const app = express();

const bodyParser = require('body-parser');
app.use(bodyParser.json());

app.get('/users', (req, res) => {
    res.status(200).send(users);
});

app.get('/users/:id', (req, res) => {
    const id = req.params.id;
    let response = 'User not found';
    for (const user of users) {
        if (parseInt(id, 10) === user.id) {
            response = user;
            break;
        }
    }
    res.status(200).send(response);
});

app.post('/users', (req, res) => {
    const user = req.body;
    users.push(user);
    res.status(201).send(user);
});

app.put('/users/:id', (req, res) => {
    const id = req.params.id;
    const user = req.body;
    for (let i = 0; i < users.length; i++) {
        if (parseInt(id, 10) === users[i].id) {
            users[i] = user;
            break;
        }
    }
    res.status(200).send(user);
});

app.delete('/users/:id', (req, res) => {
    const id = req.params.id;
    for (let i = 0; i < users.length; i++) {
        if (parseInt(id, 10) === users[i].id) {
            users.splice(i, 1);
            break;
        }
    }
    res.status(204).send();
});

app.listen(3000, () => {
    console.log('Server is running on port 3000');
});
import * as users from '../models/user.server.model';
import Logger from '../../config/logger';
import {Request, Response} from 'express';
import {validate} from './validate';



const list = async (req: Request, res: Response): Promise<void> => {
    Logger.http('GET all users')
    try {
        const userList = await users.getAll();
        res.status(200).send(userList);
    } catch (err) {
        res.status(500).send(`Error getting users: ${err}`);
    }
};

import * as schemas from '../resources/schemas.json';
const create = async (req: Request, res: Response): Promise<void> => {
    Logger.http(`POST user with username ${req.body.username}`)

    const validation = await validate(schemas.user_register, req.body);

    if (validation !== true) {
        res.status(400).send(`Bad Request: ${validation.toString()}`);
        return;
    }

    const username = req.body.username;
    try {
        const result = await users.insert(username);
        res.status(201).send({"user_id": result.insertId});
    } catch (err) {
        res.status(500).send(`Error creating user: ${err}`);
    }
};

const read = async (req: Request, res: Response): Promise<void> => {
    Logger.http(`GET single user with id ${req.params.id}`)
    const id = parseInt(req.params.id, 10);
    try {
        const user = await users.getOne(id);
        if (user.length === 0) {
            res.status(404).send(`User not found`);
        } else {
            res.status(200).send(user[0]);
        }
    } catch (err) {
        res.status(500).send(`Error reading user: ${err}`);
    }
}

const update = async (req: Request, res: Response): Promise<void> => {
    Logger.http(`PUT user with id ${req.params.id} and username ${req.body.username}`)

    const validation = await validate(schemas.user_edit, req.body);
    if (validation !== true) {
        res.status(400).send(`Bad Request: ${validation.toString()}`);
        return;
    }

    const id = parseInt(req.params.id, 10);
    const username = req.body.username;
    try {
        const result = await users.alter(id, username);
        if (result.affectedRows === 0) {
            res.status(404).send(`User not found`);
        } else {
            res.status(200).send();
        }
    } catch (err) {
        res.status(500).send(`Error updating user: ${err}`);
    }
}

const remove = async (req: Request, res: Response): Promise<void> => {
    Logger.http(`DELETE user with id ${req.params.id}`)
    const id = parseInt(req.params.id, 10);
    try {
        const result = await users.remove(id);
        if (result.affectedRows === 0) {
            res.status(404).send(`User not found`);
        } else {
            res.status(200).send();
        }
    } catch (err) {
        res.status(500).send(`Error deleting user: ${err}`);
    }
}

export { list, create, read, update, remove }
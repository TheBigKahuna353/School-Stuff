import * as convos from '../models/conversations.server.model';
import Logger from '../../config/logger';
import {Request, Response} from 'express';
import {validate} from './validate';


const list = async (req: Request, res: Response): Promise<void> => {
    Logger.http('GET all conversations')
    try {
        const convoList = await convos.getAll();
        res.status(200).send(convoList);
    } catch (err) {
        res.status(500).send(`Error getting conversations: ${err}`);
    }
}

import * as schemas from '../resources/schemas.json';
const create = async (req: Request, res: Response): Promise<void> => {
    Logger.http(`POST conversation with name ${req.body.convo_name}`)

    const validation = await validate(schemas.convo_register, req.body);

    if (validation !== true) {
        res.status(400).send(`Bad Request: ${validation.toString()}`);
        return;
    }

    const convo_name = req.body.convo_name;
    try {
        const result = await convos.insert(convo_name);
        res.status(201).send({"convo_id": result.insertId});
    } catch (err) {
        res.status(500).send(`Error creating conversation: ${err}`);
    }
}

const read = async (req: Request, res: Response): Promise<void> => {
    Logger.http(`GET conversation with id ${req.params.id}`)
    try {
        const convo = await convos.getOne(parseInt(req.params.id, 10));
        if (convo.length === 0) {
            res.status(404).send(`Conversation with id ${req.params.id} not found`);
        } else {
            res.status(200).send(convo[0]);
        }
    } catch (err) {
        res.status(500).send(`Error getting conversation: ${err}`);
    }
}

const update = async (req: Request, res: Response): Promise<void> => {
    Logger.http(`PUT conversation with id ${req.params.id}`)
    const validation = await validate(schemas.convo_register, req.body);

    if (validation !== true) {
        res.status(400).send(`Bad Request: ${validation.toString()}`);
        return;
    }

    const convo_name = req.body.convo_name;
    try {
        const result = await convos.alter(parseInt(req.params.id, 10), convo_name);
        if (result.affectedRows === 0) {
            res.status(404).send(`Conversation with id ${req.params.id} not found`);
        } else {
            res.status(200).send(`Conversation with id ${req.params.id} updated`);
        }
    } catch (err) {
        res.status(500).send(`Error updating conversation: ${err}`);
    }
}

const remove = async (req: Request, res: Response): Promise<void> => {
    Logger.http(`DELETE conversation with id ${req.params.id}`)
    try {
        const result = await convos.remove(parseInt(req.params.id, 10));
        if (result.affectedRows === 0) {
            res.status(404).send(`Conversation with id ${req.params.id} not found`);
        } else {
            res.status(200).send(`Conversation with id ${req.params.id} deleted`);
        }
    } catch (err) {
        res.status(500).send(`Error deleting conversation: ${err}`);
    }
}

export { list, create, read, update, remove }

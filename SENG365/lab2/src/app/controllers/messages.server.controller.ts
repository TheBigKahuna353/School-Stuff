import * as msgs from '../models/messages.server.model';
import Logger from '../../config/logger';
import {Request, Response} from 'express';
import {validate} from './validate';


const list = async (req: Request, res: Response): Promise<void> => {
    Logger.http('GET all Messages')
    try {
        const convoId = parseInt(req.params.id, 10);
        const msgList = await msgs.getAll(convoId);
        if (msgList.length === 0) {
            res.status(404).send(`Conversation not found`);
            return;
        }
        res.status(200).send(msgList);
    } catch (err) {
        res.status(500).send(`Error getting conversations: ${err}`);
    }
}

import * as schemas from '../resources/schemas.json';
const create = async (req: Request, res: Response): Promise<void> => {
    Logger.http(`POST message to conversation with id ${req.params.id}`)

    const validation = await validate(schemas.message_register, req.body);

    if (validation !== true) {
        res.status(400).send(`Bad Request: ${validation.toString()}`);
        return;
    }

    const userId = parseInt(req.body.user_id, 10);
    const convoId = parseInt(req.params.id, 10);
    const content = req.body.message;
    Logger.debug(`User ${userId} sending message to conversation ${convoId}: ${content}`);

    try {
        const result = await msgs.insert(convoId, userId, content);
        res.status(201).send({"message_id": result.insertId});
    } catch (err) {
        res.status(500).send(`Error creating message: ${err}`);
    }
}

const read = async (req: Request, res: Response): Promise<void> => {
    Logger.http(`GET conversation with id ${req.params.mid}`)
    try {
        const msg = await msgs.getOne(parseInt(req.params.mid, 10));
        if (msg.length === 0) {
            res.status(404).send(`Conversation with id ${req.params.id} not found`);
        } else {
            res.status(200).send(msg[0]);
        }
    } catch (err) {
        res.status(500).send(`Error getting Message: ${err}`);
    }
}

export { list, create, read }

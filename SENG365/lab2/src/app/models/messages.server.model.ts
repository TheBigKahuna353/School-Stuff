import { getPool } from '../../config/db';
import Logger from '../../config/logger';
import { ResultSetHeader } from 'mysql2'

const getAll = async (convoId : number) : Promise<Message[]> => {
    Logger.info(`Getting all messages with convoId ${convoId} from the database`);
    const pool = await getPool();
    const conn = await pool.getConnection();
    const [rows] = await conn.query('SELECT * FROM lab2_messages WHERE convo_id = ?', [convoId]);
    await conn.release();
    return rows;

}

const getOne = async (mid: number): Promise<Message[]> => {
    Logger.info(`getting message with id ${mid} from the database`);
    const conn = await getPool().getConnection();
    const query = 'select * from lab2_messages where message_id = ?';
    const [ rows ] = await conn.query( query, [mid] );
    await conn.release();
    return rows;
}

const insert = async (convoId: number, userId: number, message: string): Promise<ResultSetHeader> => {
    Logger.info(`Inserting message into database`);
    const conn = await getPool().getConnection();
    const query = 'INSERT INTO lab2_messages (convo_id, user_id, message) VALUES (?, ?, ?)';
    const [ result ] = await conn.query( query, [convoId, userId, message] );
    await conn.release();
    return result;
}


export { getAll, getOne, insert }
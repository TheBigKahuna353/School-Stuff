import { getPool } from '../../config/db';
import Logger from '../../config/logger';
import { ResultSetHeader } from 'mysql2'

const getAll = async () : Promise<Convo[]> => {
    Logger.info(`Getting all Convos from the database`);
    const pool = await getPool();
    const conn = await pool.getConnection();
    const [rows] = await conn.query('SELECT * FROM lab2_conversations');
    await conn.release();
    return rows;

}

const getOne = async (id: number): Promise<Convo[]> => {
    Logger.info(`Getting Convo with id ${id} from the database`);
    const conn = await getPool().getConnection();
    const query = 'select * from lab2_conversations where convo_id = ?';
    const [ rows ] = await conn.query( query, [id] );
    await conn.release();
    return rows;
}

const insert = async (username: string): Promise<ResultSetHeader> => {
    Logger.info(`Inserting Convo with name ${username} into the database`);
    const conn = await getPool().getConnection();
    const query = 'insert into lab2_conversations (convo_name) values (?)';
    const [ result ] = await conn.query( query, [username] );
    await conn.release();
    return result;
}

const alter = async (id: number, username: string): Promise<ResultSetHeader> => {
    Logger.info(`Updating Convo in the database`);
    const conn = await getPool().getConnection();
    const query = 'update lab2_conversations set convo_name = ? where convo_id = ?';
    const [ result ] = await conn.query( query, [username, id] );
    await conn.release();
    return result;
}

const remove = async (id: number): Promise<ResultSetHeader> => {
    Logger.info(`Deleting Convo with id ${id} from the database`);
    const conn = await getPool().getConnection();
    const query = 'delete from lab2_conversations where convo_id = ?';
    const [ result ] = await conn.query( query, [id] );
    await conn.release();
    return result;
}

export { getAll, getOne, insert, alter, remove }
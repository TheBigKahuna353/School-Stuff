"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.insert = exports.getOne = exports.getAll = void 0;
const db_1 = require("../../config/db");
const logger_1 = __importDefault(require("../../config/logger"));
const getAll = (convoId) => __awaiter(void 0, void 0, void 0, function* () {
    logger_1.default.info(`Getting all messages with convoId ${convoId} from the database`);
    const pool = yield (0, db_1.getPool)();
    const conn = yield pool.getConnection();
    const [rows] = yield conn.query('SELECT * FROM lab2_messages WHERE convo_id = ?', [convoId]);
    yield conn.release();
    return rows;
});
exports.getAll = getAll;
const getOne = (mid) => __awaiter(void 0, void 0, void 0, function* () {
    logger_1.default.info(`getting message with id ${mid} from the database`);
    const conn = yield (0, db_1.getPool)().getConnection();
    const query = 'select * from lab2_messages where message_id = ?';
    const [rows] = yield conn.query(query, [mid]);
    yield conn.release();
    return rows;
});
exports.getOne = getOne;
const insert = (convoId, userId, message) => __awaiter(void 0, void 0, void 0, function* () {
    logger_1.default.info(`Inserting message into database`);
    const conn = yield (0, db_1.getPool)().getConnection();
    const query = 'INSERT INTO lab2_messages (convo_id, user_id, message) VALUES (?, ?, ?)';
    const [result] = yield conn.query(query, [convoId, userId, message]);
    yield conn.release();
    return result;
});
exports.insert = insert;
//# sourceMappingURL=messages.server.model.js.map
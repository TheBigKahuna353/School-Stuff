"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
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
exports.read = exports.create = exports.list = void 0;
const msgs = __importStar(require("../models/messages.server.model"));
const logger_1 = __importDefault(require("../../config/logger"));
const validate_1 = require("./validate");
const list = (req, res) => __awaiter(void 0, void 0, void 0, function* () {
    logger_1.default.http('GET all Messages');
    try {
        const convoId = parseInt(req.params.id, 10);
        const msgList = yield msgs.getAll(convoId);
        if (msgList.length === 0) {
            res.status(404).send(`Conversation not found`);
            return;
        }
        res.status(200).send(msgList);
    }
    catch (err) {
        res.status(500).send(`Error getting conversations: ${err}`);
    }
});
exports.list = list;
const schemas = __importStar(require("../resources/schemas.json"));
const create = (req, res) => __awaiter(void 0, void 0, void 0, function* () {
    logger_1.default.http(`POST message to conversation with id ${req.params.id}`);
    const validation = yield (0, validate_1.validate)(schemas.message_register, req.body);
    if (validation !== true) {
        res.status(400).send(`Bad Request: ${validation.toString()}`);
        return;
    }
    const userId = parseInt(req.body.user_id, 10);
    const convoId = parseInt(req.params.id, 10);
    const content = req.body.message;
    logger_1.default.debug(`User ${userId} sending message to conversation ${convoId}: ${content}`);
    try {
        const result = yield msgs.insert(convoId, userId, content);
        res.status(201).send({ "message_id": result.insertId });
    }
    catch (err) {
        res.status(500).send(`Error creating message: ${err}`);
    }
});
exports.create = create;
const read = (req, res) => __awaiter(void 0, void 0, void 0, function* () {
    logger_1.default.http(`GET conversation with id ${req.params.mid}`);
    try {
        const msg = yield msgs.getOne(parseInt(req.params.mid, 10));
        if (msg.length === 0) {
            res.status(404).send(`Conversation with id ${req.params.id} not found`);
        }
        else {
            res.status(200).send(msg[0]);
        }
    }
    catch (err) {
        res.status(500).send(`Error getting Message: ${err}`);
    }
});
exports.read = read;
//# sourceMappingURL=messages.server.controller.js.map
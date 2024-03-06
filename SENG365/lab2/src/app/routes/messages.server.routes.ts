import {Express} from "express";
import * as msgs from '../controllers/messages.server.controller';

module.exports = ( app: Express ) => {

    app.route( '/api/conversations/:id/messages' )
        .get( msgs.list )
        .post( msgs.create );

    app.route( '/api/conversations/:id/messages/:mid' )
        .get( msgs.read )
};